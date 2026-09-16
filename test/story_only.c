#include "global.h"
#include "story_only.h"
#include "wild_encounter.h"
#include "constants/maps.h"
#include "constants/rtc.h"
#include "constants/wild_encounter.h"
#include "test/test.h"

TEST("IsStoryOnlySpecies: legendaries, mythicals, Ultra Beasts, and Paradox are story-only")
{
    EXPECT(IsStoryOnlySpecies(SPECIES_RAYQUAZA));
    EXPECT(IsStoryOnlySpecies(SPECIES_KYOGRE));
    EXPECT(IsStoryOnlySpecies(SPECIES_GROUDON));
    EXPECT(IsStoryOnlySpecies(SPECIES_ARTICUNO));     // sub-legendary
    EXPECT(IsStoryOnlySpecies(SPECIES_REGIROCK));
    EXPECT(IsStoryOnlySpecies(SPECIES_LATIAS));
    EXPECT(IsStoryOnlySpecies(SPECIES_LATIOS));
    EXPECT(IsStoryOnlySpecies(SPECIES_MEW));          // mythical
    EXPECT(IsStoryOnlySpecies(SPECIES_JIRACHI));
    EXPECT(IsStoryOnlySpecies(SPECIES_DEOXYS));
    EXPECT(IsStoryOnlySpecies(SPECIES_NIHILEGO));     // Ultra Beast
    EXPECT(IsStoryOnlySpecies(SPECIES_GREAT_TUSK));   // Paradox
    EXPECT(IsStoryOnlySpecies(SPECIES_IRON_VALIANT)); // Paradox
}

TEST("IsStoryOnlySpecies: borderline list and all their forms are story-only")
{
    EXPECT(IsStoryOnlySpecies(SPECIES_TYPE_NULL));
    EXPECT(IsStoryOnlySpecies(SPECIES_SILVALLY));
    EXPECT(IsStoryOnlySpecies(SPECIES_SILVALLY_FIRE));
    EXPECT(IsStoryOnlySpecies(SPECIES_COSMOG));
    EXPECT(IsStoryOnlySpecies(SPECIES_COSMOEM));
    EXPECT(IsStoryOnlySpecies(SPECIES_KUBFU));
    EXPECT(IsStoryOnlySpecies(SPECIES_URSHIFU));
    EXPECT(IsStoryOnlySpecies(SPECIES_URSHIFU_RAPID_STRIKE));
    EXPECT(IsStoryOnlySpecies(SPECIES_MELTAN));
    EXPECT(IsStoryOnlySpecies(SPECIES_MELMETAL));
    EXPECT(IsStoryOnlySpecies(SPECIES_MELMETAL_GMAX));
    EXPECT(IsStoryOnlySpecies(SPECIES_POIPOLE));
    EXPECT(IsStoryOnlySpecies(SPECIES_NAGANADEL));
}

TEST("IsStoryOnlySpecies: regional forms of legendaries are story-only")
{
    EXPECT(IsStoryOnlySpecies(SPECIES_ARTICUNO_GALAR));
    EXPECT(IsStoryOnlySpecies(SPECIES_ZAPDOS_GALAR));
    EXPECT(IsStoryOnlySpecies(SPECIES_MOLTRES_GALAR));
}

TEST("IsStoryOnlySpecies: ordinary and pseudo-legendary species are not story-only")
{
    EXPECT(!IsStoryOnlySpecies(SPECIES_NONE));
    EXPECT(!IsStoryOnlySpecies(SPECIES_PIKACHU));
    EXPECT(!IsStoryOnlySpecies(SPECIES_ZIGZAGOON));
    EXPECT(!IsStoryOnlySpecies(SPECIES_WOBBUFFET));
    EXPECT(!IsStoryOnlySpecies(SPECIES_EEVEE));
    // Pseudo-legendaries stay obtainable (GDD 5.5 postgame pools).
    EXPECT(!IsStoryOnlySpecies(SPECIES_DRAGONITE));
    EXPECT(!IsStoryOnlySpecies(SPECIES_TYRANITAR));
    EXPECT(!IsStoryOnlySpecies(SPECIES_METAGROSS));
    EXPECT(!IsStoryOnlySpecies(SPECIES_GARCHOMP));
    EXPECT(!IsStoryOnlySpecies(SPECIES_BAXCALIBUR));
    // Ordinary regional forms are fine too.
    EXPECT(!IsStoryOnlySpecies(SPECIES_RATTATA_ALOLA));
}

// GDD 6.8 / Task 2.2: fail `make check` if any story-only species is in any
// wild encounter table, across every time of day and encounter type. This is
// the enforcement gate for hand-edited or generated wild_encounters.json.
TEST("No story-only species appears in any wild encounter table")
{
    u32 i, t, s;

    for (i = 0; gWildMonHeaders[i].mapGroup != MAP_GROUP(MAP_UNDEFINED); i++)
    {
        for (t = 0; t < TIMES_OF_DAY_COUNT; t++)
        {
            const struct WildEncounterTypes *types = &gWildMonHeaders[i].encounterTypes[t];

            if (types->landMonsInfo != NULL)
                for (s = 0; s < NUM_LAND_MONS_ENCOUNTER_SLOTS; s++)
                    EXPECT(!IsStoryOnlySpecies(types->landMonsInfo->wildPokemon[s].species));
            if (types->waterMonsInfo != NULL)
                for (s = 0; s < NUM_WATER_MONS_ENCOUNTER_SLOTS; s++)
                    EXPECT(!IsStoryOnlySpecies(types->waterMonsInfo->wildPokemon[s].species));
            if (types->rockSmashMonsInfo != NULL)
                for (s = 0; s < NUM_ROCK_SMASH_MONS_ENCOUNTER_SLOTS; s++)
                    EXPECT(!IsStoryOnlySpecies(types->rockSmashMonsInfo->wildPokemon[s].species));
            if (types->fishingMonsInfo != NULL)
                for (s = 0; s < NUM_FISHING_MONS_ENCOUNTER_SLOTS; s++)
                    EXPECT(!IsStoryOnlySpecies(types->fishingMonsInfo->wildPokemon[s].species));
            if (types->hiddenMonsInfo != NULL)
                for (s = 0; s < NUM_HIDDEN_MONS_ENCOUNTER_SLOTS; s++)
                    EXPECT(!IsStoryOnlySpecies(types->hiddenMonsInfo->wildPokemon[s].species));
        }
    }
}
