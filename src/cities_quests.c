#include "global.h"
#include "cities_quests.h"
#include "cities_arcs.h"
#include "cities_m3.h"
#include "battle_setup.h"
#include "cities_field_events.h"
#include "event_data.h"
#include "string_util.h"
#include "constants/flags.h"
#include "constants/opponents.h"
#include "constants/vars.h"

// GDD 11.4 / Phase 9 (approved 2026-09-16): quest journal at major-beat
// granularity. Every stage is computed from flags at read time — no save
// data. Each quest exposes a name, an "is active" check, and a
// plain-language next step. Story arcs (Phases 10-12) register their
// quests here as they are written.

extern const u8 Cities_EventScript_Recap[];
extern const u8 Cities_EventScript_BecameMaster[];

// ---- Main story (one entry per big goal) ----

struct CitiesMainStage
{
    u16 doneFlag;      // stage is past once this flag is set
    const u8 *step;
};

// Checked in order; the first stage whose doneFlag is unset is current.
static const struct CitiesMainStage sMainStages[] =
{
    { FLAG_SYS_POKEMON_GET,
      COMPOUND_STRING("Help PROF. BIRCH on Route 101 and\nchoose your first partner.") },
    { FLAG_BADGE01_GET,
      COMPOUND_STRING("Win your first GYM BADGE from\nROXANNE in RUSTBORO CITY.") },
    { FLAG_BADGE02_GET,
      COMPOUND_STRING("Sail with MR. BRINEY from Route 104\nand beat BRAWLY in DEWFORD TOWN.") },
    { FLAG_BADGE03_GET,
      COMPOUND_STRING("Deliver the DEVON GOODS to SLATEPORT\nCITY, then beat WATTSON in MAUVILLE.") },
    { FLAG_BADGE04_GET,
      COMPOUND_STRING("Climb MT. CHIMNEY, then take the ash\nroad down to LAVARIDGE TOWN and\lbeat FLANNERY.") },
    { FLAG_BADGE05_GET,
      COMPOUND_STRING("Return to PETALBURG CITY and beat\nyour dad, NORMAN.") },
    { FLAG_BADGE06_GET,
      COMPOUND_STRING("Head east through rainy Route 119 to\nFORTREE CITY and beat WINONA.") },
    { FLAG_BADGE07_GET,
      COMPOUND_STRING("Follow the trouble to LILYCOVE and\nMT. PYRE, then beat TATE & LIZA in\lMOSSDEEP CITY.") },
    { FLAG_BADGE08_GET,
      COMPOUND_STRING("Stop the crisis under the sea, calm\nSOOTOPOLIS, and beat JUAN for your\llast BADGE.") },
    { FLAG_SYS_GAME_CLEAR,
      COMPOUND_STRING("Cross VICTORY ROAD and take on the\nPOKéMON LEAGUE at EVER GRANDE CITY.") },
};

static const u8 *const sText_MainPostgame =
    COMPOUND_STRING("You're the CHAMPION! Climb the\nnational rankings - rematches and\lchallengers are waiting.");

static const u8 *MainQuestStep(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sMainStages); i++)
        if (!FlagGet(sMainStages[i].doneFlag))
            return sMainStages[i].step;
    return sText_MainPostgame;
}

static bool32 MainQuestActive(void)
{
    return TRUE;
}

// ---- The Eevee experts (GDD 4.3) ----

static const u16 sEeveeTrainers[] =
{
    TRAINER_CITIES_EEVEE_VAPOREON, TRAINER_CITIES_EEVEE_JOLTEON,
    TRAINER_CITIES_EEVEE_FLAREON,  TRAINER_CITIES_EEVEE_ESPEON,
    TRAINER_CITIES_EEVEE_LEAFEON,  TRAINER_CITIES_EEVEE_SYLVEON,
    TRAINER_CITIES_EEVEE_UMBREON,  TRAINER_CITIES_EEVEE_GLACEON,
};

static u32 CountEeveeTrainersBeaten(void)
{
    u32 i, count = 0;

    for (i = 0; i < ARRAY_COUNT(sEeveeTrainers); i++)
        if (HasTrainerBeenFought(sEeveeTrainers[i]))
            count++;
    return count;
}

static bool32 EeveeQuestActive(void)
{
    return FlagGet(FLAG_BADGE02_GET) && CountEeveeTrainersBeaten() < ARRAY_COUNT(sEeveeTrainers);
}

static const u8 *EeveeQuestStep(void)
{
    if (!FlagGet(FLAG_CITIES_DEWFORD_STONE_GIVEN))
        return COMPOUND_STRING("Meet the stone expert in DEWFORD\nTOWN. She has a gift for you.");
    ConvertIntToDecimalStringN(gStringVar1, CountEeveeTrainersBeaten(), STR_CONV_MODE_LEFT_ALIGN, 1);
    return COMPOUND_STRING("Battle all eight Eeveelution experts\nacross Hoenn. So far: {STR_VAR_1} of 8.");
}

// ---- M1: Strange Weather (GDD 6.6, approved 2026-09-16) ----

