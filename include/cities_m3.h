#ifndef GUARD_CITIES_M3_H
#define GUARD_CITIES_M3_H

#include "global.h"

// Cities of Emerald M3 "On the Trail" (GDD 6.6, outline approved
// 2026-09-17): Raikou, Entei, and Suicune roam the routes with live
// journal tracking. After CITIES_M3_CHASE_MAX battle meetings a beast
// tires and settles in a fixed den, where it fights as a normal static
// that cannot flee. Beasts are never permanently lost.

enum CitiesM3Beast
{
    CITIES_M3_RAIKOU,
    CITIES_M3_ENTEI,
    CITIES_M3_SUICUNE,
    CITIES_M3_BEAST_COUNT
};

#define CITIES_M3_CHASE_MAX 3

u32 CitiesM3BeastForSpecies(u16 species);
u32 CitiesM3GetChase(u32 beast);
void CitiesM3SetChase(u32 beast, u32 count);
bool32 CitiesM3BeastCaught(u32 beast);

// Battle-end hook (ReturnFromBattleToOverworld): owns the outcome of a
// roamer battle against an M3 beast. Returns FALSE for other roamers so
// the vanilla rules still apply to them.
bool32 CitiesM3HandleRoamerBattleEnd(void);

// 10.0a for roamers: refresh an M3 roamer to the current level cap
// before its battle mon is instanced, scaling remaining HP.
void CitiesM3RefreshRoamerLevel(u32 roamerIndex);

// Script specials
void Script_CitiesM3StartRoamers(void);
bool8 Script_CitiesM3DenVisible(void);

// Quest journal (cities_quests.c): one status line per beast into dest.
void CitiesM3BufferChaseStatus(u8 *dest);

#endif // GUARD_CITIES_M3_H
