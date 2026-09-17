@ Cities of Emerald — Ember Vault (H11, GDD 6.6, approved 2026-09-17).
@ Original magma chamber under Mt. Chimney: no wild encounters. Reached
@ only via the volcanologist's vent at the summit; the south alcove
@ climbs back out.

EmberVault_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EmberVault_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, EmberVault_OnResume
	.byte 0

EmberVault_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

EmberVault_OnTransition:
	call Cities_EventScript_UpdateH11Heatran
	end
