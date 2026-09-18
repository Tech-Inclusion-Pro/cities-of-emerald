@ Cities of Emerald — V4 "The Day of the Storm" (GDD 7.2 / 6.6, Task
@ 12.5, outline approved 2026-09-18). Epoch breaks through — sideways.
@ Time rifts spill Paradox Pokémon into old places and machine places.
@ The anchors hold at Route 128; the deepest point is the drowned
@ square of Coralmere, where stepping into the rift becomes the walk
@ through the village of 12.4. The arc completes on the trio
@ (Koraidon, Miraidon, Terapagos); the pockets stay open after.
@
@ VAR_CITIES_V4_STATE: 0 locked, 1 rifts open, 2 Coralmere walked,
@ 3 complete (trio caught).

Cities_EventScript_V4TryComplete::
	goto_if_ge VAR_CITIES_V4_STATE, 3, Cities_EventScript_V4TryCompleteEnd
	goto_if_unset FLAG_CITIES_V4_KORAIDON_CAUGHT, Cities_EventScript_V4TryCompleteEnd
	goto_if_unset FLAG_CITIES_V4_MIRAIDON_CAUGHT, Cities_EventScript_V4TryCompleteEnd
	goto_if_unset FLAG_CITIES_V4_TERAPAGOS_CAUGHT, Cities_EventScript_V4TryCompleteEnd
	setvar VAR_CITIES_V4_STATE, 3
Cities_EventScript_V4TryCompleteEnd::
	return

@ -- Per-map visibility --

Cities_EventScript_UpdateV4Route111::
	goto_if_eq VAR_CITIES_V4_STATE, 0, Cities_EventScript_V4HideR111
	call Cities_EventScript_V4ShowGreatTusk
	call Cities_EventScript_V4ShowScreamTail
	call Cities_EventScript_V4ShowSandyShocks
	call Cities_EventScript_V4ShowRoaringMoon
	return

Cities_EventScript_V4HideR111::
	setflag FLAG_CITIES_HIDE_V4_GREAT_TUSK
	setflag FLAG_CITIES_HIDE_V4_SCREAM_TAIL
	setflag FLAG_CITIES_HIDE_V4_SANDY_SHOCKS
	setflag FLAG_CITIES_HIDE_V4_ROARING_MOON
	return

Cities_EventScript_UpdateV4PetalburgWoods::
	goto_if_eq VAR_CITIES_V4_STATE, 0, Cities_EventScript_V4HideWoods
	call Cities_EventScript_V4ShowBruteBonnet
	call Cities_EventScript_V4ShowSlitherWing
	call Cities_EventScript_V4ShowFlutterMane
	return

Cities_EventScript_V4HideWoods::
	setflag FLAG_CITIES_HIDE_V4_BRUTE_BONNET
	setflag FLAG_CITIES_HIDE_V4_SLITHER_WING
	setflag FLAG_CITIES_HIDE_V4_FLUTTER_MANE
	return

Cities_EventScript_UpdateV4Route119::
	goto_if_eq VAR_CITIES_V4_STATE, 0, Cities_EventScript_V4HideR119
	call Cities_EventScript_V4ShowWalkingWake
	call Cities_EventScript_V4ShowGougingFire
	call Cities_EventScript_V4ShowRagingBolt
	return

Cities_EventScript_V4HideR119::
	setflag FLAG_CITIES_HIDE_V4_WALKING_WAKE
	setflag FLAG_CITIES_HIDE_V4_GOUGING_FIRE
	setflag FLAG_CITIES_HIDE_V4_RAGING_BOLT
	return

Cities_EventScript_UpdateV4NewMauville::
	goto_if_eq VAR_CITIES_V4_STATE, 0, Cities_EventScript_V4HideNewMauville
	call Cities_EventScript_V4ShowIronTreads
	call Cities_EventScript_V4ShowIronHands
	call Cities_EventScript_V4ShowIronThorns
	goto_if_ge VAR_CITIES_V4_STATE, 3, Cities_EventScript_V4HideGnomon
	clearflag FLAG_CITIES_HIDE_V4_GNOMON
	return

Cities_EventScript_V4HideNewMauville::
	setflag FLAG_CITIES_HIDE_V4_IRON_TREADS
	setflag FLAG_CITIES_HIDE_V4_IRON_HANDS
	setflag FLAG_CITIES_HIDE_V4_IRON_THORNS
