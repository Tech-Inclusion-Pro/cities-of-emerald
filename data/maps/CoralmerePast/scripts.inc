@ Cities of Emerald — Task 12.4 (GDD 7.2): Coralmere, the day before.
@ The living counterpart of every ruin readable, at the same spot.
@ Reached only through V4's time rift (12.5 warps the player in and
@ out). Nobody here has a name, and nobody foreshadows.
CoralmerePast_MapScripts::
	.byte 0

CoralmerePast_EventScript_NetMender::
	msgbox CoralmerePast_Text_NetMender, MSGBOX_NPC
	end

CoralmerePast_EventScript_Baker::
	msgbox CoralmerePast_Text_Baker, MSGBOX_NPC
	end

CoralmerePast_EventScript_Kid1::
	msgbox CoralmerePast_Text_Kid1, MSGBOX_NPC
	end

CoralmerePast_EventScript_Kid2::
	msgbox CoralmerePast_Text_Kid2, MSGBOX_NPC
	end

CoralmerePast_EventScript_Elder::
	msgbox CoralmerePast_Text_Elder, MSGBOX_NPC
	end

CoralmerePast_EventScript_FisherHusband::
	msgbox CoralmerePast_Text_FisherHusband, MSGBOX_NPC
	end

CoralmerePast_EventScript_FisherWife::
	msgbox CoralmerePast_Text_FisherWife, MSGBOX_NPC
	end

CoralmerePast_EventScript_TownSign::
	msgbox CoralmerePast_Text_TownSign, MSGBOX_SIGN
	end

CoralmerePast_EventScript_BellTower::
	msgbox CoralmerePast_Text_BellTower, MSGBOX_SIGN
	end

CoralmerePast_EventScript_Lintel::
	msgbox CoralmerePast_Text_Lintel, MSGBOX_SIGN
	end

CoralmerePast_EventScript_Hearth::
	msgbox CoralmerePast_Text_Hearth, MSGBOX_SIGN
	end

CoralmerePast_EventScript_Barometer::
	msgbox CoralmerePast_Text_Barometer, MSGBOX_SIGN
	end

CoralmerePast_Text_NetMender:
	.string "Third net this week!\n"
	.string "The fish are winning.\p"
	.string "That's fine by me.\n"
	.string "It means there are plenty of fish.$"

CoralmerePast_Text_Baker:
	.string "Fresh bread, and it's going fast!\p"
	.string "The secret is the sea air.\n"
	.string "Everything rises better\l"
	.string "by the water.$"

CoralmerePast_Text_Kid1:
	.string "First one to ring the bell gets\n"
	.string "the biggest roll!\p"
	.string "No fair, you got a head start!$"

CoralmerePast_Text_Kid2:
	.string "Four rings today! That's a record.\p"
	.string "The whole village can hear it.\n"
	.string "That's the best part.$"

CoralmerePast_Text_Elder:
	.string "My knees say rain is coming.\n"
	.string "The barometer says FAIR.\p"
	.string "I've learned to trust the\n"
	.string "barometer.\p"
	.string "A young researcher checks it\n"
	.string "every week without fail.$"

CoralmerePast_Text_FisherHusband:
	.string "We're painting the boat blue\n"
	.string "this year.\p"
	.string "She says green. We'll end up\n"
	.string "with both, like always.$"

CoralmerePast_Text_FisherWife:
	.string "Green keeps better in salt air.\n"
	.string "He knows I'm right.\p"
	.string "Forty years, and he still argues\n"
	.string "just to keep me company.$"

CoralmerePast_Text_TownSign:
	.string "CORALMERE\p"
	.string "“May every boat come home.”$"

CoralmerePast_Text_BellTower:
	.string "The bell rope sways in the\n"
	.string "doorway.\p"
	.string "A chalk scoreboard leans on\n"
	.string "the wall…\p"
	.string "Today the children have rung\n"
	.string "the bell four times.$"

CoralmerePast_Text_Lintel:
	.string "The door's lintel is freshly\n"
	.string "carved…\p"
	.string "A wave, a bell, and two small\n"
	.string "fish.\p"
	.string "Pale chips of stone still dust\n"
	.string "the doorstep.$"

CoralmerePast_Text_Hearth:
	.string "Through the open door, a pot of\n"
	.string "stew keeps itself busy over a\l"
	.string "low fire.\p"
	.string "Someone will be back for it soon.$"

CoralmerePast_Text_Barometer:
	.string "A brass barometer hangs on its\n"
	.string "stone post at the head of the\l"
	.string "dock.\p"
	.string "Its case is polished from years\n"
	.string "of hands.\p"
	.string "The needle points to FAIR.$"
