#ifndef GUARD_STORY_ONLY_H
#define GUARD_STORY_ONLY_H

#include "constants/species.h"

// Cities of Emerald (GDD Section 6.2): single source of truth for species
// that only appear through story events. Every random source must call this:
// wild tables, overworld encounters, DexNav, random trades, the randomizer,
// and Battle Frontier rental/random pools.
bool32 IsStoryOnlySpecies(enum Species species);

#endif // GUARD_STORY_ONLY_H