Cities_EventScript_V4HideGnomon::
	setflag FLAG_CITIES_HIDE_V4_GNOMON
	return

Cities_EventScript_UpdateV4Route110::
	goto_if_eq VAR_CITIES_V4_STATE, 0, Cities_EventScript_V4HideR110
	call Cities_EventScript_V4ShowIronBundle
	call Cities_EventScript_V4ShowIronJugulis
	call Cities_EventScript_V4ShowIronMoth
	return

Cities_EventScript_V4HideR110::
	setflag FLAG_CITIES_HIDE_V4_IRON_BUNDLE
	setflag FLAG_CITIES_HIDE_V4_IRON_JUGULIS
	setflag FLAG_CITIES_HIDE_V4_IRON_MOTH
	return

Cities_EventScript_UpdateV4Deck::
	goto_if_eq VAR_CITIES_V4_STATE, 0, Cities_EventScript_V4HideDeck
	call Cities_EventScript_V4ShowIronValiant
	call Cities_EventScript_V4ShowIronLeaves
	call Cities_EventScript_V4ShowIronBoulder
	call Cities_EventScript_V4ShowIronCrown
	return

Cities_EventScript_V4HideDeck::
	setflag FLAG_CITIES_HIDE_V4_IRON_VALIANT
	setflag FLAG_CITIES_HIDE_V4_IRON_LEAVES
	setflag FLAG_CITIES_HIDE_V4_IRON_BOULDER
	setflag FLAG_CITIES_HIDE_V4_IRON_CROWN
	return

@ Route 128: anchors + Meridian. Miraidon lives on Underwater_Route128.
Cities_EventScript_UpdateV4Route128::
	goto_if_eq VAR_CITIES_V4_STATE, 0, Cities_EventScript_V4HideR128
	call Cities_EventScript_V4ShowKoraidon
	goto_if_ge VAR_CITIES_V4_STATE, 3, Cities_EventScript_V4HideMeridian
	clearflag FLAG_CITIES_HIDE_V4_MERIDIAN
	return

Cities_EventScript_V4HideR128::
	setflag FLAG_CITIES_HIDE_V4_KORAIDON
Cities_EventScript_V4HideMeridian::
	setflag FLAG_CITIES_HIDE_V4_MERIDIAN
	return

Cities_EventScript_UpdateV4Underwater128::
	goto_if_eq VAR_CITIES_V4_STATE, 0, Cities_EventScript_V4HideMiraidon
	call Cities_EventScript_V4ShowMiraidon
	return

@ Coralmere ruins: Terapagos appears only after the walk; the square
@ trigger arms only during state 1 (VAR_TEMP_2, set on transition).
Cities_EventScript_UpdateV4Coralmere::
	setvar VAR_TEMP_2, 0
	goto_if_ne VAR_CITIES_V4_STATE, 1, Cities_EventScript_V4CoralmereNoScene
	setvar VAR_TEMP_2, 1
Cities_EventScript_V4CoralmereNoScene::
	goto_if_lt VAR_CITIES_V4_STATE, 2, Cities_EventScript_V4HideTerapagos
	goto_if_set FLAG_CITIES_V4_TERAPAGOS_CAUGHT, Cities_EventScript_V4HideTerapagos
	clearflag FLAG_CITIES_HIDE_V4_TERAPAGOS
	return

Cities_EventScript_V4HideTerapagos::
	setflag FLAG_CITIES_HIDE_V4_TERAPAGOS
	return

@ -- Gnomon opens V4 (Space Center lobby, after the V3 reward) --

Cities_EventScript_V4GnomonOpens::
	msgbox Cities_Text_V4GnomonOpens, MSGBOX_DEFAULT
	setvar VAR_CITIES_V4_STATE, 1
	release
	end

@ -- The admins' second battles --

Cities_EventScript_V4Meridian::
	trainerbattle_single TRAINER_EPOCH_MERIDIAN_2, Cities_Text_V4MeridianIntro, Cities_Text_V4MeridianDefeat
	msgbox Cities_Text_V4MeridianAfter, MSGBOX_AUTOCLOSE
	end

