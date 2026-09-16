#include "global.h"
#include "cities_accessibility.h"
#include "event_data.h"
#include "main.h"
#include "constants/flags.h"

// Task 6.1/6.8/6.9 (GDD 11): defaults, presets, and the pace-slowing
// feature count all live in this one file, per the implementation plan's
// single-source-of-truth rule.

void CitiesAccess_Reset(void)
{
    memset(&gSaveBlock3Ptr->citiesAccess, 0, sizeof(gSaveBlock3Ptr->citiesAccess));
    FlagClear(FLAG_CITIES_ACCESS_INSTANT_TEXT);
}

// GDD 11.6: presets only turn options ON — every option stays adjustable
// afterward in the Accessibility menu.
void CitiesAccess_ApplyPreset(enum CitiesAccessPreset preset)
{
    struct CitiesAccessibility *a = &gSaveBlock3Ptr->citiesAccess;

    switch (preset)
    {
    case CITIES_PRESET_LOW_VISION:
        a->highContrast = TRUE;
        a->typeLabels = TRUE;
        a->numericHp = TRUE;
        a->patternedHpBars = TRUE;
        a->effectivenessIndicator = TRUE;
        break;
    case CITIES_PRESET_REDUCED_MOTION:
        a->reducedFlashing = TRUE;
        a->reducedShake = TRUE;
        gSaveBlock2Ptr->optionsBattleSceneOff = TRUE; // skip animations
        break;
    case CITIES_PRESET_READING_SUPPORT:
        gSaveBlock2Ptr->optionsTextSpeed = OPTIONS_TEXT_SPEED_SLOW;
        a->waitForButton = TRUE;
        break;
    case CITIES_PRESET_ONE_HANDED:
        a->autoRun = TRUE;
        a->toggleRun = TRUE;
        a->fewerPresses = TRUE;
        break;
    default:
        break;
    }
}

// GDD 8.4: each pace-slowing feature adds 60 seconds to the ranking
// quick-win window. This is the single source of truth for that list.
u32 CountPaceSlowingFeatures(void)
{
    const struct CitiesAccessibility *a = &gSaveBlock3Ptr->citiesAccess;
    u32 count = 0;

    if (gSaveBlock2Ptr->optionsTextSpeed == OPTIONS_TEXT_SPEED_SLOW)
        count++;
    if (a->waitForButton)
        count++;
    if (a->holdToConfirm)
        count++;
    if (a->soundSubtitles)
        count++;
    return count;
}

// Task 6.4 (partial): auto-run and toggle-run. With auto-run, holding B
// walks instead of runs. With toggle-run, pressing B flips a latch.
// Toggle-run wins when both are on.
static bool8 sToggleRunLatch;

bool32 CitiesPlayerWantsRun(u16 heldKeys)
{
    const struct CitiesAccessibility *a = &gSaveBlock3Ptr->citiesAccess;

    if (a->toggleRun)
    {
        if (JOY_NEW(B_BUTTON))
            sToggleRunLatch = !sToggleRunLatch;
        return sToggleRunLatch;
    }
    if (a->autoRun)
        return !(heldKeys & B_BUTTON);
    return (heldKeys & B_BUTTON) != 0;
}

// Setup screen / guide NPC: applies the preset chosen in gSpecialVar_Result.
void Script_CitiesApplyPreset(void)
{
    CitiesAccess_ApplyPreset(gSpecialVar_Result);
}
