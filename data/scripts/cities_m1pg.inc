@ Cities of Emerald — M1-PG "Stranger Weather" (GDD 6.6, approved
@ 2026-09-17). Postgame follow-up to M1: the three anomalies return to
@ the same sites with impossible readings — the Galarian birds. The M1
@ reporter's script branches here once the player is Champion with M1
@ complete. Fixed postgame tier: the shared 10.0a special already
@ settles at level 60 after the Champion. Postgame legendaries always
@ obey (handled in src/cities_arcs.c).

@ -- Visibility (called from each site's on_transition, after the M1 calls) --

Cities_EventScript_UpdateM1PGArticuno::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideM1PGArticuno
	goto_if_ne VAR_CITIES_M1_STATE, 2, Cities_EventScript_HideM1PGArticuno
	goto_if_set FLAG_CITIES_M1PG_ARTICUNO_CAUGHT, Cities_EventScript_HideM1PGArticuno
	clearflag FLAG_CITIES_HIDE_M1PG_ARTICUNO
	return

Cities_EventScript_HideM1PGArticuno::
	setflag FLAG_CITIES_HIDE_M1PG_ARTICUNO
	return

Cities_EventScript_UpdateM1PGZapdos::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideM1PGZapdos
	goto_if_ne VAR_CITIES_M1_STATE, 2, Cities_EventScript_HideM1PGZapdos
	goto_if_set FLAG_CITIES_M1PG_ZAPDOS_CAUGHT, Cities_EventScript_HideM1PGZapdos
	clearflag FLAG_CITIES_HIDE_M1PG_ZAPDOS
	return

Cities_EventScript_HideM1PGZapdos::
	setflag FLAG_CITIES_HIDE_M1PG_ZAPDOS
	return

Cities_EventScript_UpdateM1PGMoltres::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideM1PGMoltres
	goto_if_ne VAR_CITIES_M1_STATE, 2, Cities_EventScript_HideM1PGMoltres
	goto_if_set FLAG_CITIES_M1PG_MOLTRES_CAUGHT, Cities_EventScript_HideM1PGMoltres
	clearflag FLAG_CITIES_HIDE_M1PG_MOLTRES
	return

Cities_EventScript_HideM1PGMoltres::
	setflag FLAG_CITIES_HIDE_M1PG_MOLTRES
	return

@ -- The reporter's postgame branch (reached from Cities_EventScript_M1ReporterAfter
@    once FLAG_SYS_GAME_CLEAR is set; M1 is complete on that path by design) --

Cities_EventScript_M1PGReporter::
	setvar VAR_0x8004, 5 @ CITIES_ARC_M1PG
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_M1PGReporterAllCaught
	goto_if_eq VAR_CITIES_M1PG_STATE, 0, Cities_EventScript_M1PGReporterIntro
	msgbox Cities_Text_M1PGReporterProgress, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_M1PGReporterIntro::
	msgbox Cities_Text_M1PGReporterIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_M1PG_STATE, 1
	release
	end

Cities_EventScript_M1PGReporterAllCaught::
	goto_if_eq VAR_CITIES_M1PG_STATE, 2, Cities_EventScript_M1PGReporterAfter
	msgbox Cities_Text_M1PGReporterThanks, MSGBOX_DEFAULT
	setvar VAR_CITIES_M1PG_STATE, 2
	release
	end

Cities_EventScript_M1PGReporterAfter::
	msgbox Cities_Text_M1PGReporterAfter, MSGBOX_DEFAULT
	release
	end

@ -- The birds --

Cities_EventScript_M1PGMoltres::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MOLTRES_GALAR, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MOLTRES_GALAR
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M1PGCaughtMoltres
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_M1PGCaughtMoltres::
	setflag FLAG_CITIES_M1PG_MOLTRES_CAUGHT
	release
	end

Cities_EventScript_M1PGArticuno::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ARTICUNO_GALAR, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ARTICUNO_GALAR
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M1PGCaughtArticuno
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_M1PGCaughtArticuno::
	setflag FLAG_CITIES_M1PG_ARTICUNO_CAUGHT
	release
	end

Cities_EventScript_M1PGZapdos::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZAPDOS_GALAR, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ZAPDOS_GALAR
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M1PGCaughtZapdos
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_M1PGCaughtZapdos::
	setflag FLAG_CITIES_M1PG_ZAPDOS_CAUGHT
	release
	end

@ -- Text --

Cities_Text_M1PGReporterIntro:
	.string "{PLAYER}! The CHAMPION reads my\n"
	.string "column! Then you should hear it\l"
	.string "first:\p"
	.string "The anomalies are BACK. Same\n"
	.string "three places. But my instruments\l"
	.string "must be broken.\p"
	.string "A cold snap in SHOAL CAVE that\n"
	.string "reads as… silence. A storm over\l"
	.string "NEW MAUVILLE with no charge in\l"
	.string "it. And a fire in FIERY PATH\l"
	.string "that doesn't burn.\p"
	.string "Where did your three come from,\n"
	.string "I asked once. Maybe the answer\l"
	.string "flew here to meet you.$"

Cities_Text_M1PGReporterProgress:
	.string "Impossible readings, all three\n"
	.string "sites. FIERY PATH, SHOAL CAVE,\l"
	.string "NEW MAUVILLE.\p"
	.string "Whatever they are, they're not\n"
	.string "our birds. But they're waiting\l"
	.string "for someone.$"

Cities_Text_M1PGReporterThanks:
	.string "You caught all three?! And they\n"
	.string "look like… but they're not…\p"
	.string "Two sets of three. Same sky,\n"
	.string "different songs.\p"
	.string "Best story of my career - twice.$"

Cities_Text_M1PGReporterAfter:
	.string "My editor still doesn't believe\n"
	.string "the photos.$"
