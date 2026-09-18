EverGrandeCity_PokemonLeague_1F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, EverGrandeCity_PokemonLeague_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

EverGrandeCity_PokemonLeague_1F_OnTransition:
	call EverGrandeCity_PokemonLeague_1F_EventScript_UpdateCitiesOfficial
	setrespawn HEAL_LOCATION_EVER_GRANDE_CITY_POKEMON_LEAGUE
	setflag FLAG_LANDMARK_POKEMON_LEAGUE
	call_if_unset FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GuardsBlockDoor::
	setobjectxyperm LOCALID_LEAGUE_GUARD_1, 9, 2
	setobjectxyperm LOCALID_LEAGUE_GUARD_2, 10, 2
	return

EverGrandeCity_PokemonLeague_1F_EventScript_Nurse::
	setvar VAR_0x800B, LOCALID_LEAGUE_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

EverGrandeCity_PokemonLeague_1F_EventScript_Clerk::
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart EverGrandeCity_PokemonLeague_1F_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
EverGrandeCity_PokemonLeague_1F_Pokemart:
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_RESTORE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	pokemartlistend

@ The door guards only check for FLAG_BADGE06_GET because Winonas badge is the only one that can be skipped
@ Its assumed the player has the remaining badges
EverGrandeCity_PokemonLeague_1F_EventScript_DoorGuard::
	lockall
	goto_if_set FLAG_ENTERED_ELITE_FOUR, EverGrandeCity_PokemonLeague_1F_EventScript_GoForth
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_ge VAR_TEMP_0, 11, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight
	call_if_le VAR_TEMP_0, 8, EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft
	message EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges
	waitmessage
	delay 120
	goto_if_unset FLAG_BADGE06_GET, EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges
	closemessage
	applymovement LOCALID_LEAGUE_GUARD_1, EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay
	applymovement LOCALID_LEAGUE_GUARD_2, EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay
	waitmovement 0
	delay 10
	playfanfare MUS_OBTAIN_BADGE
	message EverGrandeCity_PokemonLeague_1F_Text_GoForth
	waitmessage
	waitfanfare
	closemessage
	copyobjectxytoperm LOCALID_LEAGUE_GUARD_1
	copyobjectxytoperm LOCALID_LEAGUE_GUARD_2
	setflag FLAG_ENTERED_ELITE_FOUR
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromRight::
	applymovement LOCALID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_PlayerMoveToFrontFromLeft::
	applymovement LOCALID_PLAYER, EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft
	waitmovement 0
	return

EverGrandeCity_PokemonLeague_1F_EventScript_NotAllBadges::
	playse SE_FAILURE
	msgbox EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges, MSGBOX_DEFAULT
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_EventScript_GoForth::
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox EverGrandeCity_PokemonLeague_1F_Text_GoForth, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromRight:
	walk_down
	walk_left
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_MoveToFrontFromLeft:
	walk_down
	walk_right
	walk_in_place_faster_up
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_LeftGuardOutOfWay:
	walk_left
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Movement_RightGuardOutOfWay:
	walk_right
	walk_in_place_faster_down
	step_end

EverGrandeCity_PokemonLeague_1F_Text_MustHaveAllGymBadges:
	.string "Beyond this point, only those TRAINERS\n"
	.string "who have collected all the GYM BADGES\l"
	.string "are permitted to enter.\p"
	.string "TRAINER, let us confirm that you have\n"
	.string "all the GYM BADGES.$"

EverGrandeCity_PokemonLeague_1F_Text_HaventObtainedAllBadges:
	.string "You haven't obtained all the BADGES.\p"
	.string "If you're bound for the POKéMON\n"
	.string "LEAGUE, you must return with them.$"

EverGrandeCity_PokemonLeague_1F_Text_GoForth:
	.string "TRAINER! Believe in yourself and your\n"
	.string "POKéMON, and go forth!$"


