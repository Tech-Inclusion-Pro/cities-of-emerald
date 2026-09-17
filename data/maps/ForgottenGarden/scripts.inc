@ Cities of Emerald — Forgotten Garden (H2a + H2b, GDD 6.6, approved
@ 2026-09-17). Walled garden past Oldale: no wild encounters. Reached
@ only by the gardener's walk-in; the south gap walks back out. Both
@ questlines share the map: Treasures of Ruin at the north stelae,
@ the Loyal Three in the south grove, Ogerpon at the mask shrine
@ once the three are caught.

ForgottenGarden_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ForgottenGarden_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, ForgottenGarden_OnResume
	.byte 0

ForgottenGarden_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end

ForgottenGarden_OnTransition:
	call Cities_EventScript_UpdateH2AWoChien
	call Cities_EventScript_UpdateH2AChienPao
	call Cities_EventScript_UpdateH2ATingLu
	call Cities_EventScript_UpdateH2AChiYu
	call Cities_EventScript_UpdateH2BOkidogi
	call Cities_EventScript_UpdateH2BMunkidori
	call Cities_EventScript_UpdateH2BFezandipiti
	call Cities_EventScript_UpdateH2BOgerpon
	end
