# Task 13.1 — Mythical Events (outline, for approval)

**Status: APPROVED + BUILT 2026-09-18.** Build note: the 13.2
completeness test caught one mythical the GDD 6.6 table predates —
**Pecharunt** — so it was added at **Mt. Pyre Summit** (ghost/poison,
among the graves) to keep every story-only species obtainable. Also:
Meloetta is in **Fallarbor Town** proper (Emerald has no Fallarbor
Contest Hall). All mythical encounters are fixed
**level 70** (GDD 6.6, [DECIDED 2026-09-17]) and unlock after the
League. Locations are the [DECIDED] GDD 6.6 table. Together with the
arcs (which already hold Mew, Celebi, Genesect, Magearna, Keldeo),
these place every remaining story-only mythical — the roster 13.2
will verify.

Shared: one arc-style entry per event in cities_arcs.c
(CITIES_ARC_MYTHIC, tier 70, always-obeys) so obedience/level are
uniform; M1-pattern statics; catch flags per species. A journal
quest "Whispers and Wishes" counts mythicals obtained.

## The simple statics (build directly — location + level decided)

Each is a lone L70 static appearing postgame at its GDD spot, with
one readable line of flavor:

| Species | Location |
|---|---|
| Jirachi | Fallarbor — Prof. Cozmo's meteorite (his house) |
| Diancie | Granite Cave (deep chamber) |
| Manaphy + Phione | Underwater Route 124 (Phione appears once Manaphy caught) |
| Victini | Mauville City (a bright corner rooftop/alley nook) |
| Meloetta | Fallarbor Contest Hall lobby |
| Volcanion | Lavaridge Town (the hot-spring steam) |
| Marshadow | Sky Pillar 1F (in a pillar's shadow — not the top; Rayquaza's story is untouched) |
| Zeraora | New Mauville (deep in the generator halls) |
| Zarude | Petalburg Woods (a vine-wall clearing) |

## The four with design detail

### Deoxys — Birth Island (reuse vanilla)
Birth Island, its harbor, and the triangle puzzle all exist in the
repo. A **Cities sailor at Lilycove Harbor** (M5 pattern) appears
postgame, gives passage, sets FLAG_ENABLE_SHIP_BIRTH_ISLAND. The
vanilla triangle puzzle runs as-is; only the Deoxys level is raised
to 70 (Cities set-level special). No new map.

### Hoopa — the Ring Chamber (new room off the Trick House)
GDD: "a strange ring appears; solving the room leads to Hoopa." To
avoid disturbing the vanilla Trick House puzzle state machine, this
is a **standalone new map** (RingChamber, ~13×13, an Unknown-Dungeon
look) reached from a golden ring that appears in the Trick House
entrance postgame. Light puzzle: three rings on the floor; stepping
them in the order named by a plaque opens the way to Hoopa. Reward:
**Prison Bottle**. Hoopa at L70.

### Meltan + Melmetal — Slateport Shipyard (collection hunt)
Mirror of H6's Zygarde cells: **6 "Meltan nuts"** (ITEM_BALL
objects) scattered around the Slateport Shipyard and harbor. A
dockworker (postgame) explains the missing hex nuts; collecting all
6 makes **Meltan** appear at the shipyard (L70). Catching Meltan
makes **Melmetal** appear once (L70) — the swarm that formed it.
Per-nut flags + a count, exactly like the cells.

### Shaymin — Route 119 meadow (Halley's payoff)
The meadow south of the Weather Institute that Halley says "bloomed
like a thank-you." Postgame, talking to Halley (after her history)
points the player to it; a flower patch there yields **Shaymin**
(L70) and the **Gracidea**. Ties the Weather Institute thread off.

## Flags/vars
New Cities flags from +0x13C (per-species catch + hide, hunt nuts,
ferry/ring/meadow gates). One var VAR_CITIES_MYTHIC_STATE if needed
for the Ring Chamber puzzle. No save-size change (within reserves).

## Decisions needed from Rocco
1. Approve the simple-static placements above.
2. Deoxys: reuse the vanilla Birth Island triangle puzzle as-is
   (just L70 + a postgame sailor)? (Recommended.)
3. Hoopa: standalone Ring Chamber off the Trick House entrance,
   rather than modifying the vanilla puzzle chain? (Recommended.)
4. Meltan: 6-nut hunt at the Slateport Shipyard, Melmetal appearing
   after Meltan is caught? (Recommended.)