Cities_EventScript_V4Gnomon::
	trainerbattle_single TRAINER_EPOCH_GNOMON_2, Cities_Text_V4GnomonIntro, Cities_Text_V4GnomonDefeat
	msgbox Cities_Text_V4GnomonAfter, MSGBOX_AUTOCLOSE
	end

@ -- The rift scene (Coralmere square -> the village of 12.4) --

Cities_EventScript_V4RiftScene::
	lockall
	msgbox Cities_Text_V4RiftOpens, MSGBOX_DEFAULT
	closemessage
	fadescreenswapbuffers FADE_TO_WHITE
	warp MAP_CORALMERE_PAST, 12, 18
	waitstate
	releaseall
	end

@ The sea ends the walk (CoralmerePast beach row).
Cities_EventScript_V4RiftCloses::
	lockall
	msgbox Cities_Text_V4RiftCloses, MSGBOX_DEFAULT
	closemessage
	setvar VAR_CITIES_V4_STATE, 2
	fadescreenswapbuffers FADE_TO_WHITE
	warp MAP_CORALMERE_RUINS, 12, 17
	waitstate
	releaseall
	end

@ The Archivist, in the middle of his village.
Cities_EventScript_V4ArchivistPast::
	lock
	faceplayer
	msgbox Cities_Text_V4ArchivistPast, MSGBOX_DEFAULT
	release
	end

@ -- Encounters (M1 pattern) --

Cities_EventScript_V4GreatTusk::
	lock
	faceplayer
	msgbox Cities_Text_V4GreatTusk, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_GREAT_TUSK, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_GREAT_TUSK
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtGreatTusk
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtGreatTusk::
	setflag FLAG_CITIES_V4_GREAT_TUSK_CAUGHT
	release
	end

Cities_EventScript_V4ScreamTail::
	lock
	faceplayer
	msgbox Cities_Text_V4ScreamTail, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SCREAM_TAIL, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_SCREAM_TAIL
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtScreamTail
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtScreamTail::
	setflag FLAG_CITIES_V4_SCREAM_TAIL_CAUGHT
	release
	end

Cities_EventScript_V4SandyShocks::
	lock
	faceplayer
	msgbox Cities_Text_V4SandyShocks, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SANDY_SHOCKS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_SANDY_SHOCKS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtSandyShocks
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtSandyShocks::
	setflag FLAG_CITIES_V4_SANDY_SHOCKS_CAUGHT
	release
	end

Cities_EventScript_V4RoaringMoon::
	lock
	faceplayer
	msgbox Cities_Text_V4RoaringMoon, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_ROARING_MOON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_ROARING_MOON
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtRoaringMoon
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtRoaringMoon::
	setflag FLAG_CITIES_V4_ROARING_MOON_CAUGHT
	release
	end

Cities_EventScript_V4BruteBonnet::
	lock
	faceplayer
	msgbox Cities_Text_V4BruteBonnet, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_BRUTE_BONNET, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_BRUTE_BONNET
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtBruteBonnet
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtBruteBonnet::
	setflag FLAG_CITIES_V4_BRUTE_BONNET_CAUGHT
	release
	end

Cities_EventScript_V4SlitherWing::
	lock
	faceplayer
	msgbox Cities_Text_V4SlitherWing, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SLITHER_WING, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_SLITHER_WING
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtSlitherWing
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtSlitherWing::
	setflag FLAG_CITIES_V4_SLITHER_WING_CAUGHT
	release
	end

Cities_EventScript_V4FlutterMane::
	lock
	faceplayer
	msgbox Cities_Text_V4FlutterMane, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_FLUTTER_MANE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_FLUTTER_MANE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtFlutterMane
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtFlutterMane::
	setflag FLAG_CITIES_V4_FLUTTER_MANE_CAUGHT
	release
	end

Cities_EventScript_V4WalkingWake::
	lock
	faceplayer
	msgbox Cities_Text_V4WalkingWake, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_WALKING_WAKE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_WALKING_WAKE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtWalkingWake
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtWalkingWake::
	setflag FLAG_CITIES_V4_WALKING_WAKE_CAUGHT
	release
	end

Cities_EventScript_V4GougingFire::
	lock
	faceplayer
	msgbox Cities_Text_V4GougingFire, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_GOUGING_FIRE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_GOUGING_FIRE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtGougingFire
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtGougingFire::
	setflag FLAG_CITIES_V4_GOUGING_FIRE_CAUGHT
	release
	end

