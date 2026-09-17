@ Cities of Emerald — H9 "The Old Heroes" (GDD 6.6, approved
@ 2026-09-17). Verdanturf's storyteller elder knows the meadow where
@ old heroes rest: the two wolves who guarded people, the crowned
@ king of harvests with his two steeds, and the student who still
@ trains to earn its place. Calyrex appears at the crown once both
@ steeds are caught. All six caught -> Rusted Sword, Rusted Shield,
@ and Reins of Unity together (three-item give with space checks).
@ Fixed 70 tier; postgame always obeys. Largest hidden-area arc.

@ -- Visibility --

Cities_EventScript_UpdateH9Elder::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH9Elder
	clearflag FLAG_CITIES_HIDE_H9_ELDER
	return

Cities_EventScript_HideH9Elder::
	setflag FLAG_CITIES_HIDE_H9_ELDER
	return

Cities_EventScript_UpdateH9Zacian::
	goto_if_set FLAG_CITIES_H9_ZACIAN_CAUGHT, Cities_EventScript_HideH9Zacian
	clearflag FLAG_CITIES_HIDE_H9_ZACIAN
	return

Cities_EventScript_HideH9Zacian::
	setflag FLAG_CITIES_HIDE_H9_ZACIAN
	return

Cities_EventScript_UpdateH9Zamazenta::
	goto_if_set FLAG_CITIES_H9_ZAMAZENTA_CAUGHT, Cities_EventScript_HideH9Zamazenta
	clearflag FLAG_CITIES_HIDE_H9_ZAMAZENTA
	return

Cities_EventScript_HideH9Zamazenta::
	setflag FLAG_CITIES_HIDE_H9_ZAMAZENTA
	return

Cities_EventScript_UpdateH9Glastrier::
	goto_if_set FLAG_CITIES_H9_GLASTRIER_CAUGHT, Cities_EventScript_HideH9Glastrier
	clearflag FLAG_CITIES_HIDE_H9_GLASTRIER
	return

Cities_EventScript_HideH9Glastrier::
	setflag FLAG_CITIES_HIDE_H9_GLASTRIER
	return

Cities_EventScript_UpdateH9Spectrier::
	goto_if_set FLAG_CITIES_H9_SPECTRIER_CAUGHT, Cities_EventScript_HideH9Spectrier
	clearflag FLAG_CITIES_HIDE_H9_SPECTRIER
	return

Cities_EventScript_HideH9Spectrier::
	setflag FLAG_CITIES_HIDE_H9_SPECTRIER
	return

@ The king returns to the crown once both steeds are with the player.
Cities_EventScript_UpdateH9Calyrex::
	goto_if_unset FLAG_CITIES_H9_GLASTRIER_CAUGHT, Cities_EventScript_HideH9Calyrex
	goto_if_unset FLAG_CITIES_H9_SPECTRIER_CAUGHT, Cities_EventScript_HideH9Calyrex
	goto_if_set FLAG_CITIES_H9_CALYREX_CAUGHT, Cities_EventScript_HideH9Calyrex
	clearflag FLAG_CITIES_HIDE_H9_CALYREX
	return

Cities_EventScript_HideH9Calyrex::
	setflag FLAG_CITIES_HIDE_H9_CALYREX
	return

Cities_EventScript_UpdateH9Kubfu::
	goto_if_set FLAG_CITIES_H9_KUBFU_CAUGHT, Cities_EventScript_HideH9Kubfu
	clearflag FLAG_CITIES_HIDE_H9_KUBFU
	return

Cities_EventScript_HideH9Kubfu::
	setflag FLAG_CITIES_HIDE_H9_KUBFU
	return

@ -- The elder (Verdanturf, postgame) --

Cities_EventScript_H9Elder::
	lock
	faceplayer
	setvar VAR_0x8004, 15 @ CITIES_ARC_H9
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_H9ElderAllCaught
	goto_if_eq VAR_CITIES_H9_STATE, 0, Cities_EventScript_H9ElderIntro
	msgbox Cities_Text_H9ElderRepeat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H9ElderTravel
	msgbox Cities_Text_H9ElderLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H9ElderIntro::
	msgbox Cities_Text_H9ElderIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_H9_STATE, 1
	msgbox Cities_Text_H9ElderOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H9ElderTravel
	msgbox Cities_Text_H9ElderLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H9ElderTravel::
	msgbox Cities_Text_H9ElderLead, MSGBOX_DEFAULT
	closemessage
	warp MAP_HEROS_MEADOW, 10, 16
	waitstate
	release
	end

