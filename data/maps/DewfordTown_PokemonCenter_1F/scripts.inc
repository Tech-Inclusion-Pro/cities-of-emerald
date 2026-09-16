DewfordTown_PokemonCenter_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

DewfordTown_PokemonCenter_1F_OnTransition:
	setrespawn HEAL_LOCATION_DEWFORD_TOWN
	call Common_EventScript_UpdateBrineyLocation
@ Cities of Emerald (GDD 4.3): the stone expert appears after badge 2.
	call_if_unset FLAG_BADGE02_GET, DewfordTown_PokemonCenter_1F_EventScript_HideStoneExpert
	call_if_set FLAG_BADGE02_GET, DewfordTown_PokemonCenter_1F_EventScript_ShowStoneExpert
	end

DewfordTown_PokemonCenter_1F_EventScript_HideStoneExpert::
	setflag FLAG_CITIES_DEWFORD_STONE_NPC_HIDDEN
	return

DewfordTown_PokemonCenter_1F_EventScript_ShowStoneExpert::
	clearflag FLAG_CITIES_DEWFORD_STONE_NPC_HIDDEN
	return

DewfordTown_PokemonCenter_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_DEWFORD_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

DewfordTown_PokemonCenter_1F_EventScript_PokefanF::
	msgbox DewfordTown_PokemonCenter_1F_Text_StoneCavern, MSGBOX_NPC
	end

DewfordTown_PokemonCenter_1F_EventScript_Man::
	msgbox DewfordTown_PokemonCenter_1F_Text_FaintedMonCanUseHM, MSGBOX_NPC
	end

@ Cities of Emerald (GDD 4.3): stone expert. Explains every stone and
@ Eeveelution in plain language before the player picks ONE free stone.
DewfordTown_PokemonCenter_1F_EventScript_StoneExpert::
	lock
	faceplayer
	goto_if_set FLAG_CITIES_DEWFORD_STONE_GIVEN, DewfordTown_PokemonCenter_1F_EventScript_StoneExpertAfter
	msgbox DewfordTown_PokemonCenter_1F_Text_StoneIntro, MSGBOX_DEFAULT
	msgbox DewfordTown_PokemonCenter_1F_Text_StonesPart1, MSGBOX_DEFAULT
	msgbox DewfordTown_PokemonCenter_1F_Text_StonesPart2, MSGBOX_DEFAULT
	msgbox DewfordTown_PokemonCenter_1F_Text_FriendshipForms, MSGBOX_DEFAULT
DewfordTown_PokemonCenter_1F_EventScript_ChooseStone::
	msgbox DewfordTown_PokemonCenter_1F_Text_WhichStone, MSGBOX_DEFAULT
	multichoice 0, 0, MULTI_CITIES_EEVEE_STONES, FALSE
	switch VAR_RESULT
	case 0, DewfordTown_PokemonCenter_1F_EventScript_GiveWaterStone
	case 1, DewfordTown_PokemonCenter_1F_EventScript_GiveThunderStone
	case 2, DewfordTown_PokemonCenter_1F_EventScript_GiveFireStone
	case 3, DewfordTown_PokemonCenter_1F_EventScript_GiveLeafStone
	case 4, DewfordTown_PokemonCenter_1F_EventScript_GiveIceStone
	case 5, DewfordTown_PokemonCenter_1F_EventScript_DeclineStone
	case MULTI_B_PRESSED, DewfordTown_PokemonCenter_1F_EventScript_DeclineStone
	end

DewfordTown_PokemonCenter_1F_EventScript_GiveWaterStone::
	msgbox DewfordTown_PokemonCenter_1F_Text_ConfirmWater, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DewfordTown_PokemonCenter_1F_EventScript_ChooseStone
	giveitem ITEM_WATER_STONE
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_PokemonCenter_1F_EventScript_StoneBagFull
	goto DewfordTown_PokemonCenter_1F_EventScript_StoneGiven

DewfordTown_PokemonCenter_1F_EventScript_GiveThunderStone::
	msgbox DewfordTown_PokemonCenter_1F_Text_ConfirmThunder, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DewfordTown_PokemonCenter_1F_EventScript_ChooseStone
	giveitem ITEM_THUNDER_STONE
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_PokemonCenter_1F_EventScript_StoneBagFull
	goto DewfordTown_PokemonCenter_1F_EventScript_StoneGiven

DewfordTown_PokemonCenter_1F_EventScript_GiveFireStone::
	msgbox DewfordTown_PokemonCenter_1F_Text_ConfirmFire, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DewfordTown_PokemonCenter_1F_EventScript_ChooseStone
	giveitem ITEM_FIRE_STONE
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_PokemonCenter_1F_EventScript_StoneBagFull
	goto DewfordTown_PokemonCenter_1F_EventScript_StoneGiven

DewfordTown_PokemonCenter_1F_EventScript_GiveLeafStone::
	msgbox DewfordTown_PokemonCenter_1F_Text_ConfirmLeaf, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DewfordTown_PokemonCenter_1F_EventScript_ChooseStone
	giveitem ITEM_LEAF_STONE
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_PokemonCenter_1F_EventScript_StoneBagFull
	goto DewfordTown_PokemonCenter_1F_EventScript_StoneGiven

DewfordTown_PokemonCenter_1F_EventScript_GiveIceStone::
	msgbox DewfordTown_PokemonCenter_1F_Text_ConfirmIce, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, DewfordTown_PokemonCenter_1F_EventScript_ChooseStone
	giveitem ITEM_ICE_STONE
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_PokemonCenter_1F_EventScript_StoneBagFull
	goto DewfordTown_PokemonCenter_1F_EventScript_StoneGiven

