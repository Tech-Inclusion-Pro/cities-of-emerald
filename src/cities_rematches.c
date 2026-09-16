#include "global.h"
#include "cities_rematches.h"
#include "battle_setup.h"
#include "event_data.h"
#include "constants/flags.h"
#include "constants/opponents.h"
#include "constants/rematches.h"
#include "constants/vars.h"
#include "data/cities_rival_rematch_parties.h"

// GDD 7.3: postgame rematch versions for gym leaders and the rival.
//
// Gym leaders ride the vanilla rematch machinery: the script special below
// arms gSaveBlock1Ptr->trainerRematches[], and GetRematchTrainerIdFromTable
// already serves the lowest _2.._5 ID whose trainer flag is unset — exactly
// "the next unbeaten version". CitiesIsGymRematchVersionLocked() clamps that
// walk so a version past the story unlock is treated as not existing, which
// also makes a fully-cleared tier repeat the highest unlocked version
// (repeats earn no ranking points because the trainer flag is already set).

u32 CitiesRematchVersionsUnlocked(void)
{
    if (!FlagGet(FLAG_SYS_GAME_CLEAR))
        return 0;
    if (FlagGet(FLAG_CITIES_POSTGAME_THREAD1_COMPLETE) && FlagGet(FLAG_CITIES_POSTGAME_THREAD2_COMPLETE))
        return 3;
    if (FlagGet(FLAG_CITIES_POSTGAME_THREAD1_MIDPOINT))
        return 2;
    return 1;
}

// rematchIndex is the index into RematchTrainer.trainerIds: 1 = V1 (_2),
// 2 = V2 (_3), 3 = V3 (_4). Index 4 (_5) is held back for a possible V4.
bool32 CitiesIsGymRematchVersionLocked(s32 rematchTableId, s32 rematchIndex)
{
    if (rematchTableId < REMATCH_ROXANNE || rematchTableId > REMATCH_JUAN)
        return FALSE;
    return rematchIndex > (s32)CitiesRematchVersionsUnlocked();
}

// The ID the rematch machinery would serve for this leader right now.
u16 CitiesGetGymRematchServeId(u16 firstBattleTrainerId)
{
    return GetRematchTrainerIdFromTable(gRematchTable, firstBattleTrainerId);
}

// Special (specialvar): offer a gym rematch? Reads the leader's _1 ID from
// VAR_TRAINER_BATTLE_OPPONENT_A, set by the trainerbattle_* command or the
// script just before the check — same contract as vanilla's
// ShouldTryRematchBattle. Arms the rematch slot so the follow-up
// trainerbattle_rematch_double serves the clamped version.
bool8 Script_CitiesTryGymRematch(void)
{
    s32 tableId = FirstBattleTrainerIdToRematchTableId(gRematchTable, TRAINER_BATTLE_PARAM.opponentA);

    if (tableId < REMATCH_ROXANNE || tableId > REMATCH_JUAN)
        return FALSE;
    if (CitiesRematchVersionsUnlocked() == 0)
        return FALSE;

    gSaveBlock1Ptr->trainerRematches[tableId] = 1; // "wants rematch"; cleared on battle end
    return TRUE;
}

bool32 CitiesIsRivalRematchTrainer(u16 trainerId)
{
    return trainerId == TRAINER_BRENDAN_PLACEHOLDER || trainerId == TRAINER_MAY_PLACEHOLDER;
}

static u16 RivalVersionBeatenFlag(u32 version)
{
    switch (version)
    {
    case 1: return FLAG_CITIES_RIVAL_REMATCH_V1_BEATEN;
    case 2: return FLAG_CITIES_RIVAL_REMATCH_V2_BEATEN;
    default: return FLAG_CITIES_RIVAL_REMATCH_V3_BEATEN;
    }
}

// Special (specialvar): pick and arm the rival rematch version. Returns the
// version to fight (1..3) — the lowest unlocked version not yet beaten, or
// the highest unlocked one as a repeat — or 0 when nothing is unlocked.
u16 Script_CitiesArmRivalRematch(void)
{
    u32 version, unlocked = CitiesRematchVersionsUnlocked();

    if (unlocked == 0)
    {
        VarSet(VAR_CITIES_RIVAL_REMATCH_VERSION, 0);
        return 0;
    }
    for (version = 1; version <= unlocked; version++)
    {
        if (!FlagGet(RivalVersionBeatenFlag(version)))
            break;
    }
    if (version > unlocked)
        version = unlocked; // every unlocked version beaten: repeat the newest
    VarSet(VAR_CITIES_RIVAL_REMATCH_VERSION, version);
    return version;
}

// GDD 8.2: each version earns ranking points once. Used by the ranking
// engine instead of the trainer flag, because all three rival versions
// share one trainer ID per gender.
bool32 CitiesRivalRematchWinEligible(void)
{
    u32 version = VarGet(VAR_CITIES_RIVAL_REMATCH_VERSION);

    if (version < 1 || version > CITIES_REMATCH_VERSIONS_MAX)
        return FALSE;
    return !FlagGet(RivalVersionBeatenFlag(version));
}

// Specials for the pre-battle notice (GDD 8.2): will the upcoming rematch
// earn points? For gyms the served version's own trainer flag decides; the
// script runs this while VAR_TRAINER_BATTLE_OPPONENT_A still holds the _1 ID.
bool8 Script_CitiesGymRematchWillScore(void)
{
    return !HasTrainerBeenFought(CitiesGetGymRematchServeId(TRAINER_BATTLE_PARAM.opponentA));
}

bool8 Script_CitiesRivalRematchWillScore(void)
{
    return CitiesRivalRematchWinEligible();
}

// Special: called from the Route 103 script after a rematch win.
void Script_CitiesRivalRematchWon(void)
{
    u32 version = VarGet(VAR_CITIES_RIVAL_REMATCH_VERSION);

    if (version >= 1 && version <= CITIES_REMATCH_VERSIONS_MAX)
        FlagSet(RivalVersionBeatenFlag(version));
    VarSet(VAR_CITIES_RIVAL_REMATCH_VERSION, 0);
}
