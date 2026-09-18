# Task 12.4 — Coralmere, The Day Before (outline, for approval)

**Status: APPROVED 2026-09-18 (outline as proposed; music =
Pacifidlog's actual theme, which is MUS_LILYCOVE — the shared
Lilycove/Pacifidlog track). Build notes: the tower and the
barometer's post use the same worn-stone metatile family as the
Route 128 ruins, so the stone is continuous across time; no warp
events — 12.5's V4 script warps by coordinates (street mouth ≈
12,18).** The time-rift version of Coralmere
for V4's centerpiece scene (GDD 7.2: "the player can walk its
streets before the crisis"). This task builds the living village and
its ambient life; the V4 scene itself — the Archivist standing in
the middle of it, the rift closing — is scripted in 12.5. "Kai"
appears nowhere, and no villager is named.

## The idea that holds it together

Every ruin readable in the present map has a living counterpart
here, at the same coordinates. The player who explored the ruins
first will recognize every corner; the player who comes back to the
ruins after V4 will read them completely differently. The stone
survived; the wood did not.

## The map (MAP_CORALMERE_PAST, 24×28)

General + Pacifidlog tilesets. The village core (y0–19) mirrors the
ruins' street plan tile-for-tile; the map extends south with a
shore, a plank dock on posts, and open sea. Coralmere was a village
on the water — which is why the survivors' hints sound like
Pacifidlog, and why the family that speaks his name rebuilt their
lives there.

- **Bell tower** (north, same spot): stone base, and this time the
  readable is alive: "The bell rope sways in the doorway. A chalk
  scoreboard leans on the wall: today the children have rung it
  four times."
- **The square**: the sign whole — "CORALMERE. May every boat come
  home." Market stalls, a bench.
- **The two houses**: the east house's lintel fresh-cut ("the
  carving is new; pale chips of stone still dust the doorstep");
  the west house's hearth warm ("a pot of stew keeps itself busy
  over a low fire. Someone will be back for it soon.")
- **The shore and dock** (new, south): plank walkways on the same
  posts the player saw as worn stumps; moored boats.
- **The harbor barometer** (head of the dock): "A brass barometer
  hangs on its post at the head of the dock. Its case is polished
  from years of hands. The needle points to FAIR." — the same
  instrument the Archivist carries in every scene afterward, and
  the empty bracket at the Weather Institute.

## Ambient villagers (~6, unnamed, warm, ordinary)

A net-mender on the dock; a baker crossing the square; two kids
racing to the bell tower; an elder on the bench who trusts the
barometer over her knees; a fisher couple arguing gently about
paint. Everyday lines only — bread, nets, bells, weather. Nobody
foreshadows. The dread belongs entirely to the player.

## Practical details

- MAP_TYPE_TOWN, WEATHER_SUNNY, MAPSEC_ROUTE_128, no name popup,
  no escaping, no encounters, no items.
- Music: **MUS_PACIFIDLOG** [needs approval] — the deliberate echo:
  when the player later stands in Pacifidlog for V5, the ending's
  "Coralmere lives on" lands in the ears too. Alternative: a
  neutral gentle track (MUS_FALLARBOR).
- No entrance from the world: 12.5's V4 script warps the player in
  (warp 0 anchor at the south street mouth) and out when the rift
  closes. Reachable in dev builds via the debug warp for playtest.
- No new flags/vars (V4 state lives in 12.5).

## Decisions needed from Rocco

1. Approve this outline (mirrored core + shore/dock extension,
   readables, six ambient villagers with everyday lines built now).
2. Music: MUS_PACIFIDLOG echo, or neutral?
