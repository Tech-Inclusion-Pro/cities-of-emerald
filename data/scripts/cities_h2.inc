@ Cities of Emerald — H2a "The Chained Ruin" + H2b "The Mask in the
@ Grove" (GDD 6.6, split approved 2026-09-17). One shared hidden area
@ (the Forgotten Garden past Oldale), one gardener guide, two
@ questlines. Treasures of Ruin = old grudges laid down, not
@ monsters; the Loyal Three are the false heroes, and Ogerpon comes
@ out of hiding once they are gone. Fixed 65 tier; postgame always
@ obeys. No rewards (GDD).

@ -- Visibility --

Cities_EventScript_UpdateH2Gardener::
	goto_if_unset FLAG_SYS_GAME_CLEAR, Cities_EventScript_HideH2Gardener
	clearflag FLAG_CITIES_HIDE_H2_GARDENER
	return

Cities_EventScript_HideH2Gardener::
	setflag FLAG_CITIES_HIDE_H2_GARDENER
	return

Cities_EventScript_UpdateH2AWoChien::
	goto_if_set FLAG_CITIES_H2A_WOCHIEN_CAUGHT, Cities_EventScript_HideH2AWoChien
	clearflag FLAG_CITIES_HIDE_H2A_WOCHIEN
	return

Cities_EventScript_HideH2AWoChien::
	setflag FLAG_CITIES_HIDE_H2A_WOCHIEN
	return

Cities_EventScript_UpdateH2AChienPao::
	goto_if_set FLAG_CITIES_H2A_CHIENPAO_CAUGHT, Cities_EventScript_HideH2AChienPao
	clearflag FLAG_CITIES_HIDE_H2A_CHIENPAO
	return

Cities_EventScript_HideH2AChienPao::
	setflag FLAG_CITIES_HIDE_H2A_CHIENPAO
	return

Cities_EventScript_UpdateH2ATingLu::
	goto_if_set FLAG_CITIES_H2A_TINGLU_CAUGHT, Cities_EventScript_HideH2ATingLu
	clearflag FLAG_CITIES_HIDE_H2A_TINGLU
	return

Cities_EventScript_HideH2ATingLu::
	setflag FLAG_CITIES_HIDE_H2A_TINGLU
	return

Cities_EventScript_UpdateH2AChiYu::
	goto_if_set FLAG_CITIES_H2A_CHIYU_CAUGHT, Cities_EventScript_HideH2AChiYu
	clearflag FLAG_CITIES_HIDE_H2A_CHIYU
	return

Cities_EventScript_HideH2AChiYu::
	setflag FLAG_CITIES_HIDE_H2A_CHIYU
	return

Cities_EventScript_UpdateH2BOkidogi::
	goto_if_set FLAG_CITIES_H2B_OKIDOGI_CAUGHT, Cities_EventScript_HideH2BOkidogi
	clearflag FLAG_CITIES_HIDE_H2B_OKIDOGI
	return

Cities_EventScript_HideH2BOkidogi::
	setflag FLAG_CITIES_HIDE_H2B_OKIDOGI
	return

Cities_EventScript_UpdateH2BMunkidori::
	goto_if_set FLAG_CITIES_H2B_MUNKIDORI_CAUGHT, Cities_EventScript_HideH2BMunkidori
	clearflag FLAG_CITIES_HIDE_H2B_MUNKIDORI
	return

Cities_EventScript_HideH2BMunkidori::
	setflag FLAG_CITIES_HIDE_H2B_MUNKIDORI
	return

Cities_EventScript_UpdateH2BFezandipiti::
	goto_if_set FLAG_CITIES_H2B_FEZANDIPITI_CAUGHT, Cities_EventScript_HideH2BFezandipiti
	clearflag FLAG_CITIES_HIDE_H2B_FEZANDIPITI
	return

Cities_EventScript_HideH2BFezandipiti::
	setflag FLAG_CITIES_HIDE_H2B_FEZANDIPITI
	return

@ The masked one comes out only once the false heroes are gone.
Cities_EventScript_UpdateH2BOgerpon::
	goto_if_unset FLAG_CITIES_H2B_OKIDOGI_CAUGHT, Cities_EventScript_HideH2BOgerpon
	goto_if_unset FLAG_CITIES_H2B_MUNKIDORI_CAUGHT, Cities_EventScript_HideH2BOgerpon
	goto_if_unset FLAG_CITIES_H2B_FEZANDIPITI_CAUGHT, Cities_EventScript_HideH2BOgerpon
	goto_if_set FLAG_CITIES_H2B_OGERPON_CAUGHT, Cities_EventScript_HideH2BOgerpon
	clearflag FLAG_CITIES_HIDE_H2B_OGERPON
	return

Cities_EventScript_HideH2BOgerpon::
	setflag FLAG_CITIES_HIDE_H2B_OGERPON
	return

