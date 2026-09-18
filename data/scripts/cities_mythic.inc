@ Cities of Emerald — Task 13.1: mythical events, simple statics
@ (GDD 6.6, all [DECIDED]; roster approved 2026-09-18). Every mythical
@ is a lone L70 M1-pattern static that appears postgame at its GDD
@ location and returns if it flees. Deoxys, Shaymin, Hoopa and Meltan
@ have their own files (islands / rooms / hunts).
@
@ NOTE: Emerald has no Fallarbor Contest Hall (contests moved to
@ Lilycove), so MELOETTA is placed in FALLARBOR TOWN proper.


Cities_EventScript_MythicJirachi::
	lock
	faceplayer
	msgbox Cities_Text_MythicJirachi, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_JIRACHI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_JIRACHI
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtJirachi
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtJirachi::
	setflag FLAG_CITIES_MYTHIC_JIRACHI_CAUGHT
	release
	end

Cities_EventScript_MythicDiancie::
	lock
	faceplayer
	msgbox Cities_Text_MythicDiancie, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_DIANCIE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_DIANCIE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtDiancie
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtDiancie::
	setflag FLAG_CITIES_MYTHIC_DIANCIE_CAUGHT
	release
	end

Cities_EventScript_MythicManaphy::
	lock
	faceplayer
	msgbox Cities_Text_MythicManaphy, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_MANAPHY, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MANAPHY
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtManaphy
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtManaphy::
	setflag FLAG_CITIES_MYTHIC_MANAPHY_CAUGHT
	release
	end

Cities_EventScript_MythicPhione::
	lock
	faceplayer
	msgbox Cities_Text_MythicPhione, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_PHIONE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_PHIONE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtPhione
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtPhione::
	setflag FLAG_CITIES_MYTHIC_PHIONE_CAUGHT
	release
	end

Cities_EventScript_MythicVictini::
	lock
	faceplayer
	msgbox Cities_Text_MythicVictini, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_VICTINI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_VICTINI
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtVictini
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtVictini::
	setflag FLAG_CITIES_MYTHIC_VICTINI_CAUGHT
	release
	end

Cities_EventScript_MythicMeloetta::
	lock
	faceplayer
	msgbox Cities_Text_MythicMeloetta, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_MELOETTA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MELOETTA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtMeloetta
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtMeloetta::
	setflag FLAG_CITIES_MYTHIC_MELOETTA_CAUGHT
	release
	end

Cities_EventScript_MythicVolcanion::
	lock
	faceplayer
	msgbox Cities_Text_MythicVolcanion, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_VOLCANION, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_VOLCANION
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtVolcanion
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtVolcanion::
	setflag FLAG_CITIES_MYTHIC_VOLCANION_CAUGHT
	release
	end

Cities_EventScript_MythicMarshadow::
	lock
	faceplayer
	msgbox Cities_Text_MythicMarshadow, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_MARSHADOW, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MARSHADOW
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtMarshadow
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtMarshadow::
	setflag FLAG_CITIES_MYTHIC_MARSHADOW_CAUGHT
	release
	end

Cities_EventScript_MythicZeraora::
	lock
	faceplayer
	msgbox Cities_Text_MythicZeraora, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_ZERAORA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ZERAORA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtZeraora
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtZeraora::
	setflag FLAG_CITIES_MYTHIC_ZERAORA_CAUGHT
	release
	end

Cities_EventScript_MythicZarude::
	lock
	faceplayer
	msgbox Cities_Text_MythicZarude, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_ZARUDE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ZARUDE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtZarude
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtZarude::
	setflag FLAG_CITIES_MYTHIC_ZARUDE_CAUGHT
	release
	end

Cities_EventScript_MythicShowJirachi::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_MythicHideJirachi
	goto_if_set FLAG_CITIES_MYTHIC_JIRACHI_CAUGHT, Cities_EventScript_MythicHideJirachi
	clearflag FLAG_CITIES_HIDE_MYTHIC_JIRACHI
	return

Cities_EventScript_MythicHideJirachi::
	setflag FLAG_CITIES_HIDE_MYTHIC_JIRACHI
	return

Cities_EventScript_MythicShowDiancie::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_MythicHideDiancie
	goto_if_set FLAG_CITIES_MYTHIC_DIANCIE_CAUGHT, Cities_EventScript_MythicHideDiancie
	clearflag FLAG_CITIES_HIDE_MYTHIC_DIANCIE
	return

Cities_EventScript_MythicHideDiancie::
	setflag FLAG_CITIES_HIDE_MYTHIC_DIANCIE
	return

Cities_EventScript_MythicShowManaphy::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_MythicHideManaphy
	goto_if_set FLAG_CITIES_MYTHIC_MANAPHY_CAUGHT, Cities_EventScript_MythicHideManaphy
	clearflag FLAG_CITIES_HIDE_MYTHIC_MANAPHY
	return

