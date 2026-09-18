@ Cities of Emerald — V5 "The Anchor" (GDD 7.2 / 6.6, Task 12.5,
@ outline approved 2026-09-18). Epoch taps Eternatus and loses
@ control; the storm that gathers heads for Pacifidlog, echoing the
@ storm that took Coralmere. The player and the Archivist go into it
@ together. The heroic act happens here; the family, the name, and
@ everything after belong to 12.6.
@
@ VAR_CITIES_V5_STATE: 0 locked, 1 storm over Pacifidlog, 2 islet
@ reached, 3 rift shut (thread complete; the storm is gone).

@ -- Pacifidlog under the storm (ON_TRANSITION) --

Cities_EventScript_UpdateV5Pacifidlog::
	call Cities_EventScript_V5MaybeStartStorm
	goto_if_eq VAR_CITIES_V5_STATE, 1, Cities_EventScript_V5PacifidlogStorm
	goto_if_eq VAR_CITIES_V5_STATE, 2, Cities_EventScript_V5PacifidlogStorm
	goto_if_ne VAR_CITIES_V5_STATE, 3, Cities_EventScript_V5PacifidlogHideArchivist
	goto_if_unset FLAG_CITIES_KAI_NAMED, Cities_EventScript_V5PacifidlogShowArchivist
	goto_if_unset FLAG_CITIES_V5_ETERNATUS_CAUGHT, Cities_EventScript_V5PacifidlogShowArchivist
	goto Cities_EventScript_V5PacifidlogHideArchivist

Cities_EventScript_V5MaybeStartStorm::
	goto_if_ne VAR_CITIES_V4_STATE, 3, Cities_EventScript_V5MaybeStartStormEnd
	goto_if_ne VAR_CITIES_V5_STATE, 0, Cities_EventScript_V5MaybeStartStormEnd
	setvar VAR_CITIES_V5_STATE, 1
Cities_EventScript_V5MaybeStartStormEnd::
	return

Cities_EventScript_V5PacifidlogStorm::
	setweather WEATHER_DOWNPOUR
Cities_EventScript_V5PacifidlogShowArchivist::
	clearflag FLAG_CITIES_HIDE_V5_ARCHIVIST_PACIFIDLOG
	return

Cities_EventScript_V5PacifidlogHideArchivist::
	setflag FLAG_CITIES_HIDE_V5_ARCHIVIST_PACIFIDLOG
	return

@ -- The Archivist at the Pacifidlog dock --

Cities_EventScript_V5ArchivistPacifidlog::
	lock
	faceplayer
	goto_if_eq VAR_CITIES_V5_STATE, 3, Cities_EventScript_V5ArchivistAfterStorm
	msgbox Cities_Text_V5ArchivistPacifidlog, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Cities_EventScript_V5ArchivistWait
	msgbox Cities_Text_V5ArchivistSail, MSGBOX_DEFAULT
	closemessage
	setvar VAR_CITIES_V5_STATE, 2
	warp MAP_STORMS_EYE, 7, 9
	waitstate
	release
	end

Cities_EventScript_V5ArchivistWait::
	msgbox Cities_Text_V5ArchivistWait, MSGBOX_DEFAULT
	release
	end

@ 12.6: at V5==3 the ending scene comes first; the ferry after.
Cities_EventScript_V5ArchivistAfterStorm::
	goto_if_unset FLAG_CITIES_KAI_NAMED, Cities_EventScript_EndingScene
	goto Cities_EventScript_V5ArchivistFerryBack

@ After the rift is shut: he still ferries the player out while
@ Eternatus remains uncaught.
Cities_EventScript_V5ArchivistFerryBack::
	msgbox Cities_Text_V5ArchivistFerry, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Cities_EventScript_V5ArchivistWait
	closemessage
	warp MAP_STORMS_EYE, 7, 9
	waitstate
	release
	end

@ -- The islet (ON_TRANSITION) --

Cities_EventScript_UpdateV5StormsEye::
	goto_if_set FLAG_CITIES_V5_ETERNATUS_CAUGHT, Cities_EventScript_V5HideEternatus
	clearflag FLAG_CITIES_HIDE_V5_ETERNATUS
	goto Cities_EventScript_V5IsletArchivist

Cities_EventScript_V5HideEternatus::
	setflag FLAG_CITIES_HIDE_V5_ETERNATUS
Cities_EventScript_V5IsletArchivist::
	goto_if_eq VAR_CITIES_V5_STATE, 2, Cities_EventScript_V5ShowIsletArchivist
	goto_if_unset FLAG_CITIES_V5_ETERNATUS_CAUGHT, Cities_EventScript_V5ShowIsletArchivist
	setflag FLAG_CITIES_HIDE_V5_ARCHIVIST_ISLET
	return

Cities_EventScript_V5ShowIsletArchivist::
	clearflag FLAG_CITIES_HIDE_V5_ARCHIVIST_ISLET
	return

