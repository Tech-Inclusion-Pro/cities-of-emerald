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

// ---- M5: The Eon Pair (GDD 6.6, approved 2026-09-17) ----

static bool32 M5QuestActive(void)
{
    return FlagGet(FLAG_BADGE08_GET) && VarGet(VAR_CITIES_M5_STATE) < 2;
}

static const u8 *M5QuestStep(void)
{
    bool32 latias = FlagGet(FLAG_CITIES_M5_LATIAS_CAUGHT);
    bool32 latios = FlagGet(FLAG_CITIES_M5_LATIOS_CAUGHT);

    if (VarGet(VAR_CITIES_M5_STATE) == 0)
        return COMPOUND_STRING("A sailor in LILYCOVE's harbor tells\nof two lights over the southern\lsea. Hear him out.");
    if (latias && latios)
        return COMPOUND_STRING("The EON PAIR flies with you! Read\nthe stone in the island grove, and\lvisit the sailor in LILYCOVE.");
    if (latias)
        return COMPOUND_STRING("LATIAS is with you, but won't\nlisten until it's reunited with\lLATIOS on SOUTHERN ISLAND.");
    if (latios)
        return COMPOUND_STRING("LATIOS is with you, but won't\nlisten until it's reunited with\lLATIAS on SOUTHERN ISLAND.");
    return COMPOUND_STRING("Two lights circle SOUTHERN ISLAND.\nThe sailor in LILYCOVE's harbor\lwill take you any time.");
}

// ---- M1-PG: Stranger Weather (GDD 6.6, approved 2026-09-17) ----

static u32 CountM1PGCaught(void)
{
    u32 count = 0;

    if (FlagGet(FLAG_CITIES_M1PG_ARTICUNO_CAUGHT)) count++;
    if (FlagGet(FLAG_CITIES_M1PG_ZAPDOS_CAUGHT))   count++;
    if (FlagGet(FLAG_CITIES_M1PG_MOLTRES_CAUGHT))  count++;
    return count;
}

static bool32 M1PGQuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_M1_STATE) == 2
        && VarGet(VAR_CITIES_M1PG_STATE) < 2;
}

static const u8 *M1PGQuestStep(void)
{
    u32 caught = CountM1PGCaught();

    if (VarGet(VAR_CITIES_M1PG_STATE) == 0)
        return COMPOUND_STRING("The reporter in SLATEPORT's POKéMON\nCENTER has a follow-up to her big\lstory. Hear her out.");
    if (caught == 3)
        return COMPOUND_STRING("Two sets of three! Tell the\nreporter in SLATEPORT's POKéMON\lCENTER how the story ends.");
    ConvertIntToDecimalStringN(gStringVar1, caught, STR_CONV_MODE_LEFT_ALIGN, 1);
    return COMPOUND_STRING("Impossible readings at the old\nsites: FIERY PATH, SHOAL CAVE, and\lNEW MAUVILLE. Calmed: {STR_VAR_1} of 3.");
}

// ---- H1: The Swords of Justice (GDD 6.6, approved 2026-09-17) ----

static u32 CountH1Caught(void)
{
    u32 count = 0;

    if (FlagGet(FLAG_CITIES_H1_COBALION_CAUGHT))  count++;
    if (FlagGet(FLAG_CITIES_H1_TERRAKION_CAUGHT)) count++;
    if (FlagGet(FLAG_CITIES_H1_VIRIZION_CAUGHT))  count++;
    if (FlagGet(FLAG_CITIES_H1_KELDEO_CAUGHT))    count++;
    return count;
}

static bool32 H1QuestActive(void)
{
    // Opens once the ranger is met (GDD 6.6 outline); drops off when done.
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_H1_STATE) == 1;
}

