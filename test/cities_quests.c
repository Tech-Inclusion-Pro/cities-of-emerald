#include "global.h"
#include "cities_quests.h"
#include "event_data.h"
#include "string_util.h"
#include "text.h"
#include "test/test.h"

// GDD 11.4 / Phase 9: the journal lists exactly the active quests, in
// order, with the main story always first.

static void ClearQuestTestState(void)
{
    FlagClear(FLAG_SYS_POKEMON_GET);
    FlagClear(FLAG_BADGE01_GET);
    FlagClear(FLAG_BADGE02_GET);
    FlagClear(FLAG_BADGE03_GET);
    FlagClear(FLAG_SYS_GAME_CLEAR);
    FlagClear(FLAG_CITIES_POKEMON_MASTER);
    VarSet(VAR_CITIES_M1_STATE, 0);
    VarSet(VAR_TEMP_9, 0);
}

static u32 CountJournalEntries(void)
{
    u32 count = 0;

    VarSet(VAR_TEMP_9, 0);
    while (Script_CitiesBufferNextJournalEntry())
    {
        count++;
        VarSet(VAR_TEMP_9, count);
    }
    return count;
}

TEST("Journal: quests activate with progress and completed ones drop off")
{
    ClearQuestTestState();

    // Fresh save: only the main story.
    EXPECT_EQ(CountJournalEntries(), 1);

    // Badge 2: the Eevee expert quest opens.
    FlagSet(FLAG_BADGE02_GET);
    EXPECT_EQ(CountJournalEntries(), 2);

    // Badge 3: the M1 arc and the ranked challengers join.
    FlagSet(FLAG_BADGE03_GET);
    EXPECT_EQ(CountJournalEntries(), 4);

    // Completing M1 (state 2) drops it from the journal.
    VarSet(VAR_CITIES_M1_STATE, 2);
    EXPECT_EQ(CountJournalEntries(), 3);
    VarSet(VAR_CITIES_M1_STATE, 0);

    // Champion: rematches and the road to Master open too.
    FlagSet(FLAG_SYS_GAME_CLEAR);
    EXPECT_EQ(CountJournalEntries(), 6);

    // The Master quest completes and leaves the journal.
    FlagSet(FLAG_CITIES_POKEMON_MASTER);
    EXPECT_EQ(CountJournalEntries(), 5);

    ClearQuestTestState();
}

TEST("Journal: the hint special always yields a non-empty main step")
{
    ClearQuestTestState();

    gStringVar3[0] = EOS;
    Script_CitiesBufferMainQuestStep();
    EXPECT(gStringVar3[0] != EOS);

    FlagSet(FLAG_SYS_GAME_CLEAR);
    gStringVar3[0] = EOS;
    Script_CitiesBufferMainQuestStep();
    EXPECT(gStringVar3[0] != EOS);

    ClearQuestTestState();
}

TEST("Journal: M4 opens at badge 7 and completes on the keeper's word")
{
    ClearQuestTestState();
    VarSet(VAR_CITIES_M4_STATE, 0);

    u32 base = CountJournalEntries();

    // Badge 7 opens The Three Lights (badge 6 also wakes M3 — count both).
    FlagSet(FLAG_BADGE06_GET);
    FlagSet(FLAG_BADGE07_GET);
    EXPECT_EQ(CountJournalEntries(), base + 2);

    // Completing the arc drops it from the journal.
    VarSet(VAR_CITIES_M4_STATE, 2);
    EXPECT_EQ(CountJournalEntries(), base + 1);

    VarSet(VAR_CITIES_M4_STATE, 0);
    FlagClear(FLAG_BADGE06_GET);
    FlagClear(FLAG_BADGE07_GET);
    ClearQuestTestState();
}
