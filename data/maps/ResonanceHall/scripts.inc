@ Cities of Emerald — Resonance Hall (H7, GDD 6.6, approved 2026-09-17).
@ Deep vault under Mauville: no wild encounters. Reached via the
@ engineer's service shaft; the south alcove climbs back. Kyurem
@ appears at the cold north end once Reshiram and Zekrom are caught.

ResonanceHall_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ResonanceHall_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, ResonanceHall_OnResume
	.byte 0

ResonanceHall_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

ResonanceHall_OnTransition:
	call Cities_EventScript_UpdateH7Reshiram
	call Cities_EventScript_UpdateH7Zekrom
	call Cities_EventScript_UpdateH7Kyurem
	end
