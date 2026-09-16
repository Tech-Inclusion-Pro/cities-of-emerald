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