Cities_EventScript_V4RagingBolt::
	lock
	faceplayer
	msgbox Cities_Text_V4RagingBolt, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_RAGING_BOLT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_RAGING_BOLT
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtRagingBolt
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtRagingBolt::
	setflag FLAG_CITIES_V4_RAGING_BOLT_CAUGHT
	release
	end

Cities_EventScript_V4IronTreads::
	lock
	faceplayer
	msgbox Cities_Text_V4IronTreads, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_IRON_TREADS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_IRON_TREADS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtIronTreads
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtIronTreads::
	setflag FLAG_CITIES_V4_IRON_TREADS_CAUGHT
	release
	end

Cities_EventScript_V4IronHands::
	lock
	faceplayer
	msgbox Cities_Text_V4IronHands, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_IRON_HANDS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_IRON_HANDS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtIronHands
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtIronHands::
	setflag FLAG_CITIES_V4_IRON_HANDS_CAUGHT
	release
	end

Cities_EventScript_V4IronThorns::
	lock
	faceplayer
	msgbox Cities_Text_V4IronThorns, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_IRON_THORNS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_IRON_THORNS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtIronThorns
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtIronThorns::
	setflag FLAG_CITIES_V4_IRON_THORNS_CAUGHT
	release
	end

Cities_EventScript_V4IronBundle::
	lock
	faceplayer
	msgbox Cities_Text_V4IronBundle, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_IRON_BUNDLE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_IRON_BUNDLE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtIronBundle
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtIronBundle::
	setflag FLAG_CITIES_V4_IRON_BUNDLE_CAUGHT
	release
	end

Cities_EventScript_V4IronJugulis::
	lock
	faceplayer
	msgbox Cities_Text_V4IronJugulis, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_IRON_JUGULIS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_IRON_JUGULIS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtIronJugulis
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtIronJugulis::
	setflag FLAG_CITIES_V4_IRON_JUGULIS_CAUGHT
	release
	end

Cities_EventScript_V4IronMoth::
	lock
	faceplayer
	msgbox Cities_Text_V4IronMoth, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_IRON_MOTH, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_IRON_MOTH
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtIronMoth
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtIronMoth::
	setflag FLAG_CITIES_V4_IRON_MOTH_CAUGHT
	release
	end

Cities_EventScript_V4IronValiant::
	lock
	faceplayer
	msgbox Cities_Text_V4IronValiant, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_IRON_VALIANT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_IRON_VALIANT
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtIronValiant
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtIronValiant::
	setflag FLAG_CITIES_V4_IRON_VALIANT_CAUGHT
	release
	end

Cities_EventScript_V4IronLeaves::
	lock
	faceplayer
	msgbox Cities_Text_V4IronLeaves, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_IRON_LEAVES, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_IRON_LEAVES
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtIronLeaves
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtIronLeaves::
	setflag FLAG_CITIES_V4_IRON_LEAVES_CAUGHT
	release
	end

Cities_EventScript_V4IronBoulder::
	lock
	faceplayer
	msgbox Cities_Text_V4IronBoulder, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_IRON_BOULDER, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_IRON_BOULDER
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtIronBoulder
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtIronBoulder::
	setflag FLAG_CITIES_V4_IRON_BOULDER_CAUGHT
	release
	end

Cities_EventScript_V4IronCrown::
	lock
	faceplayer
	msgbox Cities_Text_V4IronCrown, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_IRON_CROWN, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_IRON_CROWN
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtIronCrown
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtIronCrown::
	setflag FLAG_CITIES_V4_IRON_CROWN_CAUGHT
	release
	end

Cities_EventScript_V4Koraidon::
	lock
	faceplayer
	msgbox Cities_Text_V4Koraidon, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_KORAIDON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_KORAIDON
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtKoraidon
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtKoraidon::
	setflag FLAG_CITIES_V4_KORAIDON_CAUGHT
	call Cities_EventScript_V4TryComplete
	release
	end

Cities_EventScript_V4Miraidon::
	lock
	faceplayer
	msgbox Cities_Text_V4Miraidon, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_MIRAIDON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MIRAIDON
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtMiraidon
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtMiraidon::
	setflag FLAG_CITIES_V4_MIRAIDON_CAUGHT
	call Cities_EventScript_V4TryComplete
	release
	end

