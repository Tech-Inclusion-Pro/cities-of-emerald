@ Cities of Emerald — H8 "The Weather Menders" (GDD 6.6, approved
@ 2026-09-17). Fallarbor's weather keeps correcting itself: squalls
@ that stop mid-gust. The ash researcher's charts all point up the
@ trail to Windswept Rise, where the forces of storm hold three of
@ four stone perches. Enamorus arrives at the empty perch once the
@ trio is caught. Fixed 65 tier; postgame always obeys. Reward: the
@ Reveal Glass at the wrap (M5 Eon-stone give pattern).

@ -- Visibility --

Cities_EventScript_UpdateH8Researcher::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH8Researcher
	clearflag FLAG_CITIES_HIDE_H8_RESEARCHER
	return

Cities_EventScript_HideH8Researcher::
	setflag FLAG_CITIES_HIDE_H8_RESEARCHER
	return

Cities_EventScript_UpdateH8Tornadus::
	goto_if_set FLAG_CITIES_H8_TORNADUS_CAUGHT, Cities_EventScript_HideH8Tornadus
	clearflag FLAG_CITIES_HIDE_H8_TORNADUS
	return

Cities_EventScript_HideH8Tornadus::
	setflag FLAG_CITIES_HIDE_H8_TORNADUS
	return

Cities_EventScript_UpdateH8Thundurus::
	goto_if_set FLAG_CITIES_H8_THUNDURUS_CAUGHT, Cities_EventScript_HideH8Thundurus
	clearflag FLAG_CITIES_HIDE_H8_THUNDURUS
	return

Cities_EventScript_HideH8Thundurus::
	setflag FLAG_CITIES_HIDE_H8_THUNDURUS
	return

Cities_EventScript_UpdateH8Landorus::
	goto_if_set FLAG_CITIES_H8_LANDORUS_CAUGHT, Cities_EventScript_HideH8Landorus
	clearflag FLAG_CITIES_HIDE_H8_LANDORUS
	return

Cities_EventScript_HideH8Landorus::
	setflag FLAG_CITIES_HIDE_H8_LANDORUS
	return

@ Spring follows when the storms are settled.
Cities_EventScript_UpdateH8Enamorus::
	goto_if_unset FLAG_CITIES_H8_TORNADUS_CAUGHT, Cities_EventScript_HideH8Enamorus
	goto_if_unset FLAG_CITIES_H8_THUNDURUS_CAUGHT, Cities_EventScript_HideH8Enamorus
	goto_if_unset FLAG_CITIES_H8_LANDORUS_CAUGHT, Cities_EventScript_HideH8Enamorus
	goto_if_set FLAG_CITIES_H8_ENAMORUS_CAUGHT, Cities_EventScript_HideH8Enamorus
	clearflag FLAG_CITIES_HIDE_H8_ENAMORUS
	return

Cities_EventScript_HideH8Enamorus::
	setflag FLAG_CITIES_HIDE_H8_ENAMORUS
	return

@ -- The researcher (Fallarbor, postgame) --

Cities_EventScript_H8Researcher::
	lock
	faceplayer
	setvar VAR_0x8004, 12 @ CITIES_ARC_H8
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_H8ResearcherAllCaught
	goto_if_eq VAR_CITIES_H8_STATE, 0, Cities_EventScript_H8ResearcherIntro
	msgbox Cities_Text_H8ResearcherRepeat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H8ResearcherTravel
	msgbox Cities_Text_H8ResearcherLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H8ResearcherIntro::
	msgbox Cities_Text_H8ResearcherIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_H8_STATE, 1
	msgbox Cities_Text_H8ResearcherOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H8ResearcherTravel
	msgbox Cities_Text_H8ResearcherLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H8ResearcherTravel::
	msgbox Cities_Text_H8ResearcherLead, MSGBOX_DEFAULT
	closemessage
	warp MAP_WINDSWEPT_RISE, 9, 13
	waitstate
	release
	end

