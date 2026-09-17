#include "global.h"
#include "cities_arcs.h"
#include "caps.h"
#include "event_data.h"
#include "pokedex.h"
#include "pokemon.h"
#include "test/test.h"

// Phase 10 shared systems (GDD 6.4/6.5): badge-based obedience per arc,
// late catches, the M5 sticky flag, level-matched statics, and the
// all-caught reward check.

static void SetCaught(u16 species)
{
    GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_SET_SEEN);
    GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_SET_CAUGHT);
}

TEST("Arc obedience: each mid-game arc obeys at its badge, with the right message")
{
    static const struct { u16 species; u16 obeyFlag; u8 msg; } cases[] =
    {
        { SPECIES_ZAPDOS,    FLAG_BADGE04_GET, CITIES_ARC_MSG_HEAT_BADGE },
        { SPECIES_REGISTEEL, FLAG_BADGE06_GET, CITIES_ARC_MSG_FEATHER_BADGE },
        { SPECIES_SUICUNE,   FLAG_BADGE07_GET, CITIES_ARC_MSG_MIND_BADGE },
        { SPECIES_AZELF,     FLAG_BADGE08_GET, CITIES_ARC_MSG_RAIN_BADGE },
    };
    u32 i;
    u8 msg;

    for (i = 0; i < ARRAY_COUNT(cases); i++)
    {
        FlagClear(cases[i].obeyFlag);
        msg = 0xFF;
        EXPECT_EQ(CitiesGetArcObedience(cases[i].species, &msg), CITIES_ARC_DISOBEYS);
        EXPECT_EQ(msg, cases[i].msg);

        // Late catch / badge earned: obeys immediately.
        FlagSet(cases[i].obeyFlag);
        EXPECT_EQ(CitiesGetArcObedience(cases[i].species, &msg), CITIES_ARC_OBEYS);
        FlagClear(cases[i].obeyFlag);
    }

    // Non-arc species are untouched by the rule.
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_PIKACHU, &msg), CITIES_ARC_NOT_ARC_SPECIES);
}

TEST("Arc obedience: M5 pair rule is badge-independent and sticky")
{
    u8 msg;

    // All badges earned changes nothing for the pair.
    FlagSet(FLAG_BADGE08_GET);
    msg = 0xFF;
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_LATIAS, &msg), CITIES_ARC_DISOBEYS);
    EXPECT_EQ(msg, CITIES_ARC_MSG_NEED_LATIOS);
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_LATIOS, &msg), CITIES_ARC_DISOBEYS);
    EXPECT_EQ(msg, CITIES_ARC_MSG_NEED_LATIAS);

    // One caught is not enough.
    SetCaught(SPECIES_LATIAS);
    EXPECT(!CitiesLatiUnited());

    // Both caught: obedience arrives and the sticky flag is written.
    SetCaught(SPECIES_LATIOS);
    EXPECT(CitiesLatiUnited());
    EXPECT(FlagGet(FLAG_CITIES_LATI_UNITED));
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_LATIAS, &msg), CITIES_ARC_OBEYS);
}

TEST("Arc obedience: the M5 flag alone keeps the pair obedient (survives trade or release)")
{
    // Fresh save: neither is in the dex, only the sticky flag from a
    // past reunion — as after trading or releasing one of the pair.
    FlagSet(FLAG_CITIES_LATI_UNITED);
    EXPECT(CitiesLatiUnited());

    u8 msg;
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_LATIOS, &msg), CITIES_ARC_OBEYS);
}

