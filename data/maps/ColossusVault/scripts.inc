@ Cities of Emerald — Colossus Vault (H3, GDD 6.6, approved 2026-09-17).
@ Buried titan-hall above Petalburg: no wild encounters. Reached only
@ via the archaeologist's dig; the south alcove climbs back out.
@ Regigigas sleeps on the dais until both wardens are caught.

ColossusVault_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ColossusVault_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, ColossusVault_OnResume
	.byte 0

ColossusVault_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

ColossusVault_OnTransition:
	call Cities_EventScript_UpdateH3Regieleki
	call Cities_EventScript_UpdateH3Regidrago
	call Cities_EventScript_UpdateH3Regigigas
	end
