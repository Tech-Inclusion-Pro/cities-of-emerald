@ Cities of Emerald — H5b "The Lunar Duo" (GDD 6.6, approved 2026-09-17).
@ Dewford can't sleep: a fisher rows the Champion to Moonrise Cove,
@ where Cresselia rests by the moonpool and Darkrai keeps to the dark
@ nook. Fixed 60 tier via the shared special; postgame always obeys
@ (src/cities_arcs.c). Darkrai is written without "monster" framing —
@ its nightmares are something it cannot fully control.

@ -- Visibility --

Cities_EventScript_UpdateH5BFisher::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH5BFisher
	clearflag FLAG_CITIES_HIDE_H5B_FISHER
	return

Cities_EventScript_HideH5BFisher::
	setflag FLAG_CITIES_HIDE_H5B_FISHER
	return

Cities_EventScript_UpdateH5BCresselia::
	goto_if_set FLAG_CITIES_H5B_CRESSELIA_CAUGHT, Cities_EventScript_HideH5BCresselia
	clearflag FLAG_CITIES_HIDE_H5B_CRESSELIA
	return

Cities_EventScript_HideH5BCresselia::
	setflag FLAG_CITIES_HIDE_H5B_CRESSELIA
	return

Cities_EventScript_UpdateH5BDarkrai::
	goto_if_set FLAG_CITIES_H5B_DARKRAI_CAUGHT, Cities_EventScript_HideH5BDarkrai
	clearflag FLAG_CITIES_HIDE_H5B_DARKRAI
	return

Cities_EventScript_HideH5BDarkrai::
	setflag FLAG_CITIES_HIDE_H5B_DARKRAI
	return

@ -- The fisher (Dewford beach, postgame) --

Cities_EventScript_H5BFisher::
	lock
	faceplayer
	goto_if_eq VAR_CITIES_H5B_STATE, 0, Cities_EventScript_H5BFisherIntro
	msgbox Cities_Text_H5BFisherRepeat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H5BFisherTravel
	msgbox Cities_Text_H5BFisherLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H5BFisherIntro::
	msgbox Cities_Text_H5BFisherIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_H5B_STATE, 1
	msgbox Cities_Text_H5BFisherOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H5BFisherTravel
	msgbox Cities_Text_H5BFisherLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H5BFisherTravel::
	msgbox Cities_Text_H5BFisherLead, MSGBOX_DEFAULT
	closemessage
	warp MAP_MOONRISE_COVE, 4, 13
	waitstate
	release
	end

@ -- Leaving the cove (south alcove trigger tiles) --

Cities_EventScript_H5BCoveExit::
	lockall
	warp MAP_DEWFORD_TOWN, 4, 17
	waitstate
	releaseall
	end

@ -- The keeper (inside the cove) --

Cities_EventScript_H5BKeeper::
	lock
	faceplayer
	setvar VAR_0x8004, 7 @ CITIES_ARC_H5B
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_H5BKeeperAllCaught
	msgbox Cities_Text_H5BKeeperPair, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H5BKeeperAllCaught::
	goto_if_eq VAR_CITIES_H5B_STATE, 2, Cities_EventScript_H5BKeeperAfter
	msgbox Cities_Text_H5BKeeperThanks, MSGBOX_DEFAULT
	setvar VAR_CITIES_H5B_STATE, 2
	release
	end

Cities_EventScript_H5BKeeperAfter::
	msgbox Cities_Text_H5BKeeperAfter, MSGBOX_DEFAULT
	release
	end

@ -- The lunar duo --

Cities_EventScript_H5BCresselia::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CRESSELIA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_CRESSELIA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H5BCaughtCresselia
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H5BCaughtCresselia::
	setflag FLAG_CITIES_H5B_CRESSELIA_CAUGHT
	release
	end

Cities_EventScript_H5BDarkrai::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DARKRAI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_DARKRAI
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H5BCaughtDarkrai
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H5BCaughtDarkrai::
	setflag FLAG_CITIES_H5B_DARKRAI_CAUGHT
	release
	end

@ -- Text --

Cities_Text_H5BFisherIntro:
	.string "You look like you slept last\n"
	.string "night. Nobody here can say that.\p"
	.string "The whole town's been sharing bad\n"
	.string "dreams. Same shapes, same dark\l"
	.string "water, every night.\p"
	.string "I followed the pull of the tide\n"
	.string "out past the point. There's a cove\l"
	.string "out there you can only reach by\l"
	.string "boat, and the air over it hums.\p"
	.string "Whatever's dreaming out there,\n"
	.string "CHAMPION, it's bigger than us.$"

Cities_Text_H5BFisherOffer:
	.string "My boat's right here.\n"
	.string "Want me to row you out?$"

Cities_Text_H5BFisherRepeat:
	.string "Out to the cove again?$"

Cities_Text_H5BFisherLater:
	.string "I'll keep the boat ready.\n"
	.string "Sleep well - if you can.$"

Cities_Text_H5BFisherLead:
	.string "Hold on to something. The tide\n"
	.string "does the rowing from here.$"

Cities_Text_H5BKeeperPair:
	.string "Careful where you step - some of\n"
	.string "us are sleeping.\p"
	.string "I kept the lighthouse for forty\n"
	.string "years. Now I keep this cove.\p"
	.string "Two POKéMON rest here. One brings\n"
	.string "the calm dreams. One brings the\l"
	.string "dark ones.\p"
	.string "Before you judge the dark one -\n"
	.string "it can't always help what spills\l"
	.string "out of it. That's not wickedness.\l"
	.string "That's a burden.\p"
	.string "The bright one keeps to the pool.\n"
	.string "The other one likes the back of\l"
	.string "the cave, where it can't hurt\l"
	.string "anyone's sleep but its own.$"

Cities_Text_H5BKeeperThanks:
	.string "Both of them, with you…\p"
	.string "The town will sleep easy tonight.\n"
	.string "And the dreams - bright and dark\l"
	.string "both - are in kind hands now.\p"
	.string "Take care of the dark one\n"
	.string "especially. Few people ever\l"
	.string "bothered to.$"

Cities_Text_H5BKeeperAfter:
	.string "The cove's just a cove now.\p"
	.string "Quietest it's been in forty\n"
	.string "years. I might miss the hum.$"