static const u8 *H1QuestStep(void)
{
    u32 caught = CountH1Caught();

    if (caught == 4)
        return COMPOUND_STRING("All four guardians travel with you.\nTell the caretaker in the hollow.");
    if (caught == 3)
        return COMPOUND_STRING("The student, KELDEO, has come to\nthe hollow looking for its\lteachers. It waits in the heart\lof the clearing.");
    ConvertIntToDecimalStringN(gStringVar1, caught, STR_CONV_MODE_LEFT_ALIGN, 1);
    return COMPOUND_STRING("Three guardians keep a hidden\nhollow near LITTLEROOT. The ranger\lat the tree line will walk you in.\lWith you: {STR_VAR_1} of 4.");
}

// ---- H5b: The Lunar Duo (GDD 6.6, approved 2026-09-17) ----

static bool32 H5BQuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_H5B_STATE) == 1;
}

static const u8 *H5BQuestStep(void)
{
    bool32 cresselia = FlagGet(FLAG_CITIES_H5B_CRESSELIA_CAUGHT);
    bool32 darkrai = FlagGet(FLAG_CITIES_H5B_DARKRAI_CAUGHT);

    if (cresselia && darkrai)
        return COMPOUND_STRING("Both dreamers travel with you.\nTell the keeper in MOONRISE COVE.");
    if (cresselia)
        return COMPOUND_STRING("CRESSELIA is with you. DARKRAI\nstill keeps to the dark nook at\lthe back of MOONRISE COVE.");
    if (darkrai)
        return COMPOUND_STRING("DARKRAI is with you. CRESSELIA\nstill rests by the moonpool in\lMOONRISE COVE.");
    return COMPOUND_STRING("DEWFORD can't sleep. Two dreamers\nrest in MOONRISE COVE - the fisher\lon the beach will row you out.");
}

// ---- H10: The Island Guardians (GDD 6.6, approved 2026-09-17) ----

static u32 CountH10Caught(void)
{
    u32 count = 0;

    if (FlagGet(FLAG_CITIES_H10_KOKO_CAUGHT)) count++;
    if (FlagGet(FLAG_CITIES_H10_LELE_CAUGHT)) count++;
    if (FlagGet(FLAG_CITIES_H10_BULU_CAUGHT)) count++;
    if (FlagGet(FLAG_CITIES_H10_FINI_CAUGHT)) count++;
    return count;
}

static bool32 H10QuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_H10_STATE) == 1;
}

static const u8 *H10QuestStep(void)
{
    u32 caught = CountH10Caught();

    if (caught == 4)
        return COMPOUND_STRING("All four guardians travel with you.\nTell the caretaker on SHRINE ATOLL.");
    ConvertIntToDecimalStringN(gStringVar1, caught, STR_CONV_MODE_LEFT_ALIGN, 1);
    return COMPOUND_STRING("Four guardians wait on SHRINE\nATOLL's islets. The elder in\lPACIFIDLOG will raft you out.\lWith you: {STR_VAR_1} of 4.");
}

// ---- H11: The Heart of the Mountain (GDD 6.6, approved 2026-09-17) ----

static bool32 H11QuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_H11_STATE) == 1;
}

static const u8 *H11QuestStep(void)
{
    if (FlagGet(FLAG_CITIES_H11_HEATRAN_CAUGHT))
        return COMPOUND_STRING("The mountain's heart travels with\nyou. Tell the volcanologist in\lEMBER VAULT.");
    return COMPOUND_STRING("Something with a heartbeat sleeps\nunder MT. CHIMNEY. The volcanologist\lat the summit will climb down\lwith you.");
}

// ---- H3: The Colossus Wakes (GDD 6.6, approved 2026-09-17) ----

static bool32 H3QuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_H3_STATE) == 1;
}

