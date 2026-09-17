@ Cities of Emerald — M5 "The Eon Pair" (GDD 6.6, approved 2026-09-17).
@ A sailor in the Lilycove harbor terminal appears at badge 8, gives
@ the EON TICKET, and sails the player to Southern Island himself (the
@ SS Tidal is post-League, so he fills the Briney role; the vanilla
@ enable-ship flag is still set for post-League ferry convenience).
@ Both Latias and Latios wait in the grove as statics — the vanilla
@ single-Lati TV-pick cutscene is retired. Levels come from the shared
@ 10.0a special; obedience is the shared pair rule (neither listens
@ until both are caught). The Eon stone yields Latiasite + Latiosite
@ once both travel with the player.

@ -- Visibility (called from each map's on_transition) --

Cities_EventScript_UpdateM5Sailor::
	goto_if_set FLAG_BADGE08_GET, Cities_EventScript_ShowM5Sailor
	setflag FLAG_CITIES_HIDE_M5_SAILOR
	return

Cities_EventScript_ShowM5Sailor::
	clearflag FLAG_CITIES_HIDE_M5_SAILOR
	return

Cities_EventScript_UpdateM5Latias::
	goto_if_set FLAG_CITIES_M5_LATIAS_CAUGHT, Cities_EventScript_HideM5Latias
	clearflag FLAG_CITIES_HIDE_M5_LATIAS
	return

Cities_EventScript_HideM5Latias::
	setflag FLAG_CITIES_HIDE_M5_LATIAS
	return

Cities_EventScript_UpdateM5Latios::
	goto_if_set FLAG_CITIES_M5_LATIOS_CAUGHT, Cities_EventScript_HideM5Latios
	clearflag FLAG_CITIES_HIDE_M5_LATIOS
	return

Cities_EventScript_HideM5Latios::
	setflag FLAG_CITIES_HIDE_M5_LATIOS
	return

@ Grove on_resume: if a Lati was just caught, remove its object right
@ away (same rule as M1's birds).
Cities_EventScript_M5TryRemoveCaughtLati::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

@ -- The sailor (Lilycove harbor terminal) --

Cities_EventScript_M5Sailor::
	lock
	faceplayer
	setvar VAR_0x8004, 4 @ CITIES_ARC_M5
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_M5SailorAllCaught
	goto_if_eq VAR_CITIES_M5_STATE, 0, Cities_EventScript_M5SailorIntro
	msgbox Cities_Text_M5SailorProgress, MSGBOX_DEFAULT
	goto Cities_EventScript_M5SailorOfferSail

Cities_EventScript_M5SailorIntro::
	msgbox Cities_Text_M5SailorIntro, MSGBOX_DEFAULT
	giveitem ITEM_EON_TICKET
	setflag FLAG_ENABLE_SHIP_SOUTHERN_ISLAND
	setvar VAR_CITIES_M5_STATE, 1
	msgbox Cities_Text_M5SailorTicket, MSGBOX_DEFAULT
	goto Cities_EventScript_M5SailorOfferSail

Cities_EventScript_M5SailorOfferSail::
	msgbox Cities_Text_M5SailorOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Cities_EventScript_M5SailorStay
	msgbox Cities_Text_M5SailorCastOff, MSGBOX_DEFAULT
	closemessage
	delay 30
	warp MAP_SOUTHERN_ISLAND_EXTERIOR, 13, 22
	waitstate
	release
	end

Cities_EventScript_M5SailorStay::
	msgbox Cities_Text_M5SailorStay, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_M5SailorAllCaught::
	goto_if_eq VAR_CITIES_M5_STATE, 2, Cities_EventScript_M5SailorAfter
	msgbox Cities_Text_M5SailorThanks, MSGBOX_DEFAULT
	setvar VAR_CITIES_M5_STATE, 2
	release
	end

Cities_EventScript_M5SailorAfter::
	msgbox Cities_Text_M5SailorAfter, MSGBOX_DEFAULT
	goto Cities_EventScript_M5SailorOfferSail

@ -- The pair --

Cities_EventScript_M5Latias::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_LATIAS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_LATIAS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M5CaughtLatias
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_M5CaughtLatias::
	setflag FLAG_CITIES_M5_LATIAS_CAUGHT
	release
	end

Cities_EventScript_M5Latios::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_LATIOS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_LATIOS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M5CaughtLatios
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_M5CaughtLatios::
	setflag FLAG_CITIES_M5_LATIOS_CAUGHT
	release
	end

@ -- The Eon stone --

Cities_EventScript_M5EonStone::
	lockall
	goto_if_set FLAG_CITIES_M5_STONES_TAKEN, Cities_EventScript_M5EonStoneQuiet
	setvar VAR_0x8004, 4 @ CITIES_ARC_M5
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_M5EonStoneHums
	msgbox Cities_Text_M5EonStoneWaiting, MSGBOX_DEFAULT
	releaseall
	end

Cities_EventScript_M5EonStoneHums::
	checkitemspace ITEM_LATIASITE
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_M5EonStoneBagFull
	checkitemspace ITEM_LATIOSITE
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_M5EonStoneBagFull
	msgbox Cities_Text_M5EonStoneHums, MSGBOX_DEFAULT
	giveitem ITEM_LATIASITE
	giveitem ITEM_LATIOSITE
	setflag FLAG_CITIES_M5_STONES_TAKEN
	msgbox Cities_Text_M5EonStoneRest, MSGBOX_DEFAULT
	releaseall
	end

Cities_EventScript_M5EonStoneBagFull::
	msgbox Cities_Text_M5EonStoneBagFull, MSGBOX_DEFAULT
	releaseall
	end

Cities_EventScript_M5EonStoneQuiet::
	msgbox Cities_Text_M5EonStoneQuiet, MSGBOX_DEFAULT
	releaseall
	end

@ -- Text --

Cities_Text_M5SailorIntro:
	.string "Eight BADGES! Then you're the one\n"
	.string "I've been waiting for.\p"
	.string "Old sailors tell of two lights\n"
	.string "over the southern sea. One red,\l"
	.string "one blue. Always together, never\l"
	.string "close enough to touch.\p"
	.string "Took me thirty years, but I found\n"
	.string "the island they circle.$"

Cities_Text_M5SailorTicket:
	.string "That ticket makes it official.\n"
	.string "The ferry crews will honor it\l"
	.string "someday, too.\p"
	.string "But you don't need to wait for\n"
	.string "them. My boat's right here.$"

Cities_Text_M5SailorProgress:
	.string "The two lights are still out\n"
	.string "there, circling their island.$"

Cities_Text_M5SailorOffer:
	.string "Sail to SOUTHERN ISLAND?$"

Cities_Text_M5SailorCastOff:
	.string "Cast off! Hold on to something!$"

Cities_Text_M5SailorStay:
	.string "The sea's not going anywhere.\n"
	.string "Neither am I.$"

Cities_Text_M5SailorThanks:
	.string "Both of them, riding with you?\p"
	.string "Thirty years I chased those\n"
	.string "lights…\p"
	.string "And they were just waiting for\n"
	.string "the right trainer to stop\l"
	.string "chasing and simply ask.$"

Cities_Text_M5SailorAfter:
	.string "The southern sea feels emptier\n"
	.string "now. But quieter, too.$"

Cities_Text_M5EonStoneWaiting:
	.string "A smooth stone with two warm\n"
	.string "hollows, side by side.\p"
	.string "It seems to be waiting.$"

Cities_Text_M5EonStoneHums:
	.string "The stone hums!\p"
	.string "The two hollows glow - one red,\n"
	.string "one blue…$"

Cities_Text_M5EonStoneRest:
	.string "The stone has gone still.\n"
	.string "Its long watch is over.$"

Cities_Text_M5EonStoneBagFull:
	.string "The stone offers something, but\n"
	.string "your BAG is full.$"

Cities_Text_M5EonStoneQuiet:
	.string "The stone is still and cool.\n"
	.string "Its long watch is over.$"
