@ Cities of Emerald — H10 "The Island Guardians" (GDD 6.6, approved
@ 2026-09-17). Pacifidlog's elders say the town floats where it does
@ for a reason: four shrines ring a sunken atoll, and their guardians
@ have returned now that the sea is calm. An elder poles the Champion
@ out by raft. One Tapu per shrine platform, any order, fixed 60 tier,
@ postgame always obeys (src/cities_arcs.c).

@ -- Visibility --

Cities_EventScript_UpdateH10Elder::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH10Elder
	clearflag FLAG_CITIES_HIDE_H10_ELDER
	return

Cities_EventScript_HideH10Elder::
	setflag FLAG_CITIES_HIDE_H10_ELDER
	return

Cities_EventScript_UpdateH10Koko::
	goto_if_set FLAG_CITIES_H10_KOKO_CAUGHT, Cities_EventScript_HideH10Koko
	clearflag FLAG_CITIES_HIDE_H10_KOKO
	return

Cities_EventScript_HideH10Koko::
	setflag FLAG_CITIES_HIDE_H10_KOKO
	return

Cities_EventScript_UpdateH10Lele::
	goto_if_set FLAG_CITIES_H10_LELE_CAUGHT, Cities_EventScript_HideH10Lele
	clearflag FLAG_CITIES_HIDE_H10_LELE
	return

Cities_EventScript_HideH10Lele::
	setflag FLAG_CITIES_HIDE_H10_LELE
	return

Cities_EventScript_UpdateH10Bulu::
	goto_if_set FLAG_CITIES_H10_BULU_CAUGHT, Cities_EventScript_HideH10Bulu
	clearflag FLAG_CITIES_HIDE_H10_BULU
	return

Cities_EventScript_HideH10Bulu::
	setflag FLAG_CITIES_HIDE_H10_BULU
	return

Cities_EventScript_UpdateH10Fini::
	goto_if_set FLAG_CITIES_H10_FINI_CAUGHT, Cities_EventScript_HideH10Fini
	clearflag FLAG_CITIES_HIDE_H10_FINI
	return

Cities_EventScript_HideH10Fini::
	setflag FLAG_CITIES_HIDE_H10_FINI
	return

@ -- The elder (Pacifidlog south-east walkway, postgame) --

Cities_EventScript_H10Elder::
	lock
	faceplayer
	goto_if_eq VAR_CITIES_H10_STATE, 0, Cities_EventScript_H10ElderIntro
	msgbox Cities_Text_H10ElderRepeat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H10ElderTravel
	msgbox Cities_Text_H10ElderLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H10ElderIntro::
	msgbox Cities_Text_H10ElderIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_H10_STATE, 1
	msgbox Cities_Text_H10ElderOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H10ElderTravel
	msgbox Cities_Text_H10ElderLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H10ElderTravel::
	msgbox Cities_Text_H10ElderLead, MSGBOX_DEFAULT
	closemessage
	warp MAP_SHRINE_ATOLL, 10, 11
	waitstate
	release
	end

@ -- Leaving the atoll (moored raft, center platform SE corner) --

Cities_EventScript_H10AtollExit::
	lockall
	warp MAP_PACIFIDLOG_TOWN, 16, 23
	waitstate
	releaseall
	end

@ -- The caretaker (elder's grandchild, center platform) --

Cities_EventScript_H10Caretaker::
	lock
	faceplayer
	setvar VAR_0x8004, 8 @ CITIES_ARC_H10
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_H10CaretakerAllCaught
	msgbox Cities_Text_H10CaretakerGuardians, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H10CaretakerAllCaught::
	goto_if_eq VAR_CITIES_H10_STATE, 2, Cities_EventScript_H10CaretakerAfter
	msgbox Cities_Text_H10CaretakerThanks, MSGBOX_DEFAULT
	setvar VAR_CITIES_H10_STATE, 2
	release
	end

Cities_EventScript_H10CaretakerAfter::
	msgbox Cities_Text_H10CaretakerAfter, MSGBOX_DEFAULT
	release
	end

@ -- The guardians --

Cities_EventScript_H10Koko::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TAPU_KOKO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_TAPU_KOKO
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H10CaughtKoko
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H10CaughtKoko::
	setflag FLAG_CITIES_H10_KOKO_CAUGHT
	release
	end

Cities_EventScript_H10Lele::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TAPU_LELE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_TAPU_LELE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H10CaughtLele
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H10CaughtLele::
	setflag FLAG_CITIES_H10_LELE_CAUGHT
	release
	end

Cities_EventScript_H10Bulu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TAPU_BULU, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_TAPU_BULU
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H10CaughtBulu
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H10CaughtBulu::
	setflag FLAG_CITIES_H10_BULU_CAUGHT
	release
	end

Cities_EventScript_H10Fini::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TAPU_FINI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_TAPU_FINI
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H10CaughtFini
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H10CaughtFini::
	setflag FLAG_CITIES_H10_FINI_CAUGHT
	release
	end

@ -- Text --

Cities_Text_H10ElderIntro:
	.string "Ever wonder why our town floats\n"
	.string "HERE, of all the sea?\p"
	.string "My grandmother's grandmother\n"
	.string "helped lash the first logs. She\l"
	.string "chose this spot because of what\l"
	.string "lies beneath: four old shrines,\l"
	.string "ringing a sunken atoll.\p"
	.string "The guardians who kept them left\n"
	.string "when the sea grew loud. Now that\l"
	.string "it's calm again - they're back.\p"
	.string "The sea itself vouches for you,\n"
	.string "CHAMPION. They'll want to meet\l"
	.string "you the old way.$"

Cities_Text_H10ElderOffer:
	.string "My raft's tied just here.\n"
	.string "Shall I pole you out?$"

Cities_Text_H10ElderRepeat:
	.string "Out to the shrines again?$"

Cities_Text_H10ElderLater:
	.string "The tide keeps its own time.\n"
	.string "So can you.$"

Cities_Text_H10ElderLead:
	.string "Mind the swell. The guardians\n"
	.string "like a dramatic arrival.$"

Cities_Text_H10CaretakerGuardians:
	.string "Grandmother sent you? Then\n"
	.string "welcome to the atoll.\p"
	.string "I sweep the shrines. Four of\n"
	.string "them, one on each islet - north,\l"
	.string "east, south, west.\p"
	.string "The guardians each chose their\n"
	.string "islet when they returned. They're\l"
	.string "waiting to test you the old way:\p"
	.string "stand before one, and don't\n"
	.string "flinch.$"

Cities_Text_H10CaretakerThanks:
	.string "All four shrines, empty - and all\n"
	.string "four guardians, with you.\p"
	.string "I'll keep the shrines swept for\n"
	.string "the day they visit again.\p"
	.string "They chose the one person the\n"
	.string "sea itself vouched for. The old\l"
	.string "way still works.$"

Cities_Text_H10CaretakerAfter:
	.string "The shrines are swept. The sea\n"
	.string "is calm.\p"
	.string "Some days that's the whole job.$"
