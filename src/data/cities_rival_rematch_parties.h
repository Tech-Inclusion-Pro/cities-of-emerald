#ifndef GUARD_CITIES_RIVAL_REMATCH_PARTIES_H
#define GUARD_CITIES_RIVAL_REMATCH_PARTIES_H

// Rival rematch version parties (GDD 7.3). All three versions share the two
// placeholder trainer IDs; CreateNPCTrainerParty() swaps this party in based
// on VAR_CITIES_RIVAL_REMATCH_VERSION. The member at starterIndex is
// replaced at generation time with the rival's starter line at full
// evolution, then region-mapped like every other rival fight.
//
// PLACEHOLDER TEAMS (Task 8.1 scaffolding) — the real per-version teams are
// Task 8.2 and go to Rocco for review before they land here.

static const struct TrainerMon sCitiesRivalRematchPartyV1[] =
{
    { .species = SPECIES_SCEPTILE, .lvl = 60, .iv = TRAINER_PARTY_IVS(20, 20, 20, 20, 20, 20) }, // starter slot
    { .species = SPECIES_SWELLOW,  .lvl = 58, .iv = TRAINER_PARTY_IVS(20, 20, 20, 20, 20, 20) },
    { .species = SPECIES_MAGNETON, .lvl = 58, .iv = TRAINER_PARTY_IVS(20, 20, 20, 20, 20, 20) },
    { .species = SPECIES_BRELOOM,  .lvl = 59, .iv = TRAINER_PARTY_IVS(20, 20, 20, 20, 20, 20) },
};

static const struct TrainerMon sCitiesRivalRematchPartyV2[] =
{
    { .species = SPECIES_SCEPTILE, .lvl = 70, .iv = TRAINER_PARTY_IVS(25, 25, 25, 25, 25, 25) }, // starter slot
    { .species = SPECIES_SWELLOW,  .lvl = 68, .iv = TRAINER_PARTY_IVS(25, 25, 25, 25, 25, 25) },
    { .species = SPECIES_MAGNEZONE, .lvl = 68, .iv = TRAINER_PARTY_IVS(25, 25, 25, 25, 25, 25) },
    { .species = SPECIES_BRELOOM,  .lvl = 69, .iv = TRAINER_PARTY_IVS(25, 25, 25, 25, 25, 25) },
    { .species = SPECIES_WAILORD,  .lvl = 69, .iv = TRAINER_PARTY_IVS(25, 25, 25, 25, 25, 25) },
};

static const struct TrainerMon sCitiesRivalRematchPartyV3[] =
{
    { .species = SPECIES_SCEPTILE, .lvl = 80, .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31) }, // starter slot
    { .species = SPECIES_SWELLOW,  .lvl = 78, .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31) },
    { .species = SPECIES_MAGNEZONE, .lvl = 78, .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31) },
    { .species = SPECIES_BRELOOM,  .lvl = 79, .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31) },
    { .species = SPECIES_WAILORD,  .lvl = 79, .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31) },
    { .species = SPECIES_TROPIUS,  .lvl = 79, .iv = TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31) },
};

const struct CitiesRivalRematchParty gCitiesRivalRematchParties[CITIES_REMATCH_VERSIONS_MAX] =
{
    { sCitiesRivalRematchPartyV1, ARRAY_COUNT(sCitiesRivalRematchPartyV1), 0 },
    { sCitiesRivalRematchPartyV2, ARRAY_COUNT(sCitiesRivalRematchPartyV2), 0 },
    { sCitiesRivalRematchPartyV3, ARRAY_COUNT(sCitiesRivalRematchPartyV3), 0 },
};

#endif // GUARD_CITIES_RIVAL_REMATCH_PARTIES_H
