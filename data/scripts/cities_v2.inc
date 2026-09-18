@ Cities of Emerald — V2 "Stolen Research" (GDD 7.2 / 6.6, Task 12.5,
@ outline approved 2026-09-18). Epoch takes what it cannot buy. Gnomon
@ debuts, apologetic and precise. Magearna walks out of Epoch's hands
@ and chooses the player — the first crack in the plan. The Archivist
@ is heard, not seen: the letter completing this arc also opens the
@ sunken village (FLAG_CITIES_CORALMERE_OPEN).
@
@ VAR_CITIES_V2_STATE: 0 locked, 1 aide met / camp active,
@ 2 Gnomon beaten, 3 letter read / arc complete.

@ -- Visibility --

Cities_EventScript_UpdateV2Aide::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_V2HideAide
	goto_if_ne VAR_CITIES_V1_STATE, 3, Cities_EventScript_V2HideAide
	clearflag FLAG_CITIES_HIDE_V2_AIDE
	return

Cities_EventScript_V2HideAide::
	setflag FLAG_CITIES_HIDE_V2_AIDE
	return

Cities_EventScript_UpdateV2Camp::
	goto_if_eq VAR_CITIES_V2_STATE, 0, Cities_EventScript_V2HideCamp
	goto_if_eq VAR_CITIES_V2_STATE, 3, Cities_EventScript_V2HideCamp
	clearflag FLAG_CITIES_HIDE_V2_CAMP
	goto Cities_EventScript_UpdateV2Statics

Cities_EventScript_V2HideCamp::
	setflag FLAG_CITIES_HIDE_V2_CAMP
	goto Cities_EventScript_UpdateV2Statics

Cities_EventScript_UpdateV2Statics::
	goto_if_eq VAR_CITIES_V2_STATE, 0, Cities_EventScript_V2HideBothStatics
	goto_if_set FLAG_CITIES_V2_TYPE_NULL_CAUGHT, Cities_EventScript_V2NullCaught
	clearflag FLAG_CITIES_HIDE_V2_TYPE_NULL
	setflag FLAG_CITIES_HIDE_V2_SILVALLY
	return

Cities_EventScript_V2NullCaught::
	setflag FLAG_CITIES_HIDE_V2_TYPE_NULL
	goto_if_set FLAG_CITIES_V2_SILVALLY_CAUGHT, Cities_EventScript_V2SilvallyCaught
	clearflag FLAG_CITIES_HIDE_V2_SILVALLY
	return

Cities_EventScript_V2SilvallyCaught::
	setflag FLAG_CITIES_HIDE_V2_SILVALLY
	return

Cities_EventScript_V2HideBothStatics::
	setflag FLAG_CITIES_HIDE_V2_TYPE_NULL
	setflag FLAG_CITIES_HIDE_V2_SILVALLY
	return

@ -- The Devon aide (Devon Corp 3F, after V1) --

Cities_EventScript_V2Aide::
	lock
	faceplayer
	goto_if_eq VAR_CITIES_V2_STATE, 0, Cities_EventScript_V2AideIntro
	goto_if_eq VAR_CITIES_V2_STATE, 3, Cities_EventScript_V2AideAfter
	msgbox Cities_Text_V2AideRepeat, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_V2AideIntro::
	msgbox Cities_Text_V2AideIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_V2_STATE, 1
	release
	end

Cities_EventScript_V2AideAfter::
	msgbox Cities_Text_V2AideAfter, MSGBOX_DEFAULT
	release
	end

@ -- The camp (Route 115 cliffs, Meteor Falls shelf) --

Cities_EventScript_V2Grunt3::
	trainerbattle_single TRAINER_EPOCH_GRUNT_3, Cities_Text_V2Grunt3Intro, Cities_Text_V2Grunt3Defeat
	msgbox Cities_Text_V2Grunt3After, MSGBOX_AUTOCLOSE
	end

Cities_EventScript_V2Grunt4::
	trainerbattle_single TRAINER_EPOCH_GRUNT_4, Cities_Text_V2Grunt4Intro, Cities_Text_V2Grunt4Defeat
	msgbox Cities_Text_V2Grunt4After, MSGBOX_AUTOCLOSE
	end

Cities_EventScript_V2Gnomon::
	trainerbattle_single TRAINER_EPOCH_GNOMON_1, Cities_Text_V2GnomonIntro, Cities_Text_V2GnomonDefeat
	call_if_eq VAR_CITIES_V2_STATE, 1, Cities_EventScript_V2GnomonAdvance
	msgbox Cities_Text_V2GnomonAfterBattle, MSGBOX_AUTOCLOSE
	end

Cities_EventScript_V2GnomonAdvance::
	setvar VAR_CITIES_V2_STATE, 2
	return