Cities_EventScript_V4Terapagos::
	lock
	faceplayer
	msgbox Cities_Text_V4Terapagos, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_TERAPAGOS, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_TERAPAGOS
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_V4CaughtTerapagos
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_V4CaughtTerapagos::
	setflag FLAG_CITIES_V4_TERAPAGOS_CAUGHT
	call Cities_EventScript_V4TryComplete
	release
	end

Cities_EventScript_V4ShowGreatTusk::
	goto_if_set FLAG_CITIES_V4_GREAT_TUSK_CAUGHT, Cities_EventScript_V4HideGreatTusk
	clearflag FLAG_CITIES_HIDE_V4_GREAT_TUSK
	return

Cities_EventScript_V4HideGreatTusk::
	setflag FLAG_CITIES_HIDE_V4_GREAT_TUSK
	return

Cities_EventScript_V4ShowScreamTail::
	goto_if_set FLAG_CITIES_V4_SCREAM_TAIL_CAUGHT, Cities_EventScript_V4HideScreamTail
	clearflag FLAG_CITIES_HIDE_V4_SCREAM_TAIL
	return

Cities_EventScript_V4HideScreamTail::
	setflag FLAG_CITIES_HIDE_V4_SCREAM_TAIL
	return

Cities_EventScript_V4ShowSandyShocks::
	goto_if_set FLAG_CITIES_V4_SANDY_SHOCKS_CAUGHT, Cities_EventScript_V4HideSandyShocks
	clearflag FLAG_CITIES_HIDE_V4_SANDY_SHOCKS
	return

Cities_EventScript_V4HideSandyShocks::
	setflag FLAG_CITIES_HIDE_V4_SANDY_SHOCKS
	return

Cities_EventScript_V4ShowRoaringMoon::
	goto_if_set FLAG_CITIES_V4_ROARING_MOON_CAUGHT, Cities_EventScript_V4HideRoaringMoon
	clearflag FLAG_CITIES_HIDE_V4_ROARING_MOON
	return

Cities_EventScript_V4HideRoaringMoon::
	setflag FLAG_CITIES_HIDE_V4_ROARING_MOON
	return

Cities_EventScript_V4ShowBruteBonnet::
	goto_if_set FLAG_CITIES_V4_BRUTE_BONNET_CAUGHT, Cities_EventScript_V4HideBruteBonnet
	clearflag FLAG_CITIES_HIDE_V4_BRUTE_BONNET
	return

Cities_EventScript_V4HideBruteBonnet::
	setflag FLAG_CITIES_HIDE_V4_BRUTE_BONNET
	return

Cities_EventScript_V4ShowSlitherWing::
	goto_if_set FLAG_CITIES_V4_SLITHER_WING_CAUGHT, Cities_EventScript_V4HideSlitherWing
	clearflag FLAG_CITIES_HIDE_V4_SLITHER_WING
	return

Cities_EventScript_V4HideSlitherWing::
	setflag FLAG_CITIES_HIDE_V4_SLITHER_WING
	return

Cities_EventScript_V4ShowFlutterMane::
	goto_if_set FLAG_CITIES_V4_FLUTTER_MANE_CAUGHT, Cities_EventScript_V4HideFlutterMane
	clearflag FLAG_CITIES_HIDE_V4_FLUTTER_MANE
	return

Cities_EventScript_V4HideFlutterMane::
	setflag FLAG_CITIES_HIDE_V4_FLUTTER_MANE
	return

Cities_EventScript_V4ShowWalkingWake::
	goto_if_set FLAG_CITIES_V4_WALKING_WAKE_CAUGHT, Cities_EventScript_V4HideWalkingWake
	clearflag FLAG_CITIES_HIDE_V4_WALKING_WAKE
	return

Cities_EventScript_V4HideWalkingWake::
	setflag FLAG_CITIES_HIDE_V4_WALKING_WAKE
	return

Cities_EventScript_V4ShowGougingFire::
	goto_if_set FLAG_CITIES_V4_GOUGING_FIRE_CAUGHT, Cities_EventScript_V4HideGougingFire
	clearflag FLAG_CITIES_HIDE_V4_GOUGING_FIRE
	return

Cities_EventScript_V4HideGougingFire::
	setflag FLAG_CITIES_HIDE_V4_GOUGING_FIRE
	return

