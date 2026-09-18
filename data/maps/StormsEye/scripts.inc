@ Cities of Emerald — the Storm's Eye (V5 "The Anchor", Task 12.5).
@ Reached only by the Archivist's boat. All V5 logic lives in
@ data/scripts/cities_v5.inc.
StormsEye_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, StormsEye_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, StormsEye_OnResume
	.byte 0

StormsEye_OnTransition:
	call Cities_EventScript_UpdateV5StormsEye
	end

StormsEye_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end
