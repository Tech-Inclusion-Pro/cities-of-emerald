Underwater_Route128_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, Underwater_Route128_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Underwater_Route128_OnTransition
	.byte 0


@ Cities of Emerald — Task 12.3: the way down to Coralmere.
Underwater_Route128_EventScript_CitiesCutStone::
	msgbox Underwater_Route128_Text_CitiesCutStone, MSGBOX_SIGN
	end

Underwater_Route128_Text_CitiesCutStone:
	.string "Cut stone, planted in rows,\n"
	.string "half-buried in the sand.\p"
	.string "The dark opening ahead is framed\n"
	.string "in the same stone.\p"
	.string "It was made, not grown.$"

Underwater_Route128_OnTransition:
	call Cities_EventScript_UpdateV4Underwater128
	end

Underwater_Route128_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end
