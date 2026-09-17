@ Cities of Emerald — H6 "The Balance Below" (GDD 6.6, approved
@ 2026-09-17). Mossdeep's tide pools tip between growth and decay: an
@ ecologist at the cliff edge knows the cavern underneath. Xerneas by
@ the spring pool, Yveltal in the dark nook; Zygarde shows itself at
@ the center once both are caught. Five Zygarde Cells glow in the
@ cavern (Rocco: quick, self-contained hunt). All three caught + all
@ five cells -> the ecologist gives the Zygarde Cube. Fixed 70 tier;
@ postgame always obeys.

@ -- Visibility --

Cities_EventScript_UpdateH6Ecologist::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH6Ecologist
	clearflag FLAG_CITIES_HIDE_H6_ECOLOGIST
	return

Cities_EventScript_HideH6Ecologist::
	setflag FLAG_CITIES_HIDE_H6_ECOLOGIST
	return

Cities_EventScript_UpdateH6Xerneas::
	goto_if_set FLAG_CITIES_H6_XERNEAS_CAUGHT, Cities_EventScript_HideH6Xerneas
	clearflag FLAG_CITIES_HIDE_H6_XERNEAS
	return

Cities_EventScript_HideH6Xerneas::
	setflag FLAG_CITIES_HIDE_H6_XERNEAS
	return

Cities_EventScript_UpdateH6Yveltal::
	goto_if_set FLAG_CITIES_H6_YVELTAL_CAUGHT, Cities_EventScript_HideH6Yveltal
	clearflag FLAG_CITIES_HIDE_H6_YVELTAL
	return

Cities_EventScript_HideH6Yveltal::
	setflag FLAG_CITIES_HIDE_H6_YVELTAL
	return

@ Order shows itself once life and death are settled.
Cities_EventScript_UpdateH6Zygarde::
	goto_if_unset FLAG_CITIES_H6_XERNEAS_CAUGHT, Cities_EventScript_HideH6Zygarde
	goto_if_unset FLAG_CITIES_H6_YVELTAL_CAUGHT, Cities_EventScript_HideH6Zygarde
	goto_if_set FLAG_CITIES_H6_ZYGARDE_CAUGHT, Cities_EventScript_HideH6Zygarde
	clearflag FLAG_CITIES_HIDE_H6_ZYGARDE
	return

Cities_EventScript_HideH6Zygarde::
	setflag FLAG_CITIES_HIDE_H6_ZYGARDE
	return

@ -- The ecologist (Mossdeep cliff edge, postgame) --

Cities_EventScript_H6Ecologist::
	lock
	faceplayer
	setvar VAR_0x8004, 13 @ CITIES_ARC_H6
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_H6EcologistAllCaught
	goto_if_eq VAR_CITIES_H6_STATE, 0, Cities_EventScript_H6EcologistIntro
	msgbox Cities_Text_H6EcologistRepeat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H6EcologistTravel
	msgbox Cities_Text_H6EcologistLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H6EcologistIntro::
	msgbox Cities_Text_H6EcologistIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_H6_STATE, 1
	msgbox Cities_Text_H6EcologistOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H6EcologistTravel
	msgbox Cities_Text_H6EcologistLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H6EcologistTravel::
	msgbox Cities_Text_H6EcologistLead, MSGBOX_DEFAULT
	closemessage
	warp MAP_MOSSDEEP_UNDERCLIFF, 4, 12
	waitstate
	release
	end

@ Trio caught: the cube needs all five cells too.
Cities_EventScript_H6EcologistAllCaught::
	goto_if_set FLAG_CITIES_H6_CUBE_GIVEN, Cities_EventScript_H6EcologistAfterCube
	goto_if_unset FLAG_CITIES_H6_CELL1, Cities_EventScript_H6EcologistCellsMissing
	goto_if_unset FLAG_CITIES_H6_CELL2, Cities_EventScript_H6EcologistCellsMissing
	goto_if_unset FLAG_CITIES_H6_CELL3, Cities_EventScript_H6EcologistCellsMissing
	goto_if_unset FLAG_CITIES_H6_CELL4, Cities_EventScript_H6EcologistCellsMissing
	goto_if_unset FLAG_CITIES_H6_CELL5, Cities_EventScript_H6EcologistCellsMissing
	msgbox Cities_Text_H6EcologistThanks, MSGBOX_DEFAULT
	checkitemspace ITEM_ZYGARDE_CUBE
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H6EcologistBagFull
	giveitem ITEM_ZYGARDE_CUBE
	setflag FLAG_CITIES_H6_CUBE_GIVEN
	setvar VAR_CITIES_H6_STATE, 2
	msgbox Cities_Text_H6EcologistCube, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H6EcologistCellsMissing::
	msgbox Cities_Text_H6EcologistCellsMissing, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H6EcologistTravel
	release
	end

