@ Cities of Emerald — M3 "On the Trail" (GDD 6.6, approved 2026-09-17).
@ Ranger in the Fortree Pokémon Center releases Raikou, Entei, and
@ Suicune as roamers (src/cities_m3.c). After three battle meetings a
@ beast settles in its den: Raikou in Altering Cave, Entei in Scorched
@ Slab, Suicune in Meteor Falls. Levels come from the shared 10.0a
@ special; a defeated beast recovers (only catching removes it).

@ -- Visibility (called from each map's on_transition) --

Cities_EventScript_UpdateM3Ranger::
	goto_if_set FLAG_BADGE06_GET, Cities_EventScript_ShowM3Ranger
	setflag FLAG_CITIES_HIDE_M3_RANGER
	return

Cities_EventScript_ShowM3Ranger::
	clearflag FLAG_CITIES_HIDE_M3_RANGER
	return

Cities_EventScript_UpdateM3RaikouDen::
	setvar VAR_0x8004, 0 @ CITIES_M3_RAIKOU
	specialvar VAR_RESULT, Script_CitiesM3DenVisible
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_ShowM3RaikouDen
	setflag FLAG_CITIES_HIDE_M3_RAIKOU
	return

Cities_EventScript_ShowM3RaikouDen::
	clearflag FLAG_CITIES_HIDE_M3_RAIKOU
	return

Cities_EventScript_UpdateM3EnteiDen::
	setvar VAR_0x8004, 1 @ CITIES_M3_ENTEI
	specialvar VAR_RESULT, Script_CitiesM3DenVisible
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_ShowM3EnteiDen
	setflag FLAG_CITIES_HIDE_M3_ENTEI
	return

Cities_EventScript_ShowM3EnteiDen::
	clearflag FLAG_CITIES_HIDE_M3_ENTEI
	return

Cities_EventScript_UpdateM3SuicuneDen::
	setvar VAR_0x8004, 2 @ CITIES_M3_SUICUNE
	specialvar VAR_RESULT, Script_CitiesM3DenVisible
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_ShowM3SuicuneDen
	setflag FLAG_CITIES_HIDE_M3_SUICUNE
	return

Cities_EventScript_ShowM3SuicuneDen::
	clearflag FLAG_CITIES_HIDE_M3_SUICUNE
	return

@ -- The ranger (Fortree Pokémon Center) --

Cities_EventScript_M3Ranger::
	lock
	faceplayer
	setvar VAR_0x8004, 2 @ CITIES_ARC_M3
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_M3RangerAllCaught
	goto_if_eq VAR_CITIES_M3_STATE, 0, Cities_EventScript_M3RangerIntro
	msgbox Cities_Text_M3RangerProgress, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_M3RangerIntro::
	msgbox Cities_Text_M3RangerIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_M3_STATE, 1
	special Script_CitiesM3StartRoamers
	msgbox Cities_Text_M3RangerTracker, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_M3RangerAllCaught::
	goto_if_eq VAR_CITIES_M3_STATE, 2, Cities_EventScript_M3RangerAfter
	msgbox Cities_Text_M3RangerThanks, MSGBOX_DEFAULT
	setvar VAR_CITIES_M3_STATE, 2
	release
	end

Cities_EventScript_M3RangerAfter::
	msgbox Cities_Text_M3RangerAfter, MSGBOX_DEFAULT
	release
	end

@ -- Cornered notices (queued after the third battle meeting) --

Cities_EventScript_M3RaikouCornered::
	lockall
	msgbox Cities_Text_M3RaikouCornered, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

Cities_EventScript_M3EnteiCornered::
	lockall
	msgbox Cities_Text_M3EnteiCornered, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

Cities_EventScript_M3SuicuneCornered::
	lockall
	msgbox Cities_Text_M3SuicuneCornered, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

@ -- The dens --

Cities_EventScript_M3RaikouDen::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_RAIKOU, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_RAIKOU
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M3CaughtRaikou
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_M3CaughtRaikou::
	setflag FLAG_CITIES_M3_RAIKOU_CAUGHT
	setflag FLAG_CITIES_HIDE_M3_RAIKOU
	release
	end

Cities_EventScript_M3EnteiDen::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ENTEI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ENTEI
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M3CaughtEntei
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_M3CaughtEntei::
	setflag FLAG_CITIES_M3_ENTEI_CAUGHT
	setflag FLAG_CITIES_HIDE_M3_ENTEI
	release
	end

Cities_EventScript_M3SuicuneDen::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SUICUNE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_SUICUNE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M3CaughtSuicune
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_M3CaughtSuicune::
	setflag FLAG_CITIES_M3_SUICUNE_CAUGHT
	setflag FLAG_CITIES_HIDE_M3_SUICUNE
	release
	end

@ Den maps' on_resume: if the beast was just caught in a scripted
@ battle, remove its object right away (same rule as M1's birds).
Cities_EventScript_M3TryRemoveCaughtBeast::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

@ -- Text --

Cities_Text_M3RangerIntro:
	.string "Oh! You're the trainer with six\n"
	.string "BADGES, right? Perfect timing.\p"
	.string "I'm a POKéMON RANGER. Three rare\n"
	.string "Pokémon crossed into HOENN:\l"
	.string "RAIKOU, ENTEI, and SUICUNE.\p"
	.string "They never stay in one place.\n"
	.string "They run from route to route,\l"
	.string "fast as storms.$"

Cities_Text_M3RangerTracker:
	.string "Here - I'll link my tracker to\n"
	.string "your journal.\p"
	.string "It will always show where each\n"
	.string "beast was last seen.\p"
	.string "One more tip: meet a beast enough\n"
	.string "times and it will tire out and\l"
	.string "settle down somewhere quiet.\p"
	.string "Good luck out there!$"

Cities_Text_M3RangerProgress:
	.string "Still on the trail? Check your\n"
	.string "journal for where each beast was\l"
	.string "last seen.\p"
	.string "A beast that slips away isn't\n"
	.string "gone. It just keeps running.$"

Cities_Text_M3RangerThanks:
	.string "All three?! RAIKOU, ENTEI, and\n"
	.string "SUICUNE, running with YOU now.\p"
	.string "…You know the old story, right?\n"
	.string "Something with rainbow wings\l"
	.string "revived those three, long ago.\p"
	.string "I'd love to see whatever THAT\n"
	.string "was.$"

Cities_Text_M3RangerAfter:
	.string "RAIKOU, ENTEI, and SUICUNE chose\n"
	.string "a fine trainer.$"

Cities_Text_M3RaikouCornered:
	.string "RAIKOU is worn out from all that\n"
	.string "running!\p"
	.string "The RANGER's tracker says it went\n"
	.string "to ground in ALTERING CAVE, the\l"
	.string "small cave on ROUTE 103's shore.$"

Cities_Text_M3EnteiCornered:
	.string "ENTEI is worn out from all that\n"
	.string "running!\p"
	.string "The RANGER's tracker says it went\n"
	.string "to ground in SCORCHED SLAB, the\l"
	.string "cave in ROUTE 120's lake.$"

Cities_Text_M3SuicuneCornered:
	.string "SUICUNE is worn out from all that\n"
	.string "running!\p"
	.string "The RANGER's tracker says it went\n"
	.string "to ground deep in METEOR FALLS,\l"
	.string "up past the waterfall.$"
