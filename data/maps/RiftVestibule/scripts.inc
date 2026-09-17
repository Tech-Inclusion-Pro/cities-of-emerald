@ Cities of Emerald — Rift Vestibule (H5a, GDD 6.6, approved
@ 2026-09-17). Hall behind Lilycove where time and space thin: no
@ wild encounters. Reached via the historian's passage; the south
@ alcove climbs back. Arceus has no overworld sprite — it manifests
@ from the sanctum altar (bg sign) once the creation trio is caught
@ and all 17 Plates are found.

RiftVestibule_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RiftVestibule_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, RiftVestibule_OnResume
	.byte 0

RiftVestibule_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

RiftVestibule_OnTransition:
	call Cities_EventScript_UpdateH5ADialga
	call Cities_EventScript_UpdateH5APalkia
	end
