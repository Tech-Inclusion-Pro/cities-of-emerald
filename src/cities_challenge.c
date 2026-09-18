#include "global.h"
#include "cities_challenge.h"
#include "event_data.h"
#include "main.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "story_only.h"
#include "constants/species.h"

// GDD 10: the last PC box is the Nuzlocke memorial. Fainted Pokémon are
// laid to rest here and can't be withdrawn while Nuzlocke is on.
#define CITIES_MEMORIAL_BOX (TOTAL_BOXES_COUNT - 1)

// Cities of Emerald — Phase 15 challenge modes (GDD Section 10).
// Everything keys off gSaveBlock3Ptr->citiesChallenge and is inert unless
// the relevant mode bit is set, so an ordinary save is unaffected.

static struct CitiesChallenge *Chal(void)
{
    return &gSaveBlock3Ptr->citiesChallenge;
}

// ---- Randomizer (15.2) ----
// Deterministic: a given original species always maps to the same
// replacement for the run's seed. The replacement is always an enabled,
// non-story-only, non-alternate-forme species (evolutions included).

u16 CitiesRandomizeSpecies(u16 species)
{
    u32 h;
    u16 start, i, candidate;

    if (species == SPECIES_NONE || species >= NUM_SPECIES)
        return species;

    h = (species * 2654435761u) ^ (Chal()->randomizerSeed * 40503u + 0x9E3779B9u);
    start = 1 + (h % (NUM_SPECIES - 1));
    for (i = 0; i < NUM_SPECIES - 1; i++)
    {
        candidate = 1 + (((start - 1) + i) % (NUM_SPECIES - 1));
        if (IsSpeciesEnabled(candidate)
         && !IsStoryOnlySpecies(candidate)
         && GET_BASE_SPECIES_ID(candidate) == candidate)
            return candidate;
    }
    return species;
}

bool8 CitiesRandomizeWildOn(void)
{
    return Chal()->randomizer && Chal()->randomizeWild;
}

bool8 CitiesRandomizeStartersOn(void)
{
    return Chal()->randomizer && Chal()->randomizeStarters;
}

bool8 CitiesRandomizeTrainersOn(void)
{
    return Chal()->randomizer && Chal()->randomizeTrainers;
}

u16 CitiesMaybeRandomizeWild(u16 species)
{
    return CitiesRandomizeWildOn() ? CitiesRandomizeSpecies(species) : species;
}

u16 CitiesMaybeRandomizeTrainerMon(u16 species)
{
    // Never remap a story-only species a trainer legitimately owns into
    // something odd during the story; only randomize when the toggle is on.
    return CitiesRandomizeTrainersOn() ? CitiesRandomizeSpecies(species) : species;
}

// ---- Nuzlocke (15.1) ----

bool8 CitiesNuzlockeOn(void)
{
    return Chal()->nuzlocke;
}

bool8 CitiesNuzlockeDupesClause(void)
{
    return Chal()->dupesClause;
}

bool8 CitiesNuzlockeShinyClause(void)
{
    return Chal()->shinyClause;
}

static bool8 AreaHasFirstEncounter(u32 mapsec)
{
    if (mapsec / 8 >= CITIES_NUM_MAPSEC_BYTES)
        return TRUE; // out-of-range areas count as "used" (no catching)
    return (Chal()->firstEncounter[mapsec / 8] & (1 << (mapsec & 7))) != 0;
}

static void MarkAreaFirstEncounter(u32 mapsec)
{
    if (mapsec / 8 < CITIES_NUM_MAPSEC_BYTES)
        Chal()->firstEncounter[mapsec / 8] |= (1 << (mapsec & 7));
}

// The current overworld area. Wild battles set the region section.
static u32 CurrentArea(void)
{
    return gMapHeader.regionMapSectionId;
}

// GDD 10: may a wild Pokémon in the current area be caught right now?
// - shiny clause: shinies are always catchable and never consume the area.
// - dupes clause: a species already owned doesn't consume the area, and may
//   be caught (it doesn't count as the run's encounter for that area).
// - otherwise: only the very first catchable species per area is allowed.
bool8 CitiesNuzlockeMayCatch(u16 species, bool8 isShiny)
{
    u32 area;

    if (!Chal()->nuzlocke)
        return TRUE;
    if (Chal()->shinyClause && isShiny)
        return TRUE;
    if (Chal()->dupesClause
     && GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT))
        return TRUE;

    area = CurrentArea();
    return !AreaHasFirstEncounter(area);
}

// Call when a wild Pokémon is actually caught, to consume the area's
// "first encounter" (unless a clause exempted it).
void CitiesNuzlockeNoteCaught(u16 species, bool8 isShiny)
{
    if (!Chal()->nuzlocke)
        return;
    if (Chal()->shinyClause && isShiny)
        return;
    if (Chal()->dupesClause
     && GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_GET_CAUGHT))
        return; // already owned before this catch registered — don't consume
    MarkAreaFirstEncounter(CurrentArea());
}

// ---- Faint = memorial box (15.1b) ----

static bool8 DepositToMemorialBox(struct Pokemon *mon)
{
    u32 slot;
    for (slot = 0; slot < IN_BOX_COUNT; slot++)
    {
        if (GetBoxMonDataAt(CITIES_MEMORIAL_BOX, slot, MON_DATA_SPECIES) == SPECIES_NONE)
        {
            gPokemonStoragePtr->boxes[CITIES_MEMORIAL_BOX][slot] = mon->box;
            return TRUE;
        }
    }
    return FALSE; // memorial box full
}

// Called once when a battle ends and control returns to the field. Any
// party Pokémon that fainted is laid to rest in the memorial box and its
// party slot is cleared. Only runs under Nuzlocke.
void CitiesNuzlockeProcessFaints(void)
{
    u32 i;
    bool8 movedAny = FALSE;

    if (!Chal()->nuzlocke)
        return;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        u16 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);

        if (species == SPECIES_NONE || species == SPECIES_EGG)
            continue;
        if (GetMonData(mon, MON_DATA_HP) != 0)
            continue;

        if (!DepositToMemorialBox(mon))
            CopyMonToPC(mon); // memorial box full: fall back to normal PC
        ZeroMonData(mon);
        movedAny = TRUE;
    }
    if (movedAny)
        CompactPartySlots();
}

// GDD 10: the memorial box index, for the storage grab-guard.
u8 CitiesNuzlockeMemorialBox(void)
{
    return CITIES_MEMORIAL_BOX;
}

// ---- Setup specials (truck), VAR_0x8004 = 0/1 ----

void Script_CitiesSetNuzlocke(void)
{
    Chal()->nuzlocke = (gSpecialVar_0x8004 != 0);
    if (Chal()->nuzlocke)
    {
        Chal()->dupesClause = TRUE;  // GDD [PROPOSED] defaults, approved 2026-09-18
        Chal()->shinyClause = TRUE;
    }
}

void Script_CitiesSetRandomizer(void)
{
    Chal()->randomizer = (gSpecialVar_0x8004 != 0);
    if (Chal()->randomizer)
    {
        // The three categories Cities randomizes (GDD 10, approved).
        Chal()->randomizeWild = TRUE;
        Chal()->randomizeStarters = TRUE;
        Chal()->randomizeTrainers = TRUE;
        // Seed from the hardware counters mixed at setup time.
        Chal()->randomizerSeed = Random32() ^ (gMain.vblankCounter1 * 1103515245u + 12345u);
        if (Chal()->randomizerSeed == 0)
            Chal()->randomizerSeed = 0x1A2B3C4Du;
    }
}
