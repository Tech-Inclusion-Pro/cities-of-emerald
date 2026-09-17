#ifndef GUARD_CITIES_RANKINGS_H
#define GUARD_CITIES_RANKINGS_H

// Cities of Emerald national rankings (GDD Section 8).
// Battle-in-progress tallies are runtime-only; the persistent score lives
// in gSaveBlock3Ptr->citiesRankingScore and never drops below zero.

void CitiesRanking_BattleStart(u16 trainerId);
void CitiesRanking_TickFrame(void);
void CitiesRanking_NoteMonActed(u32 partyIndex);
void CitiesRanking_BattleEnd(void);
s32 CitiesRanking_GetScore(void);

// Pure helpers, exposed for tests (GDD 8.3/8.4).
s32 CitiesRanking_ComputeDelta(bool32 won, u32 survivedActed, u32 fainted, bool32 quickWin);
u32 CitiesRanking_QuickWinFrames(void);
void CitiesRanking_ApplyDelta(s32 delta);

u32 CitiesRanking_GetNpcCount(void);
const u8 *CitiesRanking_GetNpcName(u32 index);
s32 CitiesRanking_GetNpcScore(u32 index);
u32 CitiesRanking_GetPlayerRank(void);
void CitiesRanking_CheckBecameMaster(void);
void Script_CitiesBufferRankingScore(void);
void CB2_InitCitiesRankingsScreen(void);

#endif // GUARD_CITIES_RANKINGS_H
