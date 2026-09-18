@ Cities of Emerald — Task 12.7: the Coralmere survivors (GDD 7.2,
@ roster approved 2026-09-18). Scattered ordinary people, present from
@ the start of the game. Three stages: an everyday hint, then one step
@ more open after the player walks the rift (V4 >= 2), then - after the
@ ending - they speak of KAI by name (those texts live in
@ cities_ending.inc, the name-quarantine file; see Task 12.8).
@ Talking at any stage sets the town's MET flag for the journal.

Cities_EventScript_SurvivorDewford::
	lock
	faceplayer
	setflag FLAG_CITIES_SURVIVOR_DEWFORD
	goto_if_set FLAG_CITIES_KAI_NAMED, Cities_EventScript_SurvivorDewfordNamed
	goto_if_ge VAR_CITIES_V4_STATE, 2, Cities_EventScript_SurvivorDewfordRift
	msgbox Cities_Text_SurvivorDewfordHint, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorDewfordRift::
	msgbox Cities_Text_SurvivorDewfordRift, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorSlateport::
	lock
	faceplayer
	setflag FLAG_CITIES_SURVIVOR_SLATEPORT
	goto_if_set FLAG_CITIES_KAI_NAMED, Cities_EventScript_SurvivorSlateportNamed
	goto_if_ge VAR_CITIES_V4_STATE, 2, Cities_EventScript_SurvivorSlateportRift
	msgbox Cities_Text_SurvivorSlateportHint, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorSlateportRift::
	msgbox Cities_Text_SurvivorSlateportRift, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorMauville::
	lock
	faceplayer
	setflag FLAG_CITIES_SURVIVOR_MAUVILLE
	goto_if_set FLAG_CITIES_KAI_NAMED, Cities_EventScript_SurvivorMauvilleNamed
	goto_if_ge VAR_CITIES_V4_STATE, 2, Cities_EventScript_SurvivorMauvilleRift
	msgbox Cities_Text_SurvivorMauvilleHint, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorMauvilleRift::
	msgbox Cities_Text_SurvivorMauvilleRift, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorFallarbor::
	lock
	faceplayer
	setflag FLAG_CITIES_SURVIVOR_FALLARBOR
	goto_if_set FLAG_CITIES_KAI_NAMED, Cities_EventScript_SurvivorFallarborNamed
	goto_if_ge VAR_CITIES_V4_STATE, 2, Cities_EventScript_SurvivorFallarborRift
	msgbox Cities_Text_SurvivorFallarborHint, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorFallarborRift::
	msgbox Cities_Text_SurvivorFallarborRift, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorLilycove::
	lock
	faceplayer
	setflag FLAG_CITIES_SURVIVOR_LILYCOVE
	goto_if_set FLAG_CITIES_KAI_NAMED, Cities_EventScript_SurvivorLilycoveNamed
	goto_if_ge VAR_CITIES_V4_STATE, 2, Cities_EventScript_SurvivorLilycoveRift
	msgbox Cities_Text_SurvivorLilycoveHint, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorLilycoveRift::
	msgbox Cities_Text_SurvivorLilycoveRift, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorMossdeep::
	lock
	faceplayer
	setflag FLAG_CITIES_SURVIVOR_MOSSDEEP
	goto_if_set FLAG_CITIES_KAI_NAMED, Cities_EventScript_SurvivorMossdeepNamed
	goto_if_ge VAR_CITIES_V4_STATE, 2, Cities_EventScript_SurvivorMossdeepRift
	msgbox Cities_Text_SurvivorMossdeepHint, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorMossdeepRift::
	msgbox Cities_Text_SurvivorMossdeepRift, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorSootopolis::
	lock
	faceplayer
	setflag FLAG_CITIES_SURVIVOR_SOOTOPOLIS
	goto_if_set FLAG_CITIES_KAI_NAMED, Cities_EventScript_SurvivorSootopolisNamed
	goto_if_ge VAR_CITIES_V4_STATE, 2, Cities_EventScript_SurvivorSootopolisRift
	msgbox Cities_Text_SurvivorSootopolisHint, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_SurvivorSootopolisRift::
	msgbox Cities_Text_SurvivorSootopolisRift, MSGBOX_DEFAULT
	release
	end

