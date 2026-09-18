InsideOfTruck_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, InsideOfTruck_OnLoad
	map_script MAP_SCRIPT_ON_RESUME, InsideOfTruck_OnResume
	.byte 0

InsideOfTruck_OnLoad:
	setmetatile 4, 1, METATILE_InsideOfTruck_ExitLight_Top, FALSE
	setmetatile 4, 2, METATILE_InsideOfTruck_ExitLight_Mid, FALSE
	setmetatile 4, 3, METATILE_InsideOfTruck_ExitLight_Bottom, FALSE
	end

InsideOfTruck_OnResume:
	setstepcallback STEP_CB_TRUCK
	end

InsideOfTruck_EventScript_SetIntroFlags::
	lockall
@ Cities of Emerald (GDD 4.1/10): the setup conversation runs before the
@ journey begins. Difficulty, then Assist mode with a level cap choice.
	call InsideOfTruck_EventScript_CitiesSetup
	setflag FLAG_HIDE_MAP_NAME_POPUP
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, InsideOfTruck_EventScript_SetIntroFlagsMale
	goto_if_eq VAR_RESULT, FEMALE, InsideOfTruck_EventScript_SetIntroFlagsFemale
	end

InsideOfTruck_EventScript_SetIntroFlagsMale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
	setvar VAR_LITTLEROOT_INTRO_STATE, 1
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_SIBLING
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 1
	setdynamicwarp MAP_LITTLEROOT_TOWN, 3, 10
	releaseall
	end

InsideOfTruck_EventScript_SetIntroFlagsFemale::
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F
	setvar VAR_LITTLEROOT_INTRO_STATE, 2
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_MOM
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_SIBLING
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 1
	setdynamicwarp MAP_LITTLEROOT_TOWN, 12, 10
	releaseall
	end

InsideOfTruck_EventScript_MovingBox::
	msgbox InsideOfTruck_Text_BoxPrintedWithMonLogo, MSGBOX_SIGN
	end

InsideOfTruck_Text_BoxPrintedWithMonLogo:
	.string "The box is printed with a POKéMON logo.\p"
	.string "It's a POKéMON brand moving and\n"
	.string "delivery service.$"


InsideOfTruck_EventScript_CitiesSetup::
	msgbox InsideOfTruck_Text_SetupIntro, MSGBOX_DEFAULT
	message InsideOfTruck_Text_ChoosePreset
	waitmessage
	multichoice 0, 0, MULTI_CITIES_ACCESS_PRESET, TRUE
	special Script_CitiesApplyPreset
InsideOfTruck_EventScript_CitiesSetupPronoun::
	message InsideOfTruck_Text_ChoosePronoun
	waitmessage
	multichoice 0, 0, MULTI_CITIES_PRONOUN, FALSE
	switch VAR_RESULT
	case 0, InsideOfTruck_EventScript_PronounHe
	case 1, InsideOfTruck_EventScript_PronounShe
	case 2, InsideOfTruck_EventScript_PronounThey
	case 3, InsideOfTruck_EventScript_PronounCustom
	case MULTI_B_PRESSED, InsideOfTruck_EventScript_PronounThey
	goto InsideOfTruck_EventScript_CitiesSetupDifficulty

InsideOfTruck_EventScript_PronounHe::
	setvar VAR_0x8004, 0
	special Script_CitiesSetPronounPreset
	goto InsideOfTruck_EventScript_CitiesSetupDifficulty

InsideOfTruck_EventScript_PronounShe::
	setvar VAR_0x8004, 1
	special Script_CitiesSetPronounPreset
	goto InsideOfTruck_EventScript_CitiesSetupDifficulty

InsideOfTruck_EventScript_PronounThey::
	setvar VAR_0x8004, 2
	special Script_CitiesSetPronounPreset
	goto InsideOfTruck_EventScript_CitiesSetupDifficulty

InsideOfTruck_EventScript_PronounCustom::
	special Script_CitiesEnterCustomPronoun
	waitstate
	goto InsideOfTruck_EventScript_CitiesSetupDifficulty

InsideOfTruck_EventScript_CitiesSetupDifficulty::
	message InsideOfTruck_Text_ChooseDifficulty
	waitmessage
	multichoice 0, 0, MULTI_CITIES_DIFFICULTY, TRUE
	switch VAR_RESULT
	case 0, InsideOfTruck_EventScript_SetEasy
	case 1, InsideOfTruck_EventScript_SetNormal
	case 2, InsideOfTruck_EventScript_SetHard
	goto InsideOfTruck_EventScript_CitiesSetupDifficulty

InsideOfTruck_EventScript_SetEasy::
	setvar VAR_CITIES_DIFFICULTY, 0
	goto InsideOfTruck_EventScript_CitiesSetupAssist

InsideOfTruck_EventScript_SetNormal::
	setvar VAR_CITIES_DIFFICULTY, 1
	goto InsideOfTruck_EventScript_CitiesSetupAssist

