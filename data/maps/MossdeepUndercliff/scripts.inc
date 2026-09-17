@ Cities of Emerald — Mossdeep Undercliff (H6, GDD 6.6, approved
@ 2026-09-17). Sea-cut cavern below Mossdeep: no wild encounters.
@ Reached via the ecologist's climb; the south alcove climbs back.
@ Zygarde appears at the center once Xerneas and Yveltal are caught.
@ Five Zygarde Cell pickups use their own collect flags directly as
@ object hide-flags (collect = setflag = gone for good).

MossdeepUndercliff_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepUndercliff_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, MossdeepUndercliff_OnResume
	.byte 0

MossdeepUndercliff_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

MossdeepUndercliff_OnTransition:
	call Cities_EventScript_UpdateH6Xerneas
	call Cities_EventScript_UpdateH6Yveltal
	call Cities_EventScript_UpdateH6Zygarde
	end
