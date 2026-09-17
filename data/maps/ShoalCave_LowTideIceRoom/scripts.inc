ShoalCave_LowTideIceRoom_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ShoalCave_LowTideIceRoom_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, ShoalCave_LowTideIceRoom_OnResume
	.byte 0

ShoalCave_LowTideIceRoom_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

ShoalCave_LowTideIceRoom_OnTransition:
	call ShoalCave_LowTideIceRoom_EventScript_UpdateEeveeTrainerGlaceon
	call Cities_EventScript_UpdateM1Articuno
	end


@ Cities of Emerald (GDD 4.3): Eeveelution trainer (Glaceon), roster approved 2026-09-16.
ShoalCave_LowTideIceRoom_EventScript_UpdateEeveeTrainerGlaceon::
	setflag FLAG_CITIES_HIDE_EEVEE_TRAINER_GLACEON
	goto_if_unset FLAG_BADGE07_GET, ShoalCave_LowTideIceRoom_EventScript_UpdateEeveeTrainerGlaceon_Done
	clearflag FLAG_CITIES_HIDE_EEVEE_TRAINER_GLACEON
ShoalCave_LowTideIceRoom_EventScript_UpdateEeveeTrainerGlaceon_Done:
	return

ShoalCave_LowTideIceRoom_EventScript_EeveeTrainerGlaceon::
	trainerbattle_single TRAINER_CITIES_EEVEE_GLACEON, ShoalCave_LowTideIceRoom_Text_EeveeGlaceonIntro, ShoalCave_LowTideIceRoom_Text_EeveeGlaceonDefeat, ShoalCave_LowTideIceRoom_EventScript_EeveeTrainerGlaceon_Victory
	lock
	faceplayer
	goto_if_unset FLAG_CITIES_EEVEE_STONE_ICE_AWARDED, ShoalCave_LowTideIceRoom_EventScript_EeveeTrainerGlaceon_TryGive
	msgbox ShoalCave_LowTideIceRoom_Text_EeveeGlaceonChat, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideIceRoom_EventScript_EeveeTrainerGlaceon_Victory::
	msgbox ShoalCave_LowTideIceRoom_Text_EeveeGlaceonReward, MSGBOX_DEFAULT
	goto ShoalCave_LowTideIceRoom_EventScript_EeveeTrainerGlaceon_TryGive

ShoalCave_LowTideIceRoom_EventScript_EeveeTrainerGlaceon_TryGive::
	giveitem ITEM_ICE_STONE
	goto_if_eq VAR_RESULT, FALSE, ShoalCave_LowTideIceRoom_EventScript_EeveeTrainerGlaceon_BagFull
	setflag FLAG_CITIES_EEVEE_STONE_ICE_AWARDED
	msgbox ShoalCave_LowTideIceRoom_Text_EeveeGlaceonEnjoy, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideIceRoom_EventScript_EeveeTrainerGlaceon_BagFull::
	msgbox ShoalCave_LowTideIceRoom_Text_EeveeGlaceonBagFull, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideIceRoom_Text_EeveeGlaceonIntro:
	.string "You came through all that ice?\n"
	.string "Then you've earned a battle!$"

ShoalCave_LowTideIceRoom_Text_EeveeGlaceonDefeat:
	.string "Cool under pressure. I like it.$"

ShoalCave_LowTideIceRoom_Text_EeveeGlaceonReward:
	.string "Take this Ice Stone from the\n"
	.string "deepest part of the cave.\p"
	.string "Glaceon will glitter like fresh\n"
	.string "snow.$"

ShoalCave_LowTideIceRoom_Text_EeveeGlaceonEnjoy:
	.string "Keep the Ice Stone cool.\n"
	.string "It likes it that way.$"

ShoalCave_LowTideIceRoom_Text_EeveeGlaceonChat:
	.string "Shoal Cave's ice room is the\n"
	.string "only place I feel at home.$"

ShoalCave_LowTideIceRoom_Text_EeveeGlaceonBagFull:
	.string "Your Bag is full. Come back for\n"
	.string "the stone later!$"
