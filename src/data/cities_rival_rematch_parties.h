#ifndef GUARD_CITIES_RIVAL_REMATCH_PARTIES_H
#define GUARD_CITIES_RIVAL_REMATCH_PARTIES_H

// Rival rematch version parties (GDD 7.3; teams approved 2026-09-16 via
// docs/REMATCH_TEAMS_PROPOSAL.md). All three versions share the two
// placeholder trainer IDs; CreateNPCTrainerParty() swaps this party in based
// on VAR_CITIES_RIVAL_REMATCH_VERSION. The member at starterIndex is
// replaced at generation time with the rival's starter line at full
// evolution, then region-mapped like every other rival fight. Fixed members
// use their level-up movesets, matching the proposal.

#define CITIES_RIVAL_IVS TRAINER_PARTY_IVS(31, 31, 31, 31, 31, 31)

static const struct TrainerMon sCitiesRivalRematchPartyV1[] =
{
    { .species = SPECIES_SCEPTILE, .lvl = 65, .iv = CITIES_RIVAL_IVS }, // starter slot
    { .species = SPECIES_SWELLOW,   .lvl = 62, .iv = CITIES_RIVAL_IVS },
    { .species = SPECIES_MAGNEZONE, .lvl = 62, .iv = CITIES_RIVAL_IVS },
    { .species = SPECIES_BRELOOM,   .lvl = 63, .iv = CITIES_RIVAL_IVS },
    { .species = SPECIES_WAILORD,   .lvl = 63, .iv = CITIES_RIVAL_IVS },
};

static const struct TrainerMon sCitiesRivalRematchPartyV2[] =
{
    { .species = SPECIES_SCEPTILE, .lvl = 75, .iv = CITIES_RIVAL_IVS }, // starter slot
    { .species = SPECIES_SWELLOW,   .lvl = 72, .iv = CITIES_RIVAL_IVS },
    { .species = SPECIES_MAGNEZONE, .lvl = 72, .iv = CITIES_RIVAL_IVS },
    { .species = SPECIES_BRELOOM,   .lvl = 73, .iv = CITIES_RIVAL_IVS },
    { .species = SPECIES_FLYGON,    .lvl = 73, .iv = CITIES_RIVAL_IVS },
    { .species = SPECIES_WAILORD,   .lvl = 73, .iv = CITIES_RIVAL_IVS },
};

static const struct TrainerMon sCitiesRivalRematchPartyV3[] =
{
    { .species = SPECIES_SCEPTILE, .lvl = 85, .iv = CITIES_RIVAL_IVS }, // starter slot
    { .species = SPECIES_SWELLOW,   .lvl = 82, .iv = CITIES_RIVAL_IVS },
    { .species = SPECIES_MAGNEZONE, .lvl = 82, .iv = CITIES_RIVAL_IVS },
    { .species = SPECIES_FLYGON,    .lvl = 83, .iv = CITIES_RIVAL_IVS },
    { .species = SPECIES_LUDICOLO,  .lvl = 83, .iv = CITIES_RIVAL_IVS },
    { .species = SPECIES_WAILORD,   .lvl = 83, .iv = CITIES_RIVAL_IVS },
};

const struct CitiesRivalRematchParty gCitiesRivalRematchParties[CITIES_REMATCH_VERSIONS_MAX] =
{
    { sCitiesRivalRematchPartyV1, ARRAY_COUNT(sCitiesRivalRematchPartyV1), 0 },
    { sCitiesRivalRematchPartyV2, ARRAY_COUNT(sCitiesRivalRematchPartyV2), 0 },
    { sCitiesRivalRematchPartyV3, ARRAY_COUNT(sCitiesRivalRematchPartyV3), 0 },
};

#endif // GUARD_CITIES_RIVAL_REMATCH_PARTIES_H
