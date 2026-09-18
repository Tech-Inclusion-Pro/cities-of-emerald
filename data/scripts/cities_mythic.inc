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

@ ===================================================================
@ Meltan + Melmetal — the Slateport hex-nut hunt (Task 13.1, mirrors
@ the H6 Zygarde-cell pattern). Six nuts scattered across Slateport
@ appear postgame once a dockworker starts the hunt; collecting all
@ six draws MELTAN out (L70), and catching it draws the MELMETAL its
@ swarm became (L70).
@ ===================================================================

@ on_transition (Slateport): postgame gating for the whole hunt.
Cities_EventScript_UpdateMeltanHunt::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_MeltanHideAll
	clearflag FLAG_CITIES_HIDE_MELTAN_DOCKWORKER
	goto_if_unset FLAG_CITIES_MYTHIC_MELTAN_STARTED, Cities_EventScript_MeltanHideNuts
	goto_if_set FLAG_CITIES_MYTHIC_MELTAN_NUT_1, Cities_EventScript_MeltanHideNut1
	clearflag FLAG_CITIES_HIDE_MELTAN_NUT_1
	goto Cities_EventScript_MeltanNut1Done
Cities_EventScript_MeltanHideNut1::
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_1
Cities_EventScript_MeltanNut1Done::
	goto_if_set FLAG_CITIES_MYTHIC_MELTAN_NUT_2, Cities_EventScript_MeltanHideNut2
	clearflag FLAG_CITIES_HIDE_MELTAN_NUT_2
	goto Cities_EventScript_MeltanNut2Done
Cities_EventScript_MeltanHideNut2::
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_2
Cities_EventScript_MeltanNut2Done::
	goto_if_set FLAG_CITIES_MYTHIC_MELTAN_NUT_3, Cities_EventScript_MeltanHideNut3
	clearflag FLAG_CITIES_HIDE_MELTAN_NUT_3
	goto Cities_EventScript_MeltanNut3Done
Cities_EventScript_MeltanHideNut3::
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_3
Cities_EventScript_MeltanNut3Done::
	goto_if_set FLAG_CITIES_MYTHIC_MELTAN_NUT_4, Cities_EventScript_MeltanHideNut4
	clearflag FLAG_CITIES_HIDE_MELTAN_NUT_4
	goto Cities_EventScript_MeltanNut4Done
Cities_EventScript_MeltanHideNut4::
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_4
Cities_EventScript_MeltanNut4Done::
	goto_if_set FLAG_CITIES_MYTHIC_MELTAN_NUT_5, Cities_EventScript_MeltanHideNut5
	clearflag FLAG_CITIES_HIDE_MELTAN_NUT_5
	goto Cities_EventScript_MeltanNut5Done
Cities_EventScript_MeltanHideNut5::
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_5
Cities_EventScript_MeltanNut5Done::
	goto_if_set FLAG_CITIES_MYTHIC_MELTAN_NUT_6, Cities_EventScript_MeltanHideNut6
	clearflag FLAG_CITIES_HIDE_MELTAN_NUT_6
	goto Cities_EventScript_MeltanNut6Done
Cities_EventScript_MeltanHideNut6::
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_6
Cities_EventScript_MeltanNut6Done::
	call Cities_EventScript_MeltanUpdateMons
	return

Cities_EventScript_MeltanUpdateMons::
	goto_if_unset FLAG_CITIES_MYTHIC_MELTAN_HUNT_DONE, Cities_EventScript_MeltanHideMeltan
	goto_if_set FLAG_CITIES_MYTHIC_MELTAN_CAUGHT, Cities_EventScript_MeltanHideMeltan
	clearflag FLAG_CITIES_HIDE_MYTHIC_MELTAN
	goto Cities_EventScript_MeltanUpdateMelmetal
Cities_EventScript_MeltanHideMeltan::
	setflag FLAG_CITIES_HIDE_MYTHIC_MELTAN
