@ Cities of Emerald — H4 "Rainbow Wings" (GDD 6.6, approved
@ 2026-09-17). Pays off M3's "rainbow wings" tease, but opens freely
@ post-League (Rocco: arcs stay independent). A hiker in Fortree keeps
@ seeing a rainbow land on one tree in the deep canopy and knows the
@ climb. Ho-Oh on the sun deck, Lugia in the shaded corner; Celebi
@ shows itself at the moss shrine only once both are caught. Fixed 65
@ tier; postgame always obeys (src/cities_arcs.c).

@ -- Visibility --

Cities_EventScript_UpdateH4Hiker::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH4Hiker
	clearflag FLAG_CITIES_HIDE_H4_HIKER
	return

Cities_EventScript_HideH4Hiker::
	setflag FLAG_CITIES_HIDE_H4_HIKER
	return

Cities_EventScript_UpdateH4HoOh::
	goto_if_set FLAG_CITIES_H4_HOOH_CAUGHT, Cities_EventScript_HideH4HoOh
	clearflag FLAG_CITIES_HIDE_H4_HOOH
	return

Cities_EventScript_HideH4HoOh::
	setflag FLAG_CITIES_HIDE_H4_HOOH
	return

Cities_EventScript_UpdateH4Lugia::
	goto_if_set FLAG_CITIES_H4_LUGIA_CAUGHT, Cities_EventScript_HideH4Lugia
	clearflag FLAG_CITIES_HIDE_H4_LUGIA
	return

Cities_EventScript_HideH4Lugia::
	setflag FLAG_CITIES_HIDE_H4_LUGIA
	return

@ The timekeeper shows itself only when sky and sea are both settled.
Cities_EventScript_UpdateH4Celebi::
	goto_if_unset FLAG_CITIES_H4_HOOH_CAUGHT, Cities_EventScript_HideH4Celebi
	goto_if_unset FLAG_CITIES_H4_LUGIA_CAUGHT, Cities_EventScript_HideH4Celebi
	goto_if_set FLAG_CITIES_H4_CELEBI_CAUGHT, Cities_EventScript_HideH4Celebi
	clearflag FLAG_CITIES_HIDE_H4_CELEBI
	return

Cities_EventScript_HideH4Celebi::
	setflag FLAG_CITIES_HIDE_H4_CELEBI
	return

@ -- The hiker (Fortree, postgame) --

Cities_EventScript_H4Hiker::
	lock
	faceplayer
	setvar VAR_0x8004, 11 @ CITIES_ARC_H4
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_H4HikerAllCaught
	goto_if_eq VAR_CITIES_H4_STATE, 0, Cities_EventScript_H4HikerIntro
	msgbox Cities_Text_H4HikerRepeat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H4HikerTravel
	msgbox Cities_Text_H4HikerLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H4HikerIntro::
	msgbox Cities_Text_H4HikerIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_H4_STATE, 1
	msgbox Cities_Text_H4HikerOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H4HikerTravel
	msgbox Cities_Text_H4HikerLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H4HikerTravel::
	msgbox Cities_Text_H4HikerLead, MSGBOX_DEFAULT
	closemessage
	warp MAP_OLD_GROWTH_CANOPY, 9, 11
	waitstate
	release
	end

Cities_EventScript_H4HikerAllCaught::
	goto_if_eq VAR_CITIES_H4_STATE, 2, Cities_EventScript_H4HikerAfter
	msgbox Cities_Text_H4HikerThanks, MSGBOX_DEFAULT
	setvar VAR_CITIES_H4_STATE, 2
	release
	end

Cities_EventScript_H4HikerAfter::
	msgbox Cities_Text_H4HikerAfterText, MSGBOX_DEFAULT
	release
	end

@ -- Leaving the canopy (south walkway trigger tiles) --

Cities_EventScript_H4CanopyExit::
	lockall
	warp MAP_FORTREE_CITY, 5, 11
	waitstate
	releaseall
	end

@ -- The three legends --

Cities_EventScript_H4HoOh::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_HO_OH, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_HO_OH
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H4CaughtHoOh
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H4CaughtHoOh::
	setflag FLAG_CITIES_H4_HOOH_CAUGHT
	release
	end

Cities_EventScript_H4Lugia::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_LUGIA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_LUGIA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H4CaughtLugia
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H4CaughtLugia::
	setflag FLAG_CITIES_H4_LUGIA_CAUGHT
	release
	end

Cities_EventScript_H4Celebi::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CELEBI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_CELEBI
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H4CaughtCelebi
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H4CaughtCelebi::
	setflag FLAG_CITIES_H4_CELEBI_CAUGHT
	release
	end

@ -- Text --

Cities_Text_H4HikerIntro:
	.string "You'll believe me, right,\n"
	.string "CHAMPION? Nobody else does.\p"
	.string "There's a rainbow that LANDS.\n"
	.string "Same tree, deep in the canopy,\l"
	.string "every clear morning after rain.\p"
	.string "The ranger says the beasts she\n"
	.string "tracked once followed wings like\l"
	.string "that.\p"
	.string "I found the climb. Ropes, planks,\n"
	.string "the works. I just… haven't dared\l"
	.string "the last stretch alone.$"

Cities_Text_H4HikerOffer:
	.string "The climb starts behind this\n"
	.string "tree. Come up with me?$"

Cities_Text_H4HikerRepeat:
	.string "Up to the old tree again?$"

Cities_Text_H4HikerLater:
	.string "I'll keep checking the ropes.\n"
	.string "Rain's due tonight anyway.$"

Cities_Text_H4HikerLead:
	.string "Three rules up top: test every\n"
	.string "plank, mind the rails, and if\l"
	.string "something enormous looks at you -\l"
	.string "look back politely.$"

Cities_Text_H4HikerThanks:
	.string "The rainbow, the shadow in the\n"
	.string "shade, AND the little one at the\l"
	.string "moss shrine?!\p"
	.string "Three legends and one tree.\n"
	.string "Some stories you chase - and\l"
	.string "some land right next to you.\p"
	.string "Thanks for daring the last\n"
	.string "stretch with me.$"

Cities_Text_H4HikerAfterText:
	.string "I still climb up some mornings.\p"
	.string "The view's worth it even without\n"
	.string "the rainbow.$"
