@ Cities of Emerald — Littleroot Hollow (H1, GDD 6.6, approved 2026-09-17).
@ Original sanctuary map: no wild encounters, no puzzles. Reached only by
@ the ranger's walk-in from Littleroot; the south alcove walks back out.

LittlerootHollow_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootHollow_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, LittlerootHollow_OnResume
	.byte 0

LittlerootHollow_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

LittlerootHollow_OnTransition:
	call Cities_EventScript_UpdateH1Cobalion
	call Cities_EventScript_UpdateH1Terrakion
	call Cities_EventScript_UpdateH1Virizion
	call Cities_EventScript_UpdateH1Keldeo
	end
