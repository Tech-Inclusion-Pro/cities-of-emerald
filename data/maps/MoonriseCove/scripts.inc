@ Cities of Emerald — Moonrise Cove (H5b, GDD 6.6, approved 2026-09-17).
@ Original sea-cave sanctuary: no wild encounters, no Flash. Reached only
@ by the fisher's boat from Dewford; the south alcove rows back.

MoonriseCove_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MoonriseCove_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, MoonriseCove_OnResume
	.byte 0

MoonriseCove_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

MoonriseCove_OnTransition:
	call Cities_EventScript_UpdateH5BCresselia
	call Cities_EventScript_UpdateH5BDarkrai
	end
