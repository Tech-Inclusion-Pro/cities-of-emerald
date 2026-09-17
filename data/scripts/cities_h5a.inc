@ Cities of Emerald — H5a "The Making of Everything" (GDD 6.6,
@ approved 2026-09-17). The finale of thread 1. A Lilycove historian
@ opens the Rift Vestibule (Dialga west, Palkia east, tier 75);
@ Giratina waits on the Mt. Pyre summit where the world's other side
@ leaks through. The 17 Plates lie across Hoenn (Task 11.x, item
@ balls with FLAG_CITIES_H5A_PLATE_*). Trio caught -> the historian
@ gives the three origin items; trio + all Plates -> the sanctum
@ altar wakes Arceus (its own arc entry, fixed level 80; no
@ overworld sprite, so the altar is the encounter).

@ -- Visibility --

Cities_EventScript_UpdateH5AHistorian::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH5AHistorian
	clearflag FLAG_CITIES_HIDE_H5A_HISTORIAN
	return

Cities_EventScript_HideH5AHistorian::
	setflag FLAG_CITIES_HIDE_H5A_HISTORIAN
	return

Cities_EventScript_UpdateH5ADialga::
	goto_if_set FLAG_CITIES_H5A_DIALGA_CAUGHT, Cities_EventScript_HideH5ADialga
	clearflag FLAG_CITIES_HIDE_H5A_DIALGA
	return

Cities_EventScript_HideH5ADialga::
	setflag FLAG_CITIES_HIDE_H5A_DIALGA
	return

Cities_EventScript_UpdateH5APalkia::
	goto_if_set FLAG_CITIES_H5A_PALKIA_CAUGHT, Cities_EventScript_HideH5APalkia
	clearflag FLAG_CITIES_HIDE_H5A_PALKIA
	return

Cities_EventScript_HideH5APalkia::
	setflag FLAG_CITIES_HIDE_H5A_PALKIA
	return

@ Giratina on the Mt. Pyre summit, postgame once the historian spoke.
Cities_EventScript_UpdateH5AGiratina::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH5AGiratina
	goto_if_eq VAR_CITIES_H5A_STATE, 0, Cities_EventScript_HideH5AGiratina
	goto_if_set FLAG_CITIES_H5A_GIRATINA_CAUGHT, Cities_EventScript_HideH5AGiratina
	clearflag FLAG_CITIES_HIDE_H5A_GIRATINA
	return

Cities_EventScript_HideH5AGiratina::
	setflag FLAG_CITIES_HIDE_H5A_GIRATINA
	return

@ -- The historian (Lilycove, postgame) --

Cities_EventScript_H5AHistorian::
	lock
	faceplayer
	goto_if_eq VAR_CITIES_H5A_STATE, 0, Cities_EventScript_H5AHistorianIntro
	setvar VAR_0x8004, 18 @ CITIES_ARC_H5A
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H5AHistorianRepeat
	goto_if_unset FLAG_CITIES_H5A_CRYSTALS_GIVEN, Cities_EventScript_H5AHistorianTrioWrap
	goto_if_set FLAG_CITIES_H5A_ARCEUS_CAUGHT, Cities_EventScript_H5AHistorianFinale
	msgbox Cities_Text_H5AHistorianAltarHint, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H5AHistorianTravel
	release
	end

Cities_EventScript_H5AHistorianRepeat::
	msgbox Cities_Text_H5AHistorianRepeat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H5AHistorianTravel
	msgbox Cities_Text_H5AHistorianLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H5AHistorianIntro::
	msgbox Cities_Text_H5AHistorianIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_H5A_STATE, 1
	msgbox Cities_Text_H5AHistorianOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H5AHistorianTravel
	msgbox Cities_Text_H5AHistorianLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H5AHistorianTravel::
	msgbox Cities_Text_H5AHistorianLead, MSGBOX_DEFAULT
	closemessage
	warp MAP_RIFT_VESTIBULE, 8, 11
	waitstate
	release
	end

