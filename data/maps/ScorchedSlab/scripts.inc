ScorchedSlab_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ScorchedSlab_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, ScorchedSlab_OnResume
	.byte 0

ScorchedSlab_OnTransition:
	setflag FLAG_LANDMARK_SCORCHED_SLAB
	call Cities_EventScript_UpdateM3EnteiDen
	end

ScorchedSlab_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M3TryRemoveCaughtBeast
	end

