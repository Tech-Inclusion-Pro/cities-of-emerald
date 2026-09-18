#ifndef GUARD_CITIES_CHALLENGE_H
#define GUARD_CITIES_CHALLENGE_H

// Cities of Emerald — Phase 15 challenge modes (GDD Section 10).

u16 CitiesRandomizeSpecies(u16 species);
bool8 CitiesRandomizeWildOn(void);
bool8 CitiesRandomizeStartersOn(void);
bool8 CitiesRandomizeTrainersOn(void);
u16 CitiesMaybeRandomizeWild(u16 species);
u16 CitiesMaybeRandomizeTrainerMon(u16 species);

bool8 CitiesNuzlockeOn(void);
bool8 CitiesNuzlockeDupesClause(void);
bool8 CitiesNuzlockeShinyClause(void);
bool8 CitiesNuzlockeMayCatch(u16 species, bool8 isShiny);
void CitiesNuzlockeNoteCaught(u16 species, bool8 isShiny);
void CitiesNuzlockeProcessFaints(void);
u8 CitiesNuzlockeMemorialBox(void);

// Setup specials (truck)
void Script_CitiesSetNuzlocke(void);
void Script_CitiesSetRandomizer(void);

#endif // GUARD_CITIES_CHALLENGE_H
