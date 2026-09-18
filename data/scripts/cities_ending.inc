@ Cities of Emerald — Task 12.6: the ending (GDD 7.2, all [DECIDED];
@ family approved 2026-09-18: Tomas, Marisol, Nico, Bay — the GDD's
@ last open item, closed). Resolution through acceptance. The
@ children speak the name because to them it was never lost.
@
@ FLAG_CITIES_KAI_NAMED is THE flag: no text reachable before it may
@ contain "Kai" (Task 12.8 enforces this).

@ -- Visibility / staging (Pacifidlog ON_TRANSITION) --

Cities_EventScript_UpdateEnding::
	goto_if_ne VAR_CITIES_V5_STATE, 3, Cities_EventScript_EndingHideFamily
	clearflag FLAG_CITIES_HIDE_ENDING_FAMILY
	goto_if_set FLAG_CITIES_KAI_NAMED, Cities_EventScript_EndingFamilyHome
	setobjectxyperm LOCALID_PACIFIDLOG_CITIES_NICO, 8, 16
	setobjectxyperm LOCALID_PACIFIDLOG_CITIES_MARISOL, 9, 16
	setobjectxyperm LOCALID_PACIFIDLOG_CITIES_BAY, 10, 16
	return

Cities_EventScript_EndingFamilyHome::
	setobjectxyperm LOCALID_PACIFIDLOG_CITIES_MARISOL, 11, 25
	setobjectxyperm LOCALID_PACIFIDLOG_CITIES_BAY, 12, 25
	setobjectxyperm LOCALID_PACIFIDLOG_CITIES_NICO, 13, 25
	return

Cities_EventScript_EndingHideFamily::
	setflag FLAG_CITIES_HIDE_ENDING_FAMILY
	return

Cities_EventScript_UpdateEpilogueKaiWI::
	goto_if_unset FLAG_CITIES_KAI_NAMED, Cities_EventScript_EndingHideKaiWI
	clearflag FLAG_CITIES_HIDE_KAI_WI
	return

Cities_EventScript_EndingHideKaiWI::
	setflag FLAG_CITIES_HIDE_KAI_WI
	return

Cities_EventScript_UpdateEpilogueArchive::
	goto_if_unset FLAG_CITIES_KAI_NAMED, Cities_EventScript_EndingHideArchive
	clearflag FLAG_CITIES_HIDE_ARCHIVE_MERIDIAN
	clearflag FLAG_CITIES_HIDE_ARCHIVE_GNOMON
	return

Cities_EventScript_EndingHideArchive::
	setflag FLAG_CITIES_HIDE_ARCHIVE_MERIDIAN
	setflag FLAG_CITIES_HIDE_ARCHIVE_GNOMON
	return

