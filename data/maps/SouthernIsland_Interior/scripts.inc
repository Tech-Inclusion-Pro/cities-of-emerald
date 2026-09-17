@ Cities of Emerald M5 "The Eon Pair" (GDD 6.6, approved 2026-09-17):
@ both Latias and Latios wait in the grove as statics. The vanilla
@ single-Lati TV-pick cutscene (keyed to VAR_ROAMER_POKEMON, which
@ Cities never sets) is retired; scripts live in data/scripts/cities_m5.inc.

SouthernIsland_Interior_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, SouthernIsland_Interior_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, SouthernIsland_Interior_OnTransition
	.byte 0

SouthernIsland_Interior_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M5TryRemoveCaughtLati
	end

SouthernIsland_Interior_OnTransition:
	call Cities_EventScript_UpdateM5Latias
	call Cities_EventScript_UpdateM5Latios
	end
