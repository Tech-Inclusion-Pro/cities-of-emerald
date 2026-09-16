#include "global.h"
#include "cities_rankings.h"
#include "battle.h"
#include "battle_setup.h"
#include "cities_accessibility.h"
#include "event_data.h"
#include "pokemon.h"
#include "string_util.h"
#include "constants/battle.h"
#include "constants/flags.h"

// GDD 8.2: trainer battles only; regular trainers score on the FIRST win
// (rematch versions hook in during Phase 8); losses always count, even
// against a trainer already beaten (approved [PROPOSED] default).
// Battle Frontier and link battles never count.

static EWRAM_DATA u8 sActedMask = 0;       // player party slots that used a move
static EWRAM_DATA u32 sBattleFrames = 0;   // GDD 8.4: measured in frames
static EWRAM_DATA bool8 sEligibleForWin = FALSE;
static EWRAM_DATA bool8 sTracking = FALSE;

void CitiesRanking_BattleStart(u16 trainerId)
{
    sActedMask = 0;
    sBattleFrames = 0;
    sTracking = FALSE;
    sEligibleForWin = FALSE;

    if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
        return;
    if (gBattleTypeFlags & (BATTLE_TYPE_FRONTIER | BATTLE_TYPE_LINK | BATTLE_TYPE_TRAINER_HILL
                            | BATTLE_TYPE_EREADER_TRAINER | BATTLE_TYPE_RECORDED))
        return;

    sTracking = TRUE;
    sEligibleForWin = !HasTrainerBeenFought(trainerId);
}

void CitiesRanking_TickFrame(void)
{
    if (sTracking && sBattleFrames < 0xFFFFFF)
        sBattleFrames++;
}

void CitiesRanking_NoteMonActed(u32 partyIndex)
{
    if (sTracking && partyIndex < PARTY_SIZE)
        sActedMask |= (1 << partyIndex);
}

// GDD 8.4: 60 s base, +60 s per pace-slowing accessibility feature,
// plus the manual extra-time setting. GBA runs at ~60 frames per second.
u32 CitiesRanking_QuickWinFrames(void)
{
    u32 seconds = 60;
    seconds += 60 * CountPaceSlowingFeatures();
    seconds += 60 * gSaveBlock3Ptr->citiesAccess.extraTimeMinutes;
    return seconds * 60;
}

// GDD 8.3 scoring table. Best possible win: 14. Worst possible loss: -7.
s32 CitiesRanking_ComputeDelta(bool32 won, u32 survivedActed, u32 fainted, bool32 quickWin)
{
    s32 delta = won ? 2 : -1;

    delta += survivedActed;
    delta -= fainted;
    if (won && fainted == 0)
        delta += 3;
    if (won && quickWin)
        delta += 3;
    return delta;
}

// GDD 8.3: the total never goes below zero.
void CitiesRanking_ApplyDelta(s32 delta)
{
    s32 score = gSaveBlock3Ptr->citiesRankingScore + delta;

    if (score < 0)
        score = 0;
    gSaveBlock3Ptr->citiesRankingScore = score;
}

s32 CitiesRanking_GetScore(void)
{
    return gSaveBlock3Ptr->citiesRankingScore;
}

void CitiesRanking_BattleEnd(void)
{
    u32 i;
    u32 survivedActed = 0, fainted = 0;
    bool32 won;

    if (!sTracking)
        return;
    sTracking = FALSE;

    won = (gBattleOutcome == B_OUTCOME_WON || gBattleOutcome == B_OUTCOME_CAUGHT);
    if (won && !sEligibleForWin)
        return; // already earned points from this trainer (GDD 8.2)
    if (!won && gBattleOutcome != B_OUTCOME_LOST && gBattleOutcome != B_OUTCOME_DREW)
        return; // fled/forfeited battles score nothing

    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];
        u32 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG);

        if (species == SPECIES_NONE || species == SPECIES_EGG)
            continue;
        if (GetMonData(mon, MON_DATA_HP) == 0)
            fainted++;
        else if (sActedMask & (1 << i))
            survivedActed++;
    }

    CitiesRanking_ApplyDelta(CitiesRanking_ComputeDelta(won, survivedActed, fainted,
                                                        sBattleFrames <= CitiesRanking_QuickWinFrames()));
}