Cities_EventScript_MeltanUpdateMelmetal::
	goto_if_unset FLAG_CITIES_MYTHIC_MELTAN_CAUGHT, Cities_EventScript_MeltanHideMelmetal
	goto_if_set FLAG_CITIES_MYTHIC_MELMETAL_CAUGHT, Cities_EventScript_MeltanHideMelmetal
	clearflag FLAG_CITIES_HIDE_MYTHIC_MELMETAL
	return
Cities_EventScript_MeltanHideMelmetal::
	setflag FLAG_CITIES_HIDE_MYTHIC_MELMETAL
	return

Cities_EventScript_MeltanHideAll::
	setflag FLAG_CITIES_HIDE_MELTAN_DOCKWORKER
Cities_EventScript_MeltanHideNuts::
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_1
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_2
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_3
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_4
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_5
	setflag FLAG_CITIES_HIDE_MYTHIC_MELTAN
	setflag FLAG_CITIES_HIDE_MYTHIC_MELMETAL
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_6
	return

Cities_EventScript_MeltanTryFinish::
	goto_if_unset FLAG_CITIES_MYTHIC_MELTAN_NUT_1, Cities_EventScript_MeltanTryFinishEnd
	goto_if_unset FLAG_CITIES_MYTHIC_MELTAN_NUT_2, Cities_EventScript_MeltanTryFinishEnd
	goto_if_unset FLAG_CITIES_MYTHIC_MELTAN_NUT_3, Cities_EventScript_MeltanTryFinishEnd
	goto_if_unset FLAG_CITIES_MYTHIC_MELTAN_NUT_4, Cities_EventScript_MeltanTryFinishEnd
	goto_if_unset FLAG_CITIES_MYTHIC_MELTAN_NUT_5, Cities_EventScript_MeltanTryFinishEnd
	goto_if_unset FLAG_CITIES_MYTHIC_MELTAN_NUT_6, Cities_EventScript_MeltanTryFinishEnd
	setflag FLAG_CITIES_MYTHIC_MELTAN_HUNT_DONE
	clearflag FLAG_CITIES_HIDE_MYTHIC_MELTAN
Cities_EventScript_MeltanTryFinishEnd::
	return

@ The dockworker (Slateport, postgame): starts the hunt, then tracks it.
Cities_EventScript_MeltanDockworker::
	lock
	faceplayer
	goto_if_set FLAG_CITIES_MYTHIC_MELMETAL_CAUGHT, Cities_EventScript_MeltanDockAllDone
	goto_if_unset FLAG_CITIES_MYTHIC_MELTAN_STARTED, Cities_EventScript_MeltanDockStart
	msgbox Cities_Text_MeltanDockProgress, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_MeltanDockStart::
	msgbox Cities_Text_MeltanDockStart, MSGBOX_DEFAULT
	setflag FLAG_CITIES_MYTHIC_MELTAN_STARTED
	release
	end

Cities_EventScript_MeltanDockAllDone::
	msgbox Cities_Text_MeltanDockDone, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_MeltanNut1::
	lock
	playse SE_M_REFLECT
	msgbox Cities_Text_MeltanNut, MSGBOX_DEFAULT
	setflag FLAG_CITIES_MYTHIC_MELTAN_NUT_1
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_1
	call Cities_EventScript_MeltanTryFinish
	removeobject VAR_LAST_TALKED
	release
	end

Cities_EventScript_MeltanNut2::
	lock
	playse SE_M_REFLECT
	msgbox Cities_Text_MeltanNut, MSGBOX_DEFAULT
	setflag FLAG_CITIES_MYTHIC_MELTAN_NUT_2
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_2
	call Cities_EventScript_MeltanTryFinish
	removeobject VAR_LAST_TALKED
	release
	end