static const u8 *H3QuestStep(void)
{
    bool32 eleki = FlagGet(FLAG_CITIES_H3_REGIELEKI_CAUGHT);
    bool32 drago = FlagGet(FLAG_CITIES_H3_REGIDRAGO_CAUGHT);

    if (FlagGet(FLAG_CITIES_H3_REGIGIGAS_CAUGHT))
        return COMPOUND_STRING("The colossus travels with you.\nTell the archaeologist in the\lCOLOSSUS VAULT.");
    if (eleki && drago)
        return COMPOUND_STRING("Both wardens are with you - and\nthe dais is no longer empty. The\lcolossus is awake in the vault.");
    ConvertIntToDecimalStringN(gStringVar1, (eleki ? 1 : 0) + (drago ? 1 : 0), STR_CONV_MODE_LEFT_ALIGN, 1);
    return COMPOUND_STRING("Two wardens keep the COLOSSUS\nVAULT under PETALBURG's hills.\lBefriend both to wake the giant.\lWardens: {STR_VAR_1} of 2.");
}

// ---- H4: Rainbow Wings (GDD 6.6, approved 2026-09-17) ----

static bool32 H4QuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_H4_STATE) == 1;
}

static const u8 *H4QuestStep(void)
{
    bool32 hooh = FlagGet(FLAG_CITIES_H4_HOOH_CAUGHT);
    bool32 lugia = FlagGet(FLAG_CITIES_H4_LUGIA_CAUGHT);

    if (FlagGet(FLAG_CITIES_H4_CELEBI_CAUGHT))
        return COMPOUND_STRING("Sky, sea, and time travel with\nyou. Tell the hiker in FORTREE.");
    if (hooh && lugia)
        return COMPOUND_STRING("Sky and sea are settled - and\nsomething small now waits at the\lmoss shrine in the canopy.");
    ConvertIntToDecimalStringN(gStringVar1, (hooh ? 1 : 0) + (lugia ? 1 : 0), STR_CONV_MODE_LEFT_ALIGN, 1);
    return COMPOUND_STRING("A rainbow lands on one tree above\nFORTREE. The hiker will climb up\lwith you. Settled: {STR_VAR_1} of 2.");
}

// ---- H8: The Weather Menders (GDD 6.6, approved 2026-09-17) ----

static bool32 H8QuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_H8_STATE) == 1;
}

static const u8 *H8QuestStep(void)
{
    u32 trio = 0;

    if (FlagGet(FLAG_CITIES_H8_TORNADUS_CAUGHT))  trio++;
    if (FlagGet(FLAG_CITIES_H8_THUNDURUS_CAUGHT)) trio++;
    if (FlagGet(FLAG_CITIES_H8_LANDORUS_CAUGHT))  trio++;
    if (FlagGet(FLAG_CITIES_H8_ENAMORUS_CAUGHT))
        return COMPOUND_STRING("All four are with you. Tell the\nresearcher in FALLARBOR - she has\lsomething for you.");
    if (trio == 3)
        return COMPOUND_STRING("The storms are settled - and\nspring has come to the empty\lfourth perch on WINDSWEPT RISE.");
    ConvertIntToDecimalStringN(gStringVar1, trio, STR_CONV_MODE_LEFT_ALIGN, 1);
    return COMPOUND_STRING("Three storm forces hold perches\non WINDSWEPT RISE above FALLARBOR.\lSettled: {STR_VAR_1} of 3.");
}

// ---- H6: The Balance Below (GDD 6.6, approved 2026-09-17) ----

static u32 CountH6Cells(void)
{
    u32 count = 0;

    if (FlagGet(FLAG_CITIES_H6_CELL1)) count++;
    if (FlagGet(FLAG_CITIES_H6_CELL2)) count++;
    if (FlagGet(FLAG_CITIES_H6_CELL3)) count++;
    if (FlagGet(FLAG_CITIES_H6_CELL4)) count++;
    if (FlagGet(FLAG_CITIES_H6_CELL5)) count++;
    return count;
}

static bool32 H6QuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_H6_STATE) == 1;
}

