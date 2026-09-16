#include "global.h"
#include "cities_rankings.h"
#include "event_data.h"
#include "test/test.h"
#include "constants/flags.h"

// Task 7.5: NPC scores compute from story flags; the ladder stays ordered
// and the player must EXCEED a score to pass it.

TEST("Leaderboard: fresh save puts the player at the very bottom")
{
    gSaveBlock3Ptr->citiesRankingScore = 0;
    EXPECT_EQ(CitiesRanking_GetPlayerRank(), CitiesRanking_GetNpcCount() + 1);
}

TEST("Leaderboard: Wallace starts at 2,400 and grows with player badges")
{
    EXPECT_EQ(CitiesRanking_GetNpcScore(0), 2400);
    FlagSet(FLAG_BADGE01_GET);
    FlagSet(FLAG_BADGE02_GET);
    EXPECT_EQ(CitiesRanking_GetNpcScore(0), 2400 + 2 * 40);
    FlagClear(FLAG_BADGE01_GET);
    FlagClear(FLAG_BADGE02_GET);
}

TEST("Leaderboard: champion flag raises the whole board")
{
    s32 before = CitiesRanking_GetNpcScore(1); // Drake
    FlagSet(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(CitiesRanking_GetNpcScore(1), before + 200);
    FlagClear(FLAG_SYS_GAME_CLEAR);
}

TEST("Leaderboard: ties go to NPCs; exceeding takes the top")
{
    u32 i;
    s32 top = 0;

    for (i = 0; i < CitiesRanking_GetNpcCount(); i++)
        if (CitiesRanking_GetNpcScore(i) > top)
            top = CitiesRanking_GetNpcScore(i);

    gSaveBlock3Ptr->citiesRankingScore = top;
    EXPECT(CitiesRanking_GetPlayerRank() > 1); // tie is not enough
    gSaveBlock3Ptr->citiesRankingScore = top + 1;
    EXPECT_EQ(CitiesRanking_GetPlayerRank(), 1); // Pokémon Master territory
    gSaveBlock3Ptr->citiesRankingScore = 0;
}