Cities_EventScript_V4ShowRagingBolt::
	goto_if_set FLAG_CITIES_V4_RAGING_BOLT_CAUGHT, Cities_EventScript_V4HideRagingBolt
	clearflag FLAG_CITIES_HIDE_V4_RAGING_BOLT
	return

Cities_EventScript_V4HideRagingBolt::
	setflag FLAG_CITIES_HIDE_V4_RAGING_BOLT
	return

Cities_EventScript_V4ShowIronTreads::
	goto_if_set FLAG_CITIES_V4_IRON_TREADS_CAUGHT, Cities_EventScript_V4HideIronTreads
	clearflag FLAG_CITIES_HIDE_V4_IRON_TREADS
	return

Cities_EventScript_V4HideIronTreads::
	setflag FLAG_CITIES_HIDE_V4_IRON_TREADS
	return

Cities_EventScript_V4ShowIronHands::
	goto_if_set FLAG_CITIES_V4_IRON_HANDS_CAUGHT, Cities_EventScript_V4HideIronHands
	clearflag FLAG_CITIES_HIDE_V4_IRON_HANDS
	return

Cities_EventScript_V4HideIronHands::
	setflag FLAG_CITIES_HIDE_V4_IRON_HANDS
	return

Cities_EventScript_V4ShowIronThorns::
	goto_if_set FLAG_CITIES_V4_IRON_THORNS_CAUGHT, Cities_EventScript_V4HideIronThorns
	clearflag FLAG_CITIES_HIDE_V4_IRON_THORNS
	return

Cities_EventScript_V4HideIronThorns::
	setflag FLAG_CITIES_HIDE_V4_IRON_THORNS
	return

Cities_EventScript_V4ShowIronBundle::
	goto_if_set FLAG_CITIES_V4_IRON_BUNDLE_CAUGHT, Cities_EventScript_V4HideIronBundle
	clearflag FLAG_CITIES_HIDE_V4_IRON_BUNDLE
	return

Cities_EventScript_V4HideIronBundle::
	setflag FLAG_CITIES_HIDE_V4_IRON_BUNDLE
	return

Cities_EventScript_V4ShowIronJugulis::
	goto_if_set FLAG_CITIES_V4_IRON_JUGULIS_CAUGHT, Cities_EventScript_V4HideIronJugulis
	clearflag FLAG_CITIES_HIDE_V4_IRON_JUGULIS
	return

Cities_EventScript_V4HideIronJugulis::
	setflag FLAG_CITIES_HIDE_V4_IRON_JUGULIS
	return

Cities_EventScript_V4ShowIronMoth::
	goto_if_set FLAG_CITIES_V4_IRON_MOTH_CAUGHT, Cities_EventScript_V4HideIronMoth
	clearflag FLAG_CITIES_HIDE_V4_IRON_MOTH
	return

Cities_EventScript_V4HideIronMoth::
	setflag FLAG_CITIES_HIDE_V4_IRON_MOTH
	return

Cities_EventScript_V4ShowIronValiant::
	goto_if_set FLAG_CITIES_V4_IRON_VALIANT_CAUGHT, Cities_EventScript_V4HideIronValiant
	clearflag FLAG_CITIES_HIDE_V4_IRON_VALIANT
	return

Cities_EventScript_V4HideIronValiant::
	setflag FLAG_CITIES_HIDE_V4_IRON_VALIANT
	return

Cities_EventScript_V4ShowIronLeaves::
	goto_if_set FLAG_CITIES_V4_IRON_LEAVES_CAUGHT, Cities_EventScript_V4HideIronLeaves
	clearflag FLAG_CITIES_HIDE_V4_IRON_LEAVES
	return

Cities_EventScript_V4HideIronLeaves::
	setflag FLAG_CITIES_HIDE_V4_IRON_LEAVES
	return

Cities_EventScript_V4ShowIronBoulder::
	goto_if_set FLAG_CITIES_V4_IRON_BOULDER_CAUGHT, Cities_EventScript_V4HideIronBoulder
	clearflag FLAG_CITIES_HIDE_V4_IRON_BOULDER
	return

Cities_EventScript_V4HideIronBoulder::
	setflag FLAG_CITIES_HIDE_V4_IRON_BOULDER
	return

