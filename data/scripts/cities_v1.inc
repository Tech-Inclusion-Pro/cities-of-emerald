@ Cities of Emerald — V1 "Products and Targets" (GDD 7.2 / 6.6,
@ Task 12.5, outline approved 2026-09-18). Epoch quietly bought the
@ Space Center's records annex. The lab is clean and careful; Epoch
@ hurt no one. That is what makes it unsettling.
@
@ VAR_CITIES_V1_STATE: 0 not started, 1 researcher met / annex open,
@ 2 Meridian beaten, 3 arc complete (all three caught, Epoch gone).

@ -- Visibility (annex ON_TRANSITION; 2F handles Mew + the door) --

Cities_EventScript_UpdateV1Annex::
	call Cities_EventScript_UpdateV1Epoch
	goto_if_set FLAG_CITIES_V1_MEWTWO_CAUGHT, Cities_EventScript_V1HideMewtwo
	clearflag FLAG_CITIES_HIDE_V1_MEWTWO
	setflag FLAG_CITIES_HIDE_V1_GENESECT
	return

Cities_EventScript_V1HideMewtwo::
	setflag FLAG_CITIES_HIDE_V1_MEWTWO
	goto_if_set FLAG_CITIES_V1_GENESECT_CAUGHT, Cities_EventScript_V1HideGenesect
	clearflag FLAG_CITIES_HIDE_V1_GENESECT
	return

Cities_EventScript_V1HideGenesect::
	setflag FLAG_CITIES_HIDE_V1_GENESECT
	call Cities_EventScript_V1TryComplete
	return

Cities_EventScript_UpdateV1Epoch::
	goto_if_eq VAR_CITIES_V1_STATE, 3, Cities_EventScript_V1EpochGone
	clearflag FLAG_CITIES_HIDE_V1_EPOCH
	return

Cities_EventScript_V1EpochGone::
	setflag FLAG_CITIES_HIDE_V1_EPOCH
	return

@ Called from the Space Center 2F ON_TRANSITION as well.
Cities_EventScript_UpdateV1Mew::
	goto_if_unset FLAG_CITIES_V1_MEWTWO_CAUGHT, Cities_EventScript_V1HideMew
	goto_if_unset FLAG_CITIES_V1_GENESECT_CAUGHT, Cities_EventScript_V1HideMew
	goto_if_set FLAG_CITIES_V1_MEW_CAUGHT, Cities_EventScript_V1HideMew
	clearflag FLAG_CITIES_HIDE_V1_MEW
	return

Cities_EventScript_V1HideMew::
	setflag FLAG_CITIES_HIDE_V1_MEW
	return

Cities_EventScript_UpdateV1Researcher::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_V1HideResearcher
	clearflag FLAG_CITIES_HIDE_V1_RESEARCHER
	return

Cities_EventScript_V1HideResearcher::
	setflag FLAG_CITIES_HIDE_V1_RESEARCHER
	return

Cities_EventScript_V1TryComplete::
	goto_if_eq VAR_CITIES_V1_STATE, 3, Cities_EventScript_V1TryCompleteEnd
	goto_if_unset FLAG_CITIES_V1_MEWTWO_CAUGHT, Cities_EventScript_V1TryCompleteEnd
	goto_if_unset FLAG_CITIES_V1_GENESECT_CAUGHT, Cities_EventScript_V1TryCompleteEnd
	goto_if_unset FLAG_CITIES_V1_MEW_CAUGHT, Cities_EventScript_V1TryCompleteEnd
	setvar VAR_CITIES_V1_STATE, 3
	setflag FLAG_CITIES_HIDE_V1_EPOCH
Cities_EventScript_V1TryCompleteEnd::
	return

@ -- The Devon researcher (Space Center 1F lobby, postgame) --

Cities_EventScript_V1Researcher::
	lock
	faceplayer
	goto_if_eq VAR_CITIES_V1_STATE, 0, Cities_EventScript_V1ResearcherIntro
	goto_if_ne VAR_CITIES_V2_STATE, 3, Cities_EventScript_V1ResearcherV1Phase
	goto_if_eq VAR_CITIES_V3_STATE, 0, Cities_EventScript_V3ResearcherWormholes
	goto_if_unset FLAG_CITIES_V3_COSMOG_GIVEN, Cities_EventScript_V3ResearcherCosmogRetry
	msgbox Cities_Text_V3ResearcherDuring, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_V1ResearcherV1Phase::
	goto_if_eq VAR_CITIES_V1_STATE, 3, Cities_EventScript_V1ResearcherAfter
	msgbox Cities_Text_V1ResearcherRepeat, MSGBOX_DEFAULT
	release
	end

