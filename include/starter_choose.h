#ifndef GUARD_STARTER_CHOOSE_H
#define GUARD_STARTER_CHOOSE_H

#include "constants/species.h"

// Cities of Emerald starter regions, stored in VAR_CITIES_STARTER_REGION.
// 0 means "not chosen yet" so an unset save falls back to vanilla behavior.
enum
{
    CITIES_STARTER_REGION_NONE,
    CITIES_STARTER_REGION_KANTO,
    CITIES_STARTER_REGION_JOHTO,
    CITIES_STARTER_REGION_HOENN,
    CITIES_STARTER_REGION_SINNOH,
    CITIES_STARTER_REGION_UNOVA,
    CITIES_STARTER_REGION_KALOS,
    CITIES_STARTER_REGION_ALOLA,
    CITIES_STARTER_REGION_GALAR,
    CITIES_STARTER_REGION_PALDEA,
    CITIES_STARTER_REGION_SPECIAL, // Eevee / Pikachu / Ditto (pick stored in VAR_CITIES_STARTER_SPECIAL)
};

// [region - 1][slot: 0 grass, 1 fire, 2 water][stage 0..2]
extern const u16 gCitiesStarterStages[CITIES_STARTER_REGION_SPECIAL - 1][3][3];
// Special region choices: [slot: 0 Eevee, 1 Pikachu, 2 Ditto]
extern const u16 gCitiesSpecialStarters[3];

extern const u16 gBirchBagGrass_Pal[];
extern const u32 gBirchBagTilemap[];
extern const u32 gBirchGrassTilemap[];
extern const u32 gBirchBagGrass_Gfx[];
extern const u32 gPokeballSelection_Gfx[];

u16 GetStarterPokemon(u16 chosenStarterId);
enum Species CitiesGetRivalStarterSpecies(enum Species species);
void CB2_ChooseStarter(void);

#endif // GUARD_STARTER_CHOOSE_H
