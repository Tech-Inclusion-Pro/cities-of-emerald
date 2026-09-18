#ifndef GUARD_CITIES_ARCS_H
#define GUARD_CITIES_ARCS_H

#include "global.h"

// Cities of Emerald legendary arcs (GDD 6.4-6.7, Phase 10 shared systems).
// Mid-game arcs M1-M5; the per-arc content lands with each arc build.

enum CitiesArc
{
    CITIES_ARC_M1, // Articuno, Zapdos, Moltres  — opens badge 3, obeys badge 4
    CITIES_ARC_M2, // Regirock, Regice, Registeel — opens badge 5, obeys badge 6
    CITIES_ARC_M3, // Raikou, Entei, Suicune      — opens badge 6, obeys badge 7
    CITIES_ARC_M4, // Uxie, Mesprit, Azelf        — opens badge 7, obeys badge 8
    CITIES_ARC_M5, // Latias, Latios              — opens badge 8, obeys when both caught
    CITIES_ARC_M1PG, // Galarian birds            — postgame (League + M1 complete), always obeys
    CITIES_ARC_H1,   // Swords of Justice         — postgame hidden area (Littleroot Hollow), always obeys
    CITIES_ARC_H5B,  // Cresselia, Darkrai        — postgame hidden area (Moonrise Cove), always obeys
    CITIES_ARC_H10,  // The four Tapu             — postgame hidden area (Shrine Atoll), always obeys
    CITIES_ARC_H11,  // Heatran                   — postgame hidden area (Ember Vault), always obeys
    CITIES_ARC_H3,   // Regigigas, Regieleki, Regidrago — postgame (needs M2 complete), tier 65
    CITIES_ARC_H4,   // Ho-Oh, Lugia, Celebi      — postgame hidden area (canopy), tier 65
    CITIES_ARC_H8,   // The four forces of storm  — postgame hidden area (rise), tier 65, Reveal Glass
    CITIES_ARC_H6,   // Xerneas, Yveltal, Zygarde — postgame hidden area (undercliff), tier 70, Zygarde Cube
    CITIES_ARC_H7,   // Reshiram, Zekrom, Kyurem  — postgame hidden area (hall), tier 70, DNA Splicers
    CITIES_ARC_H9,   // The old heroes (6)        — postgame hidden area (meadow), tier 70, rusted relics + reins
    CITIES_ARC_H2A,  // Treasures of Ruin         — postgame hidden area (garden), tier 65
    CITIES_ARC_H2B,  // Loyal Three + Ogerpon     — postgame hidden area (garden), tier 65
    CITIES_ARC_H5A,  // Dialga, Palkia, Giratina  — postgame finale (vestibule + Mt. Pyre), tier 75
    CITIES_ARC_H5A_ARCEUS, // Arceus              — sanctum altar encounter, tier 80
    CITIES_ARC_V1,   // Mewtwo, Mew, Genesect     — Epoch thread (Task 12.5), tier 60
    CITIES_ARC_V2,   // Type: Null line, Magearna — Epoch thread, tier 65
    CITIES_ARC_V3,   // UBs + Cosmog line + Necrozma — Epoch thread, tier 70
    CITIES_ARC_V4,   // Paradox + rift anchors    — Epoch thread, tier 75
    CITIES_ARC_V5,   // Eternatus                 — Epoch finale, tier 80
    CITIES_ARC_MYTHIC, // all mythical events     — Phase 13, tier 70, always obeys
    CITIES_ARC_COUNT // NOTE: postgame arcs sit at the end; the always-obeys rule keys on >= CITIES_ARC_M1PG
};

// Result of the badge-based obedience rule (GDD 6.5).
enum CitiesArcObedience
{
    CITIES_ARC_NOT_ARC_SPECIES,
    CITIES_ARC_OBEYS,
    CITIES_ARC_DISOBEYS,
};

// Message indices into gCitiesWontListenStringIds.
enum
{
    CITIES_ARC_MSG_HEAT_BADGE,
    CITIES_ARC_MSG_FEATHER_BADGE,
    CITIES_ARC_MSG_MIND_BADGE,
    CITIES_ARC_MSG_RAIN_BADGE,
    CITIES_ARC_MSG_NEED_LATIOS,
    CITIES_ARC_MSG_NEED_LATIAS,
};

enum CitiesArcObedience CitiesGetArcObedience(u16 species, u8 *msgIndexOut);
bool32 CitiesArcAllCaught(u32 arc);
bool32 CitiesLatiUnited(void);
u16 CitiesGetLegendarySpeciesLevel(u16 species);

// Script specials
u16 Script_CitiesGetLegendaryLevel(void);
bool8 Script_CitiesArcAllCaught(void);
void Script_CitiesSetWildLegendary(void);

#endif // GUARD_CITIES_ARCS_H