InsideOfTruck_EventScript_SetHard::
	setvar VAR_CITIES_DIFFICULTY, 2
	goto InsideOfTruck_EventScript_CitiesSetupAssist

InsideOfTruck_EventScript_CitiesSetupAssist::
	msgbox InsideOfTruck_Text_AssistExplain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, InsideOfTruck_EventScript_CitiesSetupChallenge
	setflag FLAG_CITIES_ASSIST_MODE
	message InsideOfTruck_Text_ChooseLevelCap
	waitmessage
	multichoice 0, 0, MULTI_CITIES_LEVEL_CAP, TRUE
	switch VAR_RESULT
	case 0, InsideOfTruck_EventScript_CapKeep
	case 1, InsideOfTruck_EventScript_CapRaise
	case 2, InsideOfTruck_EventScript_CapRemove
	goto InsideOfTruck_EventScript_CitiesSetupChallenge

InsideOfTruck_EventScript_CapKeep::
	setvar VAR_CITIES_LEVEL_CAP, 0
	goto InsideOfTruck_EventScript_CitiesSetupChallenge

InsideOfTruck_EventScript_CapRaise::
	setvar VAR_CITIES_LEVEL_CAP, 1
	goto InsideOfTruck_EventScript_CitiesSetupChallenge

InsideOfTruck_EventScript_CapRemove::
	setvar VAR_CITIES_LEVEL_CAP, 100
	goto InsideOfTruck_EventScript_CitiesSetupChallenge

InsideOfTruck_EventScript_CitiesSetupChallenge::
	msgbox InsideOfTruck_Text_NuzlockeExplain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, InsideOfTruck_EventScript_CitiesSetupRandomizer
	setvar VAR_0x8004, 1
	special Script_CitiesSetNuzlocke
	msgbox InsideOfTruck_Text_NuzlockeOn, MSGBOX_DEFAULT
InsideOfTruck_EventScript_CitiesSetupRandomizer::
	msgbox InsideOfTruck_Text_RandomizerExplain, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, InsideOfTruck_EventScript_CitiesSetupDone
	setvar VAR_0x8004, 1
	special Script_CitiesSetRandomizer
	msgbox InsideOfTruck_Text_RandomizerOn, MSGBOX_DEFAULT
	goto InsideOfTruck_EventScript_CitiesSetupDone

InsideOfTruck_EventScript_CitiesSetupDone::
	msgbox InsideOfTruck_Text_SetupDone, MSGBOX_DEFAULT
	return

InsideOfTruck_Text_NuzlockeExplain:
	.string "Now, two optional challenges.\p"
	.string "NUZLOCKE mode: only your first\n"
	.string "catch in each area, and a fainted\l"
	.string "POKéMON is laid to rest for good.\p"
	.string "Turn on NUZLOCKE mode?$"

InsideOfTruck_Text_NuzlockeOn:
	.string "NUZLOCKE mode is on. Duplicate and\n"
	.string "shiny clauses are on too. Be brave.$"

InsideOfTruck_Text_RandomizerExplain:
	.string "RANDOMIZER mode: wild POKéMON,\n"
	.string "your starter, and TRAINER teams\l"
	.string "are all shuffled.\p"
	.string "Legendary and story POKéMON are\n"
	.string "never shuffled in.\p"
	.string "Turn on RANDOMIZER mode?$"

InsideOfTruck_Text_RandomizerOn:
	.string "RANDOMIZER mode is on. Expect the\n"
	.string "unexpected!$"

InsideOfTruck_Text_ChoosePronoun:
	.string "What pronouns do you use?\p"
	.string "This is just for you - your look is\n"
	.string "a separate choice, so pick whatever\l"
	.string "feels right.$"

InsideOfTruck_Text_SetupIntro:
	.string "Welcome!\p"
	.string "Before your journey begins, let's\n"
	.string "set up the game your way.\p"
	.string "There are no wrong answers.$"

InsideOfTruck_Text_ChoosePreset:
	.string "First: accessibility.\p"
	.string "A preset turns on a group of\n"
	.string "helpful settings at once.\p"
	.string "You can change every setting later\n"
	.string "in the ACCESS menu. Choose one:$"

InsideOfTruck_Text_ChooseDifficulty:
	.string "How challenging should battles be?\p"
	.string "Easy: relaxed battles.\n"
	.string "Normal: the intended balance.\l"
	.string "Hard: stronger, smarter trainers.$"

InsideOfTruck_Text_AssistExplain:
	.string "Next: Assist mode.\p"
	.string "With Assist mode on, losing a\n"
	.string "battle never costs you money.\p"
	.string "You can also loosen the level\n"
	.string "caps that keep battles fair.\p"
	.string "Turn on Assist mode?$"

InsideOfTruck_Text_ChooseLevelCap:
	.string "How should level caps work?\p"
	.string "Keep: caps follow your badges.\n"
	.string "Raise: caps are 10 levels higher.\l"
	.string "None: no level caps at all.$"

InsideOfTruck_Text_SetupDone:
	.string "All set. Enjoy your journey!$"
