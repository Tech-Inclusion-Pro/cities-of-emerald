@ Cities of Emerald — Phase 14 postgame NPCs.
@ 14.5 Mauville plaza QoL pair (free relearner + deleter; vanilla
@ Fallarbor/Lilycove NPCs stay). 14.2 random-trade NPC. 14.3 an
@ achievements records-keeper. All computed/assembled; no new save data.

@ ===================================================================
@ 14.5 — Free move relearner (Mauville plaza). No Heart Scale.
@ ===================================================================
Cities_EventScript_MauvilleRelearner::
	lock
	faceplayer
	msgbox Cities_Text_RelearnerIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Cities_EventScript_MauvilleRelearnerBye
Cities_EventScript_MauvilleRelearnerChooseMon::
	msgbox Cities_Text_RelearnerWhichMon, MSGBOX_DEFAULT
	setmoverelearnerstate MOVE_RELEARNER_LEVEL_UP_MOVES
	chooseboxmon SELECT_PC_MON_MOVE_RELEARNER
	waitstate
	goto_if_eq VAR_0x8004, PARTY_MON_CANCEL, Cities_EventScript_MauvilleRelearnerBye
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_MauvilleRelearnerEgg
	special Special_HasMoveToRelearn
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_MauvilleRelearnerNoMove
Cities_EventScript_MauvilleRelearnerChooseMove::
	msgbox Cities_Text_RelearnerWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_MauvilleRelearnerChooseMon
	msgbox Cities_Text_RelearnerDone, MSGBOX_DEFAULT
	goto Cities_EventScript_MauvilleRelearnerChooseMon

Cities_EventScript_MauvilleRelearnerNoMove::
	msgbox Cities_Text_RelearnerNoMove, MSGBOX_DEFAULT
	goto Cities_EventScript_MauvilleRelearnerChooseMon

Cities_EventScript_MauvilleRelearnerEgg::
	msgbox Cities_Text_RelearnerEgg, MSGBOX_DEFAULT
	goto Cities_EventScript_MauvilleRelearnerChooseMon

Cities_EventScript_MauvilleRelearnerBye::
	msgbox Cities_Text_RelearnerBye, MSGBOX_DEFAULT
	release
	end

@ ===================================================================
@ 14.5 — Free move deleter (Mauville plaza).
@ ===================================================================
Cities_EventScript_MauvilleDeleter::
	lock
	faceplayer
	msgbox Cities_Text_DeleterIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Cities_EventScript_MauvilleDeleterBye
Cities_EventScript_MauvilleDeleterChoose::
	msgbox Cities_Text_DeleterWhichMon, MSGBOX_DEFAULT
	chooseboxmon SELECT_PC_MON_MOVE_DELETER
	waitstate
	goto_if_eq VAR_0x8004, PARTY_MON_CANCEL, Cities_EventScript_MauvilleDeleterBye
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_MauvilleDeleterEgg
	special GetNumMovesSelectedMonHas
	goto_if_eq VAR_RESULT, 1, Cities_EventScript_MauvilleDeleterOneMove
	msgbox Cities_Text_DeleterWhichMove, MSGBOX_DEFAULT
	fadescreen FADE_TO_BLACK
	special MoveDeleterChooseMoveToForget
	fadescreen FADE_FROM_BLACK
	goto_if_eq VAR_0x8005, MAX_MON_MOVES, Cities_EventScript_MauvilleDeleterChoose
	special BufferMoveDeleterNicknameAndMove
	msgbox Cities_Text_DeleterConfirm, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Cities_EventScript_MauvilleDeleterChoose
	special IsLastMonThatKnowsSurf
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_MauvilleDeleterLastSurf
	special MoveDeleterForgetMove
	playfanfare MUS_MOVE_DELETED
	waitfanfare
	msgbox Cities_Text_DeleterDone, MSGBOX_DEFAULT
	goto Cities_EventScript_MauvilleDeleterChoose

Cities_EventScript_MauvilleDeleterLastSurf::
	msgbox Cities_Text_DeleterLastSurf, MSGBOX_DEFAULT
	goto Cities_EventScript_MauvilleDeleterChoose

Cities_EventScript_MauvilleDeleterOneMove::
	special BufferMoveDeleterNicknameAndMove
	msgbox Cities_Text_DeleterOneMove, MSGBOX_DEFAULT
	goto Cities_EventScript_MauvilleDeleterChoose

Cities_EventScript_MauvilleDeleterEgg::
	msgbox Cities_Text_DeleterEgg, MSGBOX_DEFAULT
	goto Cities_EventScript_MauvilleDeleterChoose

Cities_EventScript_MauvilleDeleterBye::
	msgbox Cities_Text_DeleterBye, MSGBOX_DEFAULT
	release
	end

