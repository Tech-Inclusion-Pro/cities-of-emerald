@ Cities of Emerald — H7 "Truth and Ideals" (GDD 6.6, approved
@ 2026-09-17). Mauville's grid keeps logging two signals, perfectly
@ out of phase, deep below the city. An engineer traced the service
@ shaft to a humming vault. Reshiram and Zekrom face each other
@ across the hall; Kyurem, the husk that remains, appears at the
@ cold north end once both are caught. All three caught -> the
@ engineer gives the DNA Splicers. Fixed 70 tier; postgame always
@ obeys.

@ -- Visibility --

Cities_EventScript_UpdateH7Engineer::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH7Engineer
	clearflag FLAG_CITIES_HIDE_H7_ENGINEER
	return

Cities_EventScript_HideH7Engineer::
	setflag FLAG_CITIES_HIDE_H7_ENGINEER
	return

Cities_EventScript_UpdateH7Reshiram::
	goto_if_set FLAG_CITIES_H7_RESHIRAM_CAUGHT, Cities_EventScript_HideH7Reshiram
	clearflag FLAG_CITIES_HIDE_H7_RESHIRAM
	return

Cities_EventScript_HideH7Reshiram::
	setflag FLAG_CITIES_HIDE_H7_RESHIRAM
	return

Cities_EventScript_UpdateH7Zekrom::
	goto_if_set FLAG_CITIES_H7_ZEKROM_CAUGHT, Cities_EventScript_HideH7Zekrom
	clearflag FLAG_CITIES_HIDE_H7_ZEKROM
	return

Cities_EventScript_HideH7Zekrom::
	setflag FLAG_CITIES_HIDE_H7_ZEKROM
	return

@ The husk appears once truth and ideals have moved on.
Cities_EventScript_UpdateH7Kyurem::
	goto_if_unset FLAG_CITIES_H7_RESHIRAM_CAUGHT, Cities_EventScript_HideH7Kyurem
	goto_if_unset FLAG_CITIES_H7_ZEKROM_CAUGHT, Cities_EventScript_HideH7Kyurem
	goto_if_set FLAG_CITIES_H7_KYUREM_CAUGHT, Cities_EventScript_HideH7Kyurem
	clearflag FLAG_CITIES_HIDE_H7_KYUREM
	return

Cities_EventScript_HideH7Kyurem::
	setflag FLAG_CITIES_HIDE_H7_KYUREM
	return

@ -- The engineer (Mauville, postgame) --

Cities_EventScript_H7Engineer::
	lock
	faceplayer
	setvar VAR_0x8004, 14 @ CITIES_ARC_H7
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_H7EngineerAllCaught
	goto_if_eq VAR_CITIES_H7_STATE, 0, Cities_EventScript_H7EngineerIntro
	msgbox Cities_Text_H7EngineerRepeat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H7EngineerTravel
	msgbox Cities_Text_H7EngineerLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H7EngineerIntro::
	msgbox Cities_Text_H7EngineerIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_H7_STATE, 1
	msgbox Cities_Text_H7EngineerOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H7EngineerTravel
	msgbox Cities_Text_H7EngineerLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H7EngineerTravel::
	msgbox Cities_Text_H7EngineerLead, MSGBOX_DEFAULT
	closemessage
	warp MAP_RESONANCE_HALL, 7, 9
	waitstate
	release
	end

Cities_EventScript_H7EngineerAllCaught::
	goto_if_set FLAG_CITIES_H7_SPLICERS_GIVEN, Cities_EventScript_H7EngineerAfter
	msgbox Cities_Text_H7EngineerThanks, MSGBOX_DEFAULT
	checkitemspace ITEM_DNA_SPLICERS
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H7EngineerBagFull
	giveitem ITEM_DNA_SPLICERS
	setflag FLAG_CITIES_H7_SPLICERS_GIVEN
	setvar VAR_CITIES_H7_STATE, 2
	msgbox Cities_Text_H7EngineerSplicers, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H7EngineerBagFull::
	msgbox Cities_Text_H7EngineerBagFull, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H7EngineerAfter::
	msgbox Cities_Text_H7EngineerAfterText, MSGBOX_DEFAULT
	release
	end

@ -- Leaving the hall (south alcove trigger tiles) --

Cities_EventScript_H7HallExit::
	lockall
	warp MAP_MAUVILLE_CITY, 17, 16
	waitstate
	releaseall
	end

@ -- The Tao trio --

Cities_EventScript_H7Reshiram::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_RESHIRAM, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_RESHIRAM
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H7CaughtReshiram
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H7CaughtReshiram::
	setflag FLAG_CITIES_H7_RESHIRAM_CAUGHT
	release
	end

Cities_EventScript_H7Zekrom::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZEKROM, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ZEKROM
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H7CaughtZekrom
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H7CaughtZekrom::
	setflag FLAG_CITIES_H7_ZEKROM_CAUGHT
	release
	end

Cities_EventScript_H7Kyurem::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KYUREM, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_KYUREM
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H7CaughtKyurem
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H7CaughtKyurem::
	setflag FLAG_CITIES_H7_KYUREM_CAUGHT
	release
	end

@ -- Text --

Cities_Text_H7EngineerIntro:
	.string "CHAMPION! You know circuits,\n"
	.string "right? No? Doesn't matter -\l"
	.string "look at THIS.\p"
	.string "Two power draws under the city.\n"
	.string "Big ones. Perfectly out of\l"
	.string "phase - when one peaks, the\l"
	.string "other dips. Like an argument.\p"
	.string "Nobody wired anything down\n"
	.string "there. I checked. Twice.\p"
	.string "I found the old service shaft.\n"
	.string "Whatever's arguing under\l"
	.string "MAUVILLE, it hums.$"

Cities_Text_H7EngineerOffer:
	.string "Shaft's open. Coming down?$"

Cities_Text_H7EngineerRepeat:
	.string "Back down the shaft?$"

Cities_Text_H7EngineerLater:
	.string "Suit yourself. The hum isn't\n"
	.string "going anywhere. I've charted it.$"

Cities_Text_H7EngineerLead:
	.string "Mind the third rung - it's\n"
	.string "more of a suggestion.$"

Cities_Text_H7EngineerThanks:
	.string "The hum stopped. Both draws flat,\n"
	.string "and the cold spot too.\p"
	.string "Truth, ideals, and what's left\n"
	.string "when they leave. All three chose\l"
	.string "to go with you.\p"
	.string "Found this bracketed to the vault\n"
	.string "wall. It's yours.$"

Cities_Text_H7EngineerSplicers:
	.string "DNA SPLICERS. The old notes say\n"
	.string "they let the husk borrow back\l"
	.string "what it lost - fuse KYUREM with\l"
	.string "RESHIRAM or ZEKROM, and part\l"
	.string "them again.$"

Cities_Text_H7EngineerBagFull:
	.string "Bag's full! Those splicers waited\n"
	.string "under a city - go make room.$"

Cities_Text_H7EngineerAfterText:
	.string "Grid's boring again. Balanced\n"
	.string "load, no mystery draws.\p"
	.string "I get to sleep at night. Weird\n"
	.string "feeling.$"