@ Creation trio caught: the three origin items, together.
Cities_EventScript_H5AHistorianTrioWrap::
	msgbox Cities_Text_H5AHistorianTrioThanks, MSGBOX_DEFAULT
	checkitemspace ITEM_ADAMANT_CRYSTAL
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H5AHistorianBagFull
	checkitemspace ITEM_LUSTROUS_GLOBE
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H5AHistorianBagFull
	checkitemspace ITEM_GRISEOUS_CORE
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H5AHistorianBagFull
	giveitem ITEM_ADAMANT_CRYSTAL
	giveitem ITEM_LUSTROUS_GLOBE
	giveitem ITEM_GRISEOUS_CORE
	setflag FLAG_CITIES_H5A_CRYSTALS_GIVEN
	msgbox Cities_Text_H5AHistorianCrystals, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H5AHistorianBagFull::
	msgbox Cities_Text_H5AHistorianBagFullText, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H5AHistorianFinale::
	goto_if_eq VAR_CITIES_H5A_STATE, 2, Cities_EventScript_H5AHistorianAfter
	msgbox Cities_Text_H5AHistorianFinaleText, MSGBOX_DEFAULT
	setvar VAR_CITIES_H5A_STATE, 2
	release
	end

Cities_EventScript_H5AHistorianAfter::
	msgbox Cities_Text_H5AHistorianAfterText, MSGBOX_DEFAULT
	release
	end

@ -- Leaving the vestibule (south alcove trigger tiles) --

Cities_EventScript_H5AVestibuleExit::
	lockall
	warp MAP_LILYCOVE_CITY, 33, 20
	waitstate
	releaseall
	end

@ -- Dialga and Palkia (tier 75 via the arc table) --

Cities_EventScript_H5ADialga::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_DIALGA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_DIALGA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H5ACaughtDialga
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H5ACaughtDialga::
	setflag FLAG_CITIES_H5A_DIALGA_CAUGHT
	release
	end

Cities_EventScript_H5APalkia::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PALKIA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_PALKIA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H5ACaughtPalkia
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H5ACaughtPalkia::
	setflag FLAG_CITIES_H5A_PALKIA_CAUGHT
	release
	end

@ -- Giratina (Mt. Pyre summit static) --

Cities_EventScript_H5AGiratina::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_GIRATINA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_GIRATINA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H5ACaughtGiratina
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H5ACaughtGiratina::
	setflag FLAG_CITIES_H5A_GIRATINA_CAUGHT
	release
	end

@ -- The sanctum altar (Arceus, fixed level 80 via its own arc) --

Cities_EventScript_H5AAltar::
	lockall
	goto_if_set FLAG_CITIES_H5A_ARCEUS_CAUGHT, Cities_EventScript_H5AAltarQuiet
	setvar VAR_0x8004, 18 @ CITIES_ARC_H5A (the creation trio)
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H5AAltarWaiting
	specialvar VAR_RESULT, Script_CitiesH5APlateCount
	goto_if_ne VAR_RESULT, 17, Cities_EventScript_H5AAltarPlates
	msgbox Cities_Text_H5AAltarWakes, MSGBOX_DEFAULT
	closemessage
	setvar VAR_0x8004, SPECIES_ARCEUS
	special Script_CitiesSetWildLegendary
	special BattleSetup_StartLegendaryBattle
	waitstate
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H5ACaughtArceus
	msgbox Cities_Text_H5AAltarRecedes, MSGBOX_DEFAULT
	releaseall
	end

Cities_EventScript_H5ACaughtArceus::
	setflag FLAG_CITIES_H5A_ARCEUS_CAUGHT
	releaseall
	end

Cities_EventScript_H5AAltarWaiting::
	msgbox Cities_Text_H5AAltarWaiting, MSGBOX_DEFAULT
	releaseall
	end

Cities_EventScript_H5AAltarPlates::
	specialvar VAR_RESULT, Script_CitiesH5APlateCount
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox Cities_Text_H5AAltarPlates, MSGBOX_DEFAULT
	releaseall
	end

Cities_EventScript_H5AAltarQuiet::
	msgbox Cities_Text_H5AAltarQuiet, MSGBOX_DEFAULT
	releaseall
	end

@ -- Text --