@ ===================================================================
@ 14.2 — Random-trade NPC (Slateport market). Wonder-trade style.
@ ===================================================================
Cities_EventScript_RandomTrader::
	lock
	faceplayer
	msgbox Cities_Text_TraderIntro, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Cities_EventScript_RandomTraderBye
	msgbox Cities_Text_TraderWhichMon, MSGBOX_DEFAULT
	special ChoosePartyMon
	waitstate
	goto_if_ge VAR_0x8004, PARTY_SIZE, Cities_EventScript_RandomTraderBye
	special IsSelectedMonEgg
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_RandomTraderEgg
	special Script_CitiesDoRandomTrade
	special Script_CitiesBufferTradeSpeciesName
	playfanfare MUS_OBTAIN_ITEM
	msgbox Cities_Text_TraderResult, MSGBOX_DEFAULT
	waitfanfare
	goto Cities_EventScript_RandomTraderBye

Cities_EventScript_RandomTraderEgg::
	msgbox Cities_Text_TraderEgg, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_RandomTraderBye::
	msgbox Cities_Text_TraderBye, MSGBOX_DEFAULT
	release
	end

@ ===================================================================
@ 14.3 — Achievements records-keeper (Mauville plaza).
@ ===================================================================
Cities_EventScript_RecordsKeeper::
	lock
	faceplayer
	special Script_CitiesBufferAchievements
	msgbox Cities_Text_RecordsKeeper, MSGBOX_DEFAULT
	release
	end

@ -- Text --

Cities_Text_RelearnerIntro:
	.string "I can bring back a move your\n"
	.string "POKéMON has forgotten - free of\l"
	.string "charge. Shall I?$"

Cities_Text_RelearnerWhichMon:
	.string "Which POKéMON?$"

Cities_Text_RelearnerWhichMove:
	.string "Which move should it recall?$"

Cities_Text_RelearnerDone:
	.string "There! The move is remembered.$"

Cities_Text_RelearnerNoMove:
	.string "That one has no move to recall.$"

Cities_Text_RelearnerEgg:
	.string "An EGG has nothing to remember\n"
	.string "yet.$"

Cities_Text_RelearnerBye:
	.string "Come back any time. It's always\n"
	.string "free here.$"

Cities_Text_DeleterIntro:
	.string "Want a POKéMON to forget a move?\n"
	.string "I'll do it for free.$"

Cities_Text_DeleterWhichMon:
	.string "Which POKéMON?$"

Cities_Text_DeleterWhichMove:
	.string "Which move should it forget?$"

Cities_Text_DeleterConfirm:
	.string "Forget that move?$"

Cities_Text_DeleterDone:
	.string "Done. The move is forgotten.$"

Cities_Text_DeleterLastSurf:
	.string "That's the only POKéMON that\n"
	.string "knows how to use SURF. Keep it.$"

Cities_Text_DeleterOneMove:
	.string "It only knows one move - it\n"
	.string "can't forget that.$"

Cities_Text_DeleterEgg:
	.string "An EGG knows no moves to forget.$"

Cities_Text_DeleterBye:
	.string "Come back any time.$"

Cities_Text_TraderIntro:
	.string "Feeling lucky? Hand me a POKéMON\n"
	.string "and I'll trade you a mystery one\l"
	.string "from far away.\p"
	.string "No legends - just surprises.\n"
	.string "Care to trade?$"

Cities_Text_TraderWhichMon:
	.string "Which POKéMON will you send?$"

Cities_Text_TraderResult:
	.string "A trade! You received {STR_VAR_1}\n"
	.string "for your POKéMON!$"

Cities_Text_TraderEgg:
	.string "I can't trade an EGG. Come back\n"
	.string "when it's hatched!$"

Cities_Text_TraderBye:
	.string "Change your mind? I'm here all\n"
	.string "day.$"

Cities_Text_RecordsKeeper:
	.string "I keep the region's book of\n"
	.string "honors. Yours reads:\p"
	.string "{STR_VAR_1} of {STR_VAR_3} earned.\p"
	.string "{STR_VAR_2}$"

@ ===================================================================
@ 14.4 — Birch's Shiny Charm at 300 caught (called from his lab script).
@ ===================================================================
Cities_EventScript_BirchGiveShinyCharm::
	msgbox Cities_Text_BirchShinyCharm, MSGBOX_DEFAULT
	giveitem ITEM_SHINY_CHARM
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_BirchShinyCharmBagFull
	setflag FLAG_CITIES_SHINY_CHARM_GIVEN
	msgbox Cities_Text_BirchShinyCharmDone, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_BirchShinyCharmBagFull::
	msgbox Cities_Text_BirchShinyCharmBagFull, MSGBOX_DEFAULT
	release
	end

Cities_Text_BirchShinyCharm:
	.string "{PLAYER}! Three hundred species\n"
	.string "logged - do you have any idea how\l"
	.string "rare that dedication is?\p"
	.string "I've been saving something for a\n"
	.string "trainer who'd truly earn it.$"

Cities_Text_BirchShinyCharmDone:
	.string "The SHINY CHARM! They say it\n"
	.string "coaxes out the rarest colors.\p"
	.string "Go find something dazzling.$"

Cities_Text_BirchShinyCharmBagFull:
	.string "Your BAG is full. Make room, and\n"
	.string "come see me again!$"