Cities_EventScript_V4ShowIronCrown::
	goto_if_set FLAG_CITIES_V4_IRON_CROWN_CAUGHT, Cities_EventScript_V4HideIronCrown
	clearflag FLAG_CITIES_HIDE_V4_IRON_CROWN
	return

Cities_EventScript_V4HideIronCrown::
	setflag FLAG_CITIES_HIDE_V4_IRON_CROWN
	return

Cities_EventScript_V4ShowKoraidon::
	goto_if_set FLAG_CITIES_V4_KORAIDON_CAUGHT, Cities_EventScript_V4HideKoraidon
	clearflag FLAG_CITIES_HIDE_V4_KORAIDON
	return

Cities_EventScript_V4HideKoraidon::
	setflag FLAG_CITIES_HIDE_V4_KORAIDON
	return

Cities_EventScript_V4ShowMiraidon::
	goto_if_set FLAG_CITIES_V4_MIRAIDON_CAUGHT, Cities_EventScript_V4HideMiraidon
	clearflag FLAG_CITIES_HIDE_V4_MIRAIDON
	return

Cities_EventScript_V4HideMiraidon::
	setflag FLAG_CITIES_HIDE_V4_MIRAIDON
	return

@ -- Static texts --

Cities_Text_V4GreatTusk:
	.string "A mountain of tusks and muscle\n"
	.string "grazes calmly in the heat haze.\p"
	.string "It is several million years out\n"
	.string "of place.$"

Cities_Text_V4ScreamTail:
	.string "Something round and pink watches\n"
	.string "you from the dune.\p"
	.string "Its tail is bigger than it is.\n"
	.string "It seems very proud of this.$"

Cities_Text_V4SandyShocks:
	.string "Iron sand hangs around it like\n"
	.string "a slow storm.\p"
	.string "The air tastes of lightning that\n"
	.string "fell a long, long time ago.$"

Cities_Text_V4RoaringMoon:
	.string "A shadow crosses the desert -\n"
	.string "wide, fast, and wrong.\p"
	.string "It lands without a sound.$"

Cities_Text_V4BruteBonnet:
	.string "The mushroom cap rises. There\n"
	.string "is an entire creature under it.\p"
	.string "The forest floor here smells\n"
	.string "of deep time.$"

Cities_Text_V4SlitherWing:
	.string "It hauls itself upright on\n"
	.string "burning wings.\p"
	.string "The trees lean away from the\n"
	.string "heat.$"

Cities_Text_V4FlutterMane:
	.string "Something drifts between the\n"
	.string "trunks like a memory of a\l"
	.string "ghost.\p"
	.string "It was old before the woods\n"
	.string "were.$"

Cities_Text_V4WalkingWake:
	.string "The river fog gathers into\n"
	.string "something with teeth and grace.\p"
	.string "It walks on the water like it\n"
	.string "owns the idea.$"

Cities_Text_V4GougingFire:
	.string "The rain hisses where it stands.\p"
	.string "It regards you with an old,\n"
	.string "patient hunger.$"

Cities_Text_V4RagingBolt:
	.string "Its neck vanishes into the\n"
	.string "clouds. The thunder answers it\l"
	.string "by name.$"

Cities_Text_V4IronTreads:
	.string "It rolls a slow circle around\n"
	.string "the generator hall, on patrol\l"
	.string "for a war that never came.$"

Cities_Text_V4IronHands:
	.string "It is doing push-ups against\n"
	.string "the wall current.\p"
	.string "The wall is losing.$"

Cities_Text_V4IronThorns:
	.string "A mountain of plates and spikes\n"
	.string "stands dormant by the coils,\l"
	.string "drinking the voltage.$"

Cities_Text_V4IronBundle:
	.string "A small, round machine waddles\n"
	.string "along the shore, spraying ice\l"
	.string "at the waves.\p"
	.string "The waves keep coming. It keeps\n"
	.string "spraying. Neither will yield.$"

Cities_Text_V4IronJugulis:
	.string "Three chrome heads turn to face\n"
	.string "you in perfect unison.$"

Cities_Text_V4IronMoth:
	.string "It hovers over the cycling road,\n"
	.string "shedding sparks like pollen.$"

Cities_Text_V4IronValiant:
	.string "It stands on the rotten deck in\n"
	.string "perfect fencing posture,\l"
	.string "dueling the sea wind.$"