@ -- The gardener (Oldale, postgame) --

Cities_EventScript_H2Gardener::
	lock
	faceplayer
	goto_if_eq VAR_CITIES_H2A_STATE, 0, Cities_EventScript_H2GardenerIntro
	setvar VAR_0x8004, 16 @ CITIES_ARC_H2A
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H2GardenerCheckB
	goto_if_ne VAR_CITIES_H2A_STATE, 2, Cities_EventScript_H2GardenerWrapA
Cities_EventScript_H2GardenerCheckB::
	setvar VAR_0x8004, 17 @ CITIES_ARC_H2B
	specialvar VAR_RESULT, Script_CitiesArcAllCaught
	goto_if_eq VAR_RESULT, FALSE, Cities_EventScript_H2GardenerVisit
	goto_if_ne VAR_CITIES_H2B_STATE, 2, Cities_EventScript_H2GardenerWrapB
Cities_EventScript_H2GardenerVisit::
	goto_if_ne VAR_CITIES_H2A_STATE, 2, Cities_EventScript_H2GardenerRepeat
	goto_if_ne VAR_CITIES_H2B_STATE, 2, Cities_EventScript_H2GardenerRepeat
	msgbox Cities_Text_H2GardenerAfterBoth, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H2GardenerTravel
	release
	end

Cities_EventScript_H2GardenerRepeat::
	msgbox Cities_Text_H2GardenerRepeat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H2GardenerTravel
	msgbox Cities_Text_H2GardenerLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H2GardenerIntro::
	msgbox Cities_Text_H2GardenerIntro, MSGBOX_DEFAULT
	setvar VAR_CITIES_H2A_STATE, 1
	setvar VAR_CITIES_H2B_STATE, 1
	msgbox Cities_Text_H2GardenerOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Cities_EventScript_H2GardenerTravel
	msgbox Cities_Text_H2GardenerLater, MSGBOX_DEFAULT
	release
	end

Cities_EventScript_H2GardenerTravel::
	msgbox Cities_Text_H2GardenerLead, MSGBOX_DEFAULT
	closemessage
	warp MAP_FORGOTTEN_GARDEN, 10, 16
	waitstate
	release
	end

Cities_EventScript_H2GardenerWrapA::
	msgbox Cities_Text_H2GardenerWrapA, MSGBOX_DEFAULT
	setvar VAR_CITIES_H2A_STATE, 2
	release
	end

Cities_EventScript_H2GardenerWrapB::
	msgbox Cities_Text_H2GardenerWrapB, MSGBOX_DEFAULT
	setvar VAR_CITIES_H2B_STATE, 2
	release
	end

@ -- Leaving the garden (south gap trigger tiles) --

Cities_EventScript_H2GardenExit::
	lockall
	warp MAP_OLDALE_TOWN, 16, 13
	waitstate
	releaseall
	end

@ -- Stelae and shrine (bg signs) --

Cities_EventScript_H2AStela1::
	msgbox Cities_Text_H2AStela1, MSGBOX_SIGN
	end

Cities_EventScript_H2AStela2::
	msgbox Cities_Text_H2AStela2, MSGBOX_SIGN
	end

Cities_EventScript_H2AStela3::
	msgbox Cities_Text_H2AStela3, MSGBOX_SIGN
	end

Cities_EventScript_H2AStela4::
	msgbox Cities_Text_H2AStela4, MSGBOX_SIGN
	end

Cities_EventScript_H2BMaskShrine::
	msgbox Cities_Text_H2BMaskShrine, MSGBOX_SIGN
	end

@ -- The Treasures of Ruin (H2a) --

Cities_EventScript_H2AWoChien::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WO_CHIEN, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_WO_CHIEN
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H2ACaughtWoChien
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H2ACaughtWoChien::
	setflag FLAG_CITIES_H2A_WOCHIEN_CAUGHT
	release
	end

Cities_EventScript_H2AChienPao::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHIEN_PAO, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_CHIEN_PAO
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H2ACaughtChienPao
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H2ACaughtChienPao::
	setflag FLAG_CITIES_H2A_CHIENPAO_CAUGHT
	release
	end

Cities_EventScript_H2ATingLu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_TING_LU, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_TING_LU
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H2ACaughtTingLu
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H2ACaughtTingLu::
	setflag FLAG_CITIES_H2A_TINGLU_CAUGHT
	release
	end

Cities_EventScript_H2AChiYu::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_CHI_YU, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_CHI_YU
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H2ACaughtChiYu
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H2ACaughtChiYu::
	setflag FLAG_CITIES_H2A_CHIYU_CAUGHT
	release
	end

@ -- The Loyal Three and Ogerpon (H2b) --

Cities_EventScript_H2BOkidogi::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_OKIDOGI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_OKIDOGI
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H2BCaughtOkidogi
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H2BCaughtOkidogi::
	setflag FLAG_CITIES_H2B_OKIDOGI_CAUGHT
	release
	end

