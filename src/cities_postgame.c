#include "global.h"
#include "cities_arcs.h"
#include "event_data.h"
#include "main.h"
#include "naming_screen.h"
#include "string_util.h"
#include "overworld.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "story_only.h"
#include "string_util.h"
#include "text.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/species.h"

// Cities of Emerald — Phase 14 postgame specials.
//
// 14.2 Random-trade NPC (GDD 9.3): swaps a chosen party Pokémon for a
// freshly generated one of a random enabled, non-story-only species, at
// the same level (no power creep). Never gives legendaries, mythicals,
// Ultra Beasts, Paradox, or the borderline story-only lines.
//
// 14.3 Achievements (GDD 9.3): computed entirely from existing flags and
// dex state — no new save data — and buffered as a display string.

// VAR_0x8004 = chosen party slot on entry; replaces that mon in place.
void Script_CitiesDoRandomTrade(void)
{
    u8 slot = gSpecialVar_0x8004;
    struct Pokemon *mon;
    u16 species;
    u8 level;

    if (slot >= PARTY_SIZE)
        return;

    mon = &gPlayerParty[slot];
    level = GetMonData(mon, MON_DATA_LEVEL);

    do
    {
        species = (Random() % (NUM_SPECIES - 1)) + 1;
    } while (!IsSpeciesEnabled(species)
          || IsStoryOnlySpecies(species)
          || GET_BASE_SPECIES_ID(species) != species);

    CreateMon(mon, species, level, Random32(), OTID_STRUCT_PLAYER_ID);
    // A trade partner's Pokémon: mark it seen and caught in the dex.
    GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_SET_SEEN);
    GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_SET_CAUGHT);
    gSpecialVar_0x8005 = species; // for the "you received {STR_VAR}" line
}

void Script_CitiesBufferTradeSpeciesName(void)
{
    StringCopy(gStringVar1, GetSpeciesName(gSpecialVar_0x8005));
}

// ---- Player pronouns (separate from the sprite/look) ----
// Stored as a short word so future text can read it; presets for the
// common choices, plus a free-text custom entry. No text currently
// genders the player, so this is inclusive + future-proof.

void Script_CitiesSetPronounPreset(void)
{
    const u8 *word;
    switch (gSpecialVar_0x8004)
    {
    case 0:  word = COMPOUND_STRING("he");   break;
    case 1:  word = COMPOUND_STRING("she");  break;
    default: word = COMPOUND_STRING("they"); break;
    }
    StringCopy(gSaveBlock3Ptr->citiesPronoun, word);
}

// Free-text entry from the truck setup; returns to the continuing script.
void Script_CitiesEnterCustomPronoun(void)
{
    DoNamingScreen(NAMING_SCREEN_CODE, gSaveBlock3Ptr->citiesPronoun, 0, 0, 0,
                   CB2_ReturnToFieldContinueScript);
}

void Script_CitiesBufferPronoun(void)
{
    StringCopy(gStringVar1, gSaveBlock3Ptr->citiesPronoun);
}

// ---- 14.4 Shiny Charm: Birch gives it at 300 caught (GDD, [DECIDED]) ----

bool8 Script_CitiesShinyCharmEligible(void)
{
    if (FlagGet(FLAG_CITIES_SHINY_CHARM_GIVEN))
        return FALSE;
    return GetNationalPokedexCount(FLAG_GET_CAUGHT) >= 300;
}

// ---- 14.3 Achievements ----

struct CitiesAchievement
{
    const u8 *name;
    bool32 (*earned)(void);
};

static bool32 AchChampion(void)   { return FlagGet(FLAG_SYS_GAME_CLEAR); }
static bool32 AchMaster(void)     { return FlagGet(FLAG_CITIES_POKEMON_MASTER); }
static bool32 AchDex300(void)     { return GetNationalPokedexCount(FLAG_GET_CAUGHT) >= 300; }
static bool32 AchEpoch(void)      { return FlagGet(FLAG_CITIES_KAI_NAMED); }
static bool32 AchCoralmere(void)  { return VarGet(VAR_CITIES_V4_STATE) >= 2; }
static bool32 AchArceus(void)     { return VarGet(VAR_CITIES_H5A_STATE) >= 2; }

static const struct CitiesAchievement sAchievements[] =
{
    { COMPOUND_STRING("Champion of Hoenn"),   AchChampion },
    { COMPOUND_STRING("Pokemon Master"),      AchMaster },
    { COMPOUND_STRING("300 Species Caught"),  AchDex300 },
    { COMPOUND_STRING("Walked Coralmere"),    AchCoralmere },
    { COMPOUND_STRING("Team Epoch's Peace"),  AchEpoch },
    { COMPOUND_STRING("The Making of All"),   AchArceus },
};

// Buffers the earned count into STR_VAR_1, the total into STR_VAR_3, and a
// scrolling list of earned achievements into STR_VAR_2 (first two lines by
// newline, the rest with a scroll prompt so a long list never overflows).
void Script_CitiesBufferAchievements(void)
{
    u32 i, earned = 0;
    u8 *cursor = gStringVar2;

    for (i = 0; i < ARRAY_COUNT(sAchievements); i++)
    {
        if (!sAchievements[i].earned())
            continue;
        if (earned == 1)
            *cursor++ = CHAR_NEWLINE;
        else if (earned >= 2)
            *cursor++ = CHAR_PROMPT_SCROLL;
        cursor = StringCopy(cursor, sAchievements[i].name);
        earned++;
    }
    if (earned == 0)
        StringCopy(gStringVar2, COMPOUND_STRING("(none yet)"));
    else
        *cursor = EOS;

    ConvertIntToDecimalStringN(gStringVar1, earned, STR_CONV_MODE_LEFT_ALIGN, 2);
    ConvertIntToDecimalStringN(gStringVar3, ARRAY_COUNT(sAchievements), STR_CONV_MODE_LEFT_ALIGN, 2);
}