@ -- Text (stages 1-2; the KAI stage is in cities_ending.inc) --

Cities_Text_SurvivorDewfordHint:
	.string "The waves off DEWFORD are good\n"
	.string "fishing.\p"
	.string "Just not east. Not toward ROUTE\n"
	.string "128. Don't ask me why.\p"
	.string "I don't fish there. That's all.$"

Cities_Text_SurvivorDewfordRift:
	.string "You've seen it now, haven't you.\n"
	.string "The streets under the water.\p"
	.string "I was small. My father rowed all\n"
	.string "night. Not everyone's did.\p"
	.string "I still can't cast a line that\n"
	.string "way.$"

Cities_Text_SurvivorSlateportHint:
	.string "Shell charms! Made the way they\n"
	.string "did back home.\p"
	.string "Everybody wants the anchor\n"
	.string "design. Nobody remembers where\l"
	.string "it's from.$"

Cities_Text_SurvivorSlateportRift:
	.string "Home was a village the sea took.\p"
	.string "I carve the charms so the shape\n"
	.string "of it stays in somebody's hands.\p"
	.string "A wave. A bell. Two little fish.\n"
	.string "That was the whole town, really.$"

Cities_Text_SurvivorMauvilleHint:
	.string "Here's one my mother taught me.\p"
	.string "(He hums a slow tune, like bells\n"
	.string "ringing out over water.)\p"
	.string "Don't know the words anymore.\n"
	.string "Just that it's about coming home.$"

Cities_Text_SurvivorMauvilleRift:
	.string "The song is from CORALMERE.\p"
	.string "You walked it, didn't you. In the\n"
	.string "rift.\p"
	.string "Then you heard this tune for\n"
	.string "real. It was the bell. It was\l"
	.string "always the bell.$"

Cities_Text_SurvivorFallarborHint:
	.string "This old map? Just a hobby.\p"
	.string "A little seaside town, drawn from\n"
	.string "memory. You won't find it on any\l"
	.string "official chart.\p"
	.string "Doesn't mean it wasn't real.$"

Cities_Text_SurvivorFallarborRift:
	.string "CORALMERE. There, you've made me\n"
	.string "say it.\p"
	.string "I teach children about every town\n"
	.string "in HOENN. I couldn't bear to\l"
	.string "leave mine off the map, even if\l"
	.string "I'm the only one still drawing\l"
	.string "it.$"

Cities_Text_SurvivorLilycoveHint:
	.string "One of my paintings? The little\n"
	.string "bell tower by the sea.\p"
	.string "From a dream, people assume.\p"
	.string "I let them assume.$"

Cities_Text_SurvivorLilycoveRift:
	.string "It wasn't a dream. You know that\n"
	.string "now.\p"
	.string "I paint the tower every year, a\n"
	.string "little more worn, a little more\l"
	.string "under the water.\p"
	.string "Some things you keep by refusing\n"
	.string "to finish them.$"

Cities_Text_SurvivorMossdeepHint:
	.string "That old sign on my wall?\n"
	.string "CORALME, something. Half the\l"
	.string "letters are gone.\p"
	.string "Fished it up years ago. Couldn't\n"
	.string "throw a town's name back in the\l"
	.string "sea.$"

Cities_Text_SurvivorMossdeepRift:
	.string "You've seen the whole sign now,\n"
	.string "haven't you. Down where it\l"
	.string "stands.\p"
	.string "Mine's the same sign, snapped off\n"
	.string "in the storm.\p"
	.string "I kept the piece that had home\n"
	.string "on it.$"

Cities_Text_SurvivorSootopolisHint:
	.string "Living in a crater, you think\n"
	.string "about the sea a lot.\p"
	.string "Do you think the legendaries ever\n"
	.string "regret the storms? Even one of\l"
	.string "them?\p"
	.string "...Never mind. Old question.$"

Cities_Text_SurvivorSootopolisRift:
	.string "A village of mine went under,\n"
	.string "long ago. One storm.\p"
	.string "I don't need the legendaries to\n"
	.string "regret it. I just needed someone\l"
	.string "to remember it was there.\p"
	.string "You did. Thank you.$"

