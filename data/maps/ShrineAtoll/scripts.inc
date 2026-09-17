@ Cities of Emerald — Shrine Atoll (H10, GDD 6.6, approved 2026-09-17).
@ Original atoll: five log platforms, four shrines, no wild encounters.
@ Reached only by the elder's raft from Pacifidlog; the moored raft at
@ the center platform's south-east corner poles back.

ShrineAtoll_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ShrineAtoll_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, ShrineAtoll_OnResume
	.byte 0

ShrineAtoll_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

ShrineAtoll_OnTransition:
	call Cities_EventScript_UpdateH10Koko
	call Cities_EventScript_UpdateH10Lele
	call Cities_EventScript_UpdateH10Bulu
	call Cities_EventScript_UpdateH10Fini
	end