@ All six caught: the three relics, together (space checked for all).
Cities_EventScript_H9ElderAllCaught::
	goto_if_set FLAG_CITIES_H9_RELICS_GIVEN, Cities_EventScript_H9ElderAfter
	msgbox Cities_Text_H9ElderThanks, MSGBOX_DEFAULT
	checkitemspace ITEM_RUSTED_SWORD
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H9ElderBagFull
	checkitemspace ITEM_RUSTED_SHIELD
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H9ElderBagFull
	checkitemspace ITEM_REINS_OF_UNITY
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H9ElderBagFull
	giveitem ITEM_RUSTED_SWORD
	giveitem ITEM_RUSTED_SHIELD
	giveitem ITEM_REINS_OF_UNITY
	setflag FLAG_CITIES_H9_RELICS_GIVEN
	setvar VAR_CITIES_H9_STATE, 2
	msgbox Cities_Text_H9ElderRelics, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H9ElderBagFull::
	msgbox Cities_Text_H9ElderBagFull, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H9ElderAfter::
	msgbox Cities_Text_H9ElderAfterText, MSGBOX_DEFAULT
	release
	end

@ -- Leaving the meadow (south gap trigger tiles) --

Cities_EventScript_H9MeadowExit::
	lockall
	warp MAP_VERDANTURF_TOWN, 4, 19
	waitstate
	releaseall
	end

@ -- The old heroes --

Cities_EventScript_H9Zacian::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZACIAN, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ZACIAN
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H9CaughtZacian
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H9CaughtZacian::
	setflag FLAG_CITIES_H9_ZACIAN_CAUGHT
	release
	end

Cities_EventScript_H9Zamazenta::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZAMAZENTA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ZAMAZENTA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H9CaughtZamazenta
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H9CaughtZamazenta::
	setflag FLAG_CITIES_H9_ZAMAZENTA_CAUGHT
	release
	end

Cities_EventScript_H9Glastrier::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_GLASTRIER, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_GLASTRIER
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H9CaughtGlastrier
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H9CaughtGlastrier::
	setflag FLAG_CITIES_H9_GLASTRIER_CAUGHT
	release
	end

Cities_EventScript_H9Spectrier::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SPECTRIER, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_SPECTRIER
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H9CaughtSpectrier
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H9CaughtSpectrier::
	setflag FLAG_CITIES_H9_SPECTRIER_CAUGHT
	release
	end

Cities_EventScript_H9Calyrex::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CALYREX, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_CALYREX
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H9CaughtCalyrex
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H9CaughtCalyrex::
	setflag FLAG_CITIES_H9_CALYREX_CAUGHT
	release
	end

Cities_EventScript_H9Kubfu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KUBFU, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_KUBFU
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H9CaughtKubfu
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H9CaughtKubfu::
	setflag FLAG_CITIES_H9_KUBFU_CAUGHT
	release
	end

@ -- Text --

Cities_Text_H9ElderIntro:
	.string "Sit a moment, CHAMPION. Every\n"
	.string "town keeps one story it doesn't\l"
	.string "tell tourists.\p"
	.string "Ours is a meadow past the clean\n"
	.string "air, where the old heroes rest.\p"
	.string "Two wolves who guarded people\n"
	.string "when people needed guarding.\l"
	.string "A crowned king of harvests, and\l"
	.string "his two steeds - one of frost,\l"
	.string "one of shadow.\p"
	.string "And a small one who still\n"
	.string "trains, every day, to earn its\l"
	.string "place among them.$"

Cities_Text_H9ElderOffer:
	.string "The path starts behind my\n"
	.string "garden. Shall we?$"

Cities_Text_H9ElderRepeat:
	.string "Back to the meadow?$"

Cities_Text_H9ElderLater:
	.string "The meadow keeps. Stories are\n"
	.string "patient.$"

Cities_Text_H9ElderLead:
	.string "Walk soft and speak plain.\n"
	.string "Heroes have good ears.$"

Cities_Text_H9ElderThanks:
	.string "The wolves. The steeds. The\n"
	.string "king come back to his crown.\l"
	.string "And the little student, too.\p"
	.string "All six chose to walk with you.\n"
	.string "That's not the end of the story -\l"
	.string "it's the next chapter.\p"
	.string "Then you should carry what they\n"
	.string "left behind.$"

Cities_Text_H9ElderRelics:
	.string "The RUSTED SWORD and RUSTED\n"
	.string "SHIELD - the wolves' old arms.\l"
	.string "They'll take them up again for\l"
	.string "you.\p"
	.string "And the REINS OF UNITY, so the\n"
	.string "king may ride with a steed once\l"
	.string "more.$"

Cities_Text_H9ElderBagFull:
	.string "Your Bag can't hold the relics -\n"
	.string "all three go together or not at\l"
	.string "all. Make room and come back.$"

Cities_Text_H9ElderAfterText:
	.string "The meadow's empty now, but not\n"
	.string "sad. Stories walk around these\l"
	.string "days - with you.$"