static const u8 *H6QuestStep(void)
{
    bool32 xerneas = FlagGet(FLAG_CITIES_H6_XERNEAS_CAUGHT);
    bool32 yveltal = FlagGet(FLAG_CITIES_H6_YVELTAL_CAUGHT);
    u32 cells = CountH6Cells();

    ConvertIntToDecimalStringN(gStringVar1, cells, STR_CONV_MODE_LEFT_ALIGN, 1);
    if (FlagGet(FLAG_CITIES_H6_ZYGARDE_CAUGHT))
    {
        if (cells == 5)
            return COMPOUND_STRING("All three, and every cell. See\nthe ecologist on MOSSDEEP's cliff\ledge - she has something for you.");
        return COMPOUND_STRING("The trio is with you, but green\ncells still glimmer in the\lUNDERCLIFF. Found: {STR_VAR_1} of 5.");
    }
    if (xerneas && yveltal)
        return COMPOUND_STRING("Life and death are settled - and\norder has appeared at the center\lof the UNDERCLIFF.\lCells found: {STR_VAR_1} of 5.");
    return COMPOUND_STRING("The balance tips in the UNDERCLIFF\nbelow MOSSDEEP. The ecologist will\lclimb down with you.\lCells found: {STR_VAR_1} of 5.");
}

// ---- H7: Truth and Ideals (GDD 6.6, approved 2026-09-17) ----

static bool32 H7QuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_H7_STATE) == 1;
}

static const u8 *H7QuestStep(void)
{
    bool32 reshiram = FlagGet(FLAG_CITIES_H7_RESHIRAM_CAUGHT);
    bool32 zekrom = FlagGet(FLAG_CITIES_H7_ZEKROM_CAUGHT);

    if (FlagGet(FLAG_CITIES_H7_KYUREM_CAUGHT))
        return COMPOUND_STRING("Truth, ideals, and the husk all\ntravel with you. See the engineer\lin MAUVILLE - he found something.");
    if (reshiram && zekrom)
        return COMPOUND_STRING("The argument under MAUVILLE is\nsettled - and something cold now\lwaits at the hall's north end.");
    ConvertIntToDecimalStringN(gStringVar1, (reshiram ? 1 : 0) + (zekrom ? 1 : 0), STR_CONV_MODE_LEFT_ALIGN, 1);
    return COMPOUND_STRING("Two currents argue in RESONANCE\nHALL under MAUVILLE. The engineer\lwill take you down. Settled:\l{STR_VAR_1} of 2.");
}

// ---- H9: The Old Heroes (GDD 6.6, approved 2026-09-17) ----

static u32 CountH9Caught(void)
{
    u32 count = 0;

    if (FlagGet(FLAG_CITIES_H9_ZACIAN_CAUGHT))    count++;
    if (FlagGet(FLAG_CITIES_H9_ZAMAZENTA_CAUGHT)) count++;
    if (FlagGet(FLAG_CITIES_H9_GLASTRIER_CAUGHT)) count++;
    if (FlagGet(FLAG_CITIES_H9_SPECTRIER_CAUGHT)) count++;
    if (FlagGet(FLAG_CITIES_H9_CALYREX_CAUGHT))   count++;
    if (FlagGet(FLAG_CITIES_H9_KUBFU_CAUGHT))     count++;
    return count;
}

static bool32 H9QuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_H9_STATE) == 1;
}

static const u8 *H9QuestStep(void)
{
    bool32 steeds = FlagGet(FLAG_CITIES_H9_GLASTRIER_CAUGHT)
                 && FlagGet(FLAG_CITIES_H9_SPECTRIER_CAUGHT);
    u32 caught = CountH9Caught();

    if (caught == 6)
        return COMPOUND_STRING("All six heroes walk with you.\nSee the elder in VERDANTURF - he\lhas their relics for you.");
    ConvertIntToDecimalStringN(gStringVar1, caught, STR_CONV_MODE_LEFT_ALIGN, 1);
    if (steeds && !FlagGet(FLAG_CITIES_H9_CALYREX_CAUGHT))
        return COMPOUND_STRING("Both steeds are with you - and\nthe king has returned to the\lmeadow's crown. With you: {STR_VAR_1} of 6.");
    return COMPOUND_STRING("Old heroes rest in a meadow past\nVERDANTURF. The elder will walk\lyou in. With you: {STR_VAR_1} of 6.");
}

