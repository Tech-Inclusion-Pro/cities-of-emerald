@ Cities of Emerald — M4 "The Three Lights" (GDD 6.6, approved 2026-09-17).
@ The keeper in the Cave of Origin entrance opens the way into the three
@ unused Ruby/Sapphire chambers, restored as the dwellings of Uxie
@ (mind), Mesprit (heart), and Azelf (will). The passage is a pair of
@ var-gated triggers in 1F's dead-end alcove; the chambers' original
@ ladder warps still chain 1F -> 1 -> 2 -> 3 -> B1F. Levels come from
@ the shared 10.0a special; a defeated spirit returns on re-entry.

@ -- Visibility (called from each map's on_transition) --

Cities_EventScript_UpdateM4Keeper::
	goto_if_set FLAG_BADGE07_GET, Cities_EventScript_ShowM4Keeper
	setflag FLAG_CITIES_HIDE_M4_KEEPER
	return

Cities_EventScript_ShowM4Keeper::
	clearflag FLAG_CITIES_HIDE_M4_KEEPER
	return

Cities_EventScript_UpdateM4Uxie::
	goto_if_set FLAG_CITIES_M4_UXIE_CAUGHT, Cities_EventScript_HideM4Uxie
	clearflag FLAG_CITIES_HIDE_M4_UXIE
	return

Cities_EventScript_HideM4Uxie::
	setflag FLAG_CITIES_HIDE_M4_UXIE
	return

Cities_EventScript_UpdateM4Mesprit::
	goto_if_set FLAG_CITIES_M4_MESPRIT_CAUGHT, Cities_EventScript_HideM4Mesprit
	clearflag FLAG_CITIES_HIDE_M4_MESPRIT
	return

Cities_EventScript_HideM4Mesprit::
	setflag FLAG_CITIES_HIDE_M4_MESPRIT
	return

Cities_EventScript_UpdateM4Azelf::
	goto_if_set FLAG_CITIES_M4_AZELF_CAUGHT, Cities_EventScript_HideM4Azelf
	clearflag FLAG_CITIES_HIDE_M4_AZELF
	return

Cities_EventScript_HideM4Azelf::
	setflag FLAG_CITIES_HIDE_M4_AZELF
	return

@ Chamber maps' on_resume: if the spirit was just caught in a scripted
@ battle, remove its object right away (same rule as M1's birds).
Cities_EventScript_M4TryRemoveCaughtSpirit::
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_ne VAR_RESULT, B_OUTCOME_CAUGHT, Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

@ -- The keeper (Cave of Origin entrance) --

Cities_EventScript_M4Keeper::
	lock
	faceplayer
	setvar VAR_0x8004, 3 @ CITIES_ARC_M4
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, TRUE, Cities_EventScript_M4KeeperAllCaught
	goto_if_eq VAR_CITIES_M4_STATE, 0, Cities_EventScript_M4KeeperIntro
	msgbox Cities_Text_M4KeeperProgress, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_M4KeeperIntro::
	msgbox Cities_Text_M4KeeperIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_M4_STATE, 1
	msgbox Cities_Text_M4KeeperOpens, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_M4KeeperAllCaught::
	goto_if_eq VAR_CITIES_M4_STATE, 2, Cities_EventScript_M4KeeperAfter
	msgbox Cities_Text_M4KeeperThanks, MSGBOX_DEFAULT
	setvar VAR_CITIES_M4_STATE, 2
	release
	end

Cities_EventScript_M4KeeperAfter::
	msgbox Cities_Text_M4KeeperAfter, MSGBOX_DEFAULT
	release
	end

@ -- The passage (1F alcove trigger; fires at state 1 and 2) --

Cities_EventScript_M4PassageEnter::
	lockall
	msgbox Cities_Text_M4PassageSteps, MSGBOX_DEFAULT
	closemessage
	warp MAP_CAVE_OF_ORIGIN_UNUSED_RUBY_SAPPHIRE_MAP1, 13, 6
	waitstate
	releaseall
	end

@ -- The spirits --

Cities_EventScript_M4Uxie::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_UXIE, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_UXIE
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M4CaughtUxie
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_M4CaughtUxie::
	setflag FLAG_CITIES_M4_UXIE_CAUGHT
	release
	end

Cities_EventScript_M4Mesprit::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MESPRIT, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MESPRIT
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M4CaughtMesprit
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_M4CaughtMesprit::
	setflag FLAG_CITIES_M4_MESPRIT_CAUGHT
	release
	end

Cities_EventScript_M4Azelf::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZELF, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_AZELF
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_M4CaughtAzelf
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_M4CaughtAzelf::
	setflag FLAG_CITIES_M4_AZELF_CAUGHT
	release
	end

@ -- The inscriptions --

Cities_EventScript_M4InscriptionMind::
	msgbox Cities_Text_M4InscriptionMind, MSGBOX_SIGN
	end

Cities_EventScript_M4InscriptionHeart::
	msgbox Cities_Text_M4InscriptionHeart, MSGBOX_SIGN
	end

Cities_EventScript_M4InscriptionWill::
	msgbox Cities_Text_M4InscriptionWill, MSGBOX_SIGN
	end

@ -- Text --

Cities_Text_M4KeeperIntro:
	.string "You carry seven BADGES into this\n"
	.string "old mountain. Then you should\l"
	.string "hear its story.\p"
	.string "When the crater rose from the\n"
	.string "sea, three lights followed the\l"
	.string "fire down into the stone.\p"
	.string "A light of MIND. A light of\n"
	.string "HEART. A light of WILL.\p"
	.string "My family has kept their doors\n"
	.string "shut for a hundred years.$"

Cities_Text_M4KeeperOpens:
	.string "…But doors are meant to open.\p"
	.string "Go inside. In the first cave,\n"
	.string "follow the right-hand wall to\l"
	.string "the far corner.\p"
	.string "The wall has already parted for\n"
	.string "you.\p"
	.string "They've waited long enough for\n"
	.string "a visitor.$"

Cities_Text_M4KeeperProgress:
	.string "The three lights are patient.\n"
	.string "They have been for ages.\p"
	.string "The way in is the far right\n"
	.string "corner of the first cave. One\l"
	.string "chamber leads to the next.$"

Cities_Text_M4KeeperThanks:
	.string "Mind, heart, and will…\n"
	.string "You carry all three now.\p"
	.string "Treat them as one, and they will\n"
	.string "treat you the same.$"

Cities_Text_M4KeeperAfter:
	.string "The mountain feels lighter.\n"
	.string "Or maybe that's just me.$"

Cities_Text_M4PassageSteps:
	.string "The parted wall breathes cool\n"
	.string "air. Steps lead down…$"

Cities_Text_M4InscriptionMind:
	.string "“Here rests the light of MIND.\p"
	.string "It remembers every beginning,\n"
	.string "including yours.”$"

Cities_Text_M4InscriptionHeart:
	.string "“Here rests the light of HEART.\p"
	.string "It felt the mountain's first\n"
	.string "warmth, and kept it.”$"

Cities_Text_M4InscriptionWill:
	.string "“Here rests the light of WILL.\p"
	.string "It chose that life should stay.\n"
	.string "It chooses still.”$"