@ All four caught: the wrap, and the Reveal Glass (GDD 6.7).
Cities_EventScript_H8ResearcherAllCaught::
	goto_if_set FLAG_CITIES_H8_GLASS_GIVEN, Cities_EventScript_H8ResearcherAfterGlass
	msgbox Cities_Text_H8ResearcherThanks, MSGBOX_DEFAULT
	checkitemspace ITEM_REVEAL_GLASS
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H8ResearcherBagFull
	giveitem ITEM_REVEAL_GLASS
	setflag FLAG_CITIES_H8_GLASS_GIVEN
	setvar VAR_CITIES_H8_STATE, 2
	msgbox Cities_Text_H8ResearcherGlass, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H8ResearcherBagFull::
	msgbox Cities_Text_H8ResearcherBagFull, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H8ResearcherAfterGlass::
	goto_if_eq VAR_CITIES_H8_STATE, 2, Cities_EventScript_H8ResearcherAfter
	setvar VAR_CITIES_H8_STATE, 2
Cities_EventScript_H8ResearcherAfter::
	msgbox Cities_Text_H8ResearcherAfterText, MSGBOX_DEFAULT
	release
	end

@ -- Leaving the rise (south gap trigger tiles) --

Cities_EventScript_H8RiseExit::
	lockall
	warp MAP_FALLARBOR_TOWN, 5, 12
	waitstate
	releaseall
	end

@ -- The forces of storm --

Cities_EventScript_H8Tornadus::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TORNADUS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_TORNADUS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H8CaughtTornadus
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H8CaughtTornadus::
	setflag FLAG_CITIES_H8_TORNADUS_CAUGHT
	release
	end

Cities_EventScript_H8Thundurus::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_THUNDURUS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_THUNDURUS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H8CaughtThundurus
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H8CaughtThundurus::
	setflag FLAG_CITIES_H8_THUNDURUS_CAUGHT
	release
	end

Cities_EventScript_H8Landorus::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_LANDORUS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_LANDORUS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H8CaughtLandorus
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H8CaughtLandorus::
	setflag FLAG_CITIES_H8_LANDORUS_CAUGHT
	release
	end

Cities_EventScript_H8Enamorus::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ENAMORUS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ENAMORUS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H8CaughtEnamorus
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H8CaughtEnamorus::
	setflag FLAG_CITIES_H8_ENAMORUS_CAUGHT
	release
	end

@ -- Text --

Cities_Text_H8ResearcherIntro:
	.string "CHAMPION, look at these charts\n"
	.string "and tell me I'm not imagining it.\p"
	.string "A squall forms over town - then\n"
	.string "stops. Mid-gust. Like someone\l"
	.string "caught it.\p"
	.string "Lightning with no storm. A dust\n"
	.string "front that turns itself around.\p"
	.string "Something up on the rise is\n"
	.string "MENDING our weather. Three\l"
	.string "somethings, if my charts are\l"
	.string "right.$"

Cities_Text_H8ResearcherOffer:
	.string "The trail up the rise starts\n"
	.string "behind the station. Coming?$"

Cities_Text_H8ResearcherRepeat:
	.string "Up to the rise again?$"

Cities_Text_H8ResearcherLater:
	.string "I'll keep charting. The sky\n"
	.string "isn't done being strange.$"

Cities_Text_H8ResearcherLead:
	.string "Keep your hat on up there.\n"
	.string "The wind has opinions.$"

Cities_Text_H8ResearcherThanks:
	.string "All FOUR? The three storm forces\n"
	.string "- and the fourth perch filled at\l"
	.string "the end?\p"
	.string "Spring follows when the storms\n"
	.string "are settled. The old records\l"
	.string "said so, and nobody believed\l"
	.string "them.\p"
	.string "You should have this. We found it\n"
	.string "on the rise years ago and never\l"
	.string "knew what it was for.$"

Cities_Text_H8ResearcherGlass:
	.string "It's called a REVEAL GLASS.\n"
	.string "Look at your four through it,\l"
	.string "and you'll see their other\l"
	.string "selves - their true forms over\l"
	.string "their homeland.$"

Cities_Text_H8ResearcherBagFull:
	.string "Your Bag is full! Come back for\n"
	.string "the glass - it's waited years,\l"
	.string "it can wait an afternoon.$"

Cities_Text_H8ResearcherAfterText:
	.string "Charts are boring again.\p"
	.string "Best boring of my life.$"