Cities_EventScript_MythicHideManaphy::
	setflag FLAG_CITIES_HIDE_MYTHIC_MANAPHY
	return

Cities_EventScript_MythicShowPhione::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_MythicHidePhione
	goto_if_set FLAG_CITIES_MYTHIC_PHIONE_CAUGHT, Cities_EventScript_MythicHidePhione
	goto_if_unset FLAG_CITIES_MYTHIC_MANAPHY_CAUGHT, Cities_EventScript_MythicHidePhione
	clearflag FLAG_CITIES_HIDE_MYTHIC_PHIONE
	return

Cities_EventScript_MythicHidePhione::
	setflag FLAG_CITIES_HIDE_MYTHIC_PHIONE
	return

Cities_EventScript_MythicShowVictini::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_MythicHideVictini
	goto_if_set FLAG_CITIES_MYTHIC_VICTINI_CAUGHT, Cities_EventScript_MythicHideVictini
	clearflag FLAG_CITIES_HIDE_MYTHIC_VICTINI
	return

Cities_EventScript_MythicHideVictini::
	setflag FLAG_CITIES_HIDE_MYTHIC_VICTINI
	return

Cities_EventScript_MythicShowMeloetta::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_MythicHideMeloetta
	goto_if_set FLAG_CITIES_MYTHIC_MELOETTA_CAUGHT, Cities_EventScript_MythicHideMeloetta
	clearflag FLAG_CITIES_HIDE_MYTHIC_MELOETTA
	return

Cities_EventScript_MythicHideMeloetta::
	setflag FLAG_CITIES_HIDE_MYTHIC_MELOETTA
	return

Cities_EventScript_MythicShowVolcanion::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_MythicHideVolcanion
	goto_if_set FLAG_CITIES_MYTHIC_VOLCANION_CAUGHT, Cities_EventScript_MythicHideVolcanion
	clearflag FLAG_CITIES_HIDE_MYTHIC_VOLCANION
	return

Cities_EventScript_MythicHideVolcanion::
	setflag FLAG_CITIES_HIDE_MYTHIC_VOLCANION
	return

Cities_EventScript_MythicShowMarshadow::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_MythicHideMarshadow
	goto_if_set FLAG_CITIES_MYTHIC_MARSHADOW_CAUGHT, Cities_EventScript_MythicHideMarshadow
	clearflag FLAG_CITIES_HIDE_MYTHIC_MARSHADOW
	return

Cities_EventScript_MythicHideMarshadow::
	setflag FLAG_CITIES_HIDE_MYTHIC_MARSHADOW
	return

Cities_EventScript_MythicShowZeraora::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_MythicHideZeraora
	goto_if_set FLAG_CITIES_MYTHIC_ZERAORA_CAUGHT, Cities_EventScript_MythicHideZeraora
	clearflag FLAG_CITIES_HIDE_MYTHIC_ZERAORA
	return

Cities_EventScript_MythicHideZeraora::
	setflag FLAG_CITIES_HIDE_MYTHIC_ZERAORA
	return

Cities_EventScript_MythicShowZarude::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_MythicHideZarude
	goto_if_set FLAG_CITIES_MYTHIC_ZARUDE_CAUGHT, Cities_EventScript_MythicHideZarude
	clearflag FLAG_CITIES_HIDE_MYTHIC_ZARUDE
	return

Cities_EventScript_MythicHideZarude::
	setflag FLAG_CITIES_HIDE_MYTHIC_ZARUDE
	return

@ -- Text --

Cities_Text_MythicJirachi:
	.string "A tag dangles from a stasis pod\n"
	.string "on COZMO's desk.\p"
	.string "Inside, curled around a star-shaped\n"
	.string "core, something is dreaming.\p"
	.string "It is said to grant a wish when it\n"
	.string "wakes. It is waking.$"

Cities_Text_MythicDiancie:
	.string "Deep in the cave, the walls glitter\n"
	.string "with raw carbon.\p"
	.string "At the center, a small figure of pink\n"
	.string "diamond turns its head toward you.\p"
	.string "It makes the stones. It IS one.$"

Cities_Text_MythicManaphy:
	.string "A blue speck drifts in the current,\n"
	.string "trailing a heart of light.\p"
	.string "It looks at you the way the sea\n"
	.string "looks at the shore - like it will\l"
	.string "always come back.$"

Cities_Text_MythicPhione:
	.string "Where MANAPHY drifted, a smaller\n"
	.string "cousin now bobs in the current,\l"
	.string "curious and unafraid.$"

Cities_Text_MythicVictini:
	.string "On a sunlit ledge, a small creature\n"
	.string "with V-shaped ears watches the city.\p"
	.string "Warmth pours off it. They say it\n"
	.string "never loses. It looks ready to prove\l"
	.string "it.$"

