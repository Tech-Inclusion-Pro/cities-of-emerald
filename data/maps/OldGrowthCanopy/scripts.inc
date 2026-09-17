@ Cities of Emerald — Old-Growth Canopy (H4, GDD 6.6, approved
@ 2026-09-17). Treetop grove above Fortree: no wild encounters.
@ Reached only by the hiker's climb; the south walkway climbs back
@ down. Celebi appears at the moss shrine once Ho-Oh and Lugia are
@ both caught.

OldGrowthCanopy_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, OldGrowthCanopy_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, OldGrowthCanopy_OnResume
	.byte 0

OldGrowthCanopy_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

OldGrowthCanopy_OnTransition:
	call Cities_EventScript_UpdateH4HoOh
	call Cities_EventScript_UpdateH4Lugia
	call Cities_EventScript_UpdateH4Celebi
	end
