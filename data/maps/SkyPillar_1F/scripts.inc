SkyPillar_1F_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, SkyPillar_1F_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, SkyPillar_1F_OnTransition
	.byte 0

SkyPillar_1F_OnTransition:
	call Cities_EventScript_MythicShowMarshadow
	call_if_lt VAR_SKY_PILLAR_STATE, 2, SkyPillar_1F_EventScript_CleanFloor
	end

SkyPillar_1F_EventScript_CleanFloor::
	setmaplayoutindex LAYOUT_SKY_PILLAR_1F_CLEAN
	return


SkyPillar_1F_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end
