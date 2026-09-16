#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "starter_choose.h"
#include "test/test.h"

// GDD 4.2 / Task 3.4: all 28 starter choices produce the right species, and
// the rival mapping yields a valid type-advantaged team for each of them.

// The rival's slot is always (player slot + 1) % 3 — set by script data.
#define RIVAL_SLOT(playerSlot) (((playerSlot) + 1) % 3)

TEST("Starter selection: all 27 regional choices give the right species")
{
    u32 region, slot;

    for (region = CITIES_STARTER_REGION_KANTO; region <= CITIES_STARTER_REGION_PALDEA; region++)
    {
        VarSet(VAR_CITIES_STARTER_REGION, region);
        for (slot = 0; slot < 3; slot++)
            EXPECT_EQ(GetStarterPokemon(slot), gCitiesStarterStages[region - 1][slot][0]);
    }
    VarSet(VAR_CITIES_STARTER_REGION, CITIES_STARTER_REGION_NONE);
}

TEST("Starter selection: the 28th choice (Special) always gives Eevee")
{
    u32 slot;

    VarSet(VAR_CITIES_STARTER_REGION, CITIES_STARTER_REGION_SPECIAL);
    for (slot = 0; slot < 3; slot++)
        EXPECT_EQ(GetStarterPokemon(slot), SPECIES_EEVEE);
    VarSet(VAR_CITIES_STARTER_REGION, CITIES_STARTER_REGION_NONE);
}

TEST("Starter selection: unset region falls back to vanilla Hoenn starters")
{
    VarSet(VAR_CITIES_STARTER_REGION, CITIES_STARTER_REGION_NONE);
    EXPECT_EQ(GetStarterPokemon(0), SPECIES_TREECKO);
    EXPECT_EQ(GetStarterPokemon(1), SPECIES_TORCHIC);
    EXPECT_EQ(GetStarterPokemon(2), SPECIES_MUDKIP);
}

TEST("Rival mapping: every stage of the Hoenn line maps to the chosen region")
{
    u32 region, line, stage;

    for (region = CITIES_STARTER_REGION_KANTO; region <= CITIES_STARTER_REGION_PALDEA; region++)
    {
        VarSet(VAR_CITIES_STARTER_REGION, region);
        for (line = 0; line < 3; line++)
        {
            for (stage = 0; stage < 3; stage++)
            {
                enum Species hoenn = gCitiesStarterStages[CITIES_STARTER_REGION_HOENN - 1][line][stage];
                enum Species expected = gCitiesStarterStages[region - 1][line][stage];

                EXPECT_EQ(CitiesGetRivalStarterSpecies(hoenn), expected);
                // Mapped species must be real, usable species.
                EXPECT(expected != SPECIES_NONE);
                EXPECT(expected < NUM_SPECIES);
            }
        }
    }
    VarSet(VAR_CITIES_STARTER_REGION, CITIES_STARTER_REGION_NONE);
}

TEST("Rival mapping: Hoenn, Special, and unset leave rival teams unchanged")
{
    static const u16 regions[] =
    {
        CITIES_STARTER_REGION_NONE,
        CITIES_STARTER_REGION_HOENN,
        CITIES_STARTER_REGION_SPECIAL,
    };
    u32 i, line, stage;

    for (i = 0; i < ARRAY_COUNT(regions); i++)
    {
        VarSet(VAR_CITIES_STARTER_REGION, regions[i]);
        for (line = 0; line < 3; line++)
        {
            for (stage = 0; stage < 3; stage++)
            {
                enum Species hoenn = gCitiesStarterStages[CITIES_STARTER_REGION_HOENN - 1][line][stage];
                EXPECT_EQ(CitiesGetRivalStarterSpecies(hoenn), hoenn);
            }
        }
        // Non-starter species always pass through untouched.
        EXPECT_EQ(CitiesGetRivalStarterSpecies(SPECIES_RALTS), SPECIES_RALTS);
        EXPECT_EQ(CitiesGetRivalStarterSpecies(SPECIES_POOCHYENA), SPECIES_POOCHYENA);
    }
    VarSet(VAR_CITIES_STARTER_REGION, CITIES_STARTER_REGION_NONE);
}

TEST("Rival mapping: the rival's starter has a type advantage in every region")
{
    u32 region, playerSlot;

    for (region = CITIES_STARTER_REGION_KANTO; region <= CITIES_STARTER_REGION_PALDEA; region++)
    {
        for (playerSlot = 0; playerSlot < 3; playerSlot++)
        {
            enum Species rival = gCitiesStarterStages[region - 1][RIVAL_SLOT(playerSlot)][0];
            enum Type rivalType = GetSpeciesType(rival, 0);

            // Slot order is grass/fire/water, so the advantage cycle is:
            // player grass -> rival fire, fire -> water, water -> grass.
            switch (playerSlot)
            {
            case 0: EXPECT_EQ(rivalType, TYPE_FIRE);  break;
            case 1: EXPECT_EQ(rivalType, TYPE_WATER); break;
            case 2: EXPECT_EQ(rivalType, TYPE_GRASS); break;
            }
        }
    }
}
