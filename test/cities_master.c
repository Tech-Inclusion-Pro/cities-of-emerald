#include "global.h"
#include "cities_rankings.h"
#include "event_data.h"
#include "test/test.h"

// GDD 8.1 / Task 7.7: the POKéMON MASTER title triggers the first time the
// player's rank reaches #1 (score must EXCEED every NPC's — ties go to NPCs)
// and is permanent.

static void ResetMasterState(void)
{
    FlagClear(FLAG_CITIES_POKEMON_MASTER);
    FlagClear(FLAG_CITIES_MASTER_ANNOUNCED);
    FlagClear(FLAG_CITIES_MASTER_CEREMONY_DONE);
    CitiesRanking_ApplyDelta(-CitiesRanking_GetScore()); // score to 0
}

TEST("Master title: not earned below #1, earned the moment #1 is reached")
{
    ResetMasterState();

    CitiesRanking_CheckBecameMaster();
    EXPECT(!FlagGet(FLAG_CITIES_POKEMON_MASTER)); // rank far below 1

    // Tie with the top NPC is not enough (ties go to NPCs).
    CitiesRanking_ApplyDelta(CitiesRanking_GetNpcScore(0) - CitiesRanking_GetScore());
    CitiesRanking_CheckBecameMaster();
    EXPECT(!FlagGet(FLAG_CITIES_POKEMON_MASTER));

    // One point past the leader: title earned.
    CitiesRanking_ApplyDelta(1);
    EXPECT_EQ(CitiesRanking_GetPlayerRank(), 1);
    CitiesRanking_CheckBecameMaster();
    EXPECT(FlagGet(FLAG_CITIES_POKEMON_MASTER));

    // Dropping below #1 afterwards never revokes it.
    CitiesRanking_ApplyDelta(-CitiesRanking_GetScore());
    CitiesRanking_CheckBecameMaster();
    EXPECT(FlagGet(FLAG_CITIES_POKEMON_MASTER));

    ResetMasterState();
}
