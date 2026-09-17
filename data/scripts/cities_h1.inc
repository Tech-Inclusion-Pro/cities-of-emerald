@ Cities of Emerald — H1 "The Swords of Justice" (GDD 6.6, approved
@ 2026-09-17). First hidden area: Littleroot Hollow, an original map
@ reached by a ranger at Littleroot's tree line (post-League). Cobalion,
@ Terrakion, and Virizion stand as statics at the fixed 60 tier; Keldeo
@ appears only after all three are caught. Postgame legendaries always
@ obey (src/cities_arcs.c). Catch removal on resume reuses
@ Cities_EventScript_M1TryRemoveCaughtBird (generic outcome check).

@ -- Visibility --

Cities_EventScript_UpdateH1Ranger::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH1Ranger
	clearflag FLAG_CITIES_HIDE_H1_RANGER
	return

Cities_EventScript_HideH1Ranger::
	setflag FLAG_CITIES_HIDE_H1_RANGER
	return

Cities_EventScript_UpdateH1Cobalion::
	goto_if_set FLAG_CITIES_H1_COBALION_CAUGHT, Cities_EventScript_HideH1Cobalion
	clearflag FLAG_CITIES_HIDE_H1_COBALION
	return

Cities_EventScript_HideH1Cobalion::
	setflag FLAG_CITIES_HIDE_H1_COBALION
	return

Cities_EventScript_UpdateH1Terrakion::
	goto_if_set FLAG_CITIES_H1_TERRAKION_CAUGHT, Cities_EventScript_HideH1Terrakion
	clearflag FLAG_CITIES_HIDE_H1_TERRAKION
	return

Cities_EventScript_HideH1Terrakion::
	setflag FLAG_CITIES_HIDE_H1_TERRAKION
	return

Cities_EventScript_UpdateH1Virizion::
	goto_if_set FLAG_CITIES_H1_VIRIZION_CAUGHT, Cities_EventScript_HideH1Virizion
	clearflag FLAG_CITIES_HIDE_H1_VIRIZION
	return

Cities_EventScript_HideH1Virizion::
	setflag FLAG_CITIES_HIDE_H1_VIRIZION
	return

@ Keldeo comes looking for its teachers only once all three are caught.
Cities_EventScript_UpdateH1Keldeo::
	goto_if_unset FLAG_CITIES_H1_COBALION_CAUGHT, Cities_EventScript_HideH1Keldeo
	goto_if_unset FLAG_CITIES_H1_TERRAKION_CAUGHT, Cities_EventScript_HideH1Keldeo
	goto_if_unset FLAG_CITIES_H1_VIRIZION_CAUGHT, Cities_EventScript_HideH1Keldeo
	goto_if_set FLAG_CITIES_H1_KELDEO_CAUGHT, Cities_EventScript_HideH1Keldeo
	clearflag FLAG_CITIES_HIDE_H1_KELDEO
	return

Cities_EventScript_HideH1Keldeo::
	setflag FLAG_CITIES_HIDE_H1_KELDEO
	return

@ -- The ranger (Littleroot tree line, postgame) --

Cities_EventScript_H1Ranger::
	lock
	faceplayer
	goto_if_eq VAR_CITIES_H1_STATE, 0, Cities_EventScript_H1RangerIntro
	msgbox Cities_Text_H1RangerRepeat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H1RangerTravel
	msgbox Cities_Text_H1RangerLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H1RangerIntro::
	msgbox Cities_Text_H1RangerIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_H1_STATE, 1
	msgbox Cities_Text_H1RangerOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H1RangerTravel
	msgbox Cities_Text_H1RangerLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H1RangerTravel::
	msgbox Cities_Text_H1RangerLead, MSGBOX_DEFAULT
	closemessage
	warp MAP_LITTLEROOT_HOLLOW, 10, 16
	waitstate
	release
	end

@ -- Leaving the hollow (south alcove trigger tiles) --

Cities_EventScript_H1HollowExit::
	lockall
	warp MAP_LITTLEROOT_TOWN, 4, 3
	waitstate
	releaseall
	end

@ -- The caretaker (inside the hollow) --

