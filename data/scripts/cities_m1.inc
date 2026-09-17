@ Cities of Emerald — M1 "Strange Weather" (GDD 6.6, approved 2026-09-16).
@ Reporter in the Slateport Pokémon Center; Moltres in Fiery Path,
@ Articuno in Shoal Cave's ice room, Zapdos in New Mauville. Levels come
@ from the shared 10.0a special; a defeated bird returns on re-entry
@ (only catching sets its CAUGHT flag).

@ -- Visibility (called from each map's on_transition) --

Cities_EventScript_UpdateM1Npcs::
	goto_if_set FLAG_BADGE03_GET, Cities_EventScript_ShowM1Npcs
	setflag FLAG_CITIES_HIDE_M1_NPCS
	return

Cities_EventScript_ShowM1Npcs::
	clearflag FLAG_CITIES_HIDE_M1_NPCS
	return

Cities_EventScript_UpdateM1Articuno::
	goto_if_unset FLAG_BADGE03_GET, Cities_EventScript_HideM1Articuno
	goto_if_set FLAG_CITIES_M1_ARTICUNO_CAUGHT, Cities_EventScript_HideM1Articuno
	clearflag FLAG_CITIES_HIDE_M1_ARTICUNO
	return

Cities_EventScript_HideM1Articuno::
	setflag FLAG_CITIES_HIDE_M1_ARTICUNO
	return

Cities_EventScript_UpdateM1Zapdos::
	goto_if_unset FLAG_BADGE03_GET, Cities_EventScript_HideM1Zapdos
	goto_if_set FLAG_CITIES_M1_ZAPDOS_CAUGHT, Cities_EventScript_HideM1Zapdos
	clearflag FLAG_CITIES_HIDE_M1_ZAPDOS
	return

Cities_EventScript_HideM1Zapdos::
	setflag FLAG_CITIES_HIDE_M1_ZAPDOS
	return

Cities_EventScript_UpdateM1Moltres::
	goto_if_unset FLAG_BADGE03_GET, Cities_EventScript_HideM1Moltres
	goto_if_set FLAG_CITIES_M1_MOLTRES_CAUGHT, Cities_EventScript_HideM1Moltres
	clearflag FLAG_CITIES_HIDE_M1_MOLTRES
	return

Cities_EventScript_HideM1Moltres::
	setflag FLAG_CITIES_HIDE_M1_MOLTRES
	return

@ -- The reporter (Slateport Pokémon Center) --

Cities_EventScript_M1Reporter::
	lock
	faceplayer
	setvar VAR_0x8004, 0 @ CITIES_ARC_M1
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_M1ReporterAllCaught
	goto_if_eq VAR_CITIES_M1_STATE, 0, Cities_EventScript_M1ReporterIntro
	msgbox Cities_Text_M1ReporterProgress, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_M1ReporterIntro::
	msgbox Cities_Text_M1ReporterIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_M1_STATE, 1
	release
	end

Cities_EventScript_M1ReporterAllCaught::
	goto_if_eq VAR_CITIES_M1_STATE, 2, Cities_EventScript_M1ReporterAfter
	msgbox Cities_Text_M1ReporterThanks, MSGBOX_DEFAULT
	setvar VAR_CITIES_M1_STATE, 2
	release
	end

Cities_EventScript_M1ReporterAfter::
	goto_if_set FLAG_SYS_GAME_CLEAR, Cities_EventScript_M1PGReporter @ M1-PG "Stranger Weather" (cities_m1pg.inc)
	msgbox Cities_Text_M1ReporterAfter, MSGBOX_DEFAULT
	release
	end

@ -- Site scientists --

Cities_EventScript_M1ScientistFire::
	msgbox Cities_Text_M1ScientistFire, MSGBOX_NPC
	end

Cities_EventScript_M1ScientistIce::
	msgbox Cities_Text_M1ScientistIce, MSGBOX_NPC
	end

Cities_EventScript_M1ScientistElectric::
	msgbox Cities_Text_M1ScientistElectric, MSGBOX_NPC
	end

@ -- The birds --

Cities_EventScript_M1Moltres::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MOLTRES, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MOLTRES
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M1CaughtMoltres
	goto Cities_EventScript_M1BirdWithdrew

Cities_EventScript_M1CaughtMoltres::
	setflag FLAG_CITIES_M1_MOLTRES_CAUGHT
	release
	end

Cities_EventScript_M1Articuno::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ARTICUNO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ARTICUNO
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M1CaughtArticuno
	goto Cities_EventScript_M1BirdWithdrew

Cities_EventScript_M1CaughtArticuno::
	setflag FLAG_CITIES_M1_ARTICUNO_CAUGHT
	release
	end

Cities_EventScript_M1Zapdos::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZAPDOS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ZAPDOS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M1CaughtZapdos
	goto Cities_EventScript_M1BirdWithdrew

Cities_EventScript_M1CaughtZapdos::
	setflag FLAG_CITIES_M1_ZAPDOS_CAUGHT
	release
	end

@ Defeated, fled, or teleported: the legendary slips away but is not
@ lost. Shared by M1's birds and M2's Regis (VAR_0x8004 holds the species).
Cities_EventScript_LegendWithdrew::
Cities_EventScript_M1BirdWithdrew::
	bufferspeciesname STR_VAR_1, VAR_0x8004
	msgbox Cities_Text_M1BirdWithdrew, MSGBOX_DEFAULT
	fadescreenswapbuffers FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreenswapbuffers FADE_FROM_BLACK
	release
	end

@ -- Text --

Cities_Text_M1ReporterIntro:
	.string "Oh! You're a trainer, right?\p"
	.string "I'm covering the strangest story of\n"
	.string "my career. Three weather anomalies,\l"
	.string "all at once:\p"
	.string "an ice storm deep in SHOAL CAVE,\n"
	.string "electric surges under NEW MAUVILLE,\l"
	.string "and a heat bloom inside FIERY PATH.\p"
	.string "Something POWERFUL must be behind\n"
	.string "each one.\p"
	.string "If you go look, be careful - and\n"
	.string "tell me what you find!$"

Cities_Text_M1ReporterProgress:
	.string "Any luck with those weather\n"
	.string "anomalies?\p"
	.string "SHOAL CAVE and NEW MAUVILLE are\n"
	.string "across the water - you'll need\l"
	.string "SURF to reach them.$"

Cities_Text_M1ReporterThanks:
	.string "You calmed all three?! The birds of\n"
	.string "legend themselves…\p"
	.string "This is the story of a lifetime.\n"
	.string "Thank you, {PLAYER}!\p"
	.string "…Though I keep wondering.\n"
	.string "Where do storms like those come\l"
	.string "from? And are there MORE of them?$"

Cities_Text_M1ReporterAfter:
	.string "The weather's been calm ever since.\p"
	.string "If I hear about anything strange\n"
	.string "again, you'll be the first to know.$"

Cities_Text_M1ScientistFire:
	.string "The rock in this tunnel is hot\n"
	.string "enough to fry an egg!\p"
	.string "Whatever's causing it is deeper\n"
	.string "inside. I'm not going further.$"

Cities_Text_M1ScientistIce:
	.string "This cave's ice room is colder than\n"
	.string "it has ever been on record.\p"
	.string "My instruments say the source is\n"
	.string "down at the deepest level.$"

Cities_Text_M1ScientistElectric:
	.string "The old generator can't explain\n"
	.string "surges this big.\p"
	.string "Something in there is MAKING\n"
	.string "electricity. A lot of it.$"

Cities_Text_M1BirdWithdrew:
	.string "{STR_VAR_1} slipped away deeper in!\p"
	.string "It hasn't left - you can try again\n"
	.string "after stepping out for a while.$"

@ ON_RESUME helper: after a catch, drop the object before the field redraws.
Cities_EventScript_M1TryRemoveCaughtBird::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return