Cities_EventScript_MeltanNut3::
	lock
	playse SE_M_REFLECT
	msgbox Cities_Text_MeltanNut, MSGBOX_DEFAULT
	setflag FLAG_CITIES_MYTHIC_MELTAN_NUT_3
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_3
	call Cities_EventScript_MeltanTryFinish
	removeobject VAR_LAST_TALKED
	release
	end

Cities_EventScript_MeltanNut4::
	lock
	playse SE_M_REFLECT
	msgbox Cities_Text_MeltanNut, MSGBOX_DEFAULT
	setflag FLAG_CITIES_MYTHIC_MELTAN_NUT_4
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_4
	call Cities_EventScript_MeltanTryFinish
	removeobject VAR_LAST_TALKED
	release
	end

Cities_EventScript_MeltanNut5::
	lock
	playse SE_M_REFLECT
	msgbox Cities_Text_MeltanNut, MSGBOX_DEFAULT
	setflag FLAG_CITIES_MYTHIC_MELTAN_NUT_5
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_5
	call Cities_EventScript_MeltanTryFinish
	removeobject VAR_LAST_TALKED
	release
	end

Cities_EventScript_MeltanNut6::
	lock
	playse SE_M_REFLECT
	msgbox Cities_Text_MeltanNut, MSGBOX_DEFAULT
	setflag FLAG_CITIES_MYTHIC_MELTAN_NUT_6
	setflag FLAG_CITIES_HIDE_MELTAN_NUT_6
	call Cities_EventScript_MeltanTryFinish
	removeobject VAR_LAST_TALKED
	release
	end

Cities_EventScript_MythicMeltan::
	lock
	faceplayer
	msgbox Cities_Text_MythicMeltan, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_MELTAN, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MELTAN
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtMeltan
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtMeltan::
	setflag FLAG_CITIES_MYTHIC_MELTAN_CAUGHT
	clearflag FLAG_CITIES_HIDE_MYTHIC_MELMETAL
	release
	end

Cities_EventScript_MythicMelmetal::
	lock
	faceplayer
	msgbox Cities_Text_MythicMelmetal, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_MELMETAL, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MELMETAL
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtMelmetal
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtMelmetal::
	setflag FLAG_CITIES_MYTHIC_MELMETAL_CAUGHT
	release
	end

Cities_Text_MeltanNut:
	.string "A heavy hex nut, humming faintly.\p"
	.string "It's warm, like something living\n"
	.string "used it for a shell.$"

Cities_Text_MeltanDockStart:
	.string "CHAMPION! You're just the sort of\n"
	.string "trouble I need.\p"
	.string "Hex nuts keep vanishing from the\n"
	.string "shipyard. Bolts, washers, whole\l"
	.string "toolboxes - gone overnight.\p"
	.string "I counted six missing, scattered\n"
	.string "clean across SLATEPORT.\p"
	.string "Find them for me? Something about\n"
	.string "this smells less like a thief and\l"
	.string "more like an APPETITE.$"

Cities_Text_MeltanDockProgress:
	.string "Still nuts out there. Whatever's\n"
	.string "taking them has good taste in\l"
	.string "hardware.$"

Cities_Text_MeltanDockDone:
	.string "So the thief was a whole SWARM of\n"
	.string "little eaters, and you've got the\l"
	.string "big one now.\p"
	.string "The shipyard's tools are safe.\n"
	.string "Mostly.$"

Cities_Text_MythicMeltan:
	.string "The gathered nuts tremble, roll\n"
	.string "together, and click into a small\l"
	.string "body with one bright eye.\p"
	.string "It eyes your team's metal parts\n"
	.string "with frank interest.$"

Cities_Text_MythicMelmetal:
	.string "Every nut and bolt MELTAN ever ate\n"
	.string "answers at once.\p"
	.string "They pour together into something\n"
	.string "huge and ancient, fists like\l"
	.string "wrecking balls.$"

@ ===================================================================
@ Hoopa — the Ring Chamber (Task 13.1). Reached through a ring that
@ appears in the Trick House entrance postgame. The plaque names the
@ order; the coord events enforce it (SUN->SEA->SKY).
@ ===================================================================