Cities_EventScript_V5ArchivistIslet::
	lock
	faceplayer
	goto_if_eq VAR_CITIES_V5_STATE, 3, Cities_EventScript_V5IsletAfter
	msgbox Cities_Text_V5IsletWalk, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_V5IsletAfter::
	msgbox Cities_Text_V5IsletTakeBack, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Cities_EventScript_V5IsletStay
	closemessage
	warp MAP_PACIFIDLOG_TOWN, 9, 17
	waitstate
	release
	end

Cities_EventScript_V5IsletStay::
	msgbox Cities_Text_V5IsletStay, MSGBOX_DEFAULT
	release
	end

@ -- Eternatus, and the heroic act --

Cities_EventScript_V5Eternatus::
	lock
	faceplayer
	msgbox Cities_Text_V5Eternatus, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_ETERNATUS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ETERNATUS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V5CaughtEternatus
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, Cities_EventScript_V5BeatEternatus
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V5CaughtEternatus::
	setflag FLAG_CITIES_V5_ETERNATUS_CAUGHT
	goto Cities_EventScript_V5HeroicAct

Cities_EventScript_V5BeatEternatus::
	goto Cities_EventScript_V5HeroicAct

@ The rift loses its anchor either way; what happens next is his.
Cities_EventScript_V5HeroicAct::
	goto_if_eq VAR_CITIES_V5_STATE, 3, Cities_EventScript_V5HeroicActEnd
	msgbox Cities_Text_V5HeroicAct1, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_WHITE
	setvar VAR_CITIES_V5_STATE, 3
	msgbox Cities_Text_V5HeroicAct2, MSGBOX_DEFAULT
	closemessage
	warp MAP_PACIFIDLOG_TOWN, 9, 17
	waitstate
Cities_EventScript_V5HeroicActEnd::
	release
	end

@ -- Text --

Cities_Text_V5ArchivistPacifidlog:
	.string "He is standing in the rain at\n"
	.string "the dock's edge, coat soaked\l"
	.string "through, watching the wall of\l"
	.string "the storm.\p"
	.string "“I did this. The machine took\n"
	.string "ETERNATUS as its anchor and now\l"
	.string "the storm wants a shore.\p"
	.string "“It's the same storm. Do you\n"
	.string "understand? It is the SAME\l"
	.string "STORM, and this time it wants\l"
	.string "THIS village.\p"
	.string "“I will not be late twice.\p"
	.string "“The eye is holding, out past\n"
	.string "the reef. Will you come with\l"
	.string "me?”$"

Cities_Text_V5ArchivistWait:
	.string "“I'll wait. The eye will not.”$"

Cities_Text_V5ArchivistSail:
	.string "His boat is small and takes the\n"
	.string "waves like it has done this\l"
	.string "before.\p"
	.string "Neither of you speaks on the\n"
	.string "way out.$"

Cities_Text_V5ArchivistFerry:
	.string "“It's still out there, circling\n"
	.string "the eye. Calmer now.\p"
	.string "“Shall I take you out?”$"

Cities_Text_V5IsletWalk:
	.string "The rain stops at the edge of\n"
	.string "the sand, like a curtain.\p"
	.string "“The rift runs through the rock\n"
	.string "under our feet, down into the\l"
	.string "old machine.\p"
	.string "“ETERNATUS is holding it open.\n"
	.string "It doesn't want to. Break its\l"
	.string "grip, and I can reach the\l"
	.string "levers.\p"
	.string "“Whatever you see me do next -\n"
	.string "let me.”$"

Cities_Text_V5IsletTakeBack:
	.string "“The sea is calm now.\n"
	.string "Ready to go back?”$"

Cities_Text_V5IsletStay:
	.string "“Take your time. That's the one\n"
	.string "thing there's plenty of again.”$"

Cities_Text_V5Eternatus:
	.string "The rock hums underfoot.\p"
	.string "Coiled through the heart of the\n"
	.string "islet, vast and exhausted, the\l"
	.string "anchor of the rift raises its\l"
	.string "head.\p"
	.string "It did not ask for this either.$"

Cities_Text_V5HeroicAct1:
	.string "The grip breaks. The rift howls\n"
	.string "open - hungry, unanchored,\l"
	.string "reaching for the village on\l"
	.string "the water.\p"
	.string "The Archivist is already\n"
	.string "moving.\p"
	.string "He puts both hands on the old\n"
	.string "stone and pours EVERYTHING in -\l"
	.string "the machine's charge, the years\l"
	.string "of work, the way back.\p"
	.string "“Not this village.\p"
	.string "“Not ANY village.\p"
	.string "“…Not even for mine.”$"

Cities_Text_V5HeroicAct2:
	.string "The rift closes like a wound\n"
	.string "healing in fast-forward.\p"
	.string "The storm does not fade -\n"
	.string "it simply STOPS, all at once,\l"
	.string "like a held breath let go.\p"
	.string "Somewhere behind the clouds,\n"
	.string "the sun has been waiting.\p"
	.string "The way back to the past is\n"
	.string "gone. He gave it up.\p"
	.string "He is very quiet on the trip\n"
	.string "home.$"
