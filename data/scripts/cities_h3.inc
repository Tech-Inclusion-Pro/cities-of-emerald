@ Cities of Emerald — H3 "The Colossus Wakes" (GDD 6.6, approved
@ 2026-09-17). Follow-up to M2: the Pacifidlog archaeologist has moved
@ her dig to the hills above Petalburg, where the sealed chambers'
@ trail ends at a buried titan-hall. Opens post-League AND only once
@ M2 is complete. Regieleki and Regidrago ward the side alcoves;
@ Regigigas wakes on the dais only when both wardens are caught.
@ Fixed 65 tier (arc table); postgame always obeys.

@ -- Visibility --

Cities_EventScript_UpdateH3Archaeologist::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH3Archaeologist
	goto_if_ne VAR_CITIES_M2_STATE, 2, Cities_EventScript_HideH3Archaeologist
	clearflag FLAG_CITIES_HIDE_H3_ARCHAEOLOGIST
	return

Cities_EventScript_HideH3Archaeologist::
	setflag FLAG_CITIES_HIDE_H3_ARCHAEOLOGIST
	return

Cities_EventScript_UpdateH3Regieleki::
	goto_if_set FLAG_CITIES_H3_REGIELEKI_CAUGHT, Cities_EventScript_HideH3Regieleki
	clearflag FLAG_CITIES_HIDE_H3_REGIELEKI
	return

Cities_EventScript_HideH3Regieleki::
	setflag FLAG_CITIES_HIDE_H3_REGIELEKI
	return

Cities_EventScript_UpdateH3Regidrago::
	goto_if_set FLAG_CITIES_H3_REGIDRAGO_CAUGHT, Cities_EventScript_HideH3Regidrago
	clearflag FLAG_CITIES_HIDE_H3_REGIDRAGO
	return

Cities_EventScript_HideH3Regidrago::
	setflag FLAG_CITIES_HIDE_H3_REGIDRAGO
	return

@ The giant sleeps until both wardens are caught.
Cities_EventScript_UpdateH3Regigigas::
	goto_if_unset FLAG_CITIES_H3_REGIELEKI_CAUGHT, Cities_EventScript_HideH3Regigigas
	goto_if_unset FLAG_CITIES_H3_REGIDRAGO_CAUGHT, Cities_EventScript_HideH3Regigigas
	goto_if_set FLAG_CITIES_H3_REGIGIGAS_CAUGHT, Cities_EventScript_HideH3Regigigas
	clearflag FLAG_CITIES_HIDE_H3_REGIGIGAS
	return

Cities_EventScript_HideH3Regigigas::
	setflag FLAG_CITIES_HIDE_H3_REGIGIGAS
	return

@ -- The archaeologist (Petalburg west tree line, postgame + M2 done) --

Cities_EventScript_H3Archaeologist::
	lock
	faceplayer
	goto_if_eq VAR_CITIES_H3_STATE, 0, Cities_EventScript_H3ArchaeologistIntro
	msgbox Cities_Text_H3ArchRepeat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H3ArchaeologistTravel
	msgbox Cities_Text_H3ArchLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H3ArchaeologistIntro::
	msgbox Cities_Text_H3ArchIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_H3_STATE, 1
	msgbox Cities_Text_H3ArchOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H3ArchaeologistTravel
	msgbox Cities_Text_H3ArchLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H3ArchaeologistTravel::
	msgbox Cities_Text_H3ArchLead, MSGBOX_DEFAULT
	closemessage
	warp MAP_COLOSSUS_VAULT, 8, 11
	waitstate
	release
	end

@ -- Leaving the vault (south alcove trigger tiles) --

Cities_EventScript_H3VaultExit::
	lockall
	warp MAP_PETALBURG_CITY, 3, 11
	waitstate
	releaseall
	end

@ -- The archaeologist inside the vault --

