AlteringCave_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, AlteringCave_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, AlteringCave_OnResume
	.byte 0

AlteringCave_OnTransition:
	setflag FLAG_LANDMARK_ALTERING_CAVE
	call Cities_EventScript_UpdateM3RaikouDen
	end

AlteringCave_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M3TryRemoveCaughtBeast
	end

