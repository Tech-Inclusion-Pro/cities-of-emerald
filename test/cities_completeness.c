#include "global.h"
#include "test/test.h"
#include "pokemon.h"
#include "story_only.h"
#include "cities_arcs.h"

// Task 13.2 (GDD 6.8): every story-only species is obtainable in exactly
// one place. Two guarantees:
//   1. No exact species is placed in more than one arc/event table.
//   2. Every story-only base line has at least one form placed — unless it
//      is obtained by evolving a placed species, or it is a vanilla
//      main-story encounter Cities leaves alone (Groudon/Kyogre/Rayquaza).
//
// Coverage is judged per base species, so alternate formes (Deoxys's,
// Giratina Origin, Zygarde 10%, the fusions, Gigantamax) ride on their
// base's placement. Galarian birds are placed as distinct entries, which
// guarantee 1 still allows because their exact IDs differ.

static bool32 IsCoverageExempt(u16 species)
{
    switch (species)
    {
    case SPECIES_URSHIFU:   // evolves from KUBFU (placed in H9)
    // Vanilla main story, unchanged (GDD 6.6).
    case SPECIES_GROUDON:
    case SPECIES_KYOGRE:
    case SPECIES_RAYQUAZA:
        return TRUE;
    default:
        return FALSE;
    }
}

TEST("Completeness: no story-only species is placed more than once")
{
    u16 species;

    for (species = 1; species < NUM_SPECIES; species++)
    {
        if (!IsSpeciesEnabled(species))
            continue;
        if (!IsStoryOnlySpecies(species))
            continue;
        EXPECT(CitiesCountExactPlacements(species) <= 1);
    }
}

TEST("Completeness: every story-only line is obtainable")
{
    u16 species;

    for (species = 1; species < NUM_SPECIES; species++)
    {
        if (!IsSpeciesEnabled(species))
            continue;
        if (!IsStoryOnlySpecies(species))
            continue;
        if (GET_BASE_SPECIES_ID(species) != species)
            continue;
        if (IsCoverageExempt(species))
            continue;
        if (!CitiesBaseFormPlaced(species))
            EXPECT_EQ(species, 0); // prints the unplaced base species id
    }
}