@ -- The scene (entered from the Archivist's dock script at V5==3) --

Cities_EventScript_EndingScene::
	msgbox Cities_Text_EndingHeWaits, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PACIFIDLOG_CITIES_NICO, Cities_Movement_NicoRuns
	waitmovement 0
	msgbox Cities_Text_EndingNico, MSGBOX_DEFAULT
	closemessage
	playse SE_M_HEAL_BELL
	waitse
	msgbox Cities_Text_EndingBell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_PACIFIDLOG_CITIES_MARISOL, Cities_Movement_MarisolSteps
	waitmovement 0
	msgbox Cities_Text_EndingMarisol, MSGBOX_DEFAULT
	closemessage
	delay 60
	msgbox Cities_Text_EndingKai, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_WHITE
	setflag FLAG_CITIES_KAI_NAMED
	msgbox Cities_Text_EndingAfter, MSGBOX_DEFAULT
	closemessage
	release
	end

Cities_Movement_NicoRuns:
	walk_fast_down
	walk_fast_left
	face_right
	step_end

Cities_Movement_MarisolSteps:
	walk_down
	walk_right
	walk_right
	face_left
	step_end

@ -- The family, before and after --

Cities_EventScript_EndingMarisol::
	lock
	faceplayer
	goto_if_set FLAG_CITIES_KAI_NAMED, Cities_EventScript_EndingMarisolAfter
	msgbox Cities_Text_MarisolBefore, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_EndingMarisolAfter::
	msgbox Cities_Text_MarisolAfter, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_EndingNico::
	lock
	faceplayer
	goto_if_set FLAG_CITIES_KAI_NAMED, Cities_EventScript_EndingNicoAfter
	msgbox Cities_Text_NicoBefore, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_EndingNicoAfter::
	msgbox Cities_Text_NicoAfter, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_EndingBay::
	lock
	faceplayer
	goto_if_set FLAG_CITIES_KAI_NAMED, Cities_EventScript_EndingBayAfter
	msgbox Cities_Text_BayBefore, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_EndingBayAfter::
	msgbox Cities_Text_BayAfter, MSGBOX_DEFAULT
	release
	end

@ -- The epilogue: Kai at the Weather Institute --

Cities_EventScript_EpilogueKai::
	lock
	faceplayer
	msgbox Cities_Text_EpilogueKai, MSGBOX_DEFAULT
	release
	end

@ -- The epilogue: the Coralmere Archive (the annex, remade) --

Cities_EventScript_ArchiveMeridian::
	lock
	faceplayer
	msgbox Cities_Text_ArchiveMeridian, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_ArchiveGnomon::
	lock
	faceplayer
	msgbox Cities_Text_ArchiveGnomon, MSGBOX_DEFAULT
	release
	end

@ -- Text --

Cities_Text_EndingHeWaits:
	.string "He is at the dock's edge, dry\n"
	.string "at last, watching the water.\p"
	.string "Not leaving.\n"
	.string "Not approaching.\p"
	.string "Behind you, a door opens.$"

Cities_Text_EndingNico:
	.string "“You're KAI!\p"
	.string "“You ARE. Grandpa TOMAS told us\n"
	.string "everything! The reef race! The\l"
	.string "bell rope! The eel!\p"
	.string "“You're brave, stubborn KAI,\n"
	.string "from before the sea!”$"

Cities_Text_EndingBell:
	.string "The small girl reaches up and\n"
	.string "rings the bell by the door.\p"
	.string "Once. Clear across the water.\p"
	.string "“Grandpa rang it every year.\n"
	.string "So anyone still out there could\l"
	.string "find their way home.”$"

Cities_Text_EndingMarisol:
	.string "“My father was TOMAS. Of\n"
	.string "CORALMERE. You'd remember him\l"
	.string "with skinned knees.\p"
	.string "“He lived, KAI. He got out. He\n"
	.string "lived a whole life on this\l"
	.string "water, and he told you into\l"
	.string "every corner of it.\p"
	.string "“We found you, years ago. The\n"
	.string "coat, the barometer. I was\l"
	.string "afraid of what you'd become.\p"
	.string "“I watched the storm stop\n"
	.string "yesterday. I'm not afraid\l"
	.string "anymore.”$"

Cities_Text_EndingKai:
	.string "For a long time he does not\n"
	.string "say anything at all.\p"
	.string "“…I spent twenty years trying\n"
	.string "to walk back into one morning.\p"
	.string "“And the whole time, the\n"
	.string "morning was walking FORWARD.\l"
	.string "Without me. Here.\p"
	.string "“TOMAS. The bell. You.\p"
	.string "“…My name is KAI.”\p"
	.string "He says it like something\n"
	.string "returned to its shelf at last.$"

Cities_Text_EndingAfter:
	.string "The sun is fully out now.\p"
	.string "Somewhere behind you, two\n"
	.string "children are already arguing\l"
	.string "about who gets to tell it.$"

Cities_Text_MarisolBefore:
	.string "The man from the storm is at\n"
	.string "our dock.\p"
	.string "I keep starting toward him and\n"
	.string "stopping.\p"
	.string "…My father would already be\n"
	.string "over there.$"

Cities_Text_MarisolAfter:
	.string "KAI eats dinner here on\n"
	.string "SUNDAYS now. He does the\l"
	.string "dishes. Badly.\p"
	.string "My father would be insufferably\n"
	.string "pleased with himself.$"

Cities_Text_NicoBefore:
	.string "Mom keeps looking at the man\n"
	.string "on the dock.\p"
	.string "I think he's from grandpa's\n"
	.string "stories. I think he's THE ONE\l"
	.string "from grandpa's stories.$"

Cities_Text_NicoAfter:
	.string "KAI says the eel story is\n"
	.string "exaggerated.\p"
	.string "Grandpa said KAI would say\n"
	.string "that. Grandpa said that PROVES\l"
	.string "IT.$"

Cities_Text_BayBefore:
	.string "When I'm scared, I ring the\n"
	.string "bell. Grandpa said it works.\p"
	.string "It always works.$"

Cities_Text_BayAfter:
	.string "KAI showed me how to read the\n"
	.string "barometer!\p"
	.string "It says FAIR. It's going to say\n"
	.string "FAIR forever, I think.$"

Cities_Text_EpilogueKai:
	.string "The desk by the window faces\n"
	.string "the sea now.\p"
	.string "“Twenty years of readings, and\n"
	.string "I never once logged a morning\l"
	.string "like this one.\p"
	.string "“HALLEY kept my chair. The\n"
	.string "charts need a decade of\l"
	.string "catching up. Good.\p"
	.string "“Storms will come again. This\n"
	.string "time the warning will be\l"
	.string "early. This time it will be\l"
	.string "signed.\p"
	.string "“- KAI.”$"

Cities_Text_ArchiveMeridian:
	.string "Welcome to the CORALMERE\n"
	.string "ARCHIVE. Mind the children -\l"
	.string "they bite, but only the\l"
	.string "history books.\p"
	.string "We keep the village here now.\n"
	.string "Not in a machine. In lessons.\p"
	.string "He saved my town's records\n"
	.string "once, over his head, through\l"
	.string "a flood.\p"
	.string "It turns out that was the\n"
	.string "whole plan, all along. It just\l"
	.string "took the rest of us twenty\l"
	.string "years to read it.$"

Cities_Text_ArchiveGnomon:
	.string "Every part catalogued, crated,\n"
	.string "and rendered extremely inert.\p"
	.string "The crates say “NEVER AGAIN.”\p"
	.string "Underneath, in small print,\n"
	.string "they say “PROBABLY.”\p"
	.string "An engineer should be honest\n"
	.string "on the label.$"

@ -- Task 12.7 survivors, KAI stage (quarantined here; gated behind
@ FLAG_CITIES_KAI_NAMED at every call site) --

Cities_EventScript_SurvivorDewfordNamed::
	msgbox Cities_Text_SurvivorDewfordNamed, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorSlateportNamed::
	msgbox Cities_Text_SurvivorSlateportNamed, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorMauvilleNamed::
	msgbox Cities_Text_SurvivorMauvilleNamed, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorFallarborNamed::
	msgbox Cities_Text_SurvivorFallarborNamed, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorLilycoveNamed::
	msgbox Cities_Text_SurvivorLilycoveNamed, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorMossdeepNamed::
	msgbox Cities_Text_SurvivorMossdeepNamed, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorSootopolisNamed::
	msgbox Cities_Text_SurvivorSootopolisNamed, MSGBOX_DEFAULT
	release
	end

Cities_Text_SurvivorDewfordNamed:
	.string "I fish east now. Toward ROUTE\n"
	.string "128.\p"
	.string "KAI showed me the village is at\n"
	.string "peace down there. So am I,\l"
	.string "slowly.$"

Cities_Text_SurvivorSlateportNamed:
	.string "KAI came by the stall. Held one\n"
	.string "of my charms a long time.\p"
	.string "Said CORALMERE always did have\n"
	.string "the best hands. Then he bought\l"
	.string "six.$"

Cities_Text_SurvivorMauvilleNamed:
	.string "I know the words to the song now.\p"
	.string "KAI remembered them. We sang it\n"
	.string "together, badly, and everyone\l"
	.string "threw coins.\p"
	.string "Best day of busking I ever had.$"

Cities_Text_SurvivorFallarborNamed:
	.string "I added CORALMERE to the class\n"
	.string "map, in ink, for good.\p"
	.string "KAI signed the corner. He said a\n"
	.string "town is real as long as someone\l"
	.string "teaches it.$"

Cities_Text_SurvivorLilycoveNamed:
	.string "I finished the painting.\p"
	.string "The tower, above the water, in\n"
	.string "the sun. KAI helped me choose\l"
	.string "the light.\p"
	.string "It hangs in the ARCHIVE now.$"

Cities_Text_SurvivorMossdeepNamed:
	.string "KAI has the other half of the\n"
	.string "sign.\p"
	.string "We fitted them together on the\n"
	.string "ARCHIVE wall. CORALMERE, whole\l"
	.string "again, in letters if not in\l"
	.string "stone.$"

Cities_Text_SurvivorSootopolisNamed:
	.string "The legendaries never answered\n"
	.string "my old question.\p"
	.string "But KAI did, with his own hands,\n"
	.string "in a storm. That turned out to\l"
	.string "be the answer.$"