DewfordTown_PokemonCenter_1F_EventScript_StoneGiven::
	setflag FLAG_CITIES_DEWFORD_STONE_GIVEN
	msgbox DewfordTown_PokemonCenter_1F_Text_StoneEnjoy, MSGBOX_DEFAULT
	release
	end

DewfordTown_PokemonCenter_1F_EventScript_StoneBagFull::
	msgbox DewfordTown_PokemonCenter_1F_Text_StoneBagFull, MSGBOX_DEFAULT
	release
	end

DewfordTown_PokemonCenter_1F_EventScript_DeclineStone::
	msgbox DewfordTown_PokemonCenter_1F_Text_StoneNoRush, MSGBOX_DEFAULT
	release
	end

DewfordTown_PokemonCenter_1F_EventScript_StoneExpertAfter::
	msgbox DewfordTown_PokemonCenter_1F_Text_StoneAfter, MSGBOX_DEFAULT
	release
	end

DewfordTown_PokemonCenter_1F_Text_StoneIntro:
	.string "Hello! I study evolution stones.\p"
	.string "Some Pokémon change into a new form\n"
	.string "when they touch a special stone.\p"
	.string "Eevee is amazing. It can become\n"
	.string "many different Pokémon!\p"
	.string "Let me tell you about each stone,\n"
	.string "so you can pick the right one.$"

DewfordTown_PokemonCenter_1F_Text_StonesPart1:
	.string "A Water Stone turns Eevee into\n"
	.string "Vaporeon, a Water-type.\p"
	.string "Vaporeon has lots of health and\n"
	.string "is a strong swimmer.\p"
	.string "A Thunder Stone turns Eevee into\n"
	.string "Jolteon, an Electric-type.\p"
	.string "Jolteon is very fast and hits\n"
	.string "hard with electric moves.$"

DewfordTown_PokemonCenter_1F_Text_StonesPart2:
	.string "A Fire Stone turns Eevee into\n"
	.string "Flareon, a Fire-type.\p"
	.string "Flareon has a very strong attack.\p"
	.string "A Leaf Stone turns Eevee into\n"
	.string "Leafeon, a Grass-type.\p"
	.string "Leafeon is a sturdy defender.\p"
	.string "An Ice Stone turns Eevee into\n"
	.string "Glaceon, an Ice-type.\p"
	.string "Glaceon hits hard with icy moves.$"

DewfordTown_PokemonCenter_1F_Text_FriendshipForms:
	.string "Three more forms need no stone\n"
	.string "at all. They come from friendship.\p"
	.string "A happy Eevee becomes Espeon,\n"
	.string "a Psychic-type, in the daytime.\p"
	.string "At night, a happy Eevee becomes\n"
	.string "Umbreon, a Dark-type.\p"
	.string "And if it knows a Fairy-type move,\n"
	.string "a happy Eevee becomes Sylveon,\l"
	.string "a Fairy-type.$"

DewfordTown_PokemonCenter_1F_Text_WhichStone:
	.string "You may take one stone as a gift.\n"
	.string "Which stone would you like?$"

DewfordTown_PokemonCenter_1F_Text_ConfirmWater:
	.string "Take the Water Stone, for\n"
	.string "Vaporeon, the Water-type?$"

DewfordTown_PokemonCenter_1F_Text_ConfirmThunder:
	.string "Take the Thunder Stone, for\n"
	.string "Jolteon, the Electric-type?$"

DewfordTown_PokemonCenter_1F_Text_ConfirmFire:
	.string "Take the Fire Stone, for\n"
	.string "Flareon, the Fire-type?$"

DewfordTown_PokemonCenter_1F_Text_ConfirmLeaf:
	.string "Take the Leaf Stone, for\n"
	.string "Leafeon, the Grass-type?$"

DewfordTown_PokemonCenter_1F_Text_ConfirmIce:
	.string "Take the Ice Stone, for\n"
	.string "Glaceon, the Ice-type?$"

DewfordTown_PokemonCenter_1F_Text_StoneEnjoy:
	.string "Wonderful choice!\p"
	.string "Come back and tell me how your\n"
	.string "Eevee grows.\p"
	.string "I hear some trainers around Hoenn\n"
	.string "give stones to those who beat\l"
	.string "them in battle. Good luck!$"

DewfordTown_PokemonCenter_1F_Text_StoneBagFull:
	.string "Oh! Your Bag is full.\p"
	.string "Please come back when you have\n"
	.string "room for the stone.$"

DewfordTown_PokemonCenter_1F_Text_StoneNoRush:
	.string "No rush at all.\n"
	.string "Come back any time.$"

DewfordTown_PokemonCenter_1F_Text_StoneAfter:
	.string "How is your Eevee doing?\p"
	.string "Remember: Espeon needs daytime.\n"
	.string "Umbreon needs nighttime.\p"
	.string "Sylveon needs to know a\n"
	.string "Fairy-type move.\p"
	.string "All three need a strong bond\n"
	.string "of friendship with you.$"

DewfordTown_PokemonCenter_1F_Text_StoneCavern:
	.string "There's a stone cavern at the edge\n"
	.string "of town.\p"
	.string "I've heard you can find rare stones\n"
	.string "there.$"

DewfordTown_PokemonCenter_1F_Text_FaintedMonCanUseHM:
	.string "Even if a POKéMON faints and can't\n"
	.string "battle, it can still use a move learned\l"
	.string "from a HIDDEN MACHINE (HM).$"

