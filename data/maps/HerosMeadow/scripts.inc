@ Cities of Emerald — Hero's Meadow (H9, GDD 6.6, approved 2026-09-17).
@ Walled meadow beyond Verdanturf: no wild encounters, no puzzles.
@ Reached only by the elder's walk-in; the south gap walks back out.
@ Calyrex appears at the meadow's crown once both steeds are caught.

HerosMeadow_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, HerosMeadow_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, HerosMeadow_OnResume
	.byte 0

HerosMeadow_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

HerosMeadow_OnTransition:
	call Cities_EventScript_UpdateH9Zacian
	call Cities_EventScript_UpdateH9Zamazenta
	call Cities_EventScript_UpdateH9Glastrier
	call Cities_EventScript_UpdateH9Spectrier
	call Cities_EventScript_UpdateH9Calyrex
	call Cities_EventScript_UpdateH9Kubfu
	end
