#include "global.h"
#include "cities_m3.h"
#include "cities_arcs.h"
#include "cities_field_events.h"
#include "battle.h"
#include "event_data.h"
#include "overworld.h"
#include "pokemon.h"
#include "region_map.h"
#include "roamer.h"
#include "string_util.h"
#include "text.h"
#include "constants/battle.h"
#include "constants/flags.h"
#include "constants/species.h"
#include "constants/vars.h"

// M3 "On the Trail" (GDD 6.6, outline approved 2026-09-17). The beasts
// use the expansion's roamer engine (ROAMER_COUNT = 3). Cities changes
// on top of the vanilla rules:
//  - the journal shows each beast's live route (no blind luck),
//  - a KO'd or Roar'd-away beast keeps roaming at full health (the
//    no-permanent-miss rule shared with the M1/M2 statics),
//  - every battle meeting counts toward CITIES_M3_CHASE_MAX; at the cap
//    the beast tires and settles in its den as a normal static.

extern const u8 Cities_EventScript_M3RaikouCornered[];
extern const u8 Cities_EventScript_M3EnteiCornered[];
extern const u8 Cities_EventScript_M3SuicuneCornered[];

struct CitiesM3BeastInfo
{
    u16 species;
    u16 caughtFlag;
    u16 denHideFlag;
    const u8 *corneredScript;
};

static const struct CitiesM3BeastInfo sBeasts[CITIES_M3_BEAST_COUNT] =
{
    [CITIES_M3_RAIKOU]  = { SPECIES_RAIKOU,  FLAG_CITIES_M3_RAIKOU_CAUGHT,  FLAG_CITIES_HIDE_M3_RAIKOU,  Cities_EventScript_M3RaikouCornered },
    [CITIES_M3_ENTEI]   = { SPECIES_ENTEI,   FLAG_CITIES_M3_ENTEI_CAUGHT,   FLAG_CITIES_HIDE_M3_ENTEI,   Cities_EventScript_M3EnteiCornered },
    [CITIES_M3_SUICUNE] = { SPECIES_SUICUNE, FLAG_CITIES_M3_SUICUNE_CAUGHT, FLAG_CITIES_HIDE_M3_SUICUNE, Cities_EventScript_M3SuicuneCornered },
};

u32 CitiesM3BeastForSpecies(u16 species)
{
    u32 i;

    for (i = 0; i < CITIES_M3_BEAST_COUNT; i++)
        if (sBeasts[i].species == species)
            return i;
    return CITIES_M3_BEAST_COUNT;
}

u32 CitiesM3GetChase(u32 beast)
{
    return (VarGet(VAR_CITIES_M3_CHASE) >> (beast * 2)) & 3;
}

void CitiesM3SetChase(u32 beast, u32 count)
{
    u16 packed = VarGet(VAR_CITIES_M3_CHASE);

    packed &= ~(3 << (beast * 2));
    packed |= (count & 3) << (beast * 2);
    VarSet(VAR_CITIES_M3_CHASE, packed);
}

bool32 CitiesM3BeastCaught(u32 beast)
{
    return FlagGet(sBeasts[beast].caughtFlag);
}

static bool32 CitiesM3BeastCornered(u32 beast)
{
    return CitiesM3GetChase(beast) >= CITIES_M3_CHASE_MAX;
}

static struct Roamer *CitiesM3FindRoamer(u16 species, u32 *indexOut)
{
    u32 i;

    for (i = 0; i < ROAMER_COUNT; i++)
    {
        struct Roamer *roamer = &gSaveBlock1Ptr->roamer[i];

        if (roamer->active && roamer->species == species)
        {
            if (indexOut != NULL)
                *indexOut = i;
            return roamer;
        }
    }
    return NULL;
}

static void HealRoamer(struct Roamer *roamer)
{
    struct Pokemon mon;

    CreateMonWithIVsPersonality(&mon, roamer->species, roamer->level,
                                roamer->ivs, roamer->personality);
    roamer->hp = GetMonData(&mon, MON_DATA_MAX_HP);
    roamer->statusA = 0;
    roamer->statusB = 0;
}

// 10.0a for roamers (GDD 6.4): a beast's level tracks the current cap,
// so arriving later never means an underleveled encounter. Remaining HP
// keeps its fraction so a wounded beast stays wounded.
void CitiesM3RefreshRoamerLevel(u32 roamerIndex)
{
    struct Roamer *roamer = &gSaveBlock1Ptr->roamer[roamerIndex];
    struct Pokemon mon;
    u32 newLevel, oldMax, newMax;

    if (!roamer->active || CitiesM3BeastForSpecies(roamer->species) == CITIES_M3_BEAST_COUNT)
        return;
    newLevel = Script_CitiesGetLegendaryLevel();
    if (newLevel == roamer->level)
        return;

    CreateMonWithIVsPersonality(&mon, roamer->species, roamer->level,
                                roamer->ivs, roamer->personality);
    oldMax = GetMonData(&mon, MON_DATA_MAX_HP);
    CreateMonWithIVsPersonality(&mon, roamer->species, newLevel,
                                roamer->ivs, roamer->personality);
    newMax = GetMonData(&mon, MON_DATA_MAX_HP);

    if (roamer->hp > 0 && oldMax > 0)
        roamer->hp = max(1, roamer->hp * newMax / oldMax);
    roamer->level = newLevel;
}