Cities_EventScript_H3VaultArchaeologist::
	lock
	faceplayer
	setvar VAR_0x8004, 10 @ CITIES_ARC_H3
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_H3VaultAllCaught
	goto_if_unset FLAG_CITIES_H3_REGIELEKI_CAUGHT, Cities_EventScript_H3VaultWardens
	goto_if_unset FLAG_CITIES_H3_REGIDRAGO_CAUGHT, Cities_EventScript_H3VaultWardens
	msgbox Cities_Text_H3VaultGiant, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H3VaultWardens::
	msgbox Cities_Text_H3VaultWardens, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H3VaultAllCaught::
	goto_if_eq VAR_CITIES_H3_STATE, 2, Cities_EventScript_H3VaultAfter
	msgbox Cities_Text_H3VaultThanks, MSGBOX_DEFAULT
	setvar VAR_CITIES_H3_STATE, 2
	release
	end

Cities_EventScript_H3VaultAfter::
	msgbox Cities_Text_H3VaultAfter, MSGBOX_DEFAULT
	release
	end

@ -- The titans --

Cities_EventScript_H3Regieleki::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIELEKI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_REGIELEKI
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H3CaughtRegieleki
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H3CaughtRegieleki::
	setflag FLAG_CITIES_H3_REGIELEKI_CAUGHT
	release
	end

Cities_EventScript_H3Regidrago::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIDRAGO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_REGIDRAGO
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H3CaughtRegidrago
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H3CaughtRegidrago::
	setflag FLAG_CITIES_H3_REGIDRAGO_CAUGHT
	release
	end

Cities_EventScript_H3Regigigas::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_REGIGIGAS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_REGIGIGAS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H3CaughtRegigigas
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H3CaughtRegigigas::
	setflag FLAG_CITIES_H3_REGIGIGAS_CAUGHT
	release
	end

@ -- Text --

Cities_Text_H3ArchIntro:
	.string "{PLAYER}! It's me - from PACIFIDLOG!\n"
	.string "The braille chambers, remember?\p"
	.string "I never stopped following the\n"
	.string "trail. Every chamber pointed the\l"
	.string "same direction. Here.\p"
	.string "There's a vault under these hills\n"
	.string "older than the sealed door itself.\l"
	.string "A hall built for something\l"
	.string "ENORMOUS.\p"
	.string "The colossus that towed the\n"
	.string "continents. It was never a myth.\l"
	.string "It was a floor plan.$"

Cities_Text_H3ArchOffer:
	.string "My dig reaches the vault now.\n"
	.string "Come down with me?$"

Cities_Text_H3ArchRepeat:
	.string "Back down to the vault?$"

Cities_Text_H3ArchLater:
	.string "I'll keep cataloguing. The vault\n"
	.string "has waited this long.$"

Cities_Text_H3ArchLead:
	.string "Mind the scaffolding. And keep\n"
	.string "your voice down - it echoes.$"

Cities_Text_H3VaultWardens:
	.string "Look at this hall! The dais alone\n"
	.string "is the size of a house.\p"
	.string "The inscriptions say the giant\n"
	.string "sleeps until its wardens rest:\l"
	.string "one of lightning, one of dragon\l"
	.string "fire, keeping watch in the side\l"
	.string "chambers.\p"
	.string "In plain words: befriend both\n"
	.string "wardens, and the dais won't be\l"
	.string "empty anymore.$"

Cities_Text_H3VaultGiant:
	.string "Both wardens chose you - and\n"
	.string "feel that? The floor is warm.\p"
	.string "It's awake. On the dais.\n"
	.string "The colossus itself.$"

Cities_Text_H3VaultThanks:
	.string "The titans of rock, ice, and\n"
	.string "steel. The wardens of lightning\l"
	.string "and dragon fire. And the colossus\l"
	.string "that towed continents.\p"
	.string "One story, and you walked every\n"
	.string "chapter of it.\p"
	.string "I'm going to write the paper of\n"
	.string "my career. You'll be in the\l"
	.string "acknowledgements. Twice.$"

Cities_Text_H3VaultAfter:
	.string "An empty vault should feel sad.\p"
	.string "This one feels finished.$"
