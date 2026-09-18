@ Cities of Emerald — V3 "The Wrong Doors" (GDD 7.2 / 6.6, Task 12.5,
@ outline approved 2026-09-18). The rift attempts fail sideways: Ultra
@ Wormholes over six sites. Epoch triages its own disaster next to the
@ player — no Epoch battles in this arc, by design. The Archivist
@ appears in person at Mt. Pyre, closes a hole by hand, apologizes,
@ and does not stop.
@
@ VAR_CITIES_V3_STATE: 0 locked, 1 wormholes open, 2 Archivist seen,
@ 3 complete (all sixteen obtained; reward given).
@ Sites: R124 Nihilego (+Necrozma later) / R119 Buzzwole+Pheromosa /
@ New Mauville Xurkitree / R120 Celesteela+Kartana+Solgaleo /
@ Jagged Pass Guzzlord (+Poipole gift, +Naganadel) / Mt. Pyre ext.
@ Stakataka+Blacephalon+Lunala + the Archivist.

@ -- Per-map visibility (called from each site's ON_TRANSITION) --

Cities_EventScript_V3SitesClosed::
	setflag FLAG_CITIES_HIDE_V3_NIHILEGO
	setflag FLAG_CITIES_HIDE_V3_BUZZWOLE
	setflag FLAG_CITIES_HIDE_V3_PHEROMOSA
	setflag FLAG_CITIES_HIDE_V3_XURKITREE
	setflag FLAG_CITIES_HIDE_V3_CELESTEELA
	setflag FLAG_CITIES_HIDE_V3_KARTANA
	setflag FLAG_CITIES_HIDE_V3_GUZZLORD
	setflag FLAG_CITIES_HIDE_V3_STAKATAKA
	setflag FLAG_CITIES_HIDE_V3_BLACEPHALON
	setflag FLAG_CITIES_HIDE_V3_SOLGALEO
	setflag FLAG_CITIES_HIDE_V3_LUNALA
	setflag FLAG_CITIES_HIDE_V3_NECROZMA
	setflag FLAG_CITIES_HIDE_V3_NAGANADEL
	setflag FLAG_CITIES_HIDE_V3_HELPERS
	setflag FLAG_CITIES_HIDE_V3_ARCHIVIST
	return

Cities_EventScript_V3UpdateHelpers::
	goto_if_eq VAR_CITIES_V3_STATE, 0, Cities_EventScript_V3HideHelpers
	goto_if_eq VAR_CITIES_V3_STATE, 3, Cities_EventScript_V3HideHelpers
	clearflag FLAG_CITIES_HIDE_V3_HELPERS
	return

Cities_EventScript_V3HideHelpers::
	setflag FLAG_CITIES_HIDE_V3_HELPERS
	return

Cities_EventScript_UpdateV3Route124::
	goto_if_eq VAR_CITIES_V3_STATE, 0, Cities_EventScript_V3SitesClosed
	call Cities_EventScript_V3UpdateHelpers
	call Cities_EventScript_V3ShowNihilego
	goto_if_unset FLAG_CITIES_V3_SOLGALEO_CAUGHT, Cities_EventScript_V3HideNecrozmaEarly
	goto_if_unset FLAG_CITIES_V3_LUNALA_CAUGHT, Cities_EventScript_V3HideNecrozmaEarly
	goto_if_set FLAG_CITIES_V3_NECROZMA_CAUGHT, Cities_EventScript_V3HideNecrozmaEarly
	clearflag FLAG_CITIES_HIDE_V3_NECROZMA
	return

Cities_EventScript_V3HideNecrozmaEarly::
	setflag FLAG_CITIES_HIDE_V3_NECROZMA
	return

Cities_EventScript_UpdateV3Route119::
	goto_if_eq VAR_CITIES_V3_STATE, 0, Cities_EventScript_V3SitesClosed
	call Cities_EventScript_V3UpdateHelpers
	call Cities_EventScript_V3ShowBuzzwole
	call Cities_EventScript_V3ShowPheromosa
	return

Cities_EventScript_UpdateV3NewMauville::
	goto_if_eq VAR_CITIES_V3_STATE, 0, Cities_EventScript_V3SitesClosed
	call Cities_EventScript_V3ShowXurkitree
	return

Cities_EventScript_UpdateV3Route120::
	goto_if_eq VAR_CITIES_V3_STATE, 0, Cities_EventScript_V3SitesClosed
	call Cities_EventScript_V3ShowCelesteela
	call Cities_EventScript_V3ShowKartana
	call Cities_EventScript_V3ShowSolgaleo
	return

Cities_EventScript_UpdateV3JaggedPass::
	goto_if_eq VAR_CITIES_V3_STATE, 0, Cities_EventScript_V3SitesClosed
	call Cities_EventScript_V3UpdateHelpers
	call Cities_EventScript_V3ShowGuzzlord
	goto_if_unset FLAG_CITIES_V3_POIPOLE_GIVEN, Cities_EventScript_V3HideNaganadelEarly
	goto_if_set FLAG_CITIES_V3_NAGANADEL_CAUGHT, Cities_EventScript_V3HideNaganadelEarly
	clearflag FLAG_CITIES_HIDE_V3_NAGANADEL
	return

Cities_EventScript_V3HideNaganadelEarly::
	setflag FLAG_CITIES_HIDE_V3_NAGANADEL
	return

Cities_EventScript_UpdateV3MtPyre::
	goto_if_eq VAR_CITIES_V3_STATE, 0, Cities_EventScript_V3SitesClosed
	call Cities_EventScript_V3UpdateHelpers
	call Cities_EventScript_V3ShowStakataka
	call Cities_EventScript_V3ShowBlacephalon
	call Cities_EventScript_V3ShowLunala
	goto_if_ge VAR_CITIES_V3_STATE, 2, Cities_EventScript_V3HideArchivist
	clearflag FLAG_CITIES_HIDE_V3_ARCHIVIST
	return

Cities_EventScript_V3HideArchivist::
	setflag FLAG_CITIES_HIDE_V3_ARCHIVIST
	return

@ -- Helper grunts (dialogue only; Epoch fights nobody this arc) --

Cities_EventScript_V3HelperR119::
	msgbox Cities_Text_V3HelperR119, MSGBOX_NPC
	end

Cities_EventScript_V3HelperMtPyre::
	msgbox Cities_Text_V3HelperMtPyre, MSGBOX_NPC
	end

Cities_EventScript_V3HelperJagged::
	lock
	faceplayer
	goto_if_set FLAG_CITIES_V3_POIPOLE_GIVEN, Cities_EventScript_V3HelperJaggedAfter
	goto_if_unset FLAG_CITIES_V3_GUZZLORD_CAUGHT, Cities_EventScript_V3HelperJaggedScared
	msgbox Cities_Text_V3PoipoleThanks, MSGBOX_DEFAULT
	givemon SPECIES_POIPOLE, 70
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, Cities_EventScript_V3PoipoleGiven
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, Cities_EventScript_V3PoipoleGiven
	msgbox Cities_Text_V3PoipoleNoRoom, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_V3PoipoleGiven::
	setflag FLAG_CITIES_V3_POIPOLE_GIVEN
	msgbox Cities_Text_V3PoipoleGiven, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_V3HelperJaggedScared::
	msgbox Cities_Text_V3HelperJaggedScared, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_V3HelperJaggedAfter::
	msgbox Cities_Text_V3HelperJaggedAfter, MSGBOX_DEFAULT
	release
	end

@ -- The Archivist, in person (Mt. Pyre exterior) --

Cities_EventScript_V3Archivist::
	lock
	faceplayer
	msgbox Cities_Text_V3Archivist, MSGBOX_DEFAULT
	closemessage
	delay 30
	setvar VAR_CITIES_V3_STATE, 2
	setflag FLAG_CITIES_HIDE_V3_ARCHIVIST
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MT_PYRE_CITIES_ARCHIVIST
	fadescreen FADE_FROM_BLACK
	release
	end

@ -- Gnomon, cleanup coordinator (Space Center lobby): the reward --

Cities_EventScript_V3GnomonReward::
	lock
	faceplayer
	goto_if_set FLAG_CITIES_V3_REWARD_GIVEN, Cities_EventScript_V3GnomonAfter
	setvar VAR_0x8004, 22 @ CITIES_ARC_V3
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_V3GnomonGive
	msgbox Cities_Text_V3GnomonProgress, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_V3GnomonGive::
	msgbox Cities_Text_V3GnomonReward, MSGBOX_DEFAULT
	checkitemspace ITEM_N_SOLARIZER
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_V3GnomonBagFull
	checkitemspace ITEM_N_LUNARIZER
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_V3GnomonBagFull
	giveitem ITEM_N_SOLARIZER
	giveitem ITEM_N_LUNARIZER
	setflag FLAG_CITIES_V3_REWARD_GIVEN
	setvar VAR_CITIES_V3_STATE, 3
	msgbox Cities_Text_V3GnomonRewardDone, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_V3GnomonBagFull::
	msgbox Cities_Text_V3GnomonBagFull, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_V3GnomonAfter::
	goto_if_eq VAR_CITIES_V4_STATE, 0, Cities_EventScript_V4GnomonOpens
	msgbox Cities_Text_V3GnomonAfter, MSGBOX_DEFAULT
	release
	end

@ -- Encounters (M1 pattern) --

Cities_EventScript_V3Nihilego::
	lock
	faceplayer
	msgbox Cities_Text_V3Nihilego, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_NIHILEGO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_NIHILEGO
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtNihilego
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtNihilego::
	setflag FLAG_CITIES_V3_NIHILEGO_CAUGHT
	release
	end

Cities_EventScript_V3Buzzwole::
	lock
	faceplayer
	msgbox Cities_Text_V3Buzzwole, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_BUZZWOLE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_BUZZWOLE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtBuzzwole
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtBuzzwole::
	setflag FLAG_CITIES_V3_BUZZWOLE_CAUGHT
	release
	end

Cities_EventScript_V3Pheromosa::
	lock
	faceplayer
	msgbox Cities_Text_V3Pheromosa, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_PHEROMOSA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_PHEROMOSA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtPheromosa
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtPheromosa::
	setflag FLAG_CITIES_V3_PHEROMOSA_CAUGHT
	release
	end

Cities_EventScript_V3Xurkitree::
	lock
	faceplayer
	msgbox Cities_Text_V3Xurkitree, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_XURKITREE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_XURKITREE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtXurkitree
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtXurkitree::
	setflag FLAG_CITIES_V3_XURKITREE_CAUGHT
	release
	end

Cities_EventScript_V3Celesteela::
	lock
	faceplayer
	msgbox Cities_Text_V3Celesteela, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_CELESTEELA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_CELESTEELA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtCelesteela
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtCelesteela::
	setflag FLAG_CITIES_V3_CELESTEELA_CAUGHT
	release
	end

Cities_EventScript_V3Kartana::
	lock
	faceplayer
	msgbox Cities_Text_V3Kartana, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_KARTANA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_KARTANA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtKartana
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtKartana::
	setflag FLAG_CITIES_V3_KARTANA_CAUGHT
	release
	end

Cities_EventScript_V3Guzzlord::
	lock
	faceplayer
	msgbox Cities_Text_V3Guzzlord, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_GUZZLORD, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_GUZZLORD
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtGuzzlord
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtGuzzlord::
	setflag FLAG_CITIES_V3_GUZZLORD_CAUGHT
	release
	end

Cities_EventScript_V3Stakataka::
	lock
	faceplayer
	msgbox Cities_Text_V3Stakataka, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_STAKATAKA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_STAKATAKA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtStakataka
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtStakataka::
	setflag FLAG_CITIES_V3_STAKATAKA_CAUGHT
	release
	end

Cities_EventScript_V3Blacephalon::
	lock
	faceplayer
	msgbox Cities_Text_V3Blacephalon, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_BLACEPHALON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_BLACEPHALON
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtBlacephalon
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtBlacephalon::
	setflag FLAG_CITIES_V3_BLACEPHALON_CAUGHT
	release
	end

Cities_EventScript_V3Solgaleo::
	lock
	faceplayer
	msgbox Cities_Text_V3Solgaleo, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SOLGALEO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_SOLGALEO
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtSolgaleo
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtSolgaleo::
	setflag FLAG_CITIES_V3_SOLGALEO_CAUGHT
	release
	end

Cities_EventScript_V3Lunala::
	lock
	faceplayer
	msgbox Cities_Text_V3Lunala, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_LUNALA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_LUNALA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtLunala
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtLunala::
	setflag FLAG_CITIES_V3_LUNALA_CAUGHT
	release
	end

Cities_EventScript_V3Necrozma::
	lock
	faceplayer
	msgbox Cities_Text_V3Necrozma, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_NECROZMA, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_NECROZMA
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtNecrozma
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtNecrozma::
	setflag FLAG_CITIES_V3_NECROZMA_CAUGHT
	release
	end

Cities_EventScript_V3Naganadel::
	lock
	faceplayer
	msgbox Cities_Text_V3Naganadel, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_NAGANADEL, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_NAGANADEL
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V3CaughtNaganadel
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V3CaughtNaganadel::
	setflag FLAG_CITIES_V3_NAGANADEL_CAUGHT
	release
	end

Cities_EventScript_V3ShowNihilego::
	goto_if_set FLAG_CITIES_V3_NIHILEGO_CAUGHT, Cities_EventScript_V3HideNihilego
	clearflag FLAG_CITIES_HIDE_V3_NIHILEGO
	return

Cities_EventScript_V3HideNihilego::
	setflag FLAG_CITIES_HIDE_V3_NIHILEGO
	return

Cities_EventScript_V3ShowBuzzwole::
	goto_if_set FLAG_CITIES_V3_BUZZWOLE_CAUGHT, Cities_EventScript_V3HideBuzzwole
	clearflag FLAG_CITIES_HIDE_V3_BUZZWOLE
	return

Cities_EventScript_V3HideBuzzwole::
	setflag FLAG_CITIES_HIDE_V3_BUZZWOLE
	return

Cities_EventScript_V3ShowPheromosa::
	goto_if_set FLAG_CITIES_V3_PHEROMOSA_CAUGHT, Cities_EventScript_V3HidePheromosa
	clearflag FLAG_CITIES_HIDE_V3_PHEROMOSA
	return

Cities_EventScript_V3HidePheromosa::
	setflag FLAG_CITIES_HIDE_V3_PHEROMOSA
	return

Cities_EventScript_V3ShowXurkitree::
	goto_if_set FLAG_CITIES_V3_XURKITREE_CAUGHT, Cities_EventScript_V3HideXurkitree
	clearflag FLAG_CITIES_HIDE_V3_XURKITREE
	return

Cities_EventScript_V3HideXurkitree::
	setflag FLAG_CITIES_HIDE_V3_XURKITREE
	return

Cities_EventScript_V3ShowCelesteela::
	goto_if_set FLAG_CITIES_V3_CELESTEELA_CAUGHT, Cities_EventScript_V3HideCelesteela
	clearflag FLAG_CITIES_HIDE_V3_CELESTEELA
	return

Cities_EventScript_V3HideCelesteela::
	setflag FLAG_CITIES_HIDE_V3_CELESTEELA
	return

Cities_EventScript_V3ShowKartana::
	goto_if_set FLAG_CITIES_V3_KARTANA_CAUGHT, Cities_EventScript_V3HideKartana
	clearflag FLAG_CITIES_HIDE_V3_KARTANA
	return

Cities_EventScript_V3HideKartana::
	setflag FLAG_CITIES_HIDE_V3_KARTANA
	return

Cities_EventScript_V3ShowGuzzlord::
	goto_if_set FLAG_CITIES_V3_GUZZLORD_CAUGHT, Cities_EventScript_V3HideGuzzlord
	clearflag FLAG_CITIES_HIDE_V3_GUZZLORD
	return

Cities_EventScript_V3HideGuzzlord::
	setflag FLAG_CITIES_HIDE_V3_GUZZLORD
	return

Cities_EventScript_V3ShowStakataka::
	goto_if_set FLAG_CITIES_V3_STAKATAKA_CAUGHT, Cities_EventScript_V3HideStakataka
	clearflag FLAG_CITIES_HIDE_V3_STAKATAKA
	return

Cities_EventScript_V3HideStakataka::
	setflag FLAG_CITIES_HIDE_V3_STAKATAKA
	return

Cities_EventScript_V3ShowBlacephalon::
	goto_if_set FLAG_CITIES_V3_BLACEPHALON_CAUGHT, Cities_EventScript_V3HideBlacephalon
	clearflag FLAG_CITIES_HIDE_V3_BLACEPHALON
	return

Cities_EventScript_V3HideBlacephalon::
	setflag FLAG_CITIES_HIDE_V3_BLACEPHALON
	return

Cities_EventScript_V3ShowSolgaleo::
	goto_if_set FLAG_CITIES_V3_SOLGALEO_CAUGHT, Cities_EventScript_V3HideSolgaleo
	clearflag FLAG_CITIES_HIDE_V3_SOLGALEO
	return

Cities_EventScript_V3HideSolgaleo::
	setflag FLAG_CITIES_HIDE_V3_SOLGALEO
	return

Cities_EventScript_V3ShowLunala::
	goto_if_set FLAG_CITIES_V3_LUNALA_CAUGHT, Cities_EventScript_V3HideLunala
	clearflag FLAG_CITIES_HIDE_V3_LUNALA
	return

Cities_EventScript_V3HideLunala::
	setflag FLAG_CITIES_HIDE_V3_LUNALA
	return

@ -- Text --

Cities_Text_V3HelperR119:
	.string "Mind the tall grass - something\n"
	.string "fast came through the hole.\p"
	.string "We opened these doors by\n"
	.string "accident. We'll help close every\l"
	.string "one of them.$"

Cities_Text_V3HelperMtPyre:
	.string "The families who visit the\n"
	.string "mountain are safe. We walked\l"
	.string "every path twice.\p"
	.string "Whatever you think of us -\n"
	.string "please believe we didn't want\l"
	.string "THIS.$"

Cities_Text_V3HelperJaggedScared:
	.string "S-stay back from the big one!\p"
	.string "It ate my field desk. It ate\n"
	.string "the SAMPLES.\p"
	.string "Catalogue THAT.$"

Cities_Text_V3PoipoleThanks:
	.string "You actually - it's gone. You\n"
	.string "caught it.\p"
	.string "Here. This little one followed\n"
	.string "me out of the hole and won't\l"
	.string "stop chewing my satchel.\p"
	.string "It likes brave people. It should\n"
	.string "be with one.$"

Cities_Text_V3PoipoleGiven:
	.string "POIPOLE looks delighted.\p"
	.string "My satchel is saved.$"

Cities_Text_V3PoipoleNoRoom:
	.string "No room? It'll wait. The satchel\n"
	.string "will not survive the wait.$"

Cities_Text_V3HelperJaggedAfter:
	.string "The sky here is just sky again.\p"
	.string "I'm going to sit down for a\n"
	.string "while.$"

Cities_Text_V3Archivist:
	.string "…So you're the one.\p"
	.string "The man in the slate-gray coat\n"
	.string "doesn't look at you. He looks at\l"
	.string "the hole in the sky.\p"
	.string "He raises one hand. The edges of\n"
	.string "the hole fold inward, slowly,\l"
	.string "like a page being turned back.\p"
	.string "“I'm sorry. This was never\n"
	.string "supposed to touch anyone.”\p"
	.string "“The doors I need are further\n"
	.string "in. I'll be more careful.”\p"
	.string "“You should keep stopping me.\n"
	.string "It's working better than\l"
	.string "anything I've built.”\p"
	.string "He tips his head - almost a\n"
	.string "bow - and walks into the mist.$"

Cities_Text_V3GnomonProgress:
	.string "GNOMON has a clipboard and\n"
	.string "seventeen open reports.\p"
	.string "“Visitors are still loose. When\n"
	.string "the sky is empty, come back -\l"
	.string "I have something of ours you\l"
	.string "should have.”$"

Cities_Text_V3GnomonReward:
	.string "“Every door closed. Every\n"
	.string "visitor accounted for.\p"
	.string "“You did most of the\n"
	.string "accounting.”$"

Cities_Text_V3GnomonRewardDone:
	.string "“The fusion instruments. We\n"
	.string "built them for the light legends\l"
	.string "and lost the right to use them.\p"
	.string "“They work. That's the problem\n"
	.string "with everything we build.”$"

Cities_Text_V3GnomonBagFull:
	.string "“Two instruments, and no bag\n"
	.string "space. Make room - they don't\l"
	.string "fold.”$"

Cities_Text_V3GnomonAfter:
	.string "“The machines are quiet. He is\n"
	.string "not. The next attempt will be\l"
	.string "the real one.\p"
	.string "“I find I am not sleeping\n"
	.string "well.”$"

Cities_Text_V3Nihilego:
	.string "Something drifts over the rocks\n"
	.string "like a jellyfish made of glass\l"
	.string "and questions.$"

Cities_Text_V3Buzzwole:
	.string "It flexes at you.\p"
	.string "It seems to consider this a\n"
	.string "complete introduction.$"

Cities_Text_V3Pheromosa:
	.string "It moves like the space between\n"
	.string "eye-blinks.\p"
	.string "It finds the jungle mud deeply\n"
	.string "offensive.$"

Cities_Text_V3Xurkitree:
	.string "The generators hum louder as it\n"
	.string "sways closer.\p"
	.string "It is either dancing or\n"
	.string "feeding. Possibly both.$"

Cities_Text_V3Celesteela:
	.string "Something vast stands among the\n"
	.string "trees, patient as a launch\l"
	.string "tower.$"

Cities_Text_V3Kartana:
	.string "A folded blade of paper hangs\n"
	.string "in the air.\p"
	.string "The grass around it is cut in\n"
	.string "perfectly straight lines.$"

Cities_Text_V3Guzzlord:
	.string "The rumbling isn't the volcano.\p"
	.string "It is chewing. Everything.$"

Cities_Text_V3Stakataka:
	.string "What looked like a stone wall\n"
	.string "has too many legs, and all of\l"
	.string "them are staring.$"

Cities_Text_V3Blacephalon:
	.string "It juggles its own head, waiting\n"
	.string "for you to applaud.\p"
	.string "This is a trap. It is a very\n"
	.string "cheerful trap.$"

Cities_Text_V3Solgaleo:
	.string "The clearing is brighter than\n"
	.string "the sky above it.\p"
	.string "The beast of the sun lowers its\n"
	.string "head to look at you.$"

Cities_Text_V3Lunala:
	.string "The mist parts around wings\n"
	.string "like a piece of night sky.\p"
	.string "The mountain's spirits are\n"
	.string "calm. It came here to mourn\l"
	.string "with them.$"

Cities_Text_V3Necrozma:
	.string "The light around the rocks\n"
	.string "bends wrong, pulled toward a\l"
	.string "shape made of hunger and\l"
	.string "prisms.\p"
	.string "It followed the sun and the\n"
	.string "moon here.$"

Cities_Text_V3Naganadel:
	.string "It circles once overhead and\n"
	.string "lands with showy precision.\p"
	.string "It seems to be looking for the\n"
	.string "little one.$"

Cities_Text_V3ResearcherWormholes:
	.string "It's bad. Look at the sky feed.\p"
	.string "Holes. Six of them, over land\n"
	.string "and sea. Things are coming\l"
	.string "THROUGH.\p"
	.string "The polite people called us\n"
	.string "first. Gave us coordinates,\l"
	.string "apologized, and started helping\l"
	.string "with the evacuations.\p"
	.string "ROUTE 124's rocks. ROUTE 119's\n"
	.string "jungle. NEW MAUVILLE. ROUTE 120.\l"
	.string "JAGGED PASS. MT. PYRE.\p"
	.string "Champion… the sky shouldn't\n"
	.string "have doors.$"

Cities_Text_V3ResearcherCosmogRetry:
	.string "The sky is still full of holes.\n"
	.string "And my office is still full of\l"
	.string "THIS.$"

Cities_Text_V3CosmogShelters:
	.string "One more thing. Something\n"
	.string "drifted out of the hole over\l"
	.string "the sea and followed our boat\l"
	.string "home.\p"
	.string "It's been sleeping in my\n"
	.string "wastepaper basket.\p"
	.string "It's not scared of you. That\n"
	.string "settles it, as far as I'm\l"
	.string "concerned.$"

Cities_Text_V3CosmogGiven:
	.string "COSMOG settled in immediately.\p"
	.string "Keep it away from wastepaper\n"
	.string "baskets.$"

Cities_Text_V3CosmogNoRoom:
	.string "No room? It'll keep the basket\n"
	.string "warm until you're back.$"

Cities_Text_V3ResearcherDuring:
	.string "Six holes. We're tracking them\n"
	.string "all from here.\p"
	.string "Close them - however it is\n"
	.string "you close such things.$"
