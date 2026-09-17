@ Cities of Emerald (GDD 8.5, Task 7.8): the four original ranked trainers
@ challenge the player from fixed overworld spots, staged by badges so the
@ challenges pace the whole run. Each battles once for ranking points
@ (vanilla trainer flags); afterwards they cheer the player on.

@ -- Visibility (called from each map's on_transition) --

Cities_EventScript_UpdateChallengerBram::
	goto_if_set FLAG_BADGE03_GET, Cities_EventScript_ShowChallengerBram
	setflag FLAG_CITIES_HIDE_CHALLENGER_BRAM
	return

Cities_EventScript_ShowChallengerBram::
	clearflag FLAG_CITIES_HIDE_CHALLENGER_BRAM
	return

Cities_EventScript_UpdateChallengerIlaria::
	goto_if_set FLAG_BADGE05_GET, Cities_EventScript_ShowChallengerIlaria
	setflag FLAG_CITIES_HIDE_CHALLENGER_ILARIA
	return

Cities_EventScript_ShowChallengerIlaria::
	clearflag FLAG_CITIES_HIDE_CHALLENGER_ILARIA
	return

Cities_EventScript_UpdateChallengerCorsen::
	goto_if_set FLAG_BADGE07_GET, Cities_EventScript_ShowChallengerCorsen
	setflag FLAG_CITIES_HIDE_CHALLENGER_CORSEN
	return

Cities_EventScript_ShowChallengerCorsen::
	clearflag FLAG_CITIES_HIDE_CHALLENGER_CORSEN
	return

Cities_EventScript_UpdateChallengerVesper::
	goto_if_set FLAG_SYS_GAME_CLEAR, Cities_EventScript_ShowChallengerVesper
	setflag FLAG_CITIES_HIDE_CHALLENGER_VESPER
	return

Cities_EventScript_ShowChallengerVesper::
	clearflag FLAG_CITIES_HIDE_CHALLENGER_VESPER
	return

@ -- Challenges --

Cities_EventScript_ChallengerBram::
	trainerbattle_single TRAINER_CITIES_CHALLENGER_BRAM, Cities_Text_BramIntro, Cities_Text_BramDefeat
	msgbox Cities_Text_BramPostBattle, MSGBOX_AUTOCLOSE
	end

Cities_EventScript_ChallengerIlaria::
	trainerbattle_single TRAINER_CITIES_CHALLENGER_ILARIA, Cities_Text_IlariaIntro, Cities_Text_IlariaDefeat
	msgbox Cities_Text_IlariaPostBattle, MSGBOX_AUTOCLOSE
	end

Cities_EventScript_ChallengerCorsen::
	trainerbattle_single TRAINER_CITIES_CHALLENGER_CORSEN, Cities_Text_CorsenIntro, Cities_Text_CorsenDefeat
	msgbox Cities_Text_CorsenPostBattle, MSGBOX_AUTOCLOSE
	end

Cities_EventScript_ChallengerVesper::
	trainerbattle_single TRAINER_CITIES_CHALLENGER_VESPER, Cities_Text_VesperIntro, Cities_Text_VesperDefeat
	msgbox Cities_Text_VesperPostBattle, MSGBOX_AUTOCLOSE
	end

Cities_Text_BramIntro:
	.string "Hey! You're {PLAYER}, right?\p"
	.string "I'm BRAM. I'm climbing the national\n"
	.string "rankings, one battle at a time.\p"
	.string "Beating you would be a big step up.\n"
	.string "Let's battle!$"

Cities_Text_BramDefeat:
	.string "Whoa! You're the real deal!$"

Cities_Text_BramPostBattle:
	.string "That loss stung, but I'm not done.\p"
	.string "Check the rankings now and then.\n"
	.string "You'll see my name keep climbing!$"

Cities_Text_IlariaIntro:
	.string "I read the national rankings the way\n"
	.string "some people read the stars.\p"
	.string "Your name keeps rising, {PLAYER}.\n"
	.string "Show me why.$"

Cities_Text_IlariaDefeat:
	.string "Just as I expected… and still,\n"
	.string "it surprised me.$"

Cities_Text_IlariaPostBattle:
	.string "Keep going. The top is closer\n"
	.string "than you think.$"

Cities_Text_CorsenIntro:
	.string "Hmph. I've held my rank for years.\p"
	.string "Everyone says you're something\n"
	.string "special. Let's find out.$"

Cities_Text_CorsenDefeat:
	.string "Ha! So the talk was true after all.$"

Cities_Text_CorsenPostBattle:
	.string "Experience isn't everything, it seems.\n"
	.string "Well fought. Go make history.$"

Cities_Text_VesperIntro:
	.string "So you're the one chasing the top.\p"
	.string "Past me, only the ELITE FOUR and\n"
	.string "WALLACE stand above.\p"
	.string "Prove you belong up here.$"

Cities_Text_VesperDefeat:
	.string "Magnificent. You're ready for\n"
	.string "the summit.$"

Cities_Text_VesperPostBattle:
	.string "Go on, then. The top of the\n"
	.string "rankings is waiting for you.$"
