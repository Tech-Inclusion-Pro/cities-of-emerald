#include "global.h"
#include "cities_accessibility.h"
#include "event_data.h"
#include "test/test.h"
#include "constants/flags.h"

// Phase 6 core: defaults, presets (GDD 11.6), pace-slowing count (GDD 8.4).

TEST("Accessibility: reset clears every setting")
{
    gSaveBlock3Ptr->citiesAccess.highContrast = TRUE;
    gSaveBlock3Ptr->citiesAccess.extraTimeMinutes = 5;
    FlagSet(FLAG_CITIES_ACCESS_INSTANT_TEXT);
    CitiesAccess_Reset();
    EXPECT(!gSaveBlock3Ptr->citiesAccess.highContrast);
    EXPECT(gSaveBlock3Ptr->citiesAccess.extraTimeMinutes == 0);
    EXPECT(!FlagGet(FLAG_CITIES_ACCESS_INSTANT_TEXT));
}

TEST("Accessibility: Low Vision preset turns on the five vision aids")
{
    CitiesAccess_Reset();
    CitiesAccess_ApplyPreset(CITIES_PRESET_LOW_VISION);
    EXPECT(gSaveBlock3Ptr->citiesAccess.highContrast);
    EXPECT(gSaveBlock3Ptr->citiesAccess.typeLabels);
    EXPECT(gSaveBlock3Ptr->citiesAccess.numericHp);
    EXPECT(gSaveBlock3Ptr->citiesAccess.patternedHpBars);
    EXPECT(gSaveBlock3Ptr->citiesAccess.effectivenessIndicator);
    EXPECT(!gSaveBlock3Ptr->citiesAccess.autoRun); // presets never spill over
}

TEST("Accessibility: Reduced Motion preset calms the screen")
{
    CitiesAccess_Reset();
    gSaveBlock2Ptr->optionsBattleSceneOff = FALSE;
    CitiesAccess_ApplyPreset(CITIES_PRESET_REDUCED_MOTION);
    EXPECT(gSaveBlock3Ptr->citiesAccess.reducedFlashing);
    EXPECT(gSaveBlock3Ptr->citiesAccess.reducedShake);
    EXPECT(gSaveBlock2Ptr->optionsBattleSceneOff);
}

TEST("Accessibility: Reading Support and One-Handed presets")
{
    CitiesAccess_Reset();
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_FAST;
    CitiesAccess_ApplyPreset(CITIES_PRESET_READING_SUPPORT);
    EXPECT(gSaveBlock2Ptr->optionsTextSpeed == OPTIONS_TEXT_SPEED_SLOW);
    EXPECT(gSaveBlock3Ptr->citiesAccess.waitForButton);

    CitiesAccess_ApplyPreset(CITIES_PRESET_ONE_HANDED);
    EXPECT(gSaveBlock3Ptr->citiesAccess.autoRun);
    EXPECT(gSaveBlock3Ptr->citiesAccess.toggleRun);
    EXPECT(gSaveBlock3Ptr->citiesAccess.fewerPresses);
}

TEST("Pace-slowing count matches the GDD 8.4 list exactly")
{
    CitiesAccess_Reset();
    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_MID;
    EXPECT_EQ(CountPaceSlowingFeatures(), 0);

    gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_SLOW;
    EXPECT_EQ(CountPaceSlowingFeatures(), 1);
    gSaveBlock3Ptr->citiesAccess.waitForButton = TRUE;
    EXPECT_EQ(CountPaceSlowingFeatures(), 2);
    gSaveBlock3Ptr->citiesAccess.holdToConfirm = TRUE;
    EXPECT_EQ(CountPaceSlowingFeatures(), 3);
    gSaveBlock3Ptr->citiesAccess.soundSubtitles = TRUE;
    EXPECT_EQ(CountPaceSlowingFeatures(), 4);

    // Non-pace-slowing options add nothing (GDD 8.4).
    gSaveBlock3Ptr->citiesAccess.highContrast = TRUE;
    gSaveBlock3Ptr->citiesAccess.typeLabels = TRUE;
    EXPECT_EQ(CountPaceSlowingFeatures(), 4);
    CitiesAccess_Reset();
}