Cities_EventScript_H1Caretaker::
	lock
	faceplayer
	setvar VAR_0x8004, 6 @ CITIES_ARC_H1
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_H1CaretakerAllCaught
	goto_if_unset FLAG_CITIES_H1_COBALION_CAUGHT, Cities_EventScript_H1CaretakerGuardians
	goto_if_unset FLAG_CITIES_H1_TERRAKION_CAUGHT, Cities_EventScript_H1CaretakerGuardians
	goto_if_unset FLAG_CITIES_H1_VIRIZION_CAUGHT, Cities_EventScript_H1CaretakerGuardians
	msgbox Cities_Text_H1CaretakerStudent, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H1CaretakerGuardians::
	msgbox Cities_Text_H1CaretakerGuardians, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H1CaretakerAllCaught::
	goto_if_eq VAR_CITIES_H1_STATE, 2, Cities_EventScript_H1CaretakerAfter
	msgbox Cities_Text_H1CaretakerThanks, MSGBOX_DEFAULT
	setvar VAR_CITIES_H1_STATE, 2
	release
	end

Cities_EventScript_H1CaretakerAfter::
	msgbox Cities_Text_H1CaretakerAfter, MSGBOX_DEFAULT
	release
	end

@ -- The guardians --

Cities_EventScript_H1Cobalion::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_COBALION, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_COBALION
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H1CaughtCobalion
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H1CaughtCobalion::
	setflag FLAG_CITIES_H1_COBALION_CAUGHT
	release
	end

Cities_EventScript_H1Terrakion::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TERRAKION, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_TERRAKION
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H1CaughtTerrakion
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H1CaughtTerrakion::
	setflag FLAG_CITIES_H1_TERRAKION_CAUGHT
	release
	end

Cities_EventScript_H1Virizion::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_VIRIZION, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_VIRIZION
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H1CaughtVirizion
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H1CaughtVirizion::
	setflag FLAG_CITIES_H1_VIRIZION_CAUGHT
	release
	end

Cities_EventScript_H1Keldeo::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KELDEO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_KELDEO
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H1CaughtKeldeo
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H1CaughtKeldeo::
	setflag FLAG_CITIES_H1_KELDEO_CAUGHT
	release
	end

@ -- Text --

Cities_Text_H1RangerIntro:
	.string "You're the CHAMPION, aren't you?\n"
	.string "Then I can finally tell someone.\p"
	.string "Hurt POKéMON have been going\n"
	.string "missing all over HOENN. Not taken.\l"
	.string "Carried. Gently.\p"
	.string "I followed the trails once. They\n"
	.string "all lead to a hollow deep in these\l"
	.string "woods, where three guardians\l"
	.string "shelter them.\p"
	.string "They won't let just anyone in.\n"
	.string "But you… you've earned the\l"
	.string "introduction.$"

Cities_Text_H1RangerOffer:
	.string "The trail is hard to find alone.\n"
	.string "Want me to walk you in?$"

Cities_Text_H1RangerRepeat:
	.string "Heading back to the hollow?$"

Cities_Text_H1RangerLater:
	.string "I'll be here. The hollow isn't\n"
	.string "going anywhere.$"

Cities_Text_H1RangerLead:
	.string "Stay close - the path doubles\n"
	.string "back on itself twice.$"

Cities_Text_H1CaretakerGuardians:
	.string "Welcome to the hollow. The hurt\n"
	.string "POKéMON you've heard about? The\l"
	.string "guardians bring them here to heal.\p"
	.string "COBALION, TERRAKION, VIRIZION.\n"
	.string "Three protectors who never trusted\l"
	.string "people much.\p"
	.string "If one stands its ground when you\n"
	.string "draw near, that's not anger.\l"
	.string "That's a test - whether POKéMON\l"
	.string "can trust you.$"

Cities_Text_H1CaretakerStudent:
	.string "All three guardians chose to go\n"
	.string "with you. I never thought I'd see\l"
	.string "it.\p"
	.string "And now look - a fourth has come.\n"
	.string "The student, KELDEO, wondering\l"
	.string "where its teachers went.\p"
	.string "It's waiting in the heart of the\n"
	.string "clearing.$"

Cities_Text_H1CaretakerThanks:
	.string "All four… then it's settled.\p"
	.string "The hollow will stay a sanctuary.\n"
	.string "And its guardians travel with\l"
	.string "someone who protects things the\l"
	.string "same way they do.\p"
	.string "That's not losing them. That's\n"
	.string "the test, passed.$"

Cities_Text_H1CaretakerAfter:
	.string "The hollow is quiet today.\p"
	.string "Good quiet.$"
