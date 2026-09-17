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
};

static const u16 sArcM1[] = { SPECIES_ARTICUNO, SPECIES_ZAPDOS, SPECIES_MOLTRES };
static const u16 sArcM2[] = { SPECIES_REGIROCK, SPECIES_REGICE, SPECIES_REGISTEEL };
static const u16 sArcM3[] = { SPECIES_RAIKOU, SPECIES_ENTEI, SPECIES_SUICUNE };
static const u16 sArcM4[] = { SPECIES_UXIE, SPECIES_MESPRIT, SPECIES_AZELF };
static const u16 sArcM5[] = { SPECIES_LATIAS, SPECIES_LATIOS };

static const struct CitiesArcInfo sArcs[CITIES_ARC_COUNT] =
{
    [CITIES_ARC_M1] = { sArcM1, ARRAY_COUNT(sArcM1), FLAG_BADGE04_GET, CITIES_ARC_MSG_HEAT_BADGE },
    [CITIES_ARC_M2] = { sArcM2, ARRAY_COUNT(sArcM2), FLAG_BADGE06_GET, CITIES_ARC_MSG_FEATHER_BADGE },
    [CITIES_ARC_M3] = { sArcM3, ARRAY_COUNT(sArcM3), FLAG_BADGE07_GET, CITIES_ARC_MSG_MIND_BADGE },
    [CITIES_ARC_M4] = { sArcM4, ARRAY_COUNT(sArcM4), FLAG_BADGE08_GET, CITIES_ARC_MSG_RAIN_BADGE },
    [CITIES_ARC_M5] = { sArcM5, ARRAY_COUNT(sArcM5), 0, 0 },
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

// Special: prepare a scripted wild battle against the legendary in
// VAR_0x8004 at the level-matched cap (10.0a). Started with
// BattleSetup_StartLegendaryBattle from the script.
void Script_CitiesSetWildLegendary(void)
{
    CreateScriptedWildMon(gSpecialVar_0x8004, Script_CitiesGetLegendaryLevel(), ITEM_NONE);
}

// Special (specialvar): VAR_0x8004 = CITIES_ARC_*; TRUE once every
// Pokémon of the arc has been caught (GDD 6.7 final rewards).
bool8 Script_CitiesArcAllCaught(void)
{
    return CitiesArcAllCaught(gSpecialVar_0x8004);
}
