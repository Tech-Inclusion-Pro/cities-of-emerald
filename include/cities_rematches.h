#ifndef GUARD_CITIES_REMATCHES_H
#define GUARD_CITIES_REMATCHES_H

#include "global.h"
#include "data.h"

// Cities of Emerald rematch versions (GDD 7.3, approved 2026-09-16):
// every gym leader and the rival have three postgame rematch versions.
//   V1 unlocks on becoming Champion (FLAG_SYS_GAME_CLEAR)
//   V2 unlocks at the postgame Thread 1 midpoint
//   V3 unlocks once both postgame threads are complete
// Gym leaders reuse the vanilla rematch trainer IDs (_2.._4) and their
// trainer flags; the rival uses the two placeholder trainer IDs with
// version-selected parties and Cities flags. No new trainer slots.

#define CITIES_REMATCH_VERSIONS_MAX 3

// Rival rematch party, selected by VAR_CITIES_RIVAL_REMATCH_VERSION.
// starterIndex marks the party member whose species is replaced with the
// rival's starter line (full evolution, region-mapped like every rival fight).
struct CitiesRivalRematchParty
{
    const struct TrainerMon *party;
    u8 partySize;
    u8 starterIndex;
};

extern const struct CitiesRivalRematchParty gCitiesRivalRematchParties[CITIES_REMATCH_VERSIONS_MAX];

u32 CitiesRematchVersionsUnlocked(void);
bool32 CitiesIsGymRematchVersionLocked(s32 rematchTableId, s32 rematchIndex);
u16 CitiesGetGymRematchServeId(u16 firstBattleTrainerId);
bool32 CitiesIsRivalRematchTrainer(u16 trainerId);
bool32 CitiesRivalRematchWinEligible(void);

// Script specials
bool8 Script_CitiesTryGymRematch(void);
u16 Script_CitiesArmRivalRematch(void);
void Script_CitiesRivalRematchWon(void);
bool8 Script_CitiesGymRematchWillScore(void);
bool8 Script_CitiesRivalRematchWillScore(void);

#endif // GUARD_CITIES_REMATCHES_H
