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
static const u16 sArcH6[] = { SPECIES_XERNEAS, SPECIES_YVELTAL, SPECIES_ZYGARDE };
static const u16 sArcH7[] = { SPECIES_RESHIRAM, SPECIES_ZEKROM, SPECIES_KYUREM };
static const u16 sArcH9[] = { SPECIES_ZACIAN, SPECIES_ZAMAZENTA, SPECIES_GLASTRIER, SPECIES_SPECTRIER, SPECIES_CALYREX, SPECIES_KUBFU };
static const u16 sArcH2A[] = { SPECIES_WO_CHIEN, SPECIES_CHIEN_PAO, SPECIES_TING_LU, SPECIES_CHI_YU };
static const u16 sArcH2B[] = { SPECIES_OKIDOGI, SPECIES_MUNKIDORI, SPECIES_FEZANDIPITI, SPECIES_OGERPON };
static const u16 sArcH5A[] = { SPECIES_DIALGA, SPECIES_PALKIA, SPECIES_GIRATINA };
static const u16 sArcH5AArceus[] = { SPECIES_ARCEUS };
// Team Epoch thread (GDD 6.6 / 7.2, Task 12.5).
static const u16 sArcV1[] = { SPECIES_MEWTWO, SPECIES_MEW, SPECIES_GENESECT };
static const u16 sArcV2[] = { SPECIES_TYPE_NULL, SPECIES_SILVALLY, SPECIES_MAGEARNA };
static const u16 sArcV3[] =
{
    SPECIES_NIHILEGO, SPECIES_BUZZWOLE, SPECIES_PHEROMOSA, SPECIES_XURKITREE,
    SPECIES_CELESTEELA, SPECIES_KARTANA, SPECIES_GUZZLORD, SPECIES_STAKATAKA,
    SPECIES_BLACEPHALON, SPECIES_POIPOLE, SPECIES_NAGANADEL,
    SPECIES_COSMOG, SPECIES_COSMOEM, SPECIES_SOLGALEO, SPECIES_LUNALA,
    SPECIES_NECROZMA,
};
static const u16 sArcV4[] =
{
    SPECIES_KORAIDON, SPECIES_MIRAIDON, SPECIES_TERAPAGOS,
    SPECIES_GREAT_TUSK, SPECIES_SCREAM_TAIL, SPECIES_BRUTE_BONNET,
    SPECIES_FLUTTER_MANE, SPECIES_SLITHER_WING, SPECIES_SANDY_SHOCKS,
    SPECIES_ROARING_MOON, SPECIES_WALKING_WAKE, SPECIES_GOUGING_FIRE,
    SPECIES_RAGING_BOLT, SPECIES_IRON_TREADS, SPECIES_IRON_BUNDLE,
    SPECIES_IRON_HANDS, SPECIES_IRON_JUGULIS, SPECIES_IRON_MOTH,
    SPECIES_IRON_THORNS, SPECIES_IRON_VALIANT, SPECIES_IRON_LEAVES,
    SPECIES_IRON_BOULDER, SPECIES_IRON_CROWN,
};
static const u16 sArcV5[] = { SPECIES_ETERNATUS };
// Mythical events (GDD 6.6, Task 13.1). All fixed level 70. Mew, Celebi,
// Genesect, Magearna and Keldeo live in their story arcs, not here.
static const u16 sArcMythic[] =
{
    SPECIES_DEOXYS, SPECIES_JIRACHI, SPECIES_DIANCIE, SPECIES_MANAPHY,
    SPECIES_PHIONE, SPECIES_SHAYMIN, SPECIES_HOOPA, SPECIES_VICTINI,
    SPECIES_MELOETTA, SPECIES_VOLCANION, SPECIES_MARSHADOW, SPECIES_ZERAORA,
    SPECIES_ZARUDE, SPECIES_MELTAN, SPECIES_MELMETAL, SPECIES_PECHARUNT,
};

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
    [CITIES_ARC_H6] = { sArcH6, ARRAY_COUNT(sArcH6), 0, 0, 70 },
    [CITIES_ARC_H7] = { sArcH7, ARRAY_COUNT(sArcH7), 0, 0, 70 },
    [CITIES_ARC_H9] = { sArcH9, ARRAY_COUNT(sArcH9), 0, 0, 70 },
    [CITIES_ARC_H2A] = { sArcH2A, ARRAY_COUNT(sArcH2A), 0, 0, 65 },
    [CITIES_ARC_H2B] = { sArcH2B, ARRAY_COUNT(sArcH2B), 0, 0, 65 },
    [CITIES_ARC_H5A] = { sArcH5A, ARRAY_COUNT(sArcH5A), 0, 0, 75 },
    [CITIES_ARC_H5A_ARCEUS] = { sArcH5AArceus, ARRAY_COUNT(sArcH5AArceus), 0, 0, 80 },
    [CITIES_ARC_V1] = { sArcV1, ARRAY_COUNT(sArcV1), 0, 0, 60 },
    [CITIES_ARC_V2] = { sArcV2, ARRAY_COUNT(sArcV2), 0, 0, 65 },
    [CITIES_ARC_V3] = { sArcV3, ARRAY_COUNT(sArcV3), 0, 0, 70 },
    [CITIES_ARC_V4] = { sArcV4, ARRAY_COUNT(sArcV4), 0, 0, 75 },
    [CITIES_ARC_V5] = { sArcV5, ARRAY_COUNT(sArcV5), 0, 0, 80 },
    [CITIES_ARC_MYTHIC] = { sArcMythic, ARRAY_COUNT(sArcMythic), 0, 0, 70 },
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

// Completeness support (GDD 6.8, Task 13.2). Two questions the test asks:
// how many arc tables list this exact species (must be <= 1), and whether
// any form of a base line is placed at all (coverage).
u32 CitiesCountExactPlacements(u16 species)
{
    u32 arc, i, n = 0;
    for (arc = 0; arc < CITIES_ARC_COUNT; arc++)
        for (i = 0; i < sArcs[arc].speciesCount; i++)
            if (sArcs[arc].species[i] == species)
                n++;
    return n;
}

bool8 CitiesBaseFormPlaced(u16 base)
{
    u32 arc, i;
    for (arc = 0; arc < CITIES_ARC_COUNT; arc++)
        for (i = 0; i < sArcs[arc].speciesCount; i++)
            if (GET_BASE_SPECIES_ID(sArcs[arc].species[i]) == base)
                return TRUE;
    return FALSE;
}

// Special (specialvar): VAR_0x8004 = CITIES_ARC_*; TRUE once every
// Pokémon of the arc has been caught (GDD 6.7 final rewards).
bool8 Script_CitiesArcAllCaught(void)
{
    return CitiesArcAllCaught(gSpecialVar_0x8004);
}