bool32 CitiesM3HandleRoamerBattleEnd(void)
{
    struct Roamer *roamer = &gSaveBlock1Ptr->roamer[gEncounteredRoamerIndex];
    u32 beast = CitiesM3BeastForSpecies(roamer->species);
    u32 chase;

    if (beast == CITIES_M3_BEAST_COUNT)
        return FALSE;

    if (gBattleOutcome == B_OUTCOME_CAUGHT)
    {
        FlagSet(sBeasts[beast].caughtFlag);
        FlagSet(sBeasts[beast].denHideFlag);
        SetRoamerInactive(gEncounteredRoamerIndex);
        return TRUE;
    }

    // Never lost: a KO (or draw) just sends the beast away to recover.
    if (gBattleOutcome == B_OUTCOME_WON || gBattleOutcome == B_OUTCOME_DREW)
        HealRoamer(roamer);

    chase = CitiesM3GetChase(beast) + 1;
    if (chase > CITIES_M3_CHASE_MAX)
        chase = CITIES_M3_CHASE_MAX;
    CitiesM3SetChase(beast, chase);

    if (chase == CITIES_M3_CHASE_MAX)
    {
        // Tired out: leave the routes and settle in the den.
        HealRoamer(roamer);
        SetRoamerInactive(gEncounteredRoamerIndex);
        FlagClear(sBeasts[beast].denHideFlag);
        CitiesQueueFieldScript(sBeasts[beast].corneredScript);
    }
    return TRUE;
}

// Special: release the three beasts onto the routes (ranger intro).
// Skips a beast that is already caught, cornered, or roaming, so a
// repeat call can never duplicate one.
void Script_CitiesM3StartRoamers(void)
{
    u32 i;
    u8 level = Script_CitiesGetLegendaryLevel();

    for (i = 0; i < CITIES_M3_BEAST_COUNT; i++)
    {
        if (CitiesM3BeastCaught(i) || CitiesM3BeastCornered(i))
            continue;
        if (CitiesM3FindRoamer(sBeasts[i].species, NULL) != NULL)
            continue;
        TryAddRoamer(sBeasts[i].species, level);
    }
}

// Special (specialvar): VAR_0x8004 = CITIES_M3_*; TRUE while the den
// static should be on the map (cornered and not yet caught).
bool8 Script_CitiesM3DenVisible(void)
{
    u32 beast = gSpecialVar_0x8004;

    if (beast >= CITIES_M3_BEAST_COUNT)
        return FALSE;
    return CitiesM3BeastCornered(beast) && !CitiesM3BeastCaught(beast);
}

// ---- Quest journal support ----

static const u8 *const sBeastNames[CITIES_M3_BEAST_COUNT] =
{
    [CITIES_M3_RAIKOU]  = COMPOUND_STRING("RAIKOU"),
    [CITIES_M3_ENTEI]   = COMPOUND_STRING("ENTEI"),
    [CITIES_M3_SUICUNE] = COMPOUND_STRING("SUICUNE"),
};

static const u8 *const sDenNames[CITIES_M3_BEAST_COUNT] =
{
    [CITIES_M3_RAIKOU]  = COMPOUND_STRING("ALTERING CAVE"),
    [CITIES_M3_ENTEI]   = COMPOUND_STRING("SCORCHED SLAB"),
    [CITIES_M3_SUICUNE] = COMPOUND_STRING("METEOR FALLS"),
};

// One plain-language line per beast, e.g.
//   RAIKOU: seen on ROUTE 110
//   ENTEI: den in SCORCHED SLAB
//   SUICUNE: with you
void CitiesM3BufferChaseStatus(u8 *dest)
{
    u32 beast, roamerIndex;
    u8 tmp[24];

    dest[0] = EOS;
    for (beast = 0; beast < CITIES_M3_BEAST_COUNT; beast++)
    {
        if (beast == 1)
            StringAppend(dest, COMPOUND_STRING("\n"));
        else if (beast > 1)
            StringAppend(dest, COMPOUND_STRING("\l"));
        StringAppend(dest, sBeastNames[beast]);
        if (CitiesM3BeastCaught(beast))
        {
            StringAppend(dest, COMPOUND_STRING(": with you"));
        }
        else if (CitiesM3BeastCornered(beast))
        {
            StringAppend(dest, COMPOUND_STRING(": den in "));
            StringAppend(dest, sDenNames[beast]);
        }
        else if (CitiesM3FindRoamer(sBeasts[beast].species, &roamerIndex) != NULL)
        {
            u8 mapGroup, mapNum;

            GetRoamerLocation(roamerIndex, &mapGroup, &mapNum);
            GetMapNameGeneric(tmp, Overworld_GetMapHeaderByGroupAndId(mapGroup, mapNum)->regionMapSectionId);
            StringAppend(dest, COMPOUND_STRING(": seen on "));
            StringAppend(dest, tmp);
        }
        else
        {
            StringAppend(dest, COMPOUND_STRING(": not seen yet"));
        }
    }
}