static u32 CountM1Caught(void)
{
    u32 count = 0;

    if (FlagGet(FLAG_CITIES_M1_ARTICUNO_CAUGHT)) count++;
    if (FlagGet(FLAG_CITIES_M1_ZAPDOS_CAUGHT))   count++;
    if (FlagGet(FLAG_CITIES_M1_MOLTRES_CAUGHT))  count++;
    return count;
}

static bool32 M1QuestActive(void)
{
    return FlagGet(FLAG_BADGE03_GET) && VarGet(VAR_CITIES_M1_STATE) < 2;
}

static const u8 *M1QuestStep(void)
{
    u32 caught = CountM1Caught();

    if (caught == 3)
        return COMPOUND_STRING("The weather has calmed! Tell the\nreporter in SLATEPORT's POKéMON\lCENTER what you found.");
    ConvertIntToDecimalStringN(gStringVar1, caught, STR_CONV_MODE_LEFT_ALIGN, 1);
    if (caught > 0 && !FlagGet(FLAG_BADGE04_GET))
        return COMPOUND_STRING("Strange weather: FIERY PATH, SHOAL\nCAVE (SURF), NEW MAUVILLE (SURF).\lCalmed: {STR_VAR_1} of 3. Your bird won't\llisten until you earn the HEAT BADGE.");
    return COMPOUND_STRING("Strange weather! Check FIERY PATH,\nSHOAL CAVE (SURF), and NEW MAUVILLE\l(SURF). Calmed: {STR_VAR_1} of 3.");
}

// ---- M2: The Sealed Chamber, Opened (GDD 6.6, approved 2026-09-16) ----

static bool32 M2QuestActive(void)
{
    return FlagGet(FLAG_BADGE05_GET) && VarGet(VAR_CITIES_M2_STATE) < 2;
}

static const u8 *M2QuestStep(void)
{
    if (VarGet(VAR_CITIES_M2_STATE) == 0)
        return COMPOUND_STRING("An archaeologist in PACIFIDLOG TOWN\nknows the SEALED CHAMBER's secret.\lVisit her (the house on the west\lside).");
    if (CitiesArcAllCaught(CITIES_ARC_M2))
        return COMPOUND_STRING("All three giants are with you!\nTell the archaeologist in\lPACIFIDLOG TOWN.");
    return COMPOUND_STRING("DIVE under Route 134 to the SEALED\nCHAMBER. One wall wants DIG; the\ldeep room wants WAILORD first and\lRELICANTH last. Then three ancient\ldoors open across HOENN.");
}

// ---- M3: On the Trail (GDD 6.6, approved 2026-09-17) ----

static u32 CountM3Caught(void)
{
    u32 beast, count = 0;

    for (beast = 0; beast < CITIES_M3_BEAST_COUNT; beast++)
        if (CitiesM3BeastCaught(beast))
            count++;
    return count;
}

static bool32 M3QuestActive(void)
{
    return FlagGet(FLAG_BADGE06_GET) && VarGet(VAR_CITIES_M3_STATE) < 2;
}

static const u8 *M3QuestStep(void)
{
    if (VarGet(VAR_CITIES_M3_STATE) == 0)
        return COMPOUND_STRING("A RANGER in FORTREE's POKéMON\nCENTER is tracking three strange\lvisitors. Ask her about them.");
    if (CitiesArcAllCaught(CITIES_ARC_M3))
        return COMPOUND_STRING("All three beasts run with you now!\nTell the RANGER in FORTREE CITY.");
    // Live positions, one line per beast (built into STR_VAR_1).
    CitiesM3BufferChaseStatus(gStringVar1);
    if (CountM3Caught() > 0 && !FlagGet(FLAG_BADGE07_GET))
        return COMPOUND_STRING("{STR_VAR_1}\pYour beast won't listen until you\nearn the MIND BADGE.");
    return COMPOUND_STRING("{STR_VAR_1}");
}

// ---- M4: The Three Lights (GDD 6.6, approved 2026-09-17) ----

static u32 CountM4Caught(void)
{
    u32 count = 0;

    if (FlagGet(FLAG_CITIES_M4_UXIE_CAUGHT))    count++;
    if (FlagGet(FLAG_CITIES_M4_MESPRIT_CAUGHT)) count++;
    if (FlagGet(FLAG_CITIES_M4_AZELF_CAUGHT))   count++;
    return count;
}

static bool32 M4QuestActive(void)
{
    return FlagGet(FLAG_BADGE07_GET) && VarGet(VAR_CITIES_M4_STATE) < 2;
}

static const u8 *M4QuestStep(void)
{
    u32 caught = CountM4Caught();

    if (VarGet(VAR_CITIES_M4_STATE) == 0)
        return COMPOUND_STRING("A keeper waits inside the CAVE OF\nORIGIN's entrance, in SOOTOPOLIS.\lShe knows the mountain's story.");
    if (caught == 3)
        return COMPOUND_STRING("Mind, heart, and will are with\nyou. Tell the keeper at the CAVE\lOF ORIGIN's entrance.");
    ConvertIntToDecimalStringN(gStringVar1, caught, STR_CONV_MODE_LEFT_ALIGN, 1);
    if (caught > 0 && !FlagGet(FLAG_BADGE08_GET))
        return COMPOUND_STRING("Three lights rest beyond the\nparted wall in the CAVE OF ORIGIN.\lFound: {STR_VAR_1} of 3. Your spirit won't\llisten until you earn the RAIN\lBADGE.");
    return COMPOUND_STRING("Three lights rest beyond the\nparted wall in the CAVE OF ORIGIN\l(far right corner of the first\lcave). Found: {STR_VAR_1} of 3.");
}