// ---- H2a/H2b: the Forgotten Garden (GDD 6.6, split approved 2026-09-17) ----

static u32 CountH2ACaught(void)
{
    u32 count = 0;

    if (FlagGet(FLAG_CITIES_H2A_WOCHIEN_CAUGHT))  count++;
    if (FlagGet(FLAG_CITIES_H2A_CHIENPAO_CAUGHT)) count++;
    if (FlagGet(FLAG_CITIES_H2A_TINGLU_CAUGHT))   count++;
    if (FlagGet(FLAG_CITIES_H2A_CHIYU_CAUGHT))    count++;
    return count;
}

static bool32 H2AQuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_H2A_STATE) == 1;
}

static const u8 *H2AQuestStep(void)
{
    u32 caught = CountH2ACaught();

    if (caught == 4)
        return COMPOUND_STRING("All four grudges are laid down.\nTell the gardener in OLDALE.");
    ConvertIntToDecimalStringN(gStringVar1, caught, STR_CONV_MODE_LEFT_ALIGN, 1);
    return COMPOUND_STRING("Four unsealed stelae stand in the\nFORGOTTEN GARDEN's courtyard. The\lgardener in OLDALE will walk you\lin. Faced: {STR_VAR_1} of 4.");
}

static bool32 H2BQuestActive(void)
{
    return FlagGet(FLAG_SYS_GAME_CLEAR) && VarGet(VAR_CITIES_H2B_STATE) == 1;
}

static const u8 *H2BQuestStep(void)
{
    u32 three = 0;

    if (FlagGet(FLAG_CITIES_H2B_OKIDOGI_CAUGHT))     three++;
    if (FlagGet(FLAG_CITIES_H2B_MUNKIDORI_CAUGHT))   three++;
    if (FlagGet(FLAG_CITIES_H2B_FEZANDIPITI_CAUGHT)) three++;
    if (FlagGet(FLAG_CITIES_H2B_OGERPON_CAUGHT))
        return COMPOUND_STRING("The masked one chose you. Tell\nthe gardener in OLDALE the true\lstory's ending.");
    if (three == 3)
        return COMPOUND_STRING("The false heroes are gone - and\nthe masked one has stepped out at\lthe shrine in the grove.");
    ConvertIntToDecimalStringN(gStringVar1, three, STR_CONV_MODE_LEFT_ALIGN, 1);
    return COMPOUND_STRING("Three 'heroes' hold the grove in\nthe FORGOTTEN GARDEN - and someone\lwronged still hides there.\lFaced: {STR_VAR_1} of 3.");
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
    { COMPOUND_STRING("The Eon Pair"),        M5QuestActive,         M5QuestStep },
    { COMPOUND_STRING("Stranger Weather"),    M1PGQuestActive,       M1PGQuestStep },
    { COMPOUND_STRING("The Swords of Justice"), H1QuestActive,       H1QuestStep },
    { COMPOUND_STRING("The Lunar Duo"),       H5BQuestActive,        H5BQuestStep },
    { COMPOUND_STRING("The Island Guardians"), H10QuestActive,       H10QuestStep },
    { COMPOUND_STRING("The Heart of the Mountain"), H11QuestActive,  H11QuestStep },
    { COMPOUND_STRING("The Colossus Wakes"),  H3QuestActive,         H3QuestStep },
    { COMPOUND_STRING("Rainbow Wings"),       H4QuestActive,         H4QuestStep },
    { COMPOUND_STRING("The Weather Menders"), H8QuestActive,         H8QuestStep },
    { COMPOUND_STRING("The Balance Below"),   H6QuestActive,         H6QuestStep },
    { COMPOUND_STRING("Truth and Ideals"),    H7QuestActive,         H7QuestStep },
    { COMPOUND_STRING("The Old Heroes"),      H9QuestActive,         H9QuestStep },
    { COMPOUND_STRING("The Chained Ruin"),    H2AQuestActive,        H2AQuestStep },
    { COMPOUND_STRING("The Mask in the Grove"), H2BQuestActive,      H2BQuestStep },
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