@ Cities of Emerald (GDD 8.1, Task 7.7): the POKéMON MASTER ceremony.
@ The official appears once the title is earned; the ceremony (and the
@ MASTER BALL) happens once, then the official stays to congratulate.
@ Cities: the official appears once the player is Champion (title
@ defenses are part of the ranking climb), not only at Master.
EverGrandeCity_PokemonLeague_1F_EventScript_UpdateCitiesOfficial::
	goto_if_set FLAG_SYS_GAME_CLEAR, EverGrandeCity_PokemonLeague_1F_EventScript_ShowCitiesOfficial
	setflag FLAG_CITIES_HIDE_LEAGUE_OFFICIAL
	return

EverGrandeCity_PokemonLeague_1F_EventScript_ShowCitiesOfficial::
	clearflag FLAG_CITIES_HIDE_LEAGUE_OFFICIAL
	return

EverGrandeCity_PokemonLeague_1F_EventScript_CitiesOfficial::
	lock
	faceplayer
	goto_if_set FLAG_CITIES_MASTER_CEREMONY_DONE, EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseOffer
	goto_if_unset FLAG_CITIES_POKEMON_MASTER, EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseOffer
	msgbox EverGrandeCity_PokemonLeague_1F_Text_CitiesCeremony, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_SYMBOL
	waitfanfare
	msgbox EverGrandeCity_PokemonLeague_1F_Text_CitiesCeremonyTitle, MSGBOX_DEFAULT
	giveitem ITEM_MASTER_BALL
	goto_if_eq VAR_RESULT, FALSE, EverGrandeCity_PokemonLeague_1F_EventScript_CitiesBagFull
	setflag FLAG_CITIES_MASTER_CEREMONY_DONE
	msgbox EverGrandeCity_PokemonLeague_1F_Text_CitiesCeremonyClose, MSGBOX_DEFAULT
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseOffer

EverGrandeCity_PokemonLeague_1F_EventScript_CitiesBagFull::
	msgbox EverGrandeCity_PokemonLeague_1F_Text_CitiesBagFull, MSGBOX_DEFAULT
	release
	end

@ -- Title defense (GDD 7.4): re-fight a ranked challenger for points --

EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseOffer::
	msgbox EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseDone
	message EverGrandeCity_PokemonLeague_1F_Text_TitleDefensePick
	waitmessage
	multichoice 0, 0, MULTI_CITIES_TITLE_DEFENSE, FALSE
	switch VAR_RESULT
	case 0, EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseBram
	case 1, EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseIlaria
	case 2, EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseCorsen
	case 3, EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseVesper
	case 4, EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseEliteFour
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseDone

EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseEliteFour::
	random 4
	switch VAR_RESULT
	case 0, EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseSidney
	case 1, EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefensePhoebe
	case 2, EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseGlacia
	case 3, EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseDrake
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseDone

@ Each challenger: clear its defeated flag so the battle triggers, arm
@ the scoring flag, fight, then re-set the flag so world state is
@ unchanged (beaten) whether the defense was won or lost.
EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseBram::
	cleartrainerflag TRAINER_CITIES_CHALLENGER_BRAM
	setflag FLAG_CITIES_TITLE_DEFENSE_ACTIVE
	trainerbattle_no_intro TRAINER_CITIES_CHALLENGER_BRAM, EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseLose
	settrainerflag TRAINER_CITIES_CHALLENGER_BRAM
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseResult

EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseIlaria::
	cleartrainerflag TRAINER_CITIES_CHALLENGER_ILARIA
	setflag FLAG_CITIES_TITLE_DEFENSE_ACTIVE
	trainerbattle_no_intro TRAINER_CITIES_CHALLENGER_ILARIA, EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseLose
	settrainerflag TRAINER_CITIES_CHALLENGER_ILARIA
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseResult

EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseCorsen::
	cleartrainerflag TRAINER_CITIES_CHALLENGER_CORSEN
	setflag FLAG_CITIES_TITLE_DEFENSE_ACTIVE
	trainerbattle_no_intro TRAINER_CITIES_CHALLENGER_CORSEN, EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseLose
	settrainerflag TRAINER_CITIES_CHALLENGER_CORSEN
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseResult

EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseVesper::
	cleartrainerflag TRAINER_CITIES_CHALLENGER_VESPER
	setflag FLAG_CITIES_TITLE_DEFENSE_ACTIVE
	trainerbattle_no_intro TRAINER_CITIES_CHALLENGER_VESPER, EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseLose
	settrainerflag TRAINER_CITIES_CHALLENGER_VESPER
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseResult

EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseSidney::
	cleartrainerflag TRAINER_SIDNEY
	setflag FLAG_CITIES_TITLE_DEFENSE_ACTIVE
	trainerbattle_no_intro TRAINER_SIDNEY, EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseLose
	settrainerflag TRAINER_SIDNEY
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseResult

EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefensePhoebe::
	cleartrainerflag TRAINER_PHOEBE
	setflag FLAG_CITIES_TITLE_DEFENSE_ACTIVE
	trainerbattle_no_intro TRAINER_PHOEBE, EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseLose
	settrainerflag TRAINER_PHOEBE
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseResult

EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseGlacia::
	cleartrainerflag TRAINER_GLACIA
	setflag FLAG_CITIES_TITLE_DEFENSE_ACTIVE
	trainerbattle_no_intro TRAINER_GLACIA, EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseLose
	settrainerflag TRAINER_GLACIA
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseResult

EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseDrake::
	cleartrainerflag TRAINER_DRAKE
	setflag FLAG_CITIES_TITLE_DEFENSE_ACTIVE
	trainerbattle_no_intro TRAINER_DRAKE, EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseLose
	settrainerflag TRAINER_DRAKE
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseResult

EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseResult::
	clearflag FLAG_CITIES_TITLE_DEFENSE_ACTIVE
	closemessage
	msgbox EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseAfter, MSGBOX_DEFAULT
	goto EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseOffer

EverGrandeCity_PokemonLeague_1F_EventScript_TitleDefenseDone::
	msgbox EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseDone, MSGBOX_DEFAULT
	release
	end

EverGrandeCity_PokemonLeague_1F_Text_CitiesCeremony:
	.string "{PLAYER}! On behalf of the entire\n"
	.string "POKéMON LEAGUE, welcome.\p"
	.string "You have reached No. 1 in the national\n"
	.string "rankings.\p"
	.string "No trainer in HOENN stands above\n"
	.string "you. Not even the CHAMPION.$"

EverGrandeCity_PokemonLeague_1F_Text_CitiesCeremonyTitle:
	.string "By the authority of the POKéMON\n"
	.string "LEAGUE, I name you…\p"
	.string "POKéMON MASTER!$"

EverGrandeCity_PokemonLeague_1F_Text_CitiesCeremonyClose:
	.string "That MASTER BALL is a gift from all\n"
	.string "of us.\p"
	.string "Your title is yours for good, no\n"
	.string "matter how the rankings shift.\p"
	.string "Congratulations, MASTER {PLAYER}!$"

EverGrandeCity_PokemonLeague_1F_Text_CitiesBagFull:
	.string "Oh! Your BAG is full.\p"
	.string "Come back for your gift when you've\n"
	.string "made some room.$"

EverGrandeCity_PokemonLeague_1F_Text_CitiesOfficialAfter:
	.string "It's an honor, MASTER {PLAYER}.\p"
	.string "The whole region looks up to you.$"

EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseOffer:
	.string "A title is not held once. It is\n"
	.string "held again, and again.\p"
	.string "Care to defend your standing\n"
	.string "against a ranked challenger?$"

EverGrandeCity_PokemonLeague_1F_Text_TitleDefensePick:
	.string "Who will you face?$"

EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseLose:
	.string "Your title wavers! Rest, and\n"
	.string "defend it again when you're ready.$"

EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseAfter:
	.string "A defense well fought. The\n"
	.string "rankings have taken note.$"

EverGrandeCity_PokemonLeague_1F_Text_TitleDefenseDone:
	.string "Your standing is safe for today.\n"
	.string "The rankings await your return.$"