@ -- The synthetic hearts (M1-pattern statics) --

Cities_EventScript_V2TypeNull::
	lock
	faceplayer
	msgbox Cities_Text_V2TypeNull, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_TYPE_NULL, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_TYPE_NULL
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V2CaughtTypeNull
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V2CaughtTypeNull::
	setflag FLAG_CITIES_V2_TYPE_NULL_CAUGHT
	release
	end

Cities_EventScript_V2Silvally::
	lock
	faceplayer
	msgbox Cities_Text_V2Silvally, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SILVALLY, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_SILVALLY
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V2CaughtSilvally
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V2CaughtSilvally::
	setflag FLAG_CITIES_V2_SILVALLY_CAUGHT
	release
	end

@ -- The sealed crate (Magearna chooses the player) --

Cities_EventScript_V2SealedCrate::
	lockall
	goto_if_set FLAG_CITIES_V2_MAGEARNA_GIVEN, Cities_EventScript_V2CrateEmpty
	goto_if_unset FLAG_CITIES_V2_TYPE_NULL_CAUGHT, Cities_EventScript_V2CrateSealed
	goto_if_unset FLAG_CITIES_V2_SILVALLY_CAUGHT, Cities_EventScript_V2CrateSealed
	msgbox Cities_Text_V2MagearnaWakes, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_MAGEARNA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	msgbox Cities_Text_V2MagearnaChooses, MSGBOX_DEFAULT
	givemon SPECIES_MAGEARNA, 65
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Cities_EventScript_V2MagearnaGiven
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Cities_EventScript_V2MagearnaGiven
	msgbox Cities_Text_V2NoRoom, MSGBOX_DEFAULT
	releaseall
	end

Cities_EventScript_V2MagearnaGiven::
	setflag FLAG_CITIES_V2_MAGEARNA_GIVEN
	msgbox Cities_Text_V2MagearnaJoined, MSGBOX_DEFAULT
	releaseall
	end

Cities_EventScript_V2CrateSealed::
	msgbox Cities_Text_V2CrateSealed, MSGBOX_DEFAULT
	releaseall
	end

Cities_EventScript_V2CrateEmpty::
	msgbox Cities_Text_V2CrateEmpty, MSGBOX_DEFAULT
	releaseall
	end

@ -- The crates and the table (the letter completes the arc) --

Cities_EventScript_V2Crates::
	msgbox Cities_Text_V2Crates, MSGBOX_SIGN
	end

Cities_EventScript_V2Table::
	lockall
	goto_if_set FLAG_CITIES_V2_LETTER_READ, Cities_EventScript_V2TableLetterAgain
	goto_if_unset FLAG_CITIES_V2_MAGEARNA_GIVEN, Cities_EventScript_V2TablePlain
	msgbox Cities_Text_V2Letter, MSGBOX_DEFAULT
	setflag FLAG_CITIES_V2_LETTER_READ
	setflag FLAG_CITIES_CORALMERE_OPEN
	setvar VAR_CITIES_V2_STATE, 3
	msgbox Cities_Text_V2LetterDone, MSGBOX_DEFAULT
	releaseall
	end

Cities_EventScript_V2TablePlain::
	msgbox Cities_Text_V2TablePlain, MSGBOX_DEFAULT
	releaseall
	end

Cities_EventScript_V2TableLetterAgain::
	msgbox Cities_Text_V2Letter, MSGBOX_DEFAULT
	releaseall
	end

@ -- Text --

Cities_Text_V2AideIntro:
	.string "CHAMPION - MR. STONE asked me to\n"
	.string "find you.\p"
	.string "Devon's vault was opened last\n"
	.string "night. A private collection too.\p"
	.string "Three pieces of “synthetic heart”\n"
	.string "research are gone.\p"
	.string "Whoever did it left receipts.\n"
	.string "RECEIPTS. Signed “for the\l"
	.string "archive.”\p"
	.string "Our trackers followed a supply\n"
	.string "line to the cliffs on ROUTE 115,\l"
	.string "above the falls.\p"
	.string "Please - quietly.$"

Cities_Text_V2AideRepeat:
	.string "The camp is on the ROUTE 115\n"
	.string "cliffs, above METEOR FALLS.\p"
	.string "Mach Bike up the slope, or come\n"
	.string "through the falls from above.$"

Cities_Text_V2AideAfter:
	.string "The research came back with\n"
	.string "interest, somehow.\p"
	.string "MR. STONE says we owe you more\n"
	.string "than we can file.$"

Cities_Text_V2Grunt3Intro:
	.string "This site is catalogued exactly\n"
	.string "as we found it.\p"
	.string "You, however, are an anomaly.$"

