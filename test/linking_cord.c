#include "global.h"
#include "pokemon.h"
#include "test/test.h"
#include "constants/items.h"

// Task 4.4 (approved): the Linking Cord performs trade evolutions in
// single-player, including held-item trades and the Karrablast/Shelmet
// partner pair (partner satisfied from the player's own party).

TEST("Linking Cord: plain trade evolutions work (Machoke)")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_MACHOKE, 30, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_LINKING_CORD, NULL, NULL, CHECK_EVO),
              SPECIES_MACHAMP);
}

TEST("Linking Cord: held-item trade evolutions need the held item (Onix)")
{
    struct Pokemon mon;
    enum Item coat = ITEM_METAL_COAT;

    CreateMon(&mon, SPECIES_ONIX, 30, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_LINKING_CORD, NULL, NULL, CHECK_EVO),
              SPECIES_NONE);
    SetMonData(&mon, MON_DATA_HELD_ITEM, &coat);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_LINKING_CORD, NULL, NULL, CHECK_EVO),
              SPECIES_STEELIX);
}

TEST("Linking Cord: Karrablast and Shelmet need their partner in the party")
{
    struct Pokemon mon;

    ZeroPlayerPartyMons();
    CreateMon(&mon, SPECIES_KARRABLAST, 30, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_LINKING_CORD, NULL, NULL, CHECK_EVO),
              SPECIES_NONE);

    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_SHELMET, 30, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_LINKING_CORD, NULL, NULL, CHECK_EVO),
              SPECIES_ESCAVALIER);

    CreateMon(&mon, SPECIES_SHELMET, 30, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_LINKING_CORD, NULL, NULL, CHECK_EVO),
              SPECIES_NONE);
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_KARRABLAST, 30, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_LINKING_CORD, NULL, NULL, CHECK_EVO),
              SPECIES_ACCELGOR);
    ZeroPlayerPartyMons();
}

TEST("Linking Cord: ordinary evolution stones are unaffected")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_EEVEE, 30, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_LINKING_CORD, NULL, NULL, CHECK_EVO),
              SPECIES_NONE);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_USE, ITEM_WATER_STONE, NULL, NULL, CHECK_EVO),
              SPECIES_VAPOREON);
}