// ---- Ranked challengers (GDD 8.5) ----

static const u16 sChallengers[] =
{
    TRAINER_CITIES_CHALLENGER_BRAM, TRAINER_CITIES_CHALLENGER_ILARIA,
    TRAINER_CITIES_CHALLENGER_CORSEN, TRAINER_CITIES_CHALLENGER_VESPER,
};

static u32 CountChallengersBeaten(void)
{
    u32 i, count = 0;

    for (i = 0; i < ARRAY_COUNT(sChallengers); i++)
        if (HasTrainerBeenFought(sChallengers[i]))
            count++;
    return count;
}

static bool32 ChallengerQuestActive(void)
{
    return FlagGet(FLAG_BADGE03_GET) && CountChallengersBeaten() < ARRAY_COUNT(sChallengers);
}

static const u8 *ChallengerQuestStep(void)
{
    ConvertIntToDecimalStringN(gStringVar1, CountChallengersBeaten(), STR_CONV_MODE_LEFT_ALIGN, 1);
    return COMPOUND_STRING("Ranked trainers wait along your way:\nRoute 110, Route 119, Route 121, and\lEVER GRANDE CITY. Beaten: {STR_VAR_1} of 4.");
}

// ---- Postgame rematch versions (GDD 7.3) ----

static bool32 RematchQuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR);
}

static const u8 *RematchQuestStep(void)
{
    return COMPOUND_STRING("Rematch the GYM LEADERS in their\ngyms and your rival on Route 103.\lStronger versions unlock as you\lexplore the postgame.");
}

// ---- Road to Pokémon Master (GDD 8.1) ----

static bool32 MasterQuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && !FlagGet(FLAG_CITIES_POKEMON_MASTER);
}

static const u8 *MasterQuestStep(void)
{
    return COMPOUND_STRING("Hold the top score in the national\nrankings to become the POKéMON\lMASTER. Check START > RANKING.");
}

// ---- Journal ----

struct CitiesQuest
{
    const u8 *name;
    bool32 (*isActive)(void);
    const u8 *(*getStep)(void);
};

static const struct CitiesQuest sQuests[] =
{
    { COMPOUND_STRING("The Hoenn Journey"),   MainQuestActive,       MainQuestStep },
    { COMPOUND_STRING("The Eevee Experts"),   EeveeQuestActive,      EeveeQuestStep },
    { COMPOUND_STRING("Strange Weather"),     M1QuestActive,         M1QuestStep },
    { COMPOUND_STRING("The Sealed Door"),     M2QuestActive,         M2QuestStep },
    { COMPOUND_STRING("On the Trail"),        M3QuestActive,         M3QuestStep },
    { COMPOUND_STRING("The Three Lights"),    M4QuestActive,         M4QuestStep },
    { COMPOUND_STRING("Ranked Challengers"),  ChallengerQuestActive, ChallengerQuestStep },
    { COMPOUND_STRING("Stronger Rematches"),  RematchQuestActive,    RematchQuestStep },
    { COMPOUND_STRING("Road to Master"),      MasterQuestActive,     MasterQuestStep },
};

// Special (specialvar): walk the active quests using VAR_TEMP_9 as cursor.
// Buffers name into STR_VAR_2 and the step into STR_VAR_3. The step may
// itself use STR_VAR_1 for a count, so that one stays free.
bool8 Script_CitiesBufferNextJournalEntry(void)
{
    u32 i, active = 0, wanted = VarGet(VAR_TEMP_9);

    for (i = 0; i < ARRAY_COUNT(sQuests); i++)
    {
        if (!sQuests[i].isActive())
            continue;
        if (active == wanted)
        {
            StringCopy(gStringVar2, sQuests[i].name);
            // Steps may embed {STR_VAR_1} counts; expansion is not
            // recursive at print time, so expand here.
            StringExpandPlaceholders(gStringVar3, sQuests[i].getStep());
            return TRUE;
        }
        active++;
    }
    return FALSE;
}

// Special: the hint (GDD 11.4) is the main quest's next step.
void Script_CitiesBufferMainQuestStep(void)
{
    StringExpandPlaceholders(gStringVar3, MainQuestStep());
}

// GDD 11.4 "last time" recap: queued on continue, shown once the player
// has control. If the Master announcement was earned but never shown
// (saved before regaining control), it takes priority.
void CitiesOnContinueGame(void)
{
    if (FlagGet(FLAG_CITIES_POKEMON_MASTER) && !FlagGet(FLAG_CITIES_MASTER_ANNOUNCED))
        CitiesQueueFieldScript(Cities_EventScript_BecameMaster);
    else
        CitiesQueueFieldScript(Cities_EventScript_Recap);
}