Cities_Text_V2Grunt3Defeat:
	.string "Anomaly confirmed.$"

Cities_Text_V2Grunt3After:
	.string "We returned everything we\n"
	.string "borrowed from DEVON.\p"
	.string "Copies are not stealing.\n"
	.string "…Mostly.$"

Cities_Text_V2Grunt4Intro:
	.string "Wind's picking up. Hold the\n"
	.string "tarp - oh.\p"
	.string "You're not with the supply run.$"

Cities_Text_V2Grunt4Defeat:
	.string "The tarp got away too.$"

Cities_Text_V2Grunt4After:
	.string "The three hearts weren't for\n"
	.string "hurting anything.\p"
	.string "They were the strongest anchors\n"
	.string "anyone ever built.$"

Cities_Text_V2GnomonIntro:
	.string "Ah. The Champion. I calculated\n"
	.string "a 70 percent chance of you.\p"
	.string "I'm GNOMON. I built the machines\n"
	.string "this research is for.\p"
	.string "I want to apologize in advance -\n"
	.string "for the theft, and for this.$"

Cities_Text_V2GnomonDefeat:
	.string "…Recalculating.$"

Cities_Text_V2GnomonAfterBattle:
	.string "The vault research is boxed and\n"
	.string "labeled. Take it back to DEVON.\p"
	.string "We kept only the measurements.\n"
	.string "Numbers belong to everyone.\p"
	.string "A door needs a frame that can\n"
	.string "hold it open. That's all we\l"
	.string "wanted: a strong enough frame.\p"
	.string "He never asks for more than\n"
	.string "that. I wish he would ask for\l"
	.string "less.$"

Cities_Text_V2TypeNull:
	.string "It stands very still under its\n"
	.string "heavy mask.\p"
	.string "Built to be everything at once,\n"
	.string "and never asked what it wanted\l"
	.string "to be.$"

Cities_Text_V2Silvally:
	.string "The mask is off.\p"
	.string "It looks at you the way a\n"
	.string "partner does - like a choice.$"

Cities_Text_V2CrateSealed:
	.string "A crate, sealed with brass\n"
	.string "clasps. Something inside it is\l"
	.string "ticking, slow and even.\p"
	.string "Like a heart with patience.$"

Cities_Text_V2MagearnaWakes:
	.string "The clasps open from the INSIDE.\p"
	.string "A small figure sits up, folds\n"
	.string "its hands, and considers you\l"
	.string "for a long moment.$"

Cities_Text_V2MagearnaChooses:
	.string "It steps out of the crate,\n"
	.string "and out of TEAM EPOCH's plan,\l"
	.string "in the same motion.\p"
	.string "MAGEARNA chose you!$"

Cities_Text_V2MagearnaJoined:
	.string "The camp is very quiet.\p"
	.string "Nobody tries to stop it from\n"
	.string "leaving.$"

Cities_Text_V2NoRoom:
	.string "It settles back into the crate,\n"
	.string "hands folded.\p"
	.string "Make room, and it will be here.$"

Cities_Text_V2Crates:
	.string "Crates, stacked and labeled in\n"
	.string "careful handwriting.\p"
	.string "“FRAGILE.” “BORROWED.”\n"
	.string "“RETURN IN BETTER CONDITION.”$"

Cities_Text_V2TablePlain:
	.string "A folding table. Weather charts,\n"
	.string "neat stacks of labels, and one\l"
	.string "empty chair.$"

Cities_Text_V2Letter:
	.string "A letter lies on the table,\n"
	.string "weighted with a gray stone.\p"
	.string "“To the Champion.\p"
	.string "“You keep taking back what we\n"
	.string "gather. I understand. From where\l"
	.string "you stand, we must look like\l"
	.string "thieves.\p"
	.string "“So you should know what this\n"
	.string "is for.\p"
	.string "“There was a village. The sea\n"
	.string "took it in one night, because a\l"
	.string "warning came too late.\p"
	.string "“Everyone who could have grown\n"
	.string "old there - didn't.\p"
	.string "“I am going to be on time.\n"
	.string "Once. Just once.\p"
	.string "“Keep the hearts. They liked\n"
	.string "you better anyway.”\p"
	.string "It is not signed.$"

Cities_Text_V2LetterDone:
	.string "The gray stone is worn smooth,\n"
	.string "like something the sea rolled\l"
	.string "for years.\p"
	.string "Somewhere south of here, there\n"
	.string "is a village to find.$"

Cities_Text_V2CrateEmpty:
	.string "The crate stands open and empty.\p"
	.string "The padding inside is shaped\n"
	.string "like a small, patient figure\l"
	.string "with folded hands.$"