@ Trick House entrance: the ring appears postgame.
Cities_EventScript_UpdateHoopaRingEntrance::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideHoopaRingEntrance
	clearflag FLAG_CITIES_MYTHIC_HOOPA_RING_NPC
	return

Cities_EventScript_HideHoopaRingEntrance::
	setflag FLAG_CITIES_MYTHIC_HOOPA_RING_NPC
	return

Cities_EventScript_HoopaRingEntrance::
	lock
	faceplayer
	msgbox Cities_Text_HoopaRingEntrance, MSGBOX_DEFAULT
	closemessage
	delay 20
	warp MAP_RING_CHAMBER, 6, 8
	waitstate
	release
	end

@ Ring Chamber: visibility + the exit + the puzzle.
Cities_EventScript_UpdateRingChamber::
	goto_if_unset FLAG_CITIES_MYTHIC_HOOPA_RING, Cities_EventScript_RingChamberUnsolved
	goto_if_set FLAG_CITIES_MYTHIC_HOOPA_CAUGHT, Cities_EventScript_RingChamberHideHoopa
	clearflag FLAG_CITIES_HIDE_MYTHIC_HOOPA
	goto Cities_EventScript_RingChamberPrize
Cities_EventScript_RingChamberHideHoopa::
	setflag FLAG_CITIES_HIDE_MYTHIC_HOOPA
Cities_EventScript_RingChamberPrize::
	goto_if_set FLAG_CITIES_MYTHIC_HOOPA_PRIZE_TAKEN, Cities_EventScript_RingChamberHidePrize
	clearflag FLAG_CITIES_HIDE_MYTHIC_HOOPA_PRIZE
	return
Cities_EventScript_RingChamberHidePrize::
	setflag FLAG_CITIES_HIDE_MYTHIC_HOOPA_PRIZE
	return
Cities_EventScript_RingChamberUnsolved::
	setflag FLAG_CITIES_HIDE_MYTHIC_HOOPA
	setflag FLAG_CITIES_HIDE_MYTHIC_HOOPA_PRIZE
	return

Cities_EventScript_RingChamberExit::
	lockall
	warp MAP_ROUTE110_TRICK_HOUSE_ENTRANCE, 10, 6
	waitstate
	releaseall
	end

Cities_EventScript_HoopaPlaque::
	msgbox Cities_Text_HoopaPlaque, MSGBOX_SIGN
	end

Cities_EventScript_HoopaRingSun::
	lockall
	goto_if_set FLAG_CITIES_MYTHIC_HOOPA_RING, Cities_EventScript_HoopaRingLit
	playse SE_M_REFLECT
	msgbox Cities_Text_HoopaRingGlow, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 1
	releaseall
	end

Cities_EventScript_HoopaRingSea::
	lockall
	goto_if_set FLAG_CITIES_MYTHIC_HOOPA_RING, Cities_EventScript_HoopaRingLit
	playse SE_M_REFLECT
	msgbox Cities_Text_HoopaRingGlow, MSGBOX_DEFAULT
	setvar VAR_TEMP_1, 2
	releaseall
	end

Cities_EventScript_HoopaRingSky::
	lockall
	goto_if_set FLAG_CITIES_MYTHIC_HOOPA_RING, Cities_EventScript_HoopaRingLit
	playse SE_M_REFLECT
	msgbox Cities_Text_HoopaRingOpen, MSGBOX_DEFAULT
	setflag FLAG_CITIES_MYTHIC_HOOPA_RING
	clearflag FLAG_CITIES_HIDE_MYTHIC_HOOPA
	clearflag FLAG_CITIES_HIDE_MYTHIC_HOOPA_PRIZE
	addobject LOCALID_RING_CHAMBER_HOOPA
	addobject LOCALID_RING_CHAMBER_PRIZE
	playse SE_M_HEAL_BELL
	releaseall
	end

