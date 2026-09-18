MtPyre_Exterior_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, MtPyre_Exterior_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, MtPyre_Exterior_OnTransition
	.byte 0

MtPyre_Exterior_OnTransition:
	call Cities_EventScript_UpdateV3MtPyre
	call MtPyre_Exterior_EventScript_CheckEnterFromSummit
	call MtPyre_Exterior_EventScript_UpdateEeveeTrainerUmbreon
	end

MtPyre_Exterior_EventScript_CheckEnterFromSummit::
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	goto_if_lt VAR_TEMP_1, 12, MtPyre_Exterior_EventScript_EnterFromSummit
	return

MtPyre_Exterior_EventScript_EnterFromSummit::
	setweather WEATHER_FOG_HORIZONTAL
	return

MtPyre_Exterior_EventScript_FogTrigger::
	setweather WEATHER_FOG_HORIZONTAL
	doweather
	end

MtPyre_Exterior_EventScript_SunTrigger::
	setweather WEATHER_SUNNY
	doweather
	end


@ Cities of Emerald (GDD 4.3): Eeveelution trainer (Umbreon), roster approved 2026-09-16.
MtPyre_Exterior_EventScript_UpdateEeveeTrainerUmbreon::
	setflag FLAG_CITIES_HIDE_EEVEE_TRAINER_UMBREON
	goto_if_unset FLAG_BADGE07_GET, MtPyre_Exterior_EventScript_UpdateEeveeTrainerUmbreon_Done
	special Script_CitiesIsNight
	goto_if_eq VAR_RESULT, FALSE, MtPyre_Exterior_EventScript_UpdateEeveeTrainerUmbreon_Done
	clearflag FLAG_CITIES_HIDE_EEVEE_TRAINER_UMBREON
MtPyre_Exterior_EventScript_UpdateEeveeTrainerUmbreon_Done:
	return

MtPyre_Exterior_EventScript_EeveeTrainerUmbreon::
	trainerbattle_single TRAINER_CITIES_EEVEE_UMBREON, MtPyre_Exterior_Text_EeveeUmbreonIntro, MtPyre_Exterior_Text_EeveeUmbreonDefeat, MtPyre_Exterior_EventScript_EeveeTrainerUmbreon_Victory
	lock
	faceplayer
	msgbox MtPyre_Exterior_Text_EeveeUmbreonChat, MSGBOX_DEFAULT
	release
	end

MtPyre_Exterior_EventScript_EeveeTrainerUmbreon_Victory::
	msgbox MtPyre_Exterior_Text_EeveeUmbreonReward, MSGBOX_DEFAULT
	release
	end

MtPyre_Exterior_Text_EeveeUmbreonIntro:
	.string "The moon is watching. So is my\n"
	.string "Umbreon. Shall we?$"

MtPyre_Exterior_Text_EeveeUmbreonDefeat:
	.string "Even shadows bow sometimes.$"

MtPyre_Exterior_Text_EeveeUmbreonReward:
	.string "Umbreon appears only under the\n"
	.string "moon.\p"
	.string "Raise your Eevee with care.\p"
	.string "When night falls and your bond\n"
	.string "is deep, it will become Umbreon.$"

MtPyre_Exterior_Text_EeveeUmbreonChat:
	.string "Moonlight suits Umbreon.\n"
	.string "It suits me, too.$"

MtPyre_Exterior_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end
