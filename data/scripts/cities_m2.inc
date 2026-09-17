@ Cities of Emerald — M2 "The Sealed Chamber, Opened" (GDD 6.6, approved
@ 2026-09-16). The archaeologist in Pacifidlog's lore house starts the
@ hint trail at badge 5; the vanilla puzzle is unchanged but every
@ braille sign gains a plain-language translation; the three Regis use
@ the shared level rule and are never permanently missable.

Cities_EventScript_UpdateM2Archaeologist::
	goto_if_set FLAG_BADGE05_GET, Cities_EventScript_ShowM2Archaeologist
	setflag FLAG_CITIES_HIDE_M2_ARCHAEOLOGIST
	return

Cities_EventScript_ShowM2Archaeologist::
	clearflag FLAG_CITIES_HIDE_M2_ARCHAEOLOGIST
	return

Cities_EventScript_M2Archaeologist::
	lock
	faceplayer
	setvar VAR_0x8004, 1 @ CITIES_ARC_M2
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_M2AllCaught
	goto_if_eq VAR_CITIES_M2_STATE, 0, Cities_EventScript_M2Intro
	msgbox Cities_Text_M2Progress, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_M2Intro::
	msgbox Cities_Text_M2Intro, MSGBOX_DEFAULT
	setvar VAR_CITIES_M2_STATE, 1
	release
	end

Cities_EventScript_M2AllCaught::
	goto_if_eq VAR_CITIES_M2_STATE, 2, Cities_EventScript_M2After
	msgbox Cities_Text_M2Thanks, MSGBOX_DEFAULT
	setvar VAR_CITIES_M2_STATE, 2
	release
	end

Cities_EventScript_M2After::
	msgbox Cities_Text_M2After, MSGBOX_DEFAULT
	release
	end

Cities_Text_M2Intro:
	.string "You have the look of an explorer!\p"
	.string "I've studied the SEALED CHAMBER my\n"
	.string "whole life. Here's everything I\l"
	.string "know, plainly:\p"
	.string "Dive underwater on Route 134 and\n"
	.string "surface inside the cavern.\p"
	.string "One wall asks you to use DIG.\p"
	.string "The deep room asks for WAILORD\n"
	.string "first in your party and RELICANTH\l"
	.string "last.\p"
	.string "Do that, and three ancient doors\n"
	.string "will open across HOENN.\p"
	.string "It's all written in braille - but\n"
	.string "every sign will explain itself,\l"
	.string "I promise. My notes made sure.$"

Cities_Text_M2Progress:
	.string "The three doors: DESERT RUINS off\n"
	.string "Route 111, ISLAND CAVE on Route\l"
	.string "105, ANCIENT TOMB on Route 120.\p"
	.string "You'll need DIVE for the SEALED\n"
	.string "CHAMBER - it's deep under Route 134.$"

Cities_Text_M2Thanks:
	.string "All three giants, befriended…\p"
	.string "My life's work, standing right in\n"
	.string "front of me. Thank you, {PLAYER}.\p"
	.string "…My notes mention one more line I\n"
	.string "never understood:\p"
	.string "“A colossus that moved whole\n"
	.string "continents sleeps deeper still.”$"

Cities_Text_M2After:
	.string "“A colossus that moved whole\n"
	.string "continents…”\p"
	.string "Maybe one day we'll learn what the\n"
	.string "ancients meant.$"

@ -- Plain-language braille translations (GDD 11 language rules) --

Cities_Text_BrailleAlphabetWall:
	.string "This wall is a braille alphabet\n"
	.string "key, left by the ancients.$"

Cities_Text_BrailleDigHere:
	.string "The braille reads: “Dig here.”\p"
	.string "(Have a POKéMON use DIG while you\n"
	.string "face this wall.)$"

Cities_Text_BrailleFirstWailord:
	.string "The braille reads: “First comes\n"
	.string "WAILORD. Last comes RELICANTH.”\p"
	.string "(Put WAILORD first and RELICANTH\n"
	.string "last in your party, then read this\l"
	.string "wall again.)$"

Cities_Text_BrailleLore1:
	.string "The braille reads: “In this cave\n"
	.string "we have lived.”$"

Cities_Text_BrailleLore2:
	.string "The braille reads: “We owe all\n"
	.string "to the POKéMON.”$"

Cities_Text_BrailleLore3:
	.string "The braille reads: “But we sealed\n"
	.string "the POKéMON away.”$"

Cities_Text_BrailleLore4:
	.string "The braille reads: “We feared it.”$"

Cities_Text_BrailleLore5:
	.string "The braille reads: “Those with\n"
	.string "courage, those with hope.”$"

Cities_Text_BrailleLore6:
	.string "The braille reads: “Open a door.\n"
	.string "An eternal POKéMON waits.”$"

Cities_Text_BrailleRockSmash:
	.string "The braille reads: “Use\n"
	.string "ROCK SMASH here.”$"

Cities_Text_BrailleShineMiddle:
	.string "The braille reads: “Let light\n"
	.string "shine in the middle.”\p"
	.string "(Stand in the room's center and\n"
	.string "use FLASH.)$"

Cities_Text_BrailleRunLap:
	.string "The braille reads: “Stop and wait.\n"
	.string "Then run one lap along the wall.”\p"
	.string "(Stand still for a moment, then\n"
	.string "run a full loop around the inside\l"
	.string "of the room.)$"
