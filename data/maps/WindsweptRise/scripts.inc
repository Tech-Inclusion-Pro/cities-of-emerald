@ Cities of Emerald — Windswept Rise (H8, GDD 6.6, approved 2026-09-17).
@ High ash moor above Fallarbor: four stone perches, no wild encounters.
@ Reached via the researcher's trail; the south gap climbs back down.
@ Enamorus arrives at the empty fourth perch once the trio is caught.

WindsweptRise_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, WindsweptRise_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, WindsweptRise_OnResume
	.byte 0

WindsweptRise_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

WindsweptRise_OnTransition:
	call Cities_EventScript_UpdateH8Tornadus
	call Cities_EventScript_UpdateH8Thundurus
	call Cities_EventScript_UpdateH8Landorus
	call Cities_EventScript_UpdateH8Enamorus
	end
