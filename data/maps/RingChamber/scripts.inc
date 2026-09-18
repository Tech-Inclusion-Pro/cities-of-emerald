@ Cities of Emerald — the Ring Chamber (Hoopa, Task 13.1). A strange
@ ring appears in the Trick House entrance postgame; through it lies
@ this chamber. A plaque names the order the rings answer to; stepping
@ them SUN -> SEA -> SKY opens the way to Hoopa (L70) and the Prison
@ Bottle. The order is enforced by the coord events' var gating, so it
@ cannot be brute-forced or desynced. All logic in cities_mythic.inc.
RingChamber_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RingChamber_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, RingChamber_OnResume
	.byte 0

RingChamber_OnTransition:
	setvar VAR_TEMP_1, 0
	call Cities_EventScript_UpdateRingChamber
	end

RingChamber_OnResume:
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, Cities_EventScript_M1TryRemoveCaughtBird
	end
