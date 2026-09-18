@ Cities of Emerald — Mossdeep annex (V1 "Products and Targets",
@ Task 12.5). All V1 logic lives in data/scripts/cities_v1.inc.
MossdeepAnnex_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepAnnex_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, MossdeepAnnex_OnResume
	.byte 0

MossdeepAnnex_OnTransition:
	call Cities_EventScript_UpdateV1Annex
	call Cities_EventScript_UpdateEpilogueArchive
	end

MossdeepAnnex_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end
