#include "global.h"
#include "battle_setup.h"
#include "cities_rematches.h"
#include "event_data.h"
#include "constants/opponents.h"
#include "constants/rematches.h"
#include "test/test.h"

// GDD 7.3 / Task 8.1: postgame rematch versions. Gym leaders reuse the
// vanilla _2.._4 rematch IDs behind a story-flag unlock clamp; the rival
// uses one trainer ID per gender with Cities version flags.

#define TRAINER_FLAG(id) (TRAINER_FLAGS_START + (id))

static void ClearRematchTestState(void)
{
    FlagClear(FLAG_SYS_GAME_CLEAR);
    FlagClear(FLAG_CITIES_POSTGAME_THREAD1_MIDPOINT);
    FlagClear(FLAG_CITIES_POSTGAME_THREAD1_COMPLETE);
    FlagClear(FLAG_CITIES_POSTGAME_THREAD2_COMPLETE);
    FlagClear(FLAG_CITIES_RIVAL_REMATCH_V1_BEATEN);
    FlagClear(FLAG_CITIES_RIVAL_REMATCH_V2_BEATEN);
    FlagClear(FLAG_CITIES_RIVAL_REMATCH_V3_BEATEN);
    FlagClear(TRAINER_FLAG(TRAINER_ROXANNE_2));
    FlagClear(TRAINER_FLAG(TRAINER_ROXANNE_3));
    FlagClear(TRAINER_FLAG(TRAINER_ROXANNE_4));
    FlagClear(TRAINER_FLAG(TRAINER_ROXANNE_5));
    VarSet(VAR_CITIES_RIVAL_REMATCH_VERSION, 0);
}