Cities_Text_H5AHistorianIntro:
	.string "CHAMPION. Good. Sit down -\n"
	.string "no, actually, stand. This is a\l"
	.string "standing kind of story.\p"
	.string "Every legend in HOENN is a\n"
	.string "chapter. The weather, the sea,\l"
	.string "the sky - chapters.\p"
	.string "I found the front page. A place\n"
	.string "behind this city where time and\l"
	.string "space wear thin, like old cloth.\p"
	.string "Two of the oldest beings stand\n"
	.string "in that hall. A third waits\l"
	.string "where HOENN honors its dead -\l"
	.string "MT. PYRE's summit.\p"
	.string "And scattered across all of\n"
	.string "HOENN… seventeen PLATES, pieces\l"
	.string "of the very first story.$"

Cities_Text_H5AHistorianOffer:
	.string "The passage is behind the\n"
	.string "museum. Come see the front page?$"

Cities_Text_H5AHistorianRepeat:
	.string "Back to the vestibule?$"

Cities_Text_H5AHistorianLater:
	.string "Take your time. This story\n"
	.string "waited longer than any other.$"

Cities_Text_H5AHistorianLead:
	.string "Don't mind the shimmer at the\n"
	.string "edges of things. That's normal.\l"
	.string "In there, anyway.$"

Cities_Text_H5AHistorianTrioThanks:
	.string "Time. Space. And the one that\n"
	.string "watches from the other side of\l"
	.string "the page.\p"
	.string "All three, walking with you.\n"
	.string "Then these belong with you too -\l"
	.string "I found them in the vestibule,\l"
	.string "and they are not mine to keep.$"

Cities_Text_H5AHistorianCrystals:
	.string "The ADAMANT CRYSTAL, the\n"
	.string "LUSTROUS GLOBE, the GRISEOUS\l"
	.string "CORE. Held close, they let the\l"
	.string "three take their true, original\l"
	.string "forms.$"

Cities_Text_H5AHistorianBagFullText:
	.string "Your Bag can't take all three,\n"
	.string "and they must stay together.\l"
	.string "Make room and come back.$"

Cities_Text_H5AHistorianAltarHint:
	.string "The trio is yours, and the\n"
	.string "crystals too. One thing remains.\p"
	.string "The altar in the sanctum. It\n"
	.string "hums when you're near, did you\l"
	.string "notice? It's counting your\l"
	.string "PLATES.\p"
	.string "Seventeen pieces of the first\n"
	.string "story - and one author.\p"
	.string "Go to the vestibule?$"

Cities_Text_H5AHistorianFinaleText:
	.string "You met the author of\n"
	.string "everything… and it chose to\l"
	.string "close the book and travel with\l"
	.string "you.\p"
	.string "I spent my life reading HOENN's\n"
	.string "legends. You went and finished\l"
	.string "the collection.\p"
	.string "There is no bigger story. There\n"
	.string "is only what you write next.$"

Cities_Text_H5AHistorianAfterText:
	.string "I've started writing it all\n"
	.string "down. Don't worry - you come\l"
	.string "off very well.$"

Cities_Text_H5AAltarWaiting:
	.string "An altar of pale stone. Seventeen\n"
	.string "shallow hollows ring its edge.\p"
	.string "It is waiting for time, space,\n"
	.string "and the world's other side to\l"
	.string "find their keeper first.$"

Cities_Text_H5AAltarPlates:
	.string "An altar of pale stone. Seventeen\n"
	.string "shallow hollows ring its edge.\p"
	.string "Your PLATES tremble in your Bag -\n"
	.string "{STR_VAR_1} of 17. The altar wants\l"
	.string "them all.$"

Cities_Text_H5AAltarWakes:
	.string "One by one, your seventeen\n"
	.string "PLATES rise and settle into the\l"
	.string "hollows.\p"
	.string "Light gathers above the altar -\n"
	.string "quiet, patient, and older than\l"
	.string "everything.$"

Cities_Text_H5AAltarRecedes:
	.string "The light recedes into the\n"
	.string "altar.\p"
	.string "It isn't gone. It's waiting for\n"
	.string "you to try again.$"

Cities_Text_H5AAltarQuiet:
	.string "The altar is quiet.\p"
	.string "The first story has a keeper\n"
	.string "now.$"
