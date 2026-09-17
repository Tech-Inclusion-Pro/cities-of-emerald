#include "global.h"
#include "cities_arcs.h"
#include "caps.h"
#include "event_data.h"
#include "pokedex.h"
#include "pokemon.h"
#include "script_pokemon_util.h"
#include "constants/flags.h"
#include "constants/species.h"
#include "constants/vars.h"

// Phase 10 shared systems (GDD 6.4-6.7, all [DECIDED]).
//
// 10.0a — level-matched statics: a mid-game legendary's level equals the
// automatic badge-based cap at encounter time (Assist overrides are
// ignored on purpose: the cap choice changes the player's rules, not the
// world). After the Champion the automatic cap is gone, so the level
// settles at the 60 tier that opens the postgame arcs (GDD 6.4).
//
// 10.0b — badge-based obedience for the arc legendaries. Vanilla
// obedience is level-based and, since these are always at the cap, would
// randomly punish the player. The Cities rule is deterministic: disobey
// with a clear message until the arc's obey badge, then obey forever.
// Late catches obey immediately by the same check.
//
// 10.0c — arc reward hook: one special that answers "has the player
// caught every Pokémon of this arc?" for the final-reward scripts.

struct CitiesArcInfo
{
    const u16 *species;
    u8 speciesCount;
    u16 obeyBadgeFlag;  // 0 = special rule (M5)
    u8 disobeyMsg;      // index into gCitiesWontListenStringIds (M1-M4)
    u8 fixedLevel;      // postgame tier (GDD 6.4); 0 = follow the automatic cap
};

static const u16 sArcM1[] = { SPECIES_ARTICUNO, SPECIES_ZAPDOS, SPECIES_MOLTRES };
static const u16 sArcM2[] = { SPECIES_REGIROCK, SPECIES_REGICE, SPECIES_REGISTEEL };
static const u16 sArcM3[] = { SPECIES_RAIKOU, SPECIES_ENTEI, SPECIES_SUICUNE };
static const u16 sArcM4[] = { SPECIES_UXIE, SPECIES_MESPRIT, SPECIES_AZELF };
static const u16 sArcM5[] = { SPECIES_LATIAS, SPECIES_LATIOS };
static const u16 sArcM1PG[] = { SPECIES_ARTICUNO_GALAR, SPECIES_ZAPDOS_GALAR, SPECIES_MOLTRES_GALAR };
static const u16 sArcH1[] = { SPECIES_COBALION, SPECIES_TERRAKION, SPECIES_VIRIZION, SPECIES_KELDEO };
static const u16 sArcH5B[] = { SPECIES_CRESSELIA, SPECIES_DARKRAI };
static const u16 sArcH10[] = { SPECIES_TAPU_KOKO, SPECIES_TAPU_LELE, SPECIES_TAPU_BULU, SPECIES_TAPU_FINI };
static const u16 sArcH11[] = { SPECIES_HEATRAN };
static const u16 sArcH3[] = { SPECIES_REGIGIGAS, SPECIES_REGIELEKI, SPECIES_REGIDRAGO };
static const u16 sArcH4[] = { SPECIES_HO_OH, SPECIES_LUGIA, SPECIES_CELEBI };
static const u16 sArcH8[] = { SPECIES_TORNADUS, SPECIES_THUNDURUS, SPECIES_LANDORUS, SPECIES_ENAMORUS };

static const struct CitiesArcInfo sArcs[CITIES_ARC_COUNT] =
{
    [CITIES_ARC_M1] = { sArcM1, ARRAY_COUNT(sArcM1), FLAG_BADGE04_GET, CITIES_ARC_MSG_HEAT_BADGE },
    [CITIES_ARC_M2] = { sArcM2, ARRAY_COUNT(sArcM2), FLAG_BADGE06_GET, CITIES_ARC_MSG_FEATHER_BADGE },
    [CITIES_ARC_M3] = { sArcM3, ARRAY_COUNT(sArcM3), FLAG_BADGE07_GET, CITIES_ARC_MSG_MIND_BADGE },
    [CITIES_ARC_M4] = { sArcM4, ARRAY_COUNT(sArcM4), FLAG_BADGE08_GET, CITIES_ARC_MSG_RAIN_BADGE },
    [CITIES_ARC_M5] = { sArcM5, ARRAY_COUNT(sArcM5), 0, 0 },
    [CITIES_ARC_M1PG] = { sArcM1PG, ARRAY_COUNT(sArcM1PG), 0, 0, 60 },
    [CITIES_ARC_H1] = { sArcH1, ARRAY_COUNT(sArcH1), 0, 0, 60 },
    [CITIES_ARC_H5B] = { sArcH5B, ARRAY_COUNT(sArcH5B), 0, 0, 60 },
    [CITIES_ARC_H10] = { sArcH10, ARRAY_COUNT(sArcH10), 0, 0, 60 },
    [CITIES_ARC_H11] = { sArcH11, ARRAY_COUNT(sArcH11), 0, 0, 60 },
    [CITIES_ARC_H3] = { sArcH3, ARRAY_COUNT(sArcH3), 0, 0, 65 },
    [CITIES_ARC_H4] = { sArcH4, ARRAY_COUNT(sArcH4), 0, 0, 65 },
    [CITIES_ARC_H8] = { sArcH8, ARRAY_COUNT(sArcH8), 0, 0, 65 },
};

