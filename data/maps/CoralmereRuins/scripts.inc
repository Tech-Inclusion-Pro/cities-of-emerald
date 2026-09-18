@ Cities of Emerald — Task 12.3 (GDD 7.2): Coralmere, present day.
@ Quiet on purpose: no encounters, no items. The village opens when
@ FLAG_CITIES_CORALMERE_OPEN is set (12.5, after V2); before that the
@ entrance current turns the player around just inside.
CoralmereRuins_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, CoralmereRuins_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, CoralmereRuins_OnTransition
	.byte 0

CoralmereRuins_OnTransition::
	call Cities_EventScript_UpdateV4Coralmere
	setvar VAR_TEMP_0, 0
	goto_if_unset FLAG_CITIES_CORALMERE_OPEN, CoralmereRuins_OnTransition_End
	setvar VAR_TEMP_0, 1
CoralmereRuins_OnTransition_End::
	end

CoralmereRuins_EventScript_CurrentTooStrong::
	lockall
	msgbox CoralmereRuins_Text_CurrentTooStrong, MSGBOX_DEFAULT
	closemessage
	warp MAP_UNDERWATER_ROUTE128, 86, 16
	waitstate
	releaseall
	end

CoralmereRuins_EventScript_TownSign::
	msgbox CoralmereRuins_Text_TownSign, MSGBOX_SIGN
	end

CoralmereRuins_EventScript_Doorway::
	msgbox CoralmereRuins_Text_Doorway, MSGBOX_SIGN
	end

CoralmereRuins_EventScript_TowerBase::
	msgbox CoralmereRuins_Text_TowerBase, MSGBOX_SIGN
	end

CoralmereRuins_EventScript_HouseFloor::
	msgbox CoralmereRuins_Text_HouseFloor, MSGBOX_SIGN
	end

CoralmereRuins_Text_CurrentTooStrong:
	.string "The current through the opening is\n"
	.string "too strong to swim against.$"

CoralmereRuins_Text_TownSign:
	.string "A worn stone sign stands at the\n"
	.string "center of the square.\p"
	.string "Most of the letters are gone.\p"
	.string "What remains reads:\n"
	.string "CO…ALME…E$"

CoralmereRuins_Text_Doorway:
	.string "A low doorway, its lintel carved\n"
	.string "by hand…\p"
	.string "A wave, a bell, and two small fish.\p"
	.string "A welcome, in somebody's language.$"

CoralmereRuins_Text_TowerBase:
	.string "The tower's door is long gone.\p"
	.string "Looking up through it, the water\n"
	.string "brightens, step by step, all the\l"
	.string "way to the sun.\p"
	.string "The bell still hangs at the top.$"

CoralmereRuins_Text_HouseFloor:
	.string "A stone floor, swept clean by\n"
	.string "years of current.\p"
	.string "In the corner, a raised hearth.\p"
	.string "Someone cooked here, once,\n"
	.string "every day.$"

CoralmereRuins_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end
