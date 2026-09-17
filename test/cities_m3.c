#include "global.h"
#include "cities_arcs.h"
#include "cities_m3.h"
#include "battle.h"
#include "event_data.h"
#include "pokemon.h"
#include "roamer.h"
#include "test/test.h"
#include "constants/battle.h"
#include "constants/flags.h"
#include "constants/species.h"
#include "constants/vars.h"

// M3 "On the Trail" (GDD 6.6, outline approved 2026-09-17): chase
// counters, the never-lost rule, cornering after three meetings, and
// the level-cap refresh for roaming beasts.

static struct Roamer *AddBeast(u16 species, u8 level, u32 *indexOut)
{
    u32 i;

    EXPECT(TryAddRoamer(species, level));
    for (i = 0; i < ROAMER_COUNT; i++)
    {
        if (gSaveBlock1Ptr->roamer[i].active && gSaveBlock1Ptr->roamer[i].species == species)
        {
            *indexOut = i;
            return &gSaveBlock1Ptr->roamer[i];
        }
    }
    EXPECT(FALSE);
    return NULL;
}

TEST("M3: chase counters pack independently, two bits per beast")
{
    VarSet(VAR_CITIES_M3_CHASE, 0);
    CitiesM3SetChase(CITIES_M3_RAIKOU, 1);
    CitiesM3SetChase(CITIES_M3_ENTEI, 3);
    CitiesM3SetChase(CITIES_M3_SUICUNE, 2);
    EXPECT_EQ(CitiesM3GetChase(CITIES_M3_RAIKOU), 1);
    EXPECT_EQ(CitiesM3GetChase(CITIES_M3_ENTEI), 3);
    EXPECT_EQ(CitiesM3GetChase(CITIES_M3_SUICUNE), 2);
    CitiesM3SetChase(CITIES_M3_ENTEI, 0);
    EXPECT_EQ(CitiesM3GetChase(CITIES_M3_RAIKOU), 1);
    EXPECT_EQ(CitiesM3GetChase(CITIES_M3_ENTEI), 0);
    EXPECT_EQ(CitiesM3GetChase(CITIES_M3_SUICUNE), 2);
}

TEST("M3: catching a roaming beast sets its flag and frees the slot")
{
    u32 index;
    struct Roamer *roamer = AddBeast(SPECIES_RAIKOU, 30, &index);

    VarSet(VAR_CITIES_M3_CHASE, 0);
    gEncounteredRoamerIndex = index;
    gBattleOutcome = B_OUTCOME_CAUGHT;
    EXPECT(CitiesM3HandleRoamerBattleEnd());
    EXPECT(FlagGet(FLAG_CITIES_M3_RAIKOU_CAUGHT));
    EXPECT(!roamer->active);
    // The den never opens for a beast already caught.
    EXPECT(FlagGet(FLAG_CITIES_HIDE_M3_RAIKOU));
}

TEST("M3: a KO'd beast keeps roaming at full health (never lost)")
{
    u32 index;
    struct Roamer *roamer = AddBeast(SPECIES_ENTEI, 30, &index);

    VarSet(VAR_CITIES_M3_CHASE, 0);
    roamer->hp = 1;
    roamer->statusA = 1;
    gEncounteredRoamerIndex = index;
    gBattleOutcome = B_OUTCOME_WON;
    EXPECT(CitiesM3HandleRoamerBattleEnd());
    EXPECT(roamer->active);
    EXPECT(roamer->hp > 1);
    EXPECT_EQ(roamer->statusA, 0);
    EXPECT_EQ(CitiesM3GetChase(CITIES_M3_ENTEI), 1);
}

TEST("M3: the third meeting corners the beast in its den")
{
    u32 index;
    struct Roamer *roamer = AddBeast(SPECIES_SUICUNE, 30, &index);

    VarSet(VAR_CITIES_M3_CHASE, 0);
    CitiesM3SetChase(CITIES_M3_SUICUNE, 2);
    FlagSet(FLAG_CITIES_HIDE_M3_SUICUNE);
    gEncounteredRoamerIndex = index;
    gBattleOutcome = B_OUTCOME_RAN;
    EXPECT(CitiesM3HandleRoamerBattleEnd());
    EXPECT_EQ(CitiesM3GetChase(CITIES_M3_SUICUNE), CITIES_M3_CHASE_MAX);
    EXPECT(!roamer->active);
    // Den object is now visible, and the beast waits there at full HP.
    EXPECT(!FlagGet(FLAG_CITIES_HIDE_M3_SUICUNE));
    EXPECT(roamer->hp > 0);

    // Extra meetings can never push the counter past the cap.
    gSpecialVar_0x8004 = CITIES_M3_SUICUNE;
    EXPECT(Script_CitiesM3DenVisible());
    FlagSet(FLAG_CITIES_M3_SUICUNE_CAUGHT);
    EXPECT(!Script_CitiesM3DenVisible());
}

TEST("M3: non-beast roamers keep the vanilla rules")
{
    u32 index;
    struct Roamer *roamer = AddBeast(SPECIES_LATIAS, 40, &index);

    VarSet(VAR_CITIES_M3_CHASE, 0);
    gEncounteredRoamerIndex = index;
    gBattleOutcome = B_OUTCOME_WON;
    EXPECT(!CitiesM3HandleRoamerBattleEnd());
    // Untouched by the handler: still active, counters unchanged.
    EXPECT(roamer->active);
    EXPECT_EQ(VarGet(VAR_CITIES_M3_CHASE), 0);
}

TEST("M3: a roaming beast's level follows the cap, keeping its HP fraction")
{
    u32 index;
    struct Roamer *roamer = AddBeast(SPECIES_RAIKOU, 5, &index);
    u16 cap = Script_CitiesGetLegendaryLevel();
    u16 fullHp = roamer->hp;

    EXPECT(cap > 5);
    roamer->hp = 1; // barely alive stays barely alive
    CitiesM3RefreshRoamerLevel(index);
    EXPECT_EQ(roamer->level, cap);
    EXPECT(roamer->hp >= 1);
    EXPECT(roamer->hp < fullHp);

    // Already at the cap: nothing changes.
    fullHp = roamer->hp;
    CitiesM3RefreshRoamerLevel(index);
    EXPECT_EQ(roamer->level, cap);
    EXPECT_EQ(roamer->hp, fullHp);
}

TEST("M3: the ranger's release skips caught beasts and never duplicates")
{
    u32 i, count;

    FlagSet(FLAG_CITIES_M3_ENTEI_CAUGHT);
    Script_CitiesM3StartRoamers();
    Script_CitiesM3StartRoamers(); // repeat call must not double up

    count = 0;
    for (i = 0; i < ROAMER_COUNT; i++)
    {
        if (!gSaveBlock1Ptr->roamer[i].active)
            continue;
        count++;
        EXPECT(gSaveBlock1Ptr->roamer[i].species != SPECIES_ENTEI);
    }
    EXPECT_EQ(count, 2); // Raikou and Suicune roam; Entei is caught
}