Cities_Text_MythicMeloetta:
	.string "Someone has been humming here - no,\n"
	.string "SOMETHING has.\p"
	.string "A melody made visible steps out of\n"
	.string "the air, green ribbons trailing,\l"
	.string "and finishes its song for you.$"

Cities_Text_MythicVolcanion:
	.string "Steam roars from the hot springs,\n"
	.string "thicker than it should be.\p"
	.string "At its heart stands a great beast of\n"
	.string "fire and water, wreathed in the\l"
	.string "cloud it makes.$"

Cities_Text_MythicMarshadow:
	.string "Your own shadow on the pillar wall\n"
	.string "is a beat too slow.\p"
	.string "It peels away, stands up, and bows -\n"
	.string "a fighter of pure shade, testing\l"
	.string "whether you noticed.$"

Cities_Text_MythicZeraora:
	.string "The dead generator hall crackles\n"
	.string "back to life around one shape.\p"
	.string "Static lifts your hair. It drops to\n"
	.string "all fours, paws sparking, and grins.$"

Cities_Text_MythicZarude:
	.string "The vines here are woven, not grown -\n"
	.string "a wall someone made.\p"
	.string "A dark simian shape drops from the\n"
	.string "canopy, bark-clad and wary, guarding\l"
	.string "its green.$"


@ ===================================================================
@ Deoxys — Birth Island (Task 13.1). The vanilla triangle puzzle is
@ reused as-is (Deoxys level raised to 70 in BirthIsland_Exterior).
@ A postgame sailor at Lilycove Harbor gives passage, Briney-style.
@ ===================================================================

Cities_EventScript_UpdateDeoxysSailor::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideDeoxysSailor
	clearflag FLAG_CITIES_MYTHIC_DEOXYS_SAILOR
	return

Cities_EventScript_HideDeoxysSailor::
	setflag FLAG_CITIES_MYTHIC_DEOXYS_SAILOR
	return

Cities_EventScript_DeoxysSailor::
	lock
	faceplayer
	msgbox Cities_Text_DeoxysSailor, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Cities_EventScript_DeoxysSailorStay
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	msgbox Cities_Text_DeoxysSailorCastOff, MSGBOX_DEFAULT
	closemessage
	delay 30
	warp MAP_BIRTH_ISLAND_HARBOR, 8, 4
	waitstate
	release
	end

Cities_EventScript_DeoxysSailorStay::
	msgbox Cities_Text_DeoxysSailorStay, MSGBOX_DEFAULT
	release
	end

Cities_Text_DeoxysSailor:
	.string "There's a speck of land out east\n"
	.string "the charts barely admit exists.\p"
	.string "Ships' compasses spin near it.\n"
	.string "Sailors call it BIRTH ISLAND.\p"
	.string "You look like trouble enough to\n"
	.string "enjoy that. Shall I take you?$"

Cities_Text_DeoxysSailorCastOff:
	.string "Hold onto something. The last\n"
	.string "stretch gets strange.$"

Cities_Text_DeoxysSailorStay:
	.string "The island's not going anywhere.\n"
	.string "Probably.$"

@ ===================================================================
@ Shaymin — the Route 119 meadow (Task 13.1). Halley's pre-League
@ hook ("the meadow bloomed like a thank-you") pays off: postgame,
@ after her history, she points the player south of the Institute.
@ ===================================================================

Cities_EventScript_UpdateShaymin::
	goto_if_unset FLAG_CITIES_MYTHIC_SHAYMIN_MEADOW, Cities_EventScript_MythicHideShaymin
	goto_if_set FLAG_CITIES_MYTHIC_SHAYMIN_CAUGHT, Cities_EventScript_MythicHideShaymin
	clearflag FLAG_CITIES_HIDE_MYTHIC_SHAYMIN
	return

Cities_EventScript_MythicHideShaymin::
	setflag FLAG_CITIES_HIDE_MYTHIC_SHAYMIN
	return

Cities_EventScript_MythicShaymin::
	lock
	faceplayer
	msgbox Cities_Text_MythicShaymin, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SHAYMIN, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_SHAYMIN
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtShaymin
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtShaymin::
	setflag FLAG_CITIES_MYTHIC_SHAYMIN_CAUGHT
	goto_if_set FLAG_CITIES_MYTHIC_SHAYMIN_GRACIDEA_GIVEN, Cities_EventScript_MythicShayminDone
	setflag FLAG_CITIES_MYTHIC_SHAYMIN_GRACIDEA_GIVEN
	giveitem ITEM_GRACIDEA
Cities_EventScript_MythicShayminDone::
	release
	end

Cities_Text_MythicShaymin:
	.string "The meadow south of the INSTITUTE\n"
	.string "is thick with gracidea flowers.\p"
	.string "One of them lifts its head, looks\n"
	.string "around, and turns out to be a\l"
	.string "small green hedgehog.\p"
	.string "The thank-you HALLEY spoke of,\n"
	.string "grown legs.$"
