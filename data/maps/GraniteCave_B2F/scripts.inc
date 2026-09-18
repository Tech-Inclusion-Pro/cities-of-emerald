GraniteCave_B2F_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, GraniteCave_B2F_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, GraniteCave_B2F_OnTransition
	.byte 0


GraniteCave_B2F_OnTransition:
	call Cities_EventScript_MythicShowDiancie
	end

GraniteCave_B2F_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end
