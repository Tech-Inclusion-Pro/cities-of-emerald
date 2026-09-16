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
	goto_if_eq VAR_RESULT, NO, InsideOfTruck_EventScript_CitiesSetupDone
	setflag FLAG_CITIES_ASSIST_MODE
	message InsideOfTruck_Text_ChooseLevelCap
	waitmessage
	multichoice 0, 0, MULTI_CITIES_LEVEL_CAP, TRUE
	switch VAR_RESULT
	case 0, InsideOfTruck_EventScript_CapKeep
	case 1, InsideOfTruck_EventScript_CapRaise
	case 2, InsideOfTruck_EventScript_CapRemove
	goto InsideOfTruck_EventScript_CitiesSetupDone

InsideOfTruck_EventScript_CapKeep::
	setvar VAR_CITIES_LEVEL_CAP, 0
	goto InsideOfTruck_EventScript_CitiesSetupDone

InsideOfTruck_EventScript_CapRaise::
	setvar VAR_CITIES_LEVEL_CAP, 1
	goto InsideOfTruck_EventScript_CitiesSetupDone

InsideOfTruck_EventScript_CapRemove::
	setvar VAR_CITIES_LEVEL_CAP, 100
	goto InsideOfTruck_EventScript_CitiesSetupDone

InsideOfTruck_EventScript_CitiesSetupDone::
	msgbox InsideOfTruck_Text_SetupDone, MSGBOX_DEFAULT
	return

InsideOfTruck_Text_SetupIntro:
	.string "Welcome!\p"
	.string "Before your journey begins, let's\n"
	.string "set up the game your way.\p"
	.string "There are no wrong answers.$"

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
