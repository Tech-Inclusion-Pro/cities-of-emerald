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
    CITIES_ARC_COUNT
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

// Script specials
u16 Script_CitiesGetLegendaryLevel(void);
bool8 Script_CitiesArcAllCaught(void);
void Script_CitiesSetWildLegendary(void);

#endif // GUARD_CITIES_ARCS_H
