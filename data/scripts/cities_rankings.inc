@ Cities of Emerald (GDD 8.5, Task 7.6 v1): text-based rankings view.
@ The full leaderboard arrives with the approved ranked-NPC roster.
Cities_EventScript_ShowRankings::
	lockall
	special Script_CitiesBufferRankingScore
	msgbox Cities_Text_RankingScore, MSGBOX_DEFAULT
	releaseall
	end

Cities_Text_RankingScore:
	.string "NATIONAL RANKINGS\p"
	.string "Your score: {STR_VAR_1} points.\p"
	.string "Win battles with your whole team\n"
	.string "to climb the rankings!$"

@ GDD 8.2: shown before a rematch that cannot earn ranking points.
Cities_EventScript_GymRematchNotice::
	specialvar VAR_RESULT, Script_CitiesGymRematchWillScore
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_RematchNoticeDone
	msgbox Cities_Text_NoRankingChange, MSGBOX_DEFAULT
Cities_EventScript_RematchNoticeDone::
	return

Cities_EventScript_RivalRematchNotice::
	specialvar VAR_RESULT, Script_CitiesRivalRematchWillScore
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_RematchNoticeDone
	msgbox Cities_Text_NoRankingChange, MSGBOX_DEFAULT
	return

Cities_Text_NoRankingChange:
	.string "You've already earned ranking points\n"
	.string "from this trainer.\p"
	.string "This battle won't change your\n"
	.string "ranking.$"

@ GDD 8.1 / Task 7.7: shown the moment the player first holds #1.
Cities_EventScript_BecameMaster::
	lockall
	playfanfare MUS_OBTAIN_SYMBOL
	waitfanfare
	setflag FLAG_CITIES_MASTER_ANNOUNCED
	msgbox Cities_Text_BecameMaster, MSGBOX_DEFAULT
	releaseall
	end

Cities_Text_BecameMaster:
	.string "{PLAYER} reached No. 1 in the\n"
	.string "national rankings!\p"
	.string "{PLAYER} is now the\n"
	.string "POKéMON MASTER!\p"
	.string "The POKéMON LEAGUE has invited you\n"
	.string "to a ceremony.\p"
	.string "An official is waiting in the\n"
	.string "POKéMON LEAGUE lobby at\l"
	.string "EVER GRANDE CITY.$"
