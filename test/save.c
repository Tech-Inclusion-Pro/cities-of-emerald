#include "global.h"
#include "pokemon_storage_system.h"
#include "test/test.h"

// If you would like to ensure save compatibility, update the values below with those for your hack. You can find these through the debug menu.
// Please note that this simple check is not 100% foolproof, but should be able to catch most unintended shifts.
#define T_SAVEBLOCK1_SIZE 15324 // Cities of Emerald: +192 B Cities flag/var ranges, +376 B bag expansion, -876 B FREE_MYSTERY_GIFT, +56 B ROAMER_COUNT 3 for M3, +8 B trainer table 864->928 (docs/SAVE_BUDGET.md)
#define T_SAVEBLOCK2_SIZE 3884
#define T_SAVEBLOCK3_SIZE 52 // Cities of Emerald: +4 B CitiesAccessibility, +4 B ranking score, +28 B CitiesChallenge, +12 B citiesPronoun (docs/SAVE_BUDGET.md)
#define T_POKEMONSTORAGE_SIZE 34144

TEST("SaveBlock1 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock1), T_SAVEBLOCK1_SIZE);
}

TEST("SaveBlock2 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock2), T_SAVEBLOCK2_SIZE);
}

TEST("SaveBlock3 is backwards compatible")
{
    EXPECT_EQ(sizeof(struct SaveBlock3), T_SAVEBLOCK3_SIZE);
}

TEST("PokemonStorage is backwards compatible")
{
    EXPECT_EQ(sizeof(struct PokemonStorage), T_POKEMONSTORAGE_SIZE);
}

#undef T_SAVEBLOCK1_SIZE
#undef T_SAVEBLOCK2_SIZE
#undef T_SAVEBLOCK3_SIZE
#undef T_POKEMONSTORAGE_SIZE