Cities_EventScript_H6EcologistBagFull::
	msgbox Cities_Text_H6EcologistBagFull, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H6EcologistAfterCube::
	msgbox Cities_Text_H6EcologistAfterText, MSGBOX_DEFAULT
	release
	end

@ -- Leaving the undercliff (south alcove trigger tiles) --

Cities_EventScript_H6UndercliffExit::
	lockall
	warp MAP_MOSSDEEP_CITY, 26, 23
	waitstate
	releaseall
	end

@ -- Zygarde Cells (the collect flag IS the object's hide flag) --

Cities_EventScript_H6Cell1::
	lock
	playse SE_M_REFLECT
	waitse
	msgbox Cities_Text_H6CellFound, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_CITIES_H6_CELL1
	removeobject VAR_LAST_TALKED
	release
	end

Cities_EventScript_H6Cell2::
	lock
	playse SE_M_REFLECT
	waitse
	msgbox Cities_Text_H6CellFound, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_CITIES_H6_CELL2
	removeobject VAR_LAST_TALKED
	release
	end

Cities_EventScript_H6Cell3::
	lock
	playse SE_M_REFLECT
	waitse
	msgbox Cities_Text_H6CellFound, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_CITIES_H6_CELL3
	removeobject VAR_LAST_TALKED
	release
	end

Cities_EventScript_H6Cell4::
	lock
	playse SE_M_REFLECT
	waitse
	msgbox Cities_Text_H6CellFound, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_CITIES_H6_CELL4
	removeobject VAR_LAST_TALKED
	release
	end

Cities_EventScript_H6Cell5::
	lock
	playse SE_M_REFLECT
	waitse
	msgbox Cities_Text_H6CellFound, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_CITIES_H6_CELL5
	removeobject VAR_LAST_TALKED
	release
	end

@ -- The aura trio --

Cities_EventScript_H6Xerneas::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_XERNEAS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_XERNEAS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H6CaughtXerneas
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H6CaughtXerneas::
	setflag FLAG_CITIES_H6_XERNEAS_CAUGHT
	release
	end

Cities_EventScript_H6Yveltal::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_YVELTAL, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_YVELTAL
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H6CaughtYveltal
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H6CaughtYveltal::
	setflag FLAG_CITIES_H6_YVELTAL_CAUGHT
	release
	end

Cities_EventScript_H6Zygarde::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZYGARDE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ZYGARDE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H6CaughtZygarde
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H6CaughtZygarde::
	setflag FLAG_CITIES_H6_ZYGARDE_CAUGHT
	release
	end

@ -- Text --

Cities_Text_H6EcologistIntro:
	.string "CHAMPION - do the tide pools\n"
	.string "look strange to you?\p"
	.string "One side of the cliff, everything\n"
	.string "blooms overnight. The other side,\l"
	.string "it withers just as fast.\p"
	.string "The balance tips back and forth\n"
	.string "like a scale being weighed.\p"
	.string "I found the cavern where the\n"
	.string "weighing happens. It's right\l"
	.string "under our feet.$"

Cities_Text_H6EcologistOffer:
	.string "The climb down starts here.\n"
	.string "Coming?$"

Cities_Text_H6EcologistRepeat:
	.string "Back down to the cavern?$"

Cities_Text_H6EcologistLater:
	.string "I'll keep logging the pools.\n"
	.string "Mind the tide when you decide.$"

Cities_Text_H6EcologistLead:
	.string "Watch for the green glimmers\n"
	.string "down there. Collect any you see -\l"
	.string "they're part of this, I'm sure\l"
	.string "of it.$"

Cities_Text_H6CellFound:
	.string "A soft green glow… it settles\n"
	.string "into your hand like a droplet.\p"
	.string "You found a ZYGARDE CELL!$"

Cities_Text_H6EcologistCellsMissing:
	.string "All three of them, with you…\n"
	.string "but the cavern still glimmers.\p"
	.string "Some of those green cells are\n"
	.string "still down there. Gather all\l"
	.string "five and come see me.\p"
	.string "Want to head down now?$"

Cities_Text_H6EcologistThanks:
	.string "Life, death, and order - and\n"
	.string "every last cell gathered.\p"
	.string "The pools evened out this\n"
	.string "morning. Balance found its\l"
	.string "keeper.$"

Cities_Text_H6EcologistCube:
	.string "The cells fit this - a ZYGARDE\n"
	.string "CUBE. Old tech, or old nature,\l"
	.string "I honestly can't tell.\p"
	.string "With the cells inside, your\n"
	.string "ZYGARDE can draw on its other\l"
	.string "forms.$"

Cities_Text_H6EcologistBagFull:
	.string "Your Bag is full! The cube waited\n"
	.string "under a cliff - it can wait for\l"
	.string "you to tidy up.$"

Cities_Text_H6EcologistAfterText:
	.string "The pools are just pools now.\p"
	.string "I almost miss the mystery.\n"
	.string "Almost.$"
