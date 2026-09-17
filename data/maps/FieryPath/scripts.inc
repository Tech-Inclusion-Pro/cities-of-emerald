FieryPath_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FieryPath_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, FieryPath_OnResume
	.byte 0

FieryPath_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

FieryPath_OnTransition:
	call_if_unset FLAG_LANDMARK_FIERY_PATH, FieryPath_EventScript_MoveScottToFallarbor
	setflag FLAG_LANDMARK_FIERY_PATH
	call FieryPath_EventScript_UpdateEeveeTrainerFlareon
	call Cities_EventScript_UpdateM1Npcs
	call Cities_EventScript_UpdateM1Moltres
	call Cities_EventScript_UpdateM1PGMoltres
	end

FieryPath_EventScript_MoveScottToFallarbor::
	setflag FLAG_HIDE_VERDANTURF_TOWN_SCOTT
	clearflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	return


@ Cities of Emerald (GDD 4.3): Eeveelution trainer (Flareon), roster approved 2026-09-16.
FieryPath_EventScript_UpdateEeveeTrainerFlareon::
	setflag FLAG_CITIES_HIDE_EEVEE_TRAINER_FLAREON
	goto_if_unset FLAG_BADGE04_GET, FieryPath_EventScript_UpdateEeveeTrainerFlareon_Done
	clearflag FLAG_CITIES_HIDE_EEVEE_TRAINER_FLAREON
FieryPath_EventScript_UpdateEeveeTrainerFlareon_Done:
	return

FieryPath_EventScript_EeveeTrainerFlareon::
	trainerbattle_single TRAINER_CITIES_EEVEE_FLAREON, FieryPath_Text_EeveeFlareonIntro, FieryPath_Text_EeveeFlareonDefeat, FieryPath_EventScript_EeveeTrainerFlareon_Victory
	lock
	faceplayer
	goto_if_unset FLAG_CITIES_EEVEE_STONE_FIRE_AWARDED, FieryPath_EventScript_EeveeTrainerFlareon_TryGive
	msgbox FieryPath_Text_EeveeFlareonChat, MSGBOX_DEFAULT
	release
	end

FieryPath_EventScript_EeveeTrainerFlareon_Victory::
	msgbox FieryPath_Text_EeveeFlareonReward, MSGBOX_DEFAULT
	goto FieryPath_EventScript_EeveeTrainerFlareon_TryGive

FieryPath_EventScript_EeveeTrainerFlareon_TryGive::
	giveitem ITEM_FIRE_STONE
	goto_if_eq VAR_RESULT, FALSE, FieryPath_EventScript_EeveeTrainerFlareon_BagFull
	setflag FLAG_CITIES_EEVEE_STONE_FIRE_AWARDED
	msgbox FieryPath_Text_EeveeFlareonEnjoy, MSGBOX_DEFAULT
	release
	end

FieryPath_EventScript_EeveeTrainerFlareon_BagFull::
	msgbox FieryPath_Text_EeveeFlareonBagFull, MSGBOX_DEFAULT
	release
	end

FieryPath_Text_EeveeFlareonIntro:
	.string "This heat is nothing! Flareon\n"
	.string "and I live for the fire!$"

FieryPath_Text_EeveeFlareonDefeat:
	.string "Burned out…$"

FieryPath_Text_EeveeFlareonReward:
	.string "You fought with heart.\p"
	.string "Take this Fire Stone, warm from\n"
	.string "the mountain itself.$"

FieryPath_Text_EeveeFlareonEnjoy:
	.string "Flareon's flame burns brightest\n"
	.string "for a trusted friend.$"

FieryPath_Text_EeveeFlareonChat:
	.string "Mt. Chimney's warmth keeps our\n"
	.string "training going all year.$"

FieryPath_Text_EeveeFlareonBagFull:
	.string "Your Bag is full. Come back for\n"
	.string "the stone later!$"
