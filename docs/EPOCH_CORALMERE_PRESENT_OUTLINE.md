# Task 12.3 — Coralmere, Present Day (outline, for approval)

**Status: APPROVED 2026-09-18 (outline as proposed; village opens
after V2). Build note: the surface ruin cluster reuses the existing
worn rock island at Route 128 (74–83, 9–17) — only the post rows,
signs, and the underwater side were added; the vanilla dive patch at
(86–87, 17–18) is now functional (it had no floor beneath it in
vanilla).** Builds GDD 7.2's [DECIDED] Coralmere
beats: surface ruins on Route 128 visible from the start of the game;
the sunken village reachable with Dive during the arc. The past
version (12.4) will reuse this village's street plan. "Kai" appears
nowhere.

## The three pieces

### 1. Surface ruins (Route 128, east half — visible from day one)

A quiet cluster in the open water around (78, 14) [exact tiles
placed at build time from collision + tile sampling], well away from
the Seafloor Cavern approach (x≈38) and the Steven/Archie/Maxie
scene (x≈37–40). Built only from the route's existing General +
Mossdeep vocabulary: a small worn white-stone structure breaking the
surface, ringed by rock nubs in unnaturally straight rows. A patch
of deep (divable) water sits beside it.

Two readable bg events (accessible-first: the text carries what the
tiles can't):
- **The tower top:** "The top of a stone tower rises out of the
  open sea. Sun and salt have worn it round. Far below, something
  pale catches the light."
- **The rows of stone:** "Worn stumps of stone stand in two straight
  lines just under the surface. They look like the posts of a very
  long dock."

### 2. The way down (Underwater_Route128, matching spot)

Diving in the new deep patch lands the player on the existing
underwater route (dive connections keep coordinates). At the
matching spot: a dark opening framed in cut stone — clearly made,
not grown — with a warp into the village map, plus one flavor bg
event ("cut stone, planted in rows, half-buried in sand").

### 3. Coralmere (new map, MAP_CORALMERE_RUINS)

~24×20, General + Underwater tilesets, MAP_TYPE_UNDERWATER,
WEATHER_UNDERWATER_BUBBLES, MUS_UNDERWATER, MAPSEC_ROUTE_128 (no
new name popup — the place should not introduce itself). No wild
encounters, no items: the village is quiet on purpose.

Layout: the entrance opens onto a main street running inland;
doorway openings and low wall footprints line it; the street widens
to a small square with the town sign; the far end is the base of
the bell tower whose top the player saw from the surface.

Readable bg events (the emotional work of the map):
- **The town sign (square):** "A worn stone sign stands at the
  center of the square. Most of the letters are gone. What remains
  reads: CO…ALME…E."
- **A doorway:** "A low doorway, its lintel carved by hand: a wave,
  a bell, and two small fish. A welcome, in somebody's language."
- **The bell tower base:** "The tower's door is long gone. Looking
  up through it, the water brightens, step by step, all the way to
  the sun. The bell still hangs at the top."
- **A small house floor:** "A stone floor swept clean by years of
  current. In the corner, a raised hearth. Someone cooked here,
  once, every day."

### Gate ("during the arc")

The village entrance is open the moment its flag is set and gently
refused before then: a coord event just inside the entrance checks
**FLAG_CITIES_CORALMERE_OPEN** (new, +0xCB); if unset — "The
current through the opening is too strong to swim against." — and
the player is placed back outside. 12.5 sets the flag during the
V thread (recommendation below). The surface ruins and the stone
doorway on the underwater route are NEVER gated — they are the
day-one mystery.

## Decisions needed from Rocco

1. Approve this outline (ruin placement approach, village shape,
   readables, no encounters/items).
2. **When does the village open?** Recommended: at V2 completion —
   the Archivist's letter (a village, a storm) is what sends the
   player looking at the sea. Alternatives: V1 start (earlier
   freedom) or V4 start (tightest reveal).

## Implementation

- Route128 + Underwater_Route128 layout edits (map.bin, tile words
  sampled from those maps' own grammars) + bg events.
- New layout + map folder CoralmereRuins; layouts.json,
  map_groups.json; warp pair with Underwater_Route128.
- flags.h: FLAG_CITIES_CORALMERE_OPEN (+0xCB).
- PLAYTEST_CHECKLIST section; GDD 7.2 status flips on build.
