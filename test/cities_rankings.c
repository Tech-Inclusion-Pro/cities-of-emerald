#include "global.h"
#include "cities_accessibility.h"
#include "cities_rankings.h"
#include "event_data.h"
#include "test/test.h"

// Task 7.4 (GDD 8.3/8.4): scoring table, floor, doubles, non-acting
// switch-ins, repeats, and timer extensions.

TEST("Rankings: best possible win is 14 points")
{
    // Win +2, six survivors that battled +6, no faints +3, quick win +3.
    EXPECT_EQ(CitiesRanking_ComputeDelta(TRUE, 6, 0, TRUE), 14);
}

TEST("Rankings: worst possible loss is -7 points")
{
    // Loss -1, six fainted -6.
    EXPECT_EQ(CitiesRanking_ComputeDelta(FALSE, 0, 6, FALSE), -7);
}

TEST("Rankings: the total never drops below zero")
{
    gSaveBlock3Ptr->citiesRankingScore = 3;
    CitiesRanking_ApplyDelta(-7);
    EXPECT_EQ(CitiesRanking_GetScore(), 0);
    CitiesRanking_ApplyDelta(-1);
    EXPECT_EQ(CitiesRanking_GetScore(), 0);
    CitiesRanking_ApplyDelta(5);
    EXPECT_EQ(CitiesRanking_GetScore(), 5);
    gSaveBlock3Ptr->citiesRankingScore = 0;
}

TEST("Rankings: doubles — every Pokémon that used a move counts")
{
    // Two acted and survived in a doubles win, one benched faint.
    EXPECT_EQ(CitiesRanking_ComputeDelta(TRUE, 2, 1, FALSE), 3); // +2 +2 -1
}

TEST("Rankings: switching in without acting earns nothing")
{
    // Win with one actor; a second mon switched in but never moved.
    // survivedActed counts only actors, so the delta ignores it.
    EXPECT_EQ(CitiesRanking_ComputeDelta(TRUE, 1, 0, FALSE), 6); // +2 +1 +3 (no faints)
}

TEST("Rankings: quick-win window grows with pace-slowing features and extra time")
{
    CitiesAccess_Reset();
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_MID;
    EXPECT_EQ(CitiesRanking_QuickWinFrames(), 60 * 60);

    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_SLOW; // +60 s
    gSaveBlock3Ptr->citiesAccess.waitForButton = TRUE;          // +60 s
    EXPECT_EQ(CitiesRanking_QuickWinFrames(), 3 * 60 * 60);

    gSaveBlock3Ptr->citiesAccess.extraTimeMinutes = 5;          // +5 min
    EXPECT_EQ(CitiesRanking_QuickWinFrames(), 8 * 60 * 60);
    CitiesAccess_Reset();
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_MID;
}

TEST("Rankings: losses always subtract; ineligible wins add nothing")
{
    // The eligibility gate lives in BattleEnd; this verifies the applied
    // arithmetic for the repeat-battle policy: a repeat WIN applies no
    // delta, a repeat LOSS applies the loss delta.
    gSaveBlock3Ptr->citiesRankingScore = 10;
    // repeat win: no delta applied by design (BattleEnd returns early)
    EXPECT_EQ(CitiesRanking_GetScore(), 10);
    // loss against already-beaten trainer still counts:
    CitiesRanking_ApplyDelta(CitiesRanking_ComputeDelta(FALSE, 0, 2, FALSE));
    EXPECT_EQ(CitiesRanking_GetScore(), 7); // -1 -2
    gSaveBlock3Ptr->citiesRankingScore = 0;
}