@ V3 entry: the researcher reports the wormholes and Cosmog moves in.
Cities_EventScript_V3ResearcherWormholes::
	msgbox Cities_Text_V3ResearcherWormholes, MSGBOX_DEFAULT
	setvar VAR_CITIES_V3_STATE, 1
	goto Cities_EventScript_V3ResearcherGiveCosmog

Cities_EventScript_V3ResearcherCosmogRetry::
	msgbox Cities_Text_V3ResearcherCosmogRetry, MSGBOX_DEFAULT
Cities_EventScript_V3ResearcherGiveCosmog::
	msgbox Cities_Text_V3CosmogShelters, MSGBOX_DEFAULT
	givemon SPECIES_COSMOG, 70
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Cities_EventScript_V3CosmogGiven
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Cities_EventScript_V3CosmogGiven
	msgbox Cities_Text_V3CosmogNoRoom, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_V3CosmogGiven::
	setflag FLAG_CITIES_V3_COSMOG_GIVEN
	msgbox Cities_Text_V3CosmogGiven, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_V1ResearcherIntro::
	msgbox Cities_Text_V1ResearcherIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_V1_STATE, 1
	release
	end

Cities_EventScript_V1ResearcherAfter::
	msgbox Cities_Text_V1ResearcherAfter, MSGBOX_DEFAULT
	release
	end

@ -- The annex (Epoch, while the arc runs) --

Cities_EventScript_V1Grunt1::
	trainerbattle_single TRAINER_EPOCH_GRUNT_1, Cities_Text_V1Grunt1Intro, Cities_Text_V1Grunt1Defeat
	msgbox Cities_Text_V1Grunt1After, MSGBOX_AUTOCLOSE
	end

Cities_EventScript_V1Grunt2::
	trainerbattle_single TRAINER_EPOCH_GRUNT_2, Cities_Text_V1Grunt2Intro, Cities_Text_V1Grunt2Defeat
	msgbox Cities_Text_V1Grunt2After, MSGBOX_AUTOCLOSE
	end

Cities_EventScript_V1Meridian::
	trainerbattle_single TRAINER_EPOCH_MERIDIAN_1, Cities_Text_V1MeridianIntro, Cities_Text_V1MeridianDefeat
	call_if_eq VAR_CITIES_V1_STATE, 1, Cities_EventScript_V1MeridianAdvance
	msgbox Cities_Text_V1MeridianAfterBattle, MSGBOX_AUTOCLOSE
	end

Cities_EventScript_V1MeridianAdvance::
	setvar VAR_CITIES_V1_STATE, 2
	return

@ -- The three (M1-pattern statics) --

Cities_EventScript_V1Mewtwo::
	lock
	faceplayer
	msgbox Cities_Text_V1MewtwoRing, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_MEWTWO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MEWTWO
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V1CaughtMewtwo
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V1CaughtMewtwo::
	setflag FLAG_CITIES_V1_MEWTWO_CAUGHT
	release
	end

Cities_EventScript_V1Genesect::
	lock
	faceplayer
	msgbox Cities_Text_V1GenesectWakes, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_GENESECT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_GENESECT
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V1CaughtGenesect
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V1CaughtGenesect::
	setflag FLAG_CITIES_V1_GENESECT_CAUGHT
	release
	end

Cities_EventScript_V1Mew::
	lock
	faceplayer
	msgbox Cities_Text_V1MewAppears, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_MEW, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MEW
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V1CaughtMew
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V1CaughtMew::
	setflag FLAG_CITIES_V1_MEW_CAUGHT
	call Cities_EventScript_V1TryComplete
	release
	end

@ -- Readables --

Cities_EventScript_V1Manifests::
	msgbox Cities_Text_V1Manifests, MSGBOX_SIGN
	end

Cities_EventScript_V1ContainmentLog::
	msgbox Cities_Text_V1ContainmentLog, MSGBOX_SIGN
	end

