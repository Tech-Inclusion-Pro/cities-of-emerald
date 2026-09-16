#include "global.h"
#include "pokemon.h"
#include "story_only.h"

bool32 IsStoryOnlySpecies(enum Species species)
{
    const struct SpeciesInfo *info;

    if (species == SPECIES_NONE)
        return FALSE;
    if (species >= NUM_SPECIES)
        return TRUE; // Invalid IDs fail safe: never spawnable.

    info = &gSpeciesInfo[species];
    if (info->isRestrictedLegendary
     || info->isSubLegendary
     || info->isMythical
     || info->isUltraBeast
     || info->isParadox)
        return TRUE;

    // Borderline cases (GDD 6.1). Checking the base species covers every
    // form: regional forms, Silvally's types, Urshifu's styles, Gigantamax.
    switch (GET_BASE_SPECIES_ID(species))
    {
    case SPECIES_TYPE_NULL:
    case SPECIES_SILVALLY:
    case SPECIES_COSMOG:
    case SPECIES_COSMOEM:
    case SPECIES_KUBFU:
    case SPECIES_URSHIFU:
    case SPECIES_MELTAN:
    case SPECIES_MELMETAL:
    case SPECIES_POIPOLE:
    case SPECIES_NAGANADEL:
        return TRUE;
    default:
        return FALSE;
    }
}
