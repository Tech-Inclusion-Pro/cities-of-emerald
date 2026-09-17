@ Cities of Emerald (GDD 11.4, Phase 9): quest journal and "last time"
@ recap. Quest names and steps are computed from flags in
@ src/cities_quests.c; the journal pages through every active quest.

Cities_EventScript_ShowJournal::
	lockall
	setvar VAR_TEMP_9, 0
Cities_EventScript_JournalLoop::
	specialvar VAR_RESULT, Script_CitiesBufferNextJournalEntry
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_JournalDone
	msgbox Cities_Text_JournalEntry, MSGBOX_DEFAULT
	addvar VAR_TEMP_9, 1
	goto Cities_EventScript_JournalLoop
Cities_EventScript_JournalDone::
	closemessage
	releaseall
	end

Cities_Text_JournalEntry:
	.string "{STR_VAR_2}\p"
	.string "{STR_VAR_3}$"

@ Shown once on loading a save, when the player has control (GDD 11.4).
Cities_EventScript_Recap::
	lockall
	special Script_CitiesBufferMainQuestStep
	msgbox Cities_Text_Recap, MSGBOX_DEFAULT
	closemessage
	releaseall
	end

Cities_Text_Recap:
	.string "Welcome back, {PLAYER}!\p"
	.string "{STR_VAR_3}$"