@ -- Text --

Cities_Text_V1ResearcherIntro:
	.string "Oh - CHAMPION. Good. Someone\n"
	.string "should hear this.\p"
	.string "A group bought our records annex\n"
	.string "upstairs. Paid well. Paperwork\l"
	.string "perfect. Very polite.\p"
	.string "Since then they've been buying\n"
	.string "research. Old research.\l"
	.string "Genetics. Machines. Origins.\p"
	.string "Nothing they've done is wrong,\n"
	.string "exactly.\p"
	.string "That's what bothers me. Would\n"
	.string "you take a look?\p"
	.string "The annex door is upstairs,\n"
	.string "at the back.$"

Cities_Text_V1ResearcherRepeat:
	.string "The annex door is upstairs,\n"
	.string "at the back.\p"
	.string "Polite people, all of them.\n"
	.string "That's what bothers me.$"

Cities_Text_V1ResearcherAfter:
	.string "They've gone. Left the annex\n"
	.string "cleaner than they found it.\p"
	.string "Who apologizes to a BUILDING?$"

Cities_Text_V1Grunt1Intro:
	.string "Visitors sign the ledger,\n"
	.string "please.\p"
	.string "Oh. You're not here to sign\n"
	.string "the ledger.$"

Cities_Text_V1Grunt1Defeat:
	.string "Noted, dated, and filed.$"

Cities_Text_V1Grunt1After:
	.string "We don't take things. We keep\n"
	.string "them.\p"
	.string "There's a difference. There has\n"
	.string "to be.$"

Cities_Text_V1Grunt2Intro:
	.string "Careful with the equipment.\n"
	.string "It's older than both of us.\p"
	.string "And if you're going to interfere,\n"
	.string "I'm required to stop you.$"

Cities_Text_V1Grunt2Defeat:
	.string "Filed under “setbacks.”$"

Cities_Text_V1Grunt2After:
	.string "Every item in this room is\n"
	.string "catalogued and cared for.\p"
	.string "We're not thieves. We're\n"
	.string "custodians.$"

Cities_Text_V1MeridianIntro:
	.string "You must be the Champion.\n"
	.string "I'm MERIDIAN.\p"
	.string "We haven't broken any laws.\n"
	.string "I checked twice.\p"
	.string "But you're going to open that\n"
	.string "containment ring, and I'm going\l"
	.string "to try to stop you.\p"
	.string "Courtesy first, though:\n"
	.string "it's nothing personal.$"

Cities_Text_V1MeridianDefeat:
	.string "…Thorough. He said you\n"
	.string "would be.$"

Cities_Text_V1MeridianAfterBattle:
	.string "Go on, then. Open it.\p"
	.string "We needed something strong enough\n"
	.string "to hold a door open. A door in\l"
	.string "TIME, if you want the truth.\p"
	.string "The one who leads us lost\n"
	.string "something. We're going to get\l"
	.string "it back.\p"
	.string "You'll think that's impossible.\n"
	.string "He would say: so was this lab,\l"
	.string "once.$"

Cities_Text_V1MewtwoRing:
	.string "The containment ring hums.\p"
	.string "Inside it, something made by\n"
	.string "people watches you with eyes\l"
	.string "that owe nobody anything.$"

Cities_Text_V1GenesectWakes:
	.string "The bay lights flicker on,\n"
	.string "one by one.\p"
	.string "Something ancient - and rebuilt -\n"
	.string "unfolds itself and stands.$"

Cities_Text_V1MewAppears:
	.string "Something small is floating by\n"
	.string "the annex door, as if it had\l"
	.string "been waiting for you.\p"
	.string "It didn't come for the lab.\n"
	.string "It came for you.$"

Cities_Text_V1Manifests:
	.string "Purchase manifests, in careful\n"
	.string "handwriting.\p"
	.string "Cell samples. Drive units. A\n"
	.string "journal from a research island\l"
	.string "that burned down long ago.\p"
	.string "Every line says PRESERVE.\n"
	.string "None of them say WHY.$"

Cities_Text_V1ContainmentLog:
	.string "A containment log.\p"
	.string "“Subject calm. Subject is not a\n"
	.string "subject. Correction logged.”\p"
	.string "“It watches the door. We have\n"
	.string "agreed not to stand near the\l"
	.string "door.”$"
