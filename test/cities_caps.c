#include "global.h"
#include "caps.h"
#include "difficulty.h"
#include "event_data.h"
#include "test/test.h"

// Phase 5: VAR_CITIES_LEVEL_CAP semantics (GDD 9.1/10).
// 0 = automatic badge cap; 1 = automatic + 10 (Assist "raised");
// MAX_LEVEL = no cap; anything else = fixed override.
// Tests run with no badges, so the automatic cap is the first entry (15).

TEST("Level caps: automatic badge cap with var 0")
{
    VarSet(VAR_CITIES_LEVEL_CAP, 0);
    EXPECT_EQ(GetCurrentLevelCap(), 15);
}

TEST("Level caps: Assist raised cap adds 10")
{
    VarSet(VAR_CITIES_LEVEL_CAP, 1);
    EXPECT_EQ(GetCurrentLevelCap(), 25);
    VarSet(VAR_CITIES_LEVEL_CAP, 0);
}

TEST("Level caps: MAX_LEVEL removes the cap; other values are fixed overrides")
{
    VarSet(VAR_CITIES_LEVEL_CAP, MAX_LEVEL);
    EXPECT_EQ(GetCurrentLevelCap(), MAX_LEVEL);
    VarSet(VAR_CITIES_LEVEL_CAP, 37);
    EXPECT_EQ(GetCurrentLevelCap(), 37);
    VarSet(VAR_CITIES_LEVEL_CAP, 0);
}

TEST("Difficulty: set and get round-trips all three levels")
{
    // The TESTING build redirects B_VAR_DIFFICULTY, so go through the API.
    SetCurrentDifficultyLevel(DIFFICULTY_EASY);
    EXPECT_EQ(GetCurrentDifficultyLevel(), DIFFICULTY_EASY);
    SetCurrentDifficultyLevel(DIFFICULTY_HARD);
    EXPECT_EQ(GetCurrentDifficultyLevel(), DIFFICULTY_HARD);
    SetCurrentDifficultyLevel(DIFFICULTY_NORMAL);
    EXPECT_EQ(GetCurrentDifficultyLevel(), DIFFICULTY_NORMAL);
}