TEST("Rematch unlocks: the version ladder follows the story flags")
{
    ClearRematchTestState();
    EXPECT_EQ(CitiesRematchVersionsUnlocked(), 0);

    FlagSet(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(CitiesRematchVersionsUnlocked(), 1);

    FlagSet(FLAG_CITIES_POSTGAME_THREAD1_MIDPOINT);
    EXPECT_EQ(CitiesRematchVersionsUnlocked(), 2);

    FlagSet(FLAG_CITIES_POSTGAME_THREAD1_COMPLETE);
    EXPECT_EQ(CitiesRematchVersionsUnlocked(), 2); // thread 2 still open

    FlagSet(FLAG_CITIES_POSTGAME_THREAD2_COMPLETE);
    EXPECT_EQ(CitiesRematchVersionsUnlocked(), 3);

    ClearRematchTestState();
}

TEST("Gym versions: served in order and clamped to the unlocked tier")
{
    ClearRematchTestState();
    FlagSet(FLAG_SYS_GAME_CLEAR);

    // V1 unlocked, nothing beaten: serve V1 (_2).
    EXPECT_EQ(CitiesGetGymRematchServeId(TRAINER_ROXANNE_1), TRAINER_ROXANNE_2);

    // V1 beaten, V2 still locked: repeat V1 instead of leaking V2.
    FlagSet(TRAINER_FLAG(TRAINER_ROXANNE_2));
    EXPECT_EQ(CitiesGetGymRematchServeId(TRAINER_ROXANNE_1), TRAINER_ROXANNE_2);

    // Midpoint reached: V2 (_3) opens up.
    FlagSet(FLAG_CITIES_POSTGAME_THREAD1_MIDPOINT);
    EXPECT_EQ(CitiesGetGymRematchServeId(TRAINER_ROXANNE_1), TRAINER_ROXANNE_3);

    // Both threads done and V2 beaten: V3 (_4) is the last version; _5 is
    // reserved and must never be served even with everything beaten.
    FlagSet(TRAINER_FLAG(TRAINER_ROXANNE_3));
    FlagSet(FLAG_CITIES_POSTGAME_THREAD1_COMPLETE);
    FlagSet(FLAG_CITIES_POSTGAME_THREAD2_COMPLETE);
    EXPECT_EQ(CitiesGetGymRematchServeId(TRAINER_ROXANNE_1), TRAINER_ROXANNE_4);
    FlagSet(TRAINER_FLAG(TRAINER_ROXANNE_4));
    EXPECT_EQ(CitiesGetGymRematchServeId(TRAINER_ROXANNE_1), TRAINER_ROXANNE_4);

    ClearRematchTestState();
}

TEST("Gym versions: the unlock clamp only touches gym leader entries")
{
    u32 i;

    ClearRematchTestState();
    FlagSet(FLAG_SYS_GAME_CLEAR); // one version unlocked

    for (i = REMATCH_ROXANNE; i <= REMATCH_JUAN; i++)
        EXPECT(CitiesIsGymRematchVersionLocked(i, 2)); // V2 locked for leaders

    EXPECT(!CitiesIsGymRematchVersionLocked(REMATCH_ROSE, 4));
    EXPECT(!CitiesIsGymRematchVersionLocked(REMATCH_WALLY_VR, 4));
    EXPECT(!CitiesIsGymRematchVersionLocked(REMATCH_SIDNEY, 4));

    ClearRematchTestState();
}

TEST("Rival versions: arming picks the lowest unbeaten, then repeats the newest")
{
    ClearRematchTestState();

    EXPECT_EQ(Script_CitiesArmRivalRematch(), 0); // not Champion yet

    FlagSet(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(Script_CitiesArmRivalRematch(), 1);
    EXPECT_EQ(VarGet(VAR_CITIES_RIVAL_REMATCH_VERSION), 1);

    // V1 beaten and only tier 1 unlocked: repeat V1.
    FlagSet(FLAG_CITIES_RIVAL_REMATCH_V1_BEATEN);
    EXPECT_EQ(Script_CitiesArmRivalRematch(), 1);

    // Tier 2 unlocked: V2 is next.
    FlagSet(FLAG_CITIES_POSTGAME_THREAD1_MIDPOINT);
    EXPECT_EQ(Script_CitiesArmRivalRematch(), 2);

    // Everything unlocked and beaten: repeat the newest (V3).
    FlagSet(FLAG_CITIES_POSTGAME_THREAD1_COMPLETE);
    FlagSet(FLAG_CITIES_POSTGAME_THREAD2_COMPLETE);
    FlagSet(FLAG_CITIES_RIVAL_REMATCH_V2_BEATEN);
    FlagSet(FLAG_CITIES_RIVAL_REMATCH_V3_BEATEN);
    EXPECT_EQ(Script_CitiesArmRivalRematch(), 3);

    ClearRematchTestState();
}

TEST("Rival versions: ranking win eligibility is once per version")
{
    ClearRematchTestState();
    FlagSet(FLAG_SYS_GAME_CLEAR);

    EXPECT(CitiesIsRivalRematchTrainer(TRAINER_BRENDAN_PLACEHOLDER));
    EXPECT(CitiesIsRivalRematchTrainer(TRAINER_MAY_PLACEHOLDER));
    EXPECT(!CitiesIsRivalRematchTrainer(TRAINER_ROXANNE_2));

    // Nothing armed: no points.
    EXPECT(!CitiesRivalRematchWinEligible());

    // V1 armed and unbeaten: eligible. Winning marks it and disarms.
    EXPECT_EQ(Script_CitiesArmRivalRematch(), 1);
    EXPECT(CitiesRivalRematchWinEligible());
    Script_CitiesRivalRematchWon();
    EXPECT(FlagGet(FLAG_CITIES_RIVAL_REMATCH_V1_BEATEN));
    EXPECT_EQ(VarGet(VAR_CITIES_RIVAL_REMATCH_VERSION), 0);

    // Rearmed repeat of V1: no points this time.
    EXPECT_EQ(Script_CitiesArmRivalRematch(), 1);
    EXPECT(!CitiesRivalRematchWinEligible());

    ClearRematchTestState();
}