TEST("Arc obedience: the postgame arc always obeys, badges or none (GDD 6.5)")
{
    u8 msg = 0xFF;

    // No badges at all — the postgame rule doesn't care.
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_ARTICUNO_GALAR, &msg), CITIES_ARC_OBEYS);
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_ZAPDOS_GALAR, &msg), CITIES_ARC_OBEYS);
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_MOLTRES_GALAR, &msg), CITIES_ARC_OBEYS);

    // Same for the H1 hidden-area guardians.
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_COBALION, &msg), CITIES_ARC_OBEYS);
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_TERRAKION, &msg), CITIES_ARC_OBEYS);
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_VIRIZION, &msg), CITIES_ARC_OBEYS);
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_KELDEO, &msg), CITIES_ARC_OBEYS);

    // And the H5b / H10 / H11 residents.
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_CRESSELIA, &msg), CITIES_ARC_OBEYS);
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_DARKRAI, &msg), CITIES_ARC_OBEYS);
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_TAPU_KOKO, &msg), CITIES_ARC_OBEYS);
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_TAPU_FINI, &msg), CITIES_ARC_OBEYS);
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_HEATRAN, &msg), CITIES_ARC_OBEYS);

    // The Kantonian birds still follow their own arc's badge rule.
    FlagClear(FLAG_BADGE04_GET);
    EXPECT_EQ(CitiesGetArcObedience(SPECIES_ARTICUNO, &msg), CITIES_ARC_DISOBEYS);
    EXPECT_EQ(msg, CITIES_ARC_MSG_HEAT_BADGE);
}

TEST("Arc rewards: all-caught check flips only when the whole arc is caught")
{
    EXPECT(!CitiesArcAllCaught(CITIES_ARC_M2));
    SetCaught(SPECIES_REGIROCK);
    SetCaught(SPECIES_REGICE);
    EXPECT(!CitiesArcAllCaught(CITIES_ARC_M2));
    SetCaught(SPECIES_REGISTEEL);
    EXPECT(CitiesArcAllCaught(CITIES_ARC_M2));
    EXPECT(!CitiesArcAllCaught(CITIES_ARC_M1));
}

TEST("Arc levels: legendary level tracks the automatic cap and ignores Assist overrides")
{
    // No badges: the pre-badge cap.
    EXPECT_EQ(Script_CitiesGetLegendaryLevel(), 15);

    FlagSet(FLAG_BADGE01_GET);
    EXPECT_EQ(Script_CitiesGetLegendaryLevel(), 19);

    // The Assist override raises the player's cap, not the world's.
    VarSet(VAR_CITIES_LEVEL_CAP, 100);
    EXPECT_EQ(Script_CitiesGetLegendaryLevel(), 19);
    VarSet(VAR_CITIES_LEVEL_CAP, 0);

    // Post-Champion the automatic cap is open-ended; statics settle at 60.
    FlagSet(FLAG_BADGE02_GET);
    FlagSet(FLAG_BADGE03_GET);
    FlagSet(FLAG_BADGE04_GET);
    FlagSet(FLAG_BADGE05_GET);
    FlagSet(FLAG_BADGE06_GET);
    FlagSet(FLAG_BADGE07_GET);
    FlagSet(FLAG_BADGE08_GET);
    FlagSet(FLAG_IS_CHAMPION);
    EXPECT_EQ(Script_CitiesGetLegendaryLevel(), 60);
}

TEST("Arc levels: postgame arcs use their fixed tier, mid-game arcs follow the cap")
{
    // Mid-game species with no badges: the automatic cap, not a tier.
    EXPECT_EQ(CitiesGetLegendarySpeciesLevel(SPECIES_ZAPDOS), Script_CitiesGetLegendaryLevel());

    // Postgame arcs are pinned to the GDD 6.4 tier table even though
    // the automatic cap would say the same or something else.
    EXPECT_EQ(CitiesGetLegendarySpeciesLevel(SPECIES_ARTICUNO_GALAR), 60);
    EXPECT_EQ(CitiesGetLegendarySpeciesLevel(SPECIES_KELDEO), 60);
    EXPECT_EQ(CitiesGetLegendarySpeciesLevel(SPECIES_DARKRAI), 60);
    EXPECT_EQ(CitiesGetLegendarySpeciesLevel(SPECIES_TAPU_BULU), 60);
    EXPECT_EQ(CitiesGetLegendarySpeciesLevel(SPECIES_HEATRAN), 60);

    // Non-arc species fall back to the cap rule.
    EXPECT_EQ(CitiesGetLegendarySpeciesLevel(SPECIES_PIKACHU), Script_CitiesGetLegendaryLevel());
}
