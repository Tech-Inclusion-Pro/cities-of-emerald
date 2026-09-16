#ifndef GUARD_CITIES_ACCESSIBILITY_H
#define GUARD_CITIES_ACCESSIBILITY_H

// Cities of Emerald accessibility (GDD Section 11). Settings live in
// gSaveBlock3Ptr->citiesAccess plus FLAG_CITIES_ACCESS_INSTANT_TEXT.

enum CitiesAccessPreset
{
    CITIES_PRESET_NONE,
    CITIES_PRESET_LOW_VISION,
    CITIES_PRESET_REDUCED_MOTION,
    CITIES_PRESET_READING_SUPPORT,
    CITIES_PRESET_ONE_HANDED,
    CITIES_PRESET_COUNT,
};

void CitiesAccess_Reset(void);
void CitiesAccess_ApplyPreset(enum CitiesAccessPreset preset);
u32 CountPaceSlowingFeatures(void);
bool32 CitiesPlayerWantsRun(u16 heldKeys);
void Script_CitiesApplyPreset(void);
void CB2_InitCitiesAccessMenu(void);

#endif // GUARD_CITIES_ACCESSIBILITY_H