// Rankings view (Task 7.6 v1): buffers score text for the start-menu script.
void Script_CitiesBufferRankingScore(void)
{
    ConvertIntToDecimalStringN(gStringVar1, CitiesRanking_GetScore(), STR_CONV_MODE_LEFT_ALIGN, 6);
}

// Task 7.5 (roster approved 2026-09-16): ranked NPCs. Scores are computed
// from story flags at display time (GDD 8.6) — zero save cost. Each NPC:
// base + perBadge for every badge the PLAYER holds + a bonus once the
// player is Champion. Postgame-arc increments hook in when those arcs
// exist (Phases 10-12). The Archivist joins the board when the V-arc
// flags exist, with the Kai name swap (GDD 7.2).

struct CitiesRankedNpc
{
    const u8 *name;
    u16 base;
    u8 perBadge;
    u16 champBonus;
};

static const struct CitiesRankedNpc sRankedNpcs[] =
{
    {COMPOUND_STRING("Wallace"),     2400, 40, 280},
    {COMPOUND_STRING("Drake"),       2100, 25, 200},
    {COMPOUND_STRING("Glacia"),      2000, 22, 176},
    {COMPOUND_STRING("Phoebe"),      1900, 20, 140},
    {COMPOUND_STRING("Sidney"),      1800, 18, 110},
    {COMPOUND_STRING("Vesper"),      1700, 19,  98},
    {COMPOUND_STRING("Juan"),        1500, 19,  98},
    {COMPOUND_STRING("Tate & Liza"), 1400, 15,  80},
    {COMPOUND_STRING("Corsen"),      1300, 12, 104},
    {COMPOUND_STRING("Winona"),      1200, 15,  80},
    {COMPOUND_STRING("Norman"),      1100, 12, 104},
    {COMPOUND_STRING("Ilaria"),       950, 16, 122},
    {COMPOUND_STRING("Flannery"),     850, 14,  88},
    {COMPOUND_STRING("Wattson"),      750, 11, 112},
    {COMPOUND_STRING("Bram"),         600, 15, 130},
    {COMPOUND_STRING("Brawly"),       500, 12, 104},
    {COMPOUND_STRING("Roxanne"),      400, 12, 104},
    {COMPOUND_STRING("Rival"),         10, 150, 590},
    {COMPOUND_STRING("Wally"),          0, 88, 696},
};

static u32 CountPlayerBadges(void)
{
    static const u16 badgeFlags[] =
    {
        FLAG_BADGE01_GET, FLAG_BADGE02_GET, FLAG_BADGE03_GET, FLAG_BADGE04_GET,
        FLAG_BADGE05_GET, FLAG_BADGE06_GET, FLAG_BADGE07_GET, FLAG_BADGE08_GET,
    };
    u32 i, count = 0;

    for (i = 0; i < ARRAY_COUNT(badgeFlags); i++)
        if (FlagGet(badgeFlags[i]))
            count++;
    return count;
}

u32 CitiesRanking_GetNpcCount(void)
{
    return ARRAY_COUNT(sRankedNpcs);
}

const u8 *CitiesRanking_GetNpcName(u32 index)
{
    return sRankedNpcs[index].name;
}

s32 CitiesRanking_GetNpcScore(u32 index)
{
    const struct CitiesRankedNpc *npc = &sRankedNpcs[index];
    s32 score = npc->base + npc->perBadge * CountPlayerBadges();

    if (FlagGet(FLAG_SYS_GAME_CLEAR))
        score += npc->champBonus;
    return score;
}

// 1-based rank; ties go to NPCs, so the player must EXCEED a score to
// pass it — "holding the top" means beating Wallace outright (GDD 8.1).
u32 CitiesRanking_GetPlayerRank(void)
{
    u32 i, rank = 1;
    s32 playerScore = CitiesRanking_GetScore();

    for (i = 0; i < ARRAY_COUNT(sRankedNpcs); i++)
        if (CitiesRanking_GetNpcScore(i) >= playerScore)
            rank++;
    return rank;
}