Cities_Text_V4IronLeaves:
	.string "Light bends along its blades.\p"
	.string "The deck boards under it are\n"
	.string "sliced into neat green-lit\l"
	.string "lines.$"

Cities_Text_V4IronBoulder:
	.string "It waits at the bow like a\n"
	.string "figurehead that got tired of\l"
	.string "holding still.$"

Cities_Text_V4IronCrown:
	.string "Blades orbit it slowly, like a\n"
	.string "crown too heavy to wear.$"

Cities_Text_V4Koraidon:
	.string "The rift over the ruins bends\n"
	.string "toward the scarlet beast on\l"
	.string "the old stones.\p"
	.string "The past end of the anchor.$"

Cities_Text_V4Miraidon:
	.string "Violet light floods the sunken\n"
	.string "pocket.\p"
	.string "The future end of the anchor\n"
	.string "coils around the cut stone.$"

Cities_Text_V4Terapagos:
	.string "In the middle of the drowned\n"
	.string "square, a small creature turns\l"
	.string "in slow circles, glittering.\p"
	.string "The deepest point of the rift.\n"
	.string "It was here before the anchor,\l"
	.string "and it will outlast it.$"

@ -- Scene texts --

Cities_Text_V4GnomonOpens:
	.string "GNOMON does not look up from\n"
	.string "the readouts.\p"
	.string "“He broke through last night.\n"
	.string "Not to WHEN he wanted -\l"
	.string "sideways, into every when at\l"
	.string "once.\p"
	.string "“Rift pockets are opening over\n"
	.string "old places and new places.\l"
	.string "Things are stepping out of\l"
	.string "them.\p"
	.string "“The anchors are holding at\n"
	.string "ROUTE 128, over the drowned\l"
	.string "village.\p"
	.string "“MERIDIAN is guarding them.\n"
	.string "She won't step aside. I no\l"
	.string "longer ask her to.”$"

Cities_Text_V4MeridianIntro:
	.string "The sea is louder than last\n"
	.string "time we met.\p"
	.string "Past that light is everything\n"
	.string "he has left.\p"
	.string "I know how this ends. I read\n"
	.string "the reports too.\p"
	.string "But he held MY town's whole\n"
	.string "history over his head through\l"
	.string "a flood.\p"
	.string "Some debts you guard.$"

Cities_Text_V4MeridianDefeat:
	.string "…Guarded. Not repaid.$"

Cities_Text_V4MeridianAfter:
	.string "Go on. The anchors don't need\n"
	.string "me - they need to come down.\p"
	.string "He's past listening to me.\n"
	.string "Maybe not to you.$"

Cities_Text_V4GnomonIntro:
	.string "I keep the pocket here stable\n"
	.string "so the city's power stays on.\p"
	.string "If you pull the visitors out,\n"
	.string "it collapses safely.\p"
	.string "I calculated whether to stop\n"
	.string "you.\p"
	.string "The honest answer is that I\n"
	.string "want to see the math up close.$"

Cities_Text_V4GnomonDefeat:
	.string "…The math is beautiful.$"

Cities_Text_V4GnomonAfter:
	.string "We can hold the door open.\p"
	.string "I never asked whether we\n"
	.string "should walk through.\p"
	.string "I am asking now. Out loud.\n"
	.string "You heard me ask.$"

Cities_Text_V4RiftOpens:
	.string "The water over the square\n"
	.string "brightens - not with sunlight.\p"
	.string "The worn sign, the doorways,\n"
	.string "the tower… the rift folds them\l"
	.string "all upward, into a morning that\l"
	.string "happened long ago.$"

Cities_Text_V4RiftCloses:
	.string "The light thins.\p"
	.string "The bell, the bread, the nets,\n"
	.string "the argument about paint -\p"
	.string "The past cannot be held.\p"
	.string "The sea comes back gently, like\n"
	.string "a tide, and the morning folds\l"
	.string "away.$"

Cities_Text_V4ArchivistPast:
	.string "He stands in the middle of the\n"
	.string "square, holding the barometer.\p"
	.string "He does not move. He does not\n"
	.string "speak.\p"
	.string "He is not here to change\n"
	.string "anything.\p"
	.string "He is here to LOOK.$"
