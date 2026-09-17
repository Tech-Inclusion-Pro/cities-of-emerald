# Arc Outlines — H5b, H10, H11 (for approval)

**Status: APPROVED 2026-09-17 (all three as drafted) — implementing
on cities/task-11-h5b / -h10 / -h11.**

The three remaining level-60 hidden areas (GDD 6.4 tier table). All
three follow H1's proven shape: a guide NPC in the entry town
(post-League, hide-flag) walks the player into one original map via a
direct `warp`; statics use the M1 battle pattern; postgame always-obeys
is automatic (`arc >= CITIES_ARC_M1PG`); an exit alcove/tile warps
back; a journal quest tracks N of M; no reward items (GDD 6.6). New
mechanics: none. All quest/area/NPC names below are [PROPOSED].

---

## H5b — "The Lunar Duo" (Cresselia, Darkrai) — Dewford

**Map: Moonrise Cove** — a small sea cave (General + Cave tilesets,
sampled from Shoal Cave, ~18×18). An outer moonlit chamber and a
darker inner nook. No wild encounters, no Flash needed.

- **Hook: the town that can't sleep.** Post-League, Dewford's nights
  have gone wrong — shared bad dreams, the whole town waking tired. A
  fisher on the beach (the guide) traced the pull of the tides to a
  cove only reachable by boat, and rows the Champion out.
- **Inside:** one caretaker-style NPC (a lighthouse keeper who camps
  in the cove) explains the pair: one brings calm dreams, one brings
  the dark ones — and neither is evil; Darkrai's nightmares are
  something it cannot fully control, not something it enjoys
  (plain-language, no "monster" framing).
- **Statics:** Cresselia in the moonlit outer chamber; Darkrai in the
  inner nook. Both present from the start, either order, level 60.
- **Wrap:** both caught → the keeper's closing line: Dewford sleeps
  easy again, and the dreams — bright and dark — are in kind hands.
  Journal "The Lunar Duo" shows N of 2.

## H10 — "The Island Guardians" (Tapu Koko, Tapu Lele, Tapu Bulu, Tapu Fini) — Pacifidlog

**Map: Shrine Atoll** — a ring of log-and-reef islets (General +
Pacifidlog tilesets, ~22×22): four small shrine platforms around a
central walkway, open sky and sea. No wild encounters, no Surf needed
inside (log bridges connect everything).

- **Hook: the shrines under the water.** Pacifidlog's elders say the
  town floats where it does for a reason: four old shrines ring a
  sunken atoll nearby, and the guardians who kept them have returned
  now that the sea is calm. An elder (the guide) polls the player out
  on a raft from the town's east walkway.
- **Inside:** the elder's grandchild tends the shrines (caretaker
  NPC) and introduces the four guardians — protectors who each chose
  an islet, waiting to test the Champion the old way.
- **Statics:** one Tapu per shrine platform (Koko north, Lele east,
  Bulu south, Fini west), any order, level 60.
- **Wrap:** all four caught → the caretaker: the shrines will be kept
  swept for the day the guardians visit again; they chose to travel
  with the one person the sea itself vouched for. Journal "The Island
  Guardians" shows N of 4.

## H11 — "The Heart of the Mountain" (Heatran) — Mt. Chimney

**Map: Ember Vault** — a small magma chamber under the summit
(General + Lavaridge tilesets, sampled from Mt. Chimney/Magma Hideout,
~16×14). One chamber, lava pools at the walls, a basalt platform at
the center. No wild encounters.

- **Hook: the mountain's second heartbeat.** Post-League, the summit
  researchers' instruments pick up a slow second pulse deep under
  Mt. Chimney — too steady to be magma. A volcanologist at the summit
  (the guide, near the cable car station) has found the vent that
  leads down, and won't go alone.
- **Inside:** the volcanologist follows the player in and acts as the
  caretaker-style commentator (single NPC doubles as both roles —
  smallest arc, one new NPC total): the pulse is a Pokémon that has
  slept in the mountain since before Sootopolis was a crater, and it
  woke when Groudon did.
- **Static:** Heatran alone on the central platform, level 60.
- **Wrap:** caught → her closing line: the mountain still rumbles,
  but now it's just a mountain; its heart chose to see the world.
  Journal "The Heart of the Mountain" shows the single objective.
- Note: the guide NPC stands on the existing Mt. Chimney summit map
  (outdoor), so this arc has TWO placement sites like H1
  (town/summit + new map) — same wiring shape as H1's ranger.

---

## Shared build notes (all three)

- **Arc table:** `CITIES_ARC_H5B`, `CITIES_ARC_H10`, `CITIES_ARC_H11`
  appended after `CITIES_ARC_H1` (postgame block at enum end keeps
  always-obeys automatic).
- **Levels:** all level 60 — the existing legendary-level special
  applies unchanged. (The per-arc fixed-level mechanism arrives with
  the 65-tier batch, not now.)
- **Story-only:** all seven species are already story-only; the wild
  sweep gate covers them.
- **Save data (reserved ranges only, no layout change):**
  - `VAR_CITIES_H5B_STATE`, `VAR_CITIES_H10_STATE`,
    `VAR_CITIES_H11_STATE` (0 = not started, 1 = guide met, 2 = done)
  - Per-arc hide flags (guide + statics) and `_CAUGHT` flags,
    continuing from +0x53.
- **Playtest items** land as three checklist sections mirroring H1's
  (guide gating, walk-in/walk-out, static rules, always-obey,
  journal open/complete/drop-off, no wild encounters, map visuals).