Cities_EventScript_H2BMunkidori::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_MUNKIDORI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_MUNKIDORI
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H2BCaughtMunkidori
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H2BCaughtMunkidori::
	setflag FLAG_CITIES_H2B_MUNKIDORI_CAUGHT
	release
	end

Cities_EventScript_H2BFezandipiti::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_FEZANDIPITI, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_FEZANDIPITI
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H2BCaughtFezandipiti
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H2BCaughtFezandipiti::
	setflag FLAG_CITIES_H2B_FEZANDIPITI_CAUGHT
	release
	end

Cities_EventScript_H2BOgerpon::
	lock
	faceplayer
	msgbox Cities_Text_H2BOgerponMeets, MSGBOX_DEFAULT
	waitse
	playmoncry SPECIES_OGERPON, CRY_MODE_ENCOUNTER
	delay 40
	waitmoncry
	setvar VAR_0x8004, SPECIES_OGERPON
	special Script_CitiesSetWildLegendary
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	special BattleSetup_StartLegendaryBattle
	waitstate
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_CAUGHT, Cities_EventScript_H2BCaughtOgerpon
	goto Cities_EventScript_LegendWithdrew

Cities_EventScript_H2BCaughtOgerpon::
	setflag FLAG_CITIES_H2B_OGERPON_CAUGHT
	release
	end

@ -- Text --

Cities_Text_H2GardenerIntro:
	.string "Mind the roses. They bite.\p"
	.string "You're the CHAMPION, so I'll\n"
	.string "tell you what I tell nobody:\l"
	.string "there's a garden past this town\l"
	.string "that everyone forgot on purpose.\p"
	.string "Four sealed stones in the north\n"
	.string "courtyard - and the seals rusted\l"
	.string "through years ago.\p"
	.string "And in the south grove, three\n"
	.string "so-called heroes… and one true\l"
	.string "one, still hiding behind a mask.\p"
	.string "Somebody with your patience\n"
	.string "could set all of it right.$"

Cities_Text_H2GardenerOffer:
	.string "The gate's behind my hedge.\n"
	.string "Shall I walk you in?$"

Cities_Text_H2GardenerRepeat:
	.string "Back to the garden?$"

Cities_Text_H2GardenerLater:
	.string "The garden's waited this long.\n"
	.string "It can wait for you.$"

Cities_Text_H2GardenerLead:
	.string "Stay on the paths. And if a\n"
	.string "stone whispers - listen politely,\l"
	.string "then keep walking.$"

Cities_Text_H2GardenerWrapA:
	.string "The courtyard's quiet? All four?\p"
	.string "Old grudges don't want to be\n"
	.string "feared. They want to be faced.\l"
	.string "You did what the seals never\l"
	.string "could.\p"
	.string "It's just a garden again up\n"
	.string "there. Thank you.$"

Cities_Text_H2GardenerWrapB:
	.string "So the masked one finally came\n"
	.string "out - and went with YOU.\p"
	.string "The village called those three\n"
	.string "'the Loyal Three'. Statues and\l"
	.string "everything. But they took what\l"
	.string "wasn't theirs, and the real hero\l"
	.string "hid rather than be called a\l"
	.string "villain.\p"
	.string "It was owed an apology.\n"
	.string "It got a friend instead.\l"
	.string "That's better.$"

Cities_Text_H2GardenerAfterBoth:
	.string "The garden grows honest flowers\n"
	.string "now. Want to visit?$"

Cities_Text_H2AStela1:
	.string "The stone is wrapped in carved\n"
	.string "chains, long rusted through.\p"
	.string "“Here rests an old envy.\n"
	.string "Face it kindly, and it rests\l"
	.string "for good.”$"

Cities_Text_H2AStela2:
	.string "Frost has split the stone from\n"
	.string "crown to base.\p"
	.string "“Here rests an old hatred.\n"
	.string "It is colder than it is cruel.”$"

Cities_Text_H2AStela3:
	.string "The stone leans, as if something\n"
	.string "heavy pressed it for centuries.\p"
	.string "“Here rests an old fear.\n"
	.string "It hides its eyes. Be gentle.”$"

Cities_Text_H2AStela4:
	.string "The stone is warm to the touch.\p"
	.string "“Here rests an old greed.\n"
	.string "It burned for more and was\l"
	.string "never full. Pity it.”$"

Cities_Text_H2BMaskShrine:
	.string "A small shrine, swept clean.\n"
	.string "A carved mask rests on it -\l"
	.string "someone repaints it every year.\p"
	.string "“For the one who was wronged,\n"
	.string "whenever it is ready.”$"

Cities_Text_H2BOgerponMeets:
	.string "The masked one steps out at\n"
	.string "last. It studies you - then\l"
	.string "stamps twice, like an invitation\l"
	.string "to dance.$"
