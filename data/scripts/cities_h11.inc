@ Cities of Emerald — H11 "The Heart of the Mountain" (GDD 6.6,
@ approved 2026-09-17). The summit instruments pick up a second, slower
@ pulse under Mt. Chimney. A volcanologist has found the vent down and
@ won't go alone; inside, she stays near the entrance while the player
@ approaches Heatran on the basalt floor. Smallest arc: one species,
@ one guide who doubles as the caretaker. Fixed 60 tier; postgame
@ always obeys (src/cities_arcs.c).

@ -- Visibility --

Cities_EventScript_UpdateH11Volcanologist::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH11Volcanologist
	clearflag FLAG_CITIES_HIDE_H11_VOLCANOLOGIST
	return

Cities_EventScript_HideH11Volcanologist::
	setflag FLAG_CITIES_HIDE_H11_VOLCANOLOGIST
	return

Cities_EventScript_UpdateH11Heatran::
	goto_if_set FLAG_CITIES_H11_HEATRAN_CAUGHT, Cities_EventScript_HideH11Heatran
	clearflag FLAG_CITIES_HIDE_H11_HEATRAN
	return

Cities_EventScript_HideH11Heatran::
	setflag FLAG_CITIES_HIDE_H11_HEATRAN
	return

@ -- The volcanologist (Mt. Chimney summit, postgame) --

Cities_EventScript_H11Volcanologist::
	lock
	faceplayer
	goto_if_eq VAR_CITIES_H11_STATE, 0, Cities_EventScript_H11VolcanologistIntro
	msgbox Cities_Text_H11VolcanologistRepeat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H11VolcanologistTravel
	msgbox Cities_Text_H11VolcanologistLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H11VolcanologistIntro::
	msgbox Cities_Text_H11VolcanologistIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_H11_STATE, 1
	msgbox Cities_Text_H11VolcanologistOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H11VolcanologistTravel
	msgbox Cities_Text_H11VolcanologistLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H11VolcanologistTravel::
	msgbox Cities_Text_H11VolcanologistLead, MSGBOX_DEFAULT
	closemessage
	warp MAP_EMBER_VAULT, 7, 9
	waitstate
	release
	end

@ -- Leaving the vault (south alcove trigger tiles) --

Cities_EventScript_H11VaultExit::
	lockall
	warp MAP_MT_CHIMNEY, 20, 38
	waitstate
	releaseall
	end

@ -- The volcanologist inside the vault --

Cities_EventScript_H11VaultVolcanologist::
	lock
	faceplayer
	setvar VAR_0x8004, 9 @ CITIES_ARC_H11
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_H11VaultAllCaught
	msgbox Cities_Text_H11VaultPulse, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H11VaultAllCaught::
	goto_if_eq VAR_CITIES_H11_STATE, 2, Cities_EventScript_H11VaultAfter
	msgbox Cities_Text_H11VaultThanks, MSGBOX_DEFAULT
	setvar VAR_CITIES_H11_STATE, 2
	release
	end

Cities_EventScript_H11VaultAfter::
	msgbox Cities_Text_H11VaultAfter, MSGBOX_DEFAULT
	release
	end

@ -- The heart of the mountain --

Cities_EventScript_H11Heatran::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_HEATRAN, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_HEATRAN
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H11CaughtHeatran
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H11CaughtHeatran::
	setflag FLAG_CITIES_H11_HEATRAN_CAUGHT
	release
	end

@ -- Text --

Cities_Text_H11VolcanologistIntro:
	.string "CHAMPION! Perfect timing. Look at\n"
	.string "this readout.\p"
	.string "The mountain has a heartbeat.\n"
	.string "We've always known that one -\l"
	.string "magma, rising and falling.\p"
	.string "But since the crisis ended, there's\n"
	.string "a SECOND pulse. Slower. Deeper.\l"
	.string "Too steady to be magma.\p"
	.string "I found the vent it echoes up\n"
	.string "through. I'll be honest - I'm not\l"
	.string "going down there alone.$"

Cities_Text_H11VolcanologistOffer:
	.string "The vent's right here.\n"
	.string "Climb down with me?$"

Cities_Text_H11VolcanologistRepeat:
	.string "Back down the vent?$"

Cities_Text_H11VolcanologistLater:
	.string "I'll keep logging the pulse.\n"
	.string "It's not going anywhere. Probably.$"

Cities_Text_H11VolcanologistLead:
	.string "Watch your grip - and don't\n"
	.string "touch anything that glows.$"

Cities_Text_H11VaultPulse:
	.string "Feel that? The floor beats like\n"
	.string "a drum.\p"
	.string "It's been asleep down here since\n"
	.string "before SOOTOPOLIS was a crater.\l"
	.string "The crisis woke GROUDON - and\l"
	.string "GROUDON's waking stirred this one.\p"
	.string "There it is, on the basalt.\n"
	.string "The heart of the mountain.$"

Cities_Text_H11VaultThanks:
	.string "The second pulse just… stopped.\n"
	.string "And the mountain didn't mind.\p"
	.string "It still rumbles - but now it's\n"
	.string "just a mountain.\p"
	.string "Its heart chose to go see the\n"
	.string "world. Take good care of it.$"

Cities_Text_H11VaultAfter:
	.string "One heartbeat, steady as ever.\p"
	.string "Shortest research paper I'll ever\n"
	.string "write. Worth it.$"