Cities_EventScript_HoopaRingLit::
	releaseall
	end

Cities_EventScript_MythicHoopa::
	lock
	faceplayer
	msgbox Cities_Text_MythicHoopa, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_HOOPA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_HOOPA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtHoopa
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtHoopa::
	setflag FLAG_CITIES_MYTHIC_HOOPA_CAUGHT
	release
	end

Cities_EventScript_HoopaPrize::
	lockall
	goto_if_set FLAG_CITIES_MYTHIC_HOOPA_PRIZE_TAKEN, Cities_EventScript_HoopaPrizeGone
	checkitemspace ITEM_PRISON_BOTTLE
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_HoopaPrizeFull
	giveitem ITEM_PRISON_BOTTLE
	setflag FLAG_CITIES_MYTHIC_HOOPA_PRIZE_TAKEN
	setflag FLAG_CITIES_HIDE_MYTHIC_HOOPA_PRIZE
	removeobject LOCALID_RING_CHAMBER_PRIZE
	releaseall
	end

Cities_EventScript_HoopaPrizeFull::
	msgbox Cities_Text_HoopaPrizeFull, MSGBOX_DEFAULT
	releaseall
	end

Cities_EventScript_HoopaPrizeGone::
	releaseall
	end

Cities_Text_HoopaRingEntrance:
	.string "A golden ring hangs in the air\n"
	.string "where no ring should be.\p"
	.string "Reaching toward it, your hand\n"
	.string "passes through - and pulls the\l"
	.string "rest of you after.$"

Cities_Text_HoopaPlaque:
	.string "Carved around a stone hoop:\p"
	.string "“The rings answer in turn.\n"
	.string "SUN, then SEA, then SKY.”$"

Cities_Text_HoopaRingGlow:
	.string "The ring lights, and holds.$"

Cities_Text_HoopaRingOpen:
	.string "The last ring blazes. All three\n"
	.string "hoops line up - and something\l"
	.string "reaches through from the other\l"
	.string "side, laughing.$"

Cities_Text_MythicHoopa:
	.string "It spins a ring on one finger,\n"
	.string "grinning at you through it.\p"
	.string "Six rings, six mischiefs. It has\n"
	.string "been waiting for someone worth\l"
	.string "the trouble.$"

Cities_Text_HoopaPrizeFull:
	.string "A bottle rests in the last ring.\n"
	.string "Your BAG is too full to take it.$"

@ ===================================================================
@ Pecharunt — Mt. Pyre Summit (Task 13.1). NOT in the GDD 6.6 table
@ (a newer mythical); added so the 13.2 completeness test passes and
@ no story-only species is unobtainable. Ghost/Poison — the grudge
@ mochi rests among the mountain's graves. L70 like the rest.
@ ===================================================================

Cities_EventScript_MythicShowPecharunt::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_MythicHidePecharunt
	goto_if_set FLAG_CITIES_MYTHIC_PECHARUNT_CAUGHT, Cities_EventScript_MythicHidePecharunt
	clearflag FLAG_CITIES_HIDE_MYTHIC_PECHARUNT
	return

Cities_EventScript_MythicHidePecharunt::
	setflag FLAG_CITIES_HIDE_MYTHIC_PECHARUNT
	return

Cities_EventScript_MythicPecharunt::
	lock
	faceplayer
	msgbox Cities_Text_MythicPecharunt, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_PECHARUNT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_PECHARUNT
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_MythicCaughtPecharunt
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_MythicCaughtPecharunt::
	setflag FLAG_CITIES_MYTHIC_PECHARUNT_CAUGHT
	release
	end

Cities_Text_MythicPecharunt:
	.string "Among the graves, a chained pot\n"
	.string "sits where no one left it.\p"
	.string "A small ghost peers over its rim,\n"
	.string "offering you a mochi with a smile\l"
	.string "that has plans.$"