static bool32 SpeciesCaught(u16 species)
{
    return GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT);
}

// GDD 6.5 M5 exception: obedience arrives when both have been caught and
// is never revoked afterwards — the sticky flag survives trading or
// releasing either of the pair.
bool32 CitiesLatiUnited(void)
{
    if (FlagGet(FLAG_CITIES_LATI_UNITED))
        return TRUE;
    if (SpeciesCaught(SPECIES_LATIAS) && SpeciesCaught(SPECIES_LATIOS))
    {
        FlagSet(FLAG_CITIES_LATI_UNITED);
        return TRUE;
    }
    return FALSE;
}

enum CitiesArcObedience CitiesGetArcObedience(u16 species, u8 *msgIndexOut)
{
    u32 arc, i;

    for (arc = 0; arc < CITIES_ARC_COUNT; arc++)
    {
        const struct CitiesArcInfo *info = &sArcs[arc];

        for (i = 0; i < info->speciesCount; i++)
        {
            if (info->species[i] != species)
                continue;
            // Postgame arcs always obey (GDD 6.5); they sit at the end of the enum.
            if (arc >= CITIES_ARC_M1PG)
                return CITIES_ARC_OBEYS;
            if (arc == CITIES_ARC_M5)
            {
                if (CitiesLatiUnited())
                    return CITIES_ARC_OBEYS;
                *msgIndexOut = (species == SPECIES_LATIAS)
                             ? CITIES_ARC_MSG_NEED_LATIOS : CITIES_ARC_MSG_NEED_LATIAS;
                return CITIES_ARC_DISOBEYS;
            }
            if (FlagGet(info->obeyBadgeFlag))
                return CITIES_ARC_OBEYS;
            *msgIndexOut = info->disobeyMsg;
            return CITIES_ARC_DISOBEYS;
        }
    }
    return CITIES_ARC_NOT_ARC_SPECIES;
}

bool32 CitiesArcAllCaught(u32 arc)
{
    u32 i;

    if (arc >= CITIES_ARC_COUNT)
        return FALSE;
    for (i = 0; i < sArcs[arc].speciesCount; i++)
        if (!SpeciesCaught(sArcs[arc].species[i]))
            return FALSE;
    return TRUE;
}

// Special (specialvar): the level for a mid-game legendary static
// encounter (GDD 6.4).
u16 Script_CitiesGetLegendaryLevel(void)
{
    u32 level = GetAutomaticLevelCap();

    if (level > 60)
        level = 60; // post-Champion floor of the postgame tiers
    return level;
}

// The level for a specific arc species: postgame arcs use their fixed
// tier (GDD 6.4); mid-game arcs follow the automatic cap.
u16 CitiesGetLegendarySpeciesLevel(u16 species)
{
    u32 arc, i;

    for (arc = 0; arc < CITIES_ARC_COUNT; arc++)
    {
        const struct CitiesArcInfo *info = &sArcs[arc];

        for (i = 0; i < info->speciesCount; i++)
            if (info->species[i] == species && info->fixedLevel != 0)
                return info->fixedLevel;
    }
    return Script_CitiesGetLegendaryLevel();
}

// Special: prepare a scripted wild battle against the legendary in
// VAR_0x8004 at its tier (fixed for postgame arcs, level-matched cap
// for mid-game ones). Started with BattleSetup_StartLegendaryBattle
// from the script.
void Script_CitiesSetWildLegendary(void)
{
    CreateScriptedWildMon(gSpecialVar_0x8004, CitiesGetLegendarySpeciesLevel(gSpecialVar_0x8004), ITEM_NONE);
}

// Special (specialvar): VAR_0x8004 = CITIES_ARC_*; TRUE once every
// Pokémon of the arc has been caught (GDD 6.7 final rewards).
bool8 Script_CitiesArcAllCaught(void)
{
    return CitiesArcAllCaught(gSpecialVar_0x8004);
}
