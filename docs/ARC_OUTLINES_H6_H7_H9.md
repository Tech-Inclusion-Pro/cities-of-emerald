# Arc Outlines — H6, H7, H9

**Status: APPROVED 2026-09-17 (batch shape signed off by Rocco;
Zygarde Cells kept quick and self-contained) — implementing on
cities/task-11-h6 / -h7 / -h9.**

The 70-tier hidden areas (GDD 6.4), each with a form-change item
reward (GDD 6.7). Same proven shape: post-League guide, one original
map, M1-pattern statics, always-obeys, journal quest, exit alcove.
All names [PROPOSED].

---

## H6 — "The Balance Below" (Xerneas, Yveltal, Zygarde) — Mossdeep

**Map: Mossdeep Undercliff** — a sea-cut cavern beneath Mossdeep's
cliffs (General + Cave grammar, ~18×16): a spring chamber with a
glowing pool, a dark nook, and a center floor.

- **Hook:** the tide pools under the city have gone strange — things
  grow overnight on one side and wither on the other. An ecologist at
  the cliff edge has watched the balance tip back and forth, and
  knows the way down.
- **Life and death first:** Xerneas by the spring pool, Yveltal in
  the dark nook, both present from the start. **Zygarde appears on
  the center floor only once both are caught** — order shows itself
  when life and death are settled.
- **Zygarde Cells, quick version (Rocco's call):** 5 glowing cell
  objects scattered inside the Undercliff itself. Touch one to
  collect it (flag + object removed). No overworld-wide hunt.
- **Reward:** all three caught AND all 5 cells → the ecologist gives
  the **Zygarde Cube** (bag-full retry). Journal shows cells x of 5
  alongside the trio.

## H7 — "Truth and Ideals" (Reshiram, Zekrom, Kyurem) — Mauville

**Map: Resonance Hall** — a deep vault under Mauville's grid
(General + Cave grammar, ~16×14) where two opposing currents hum.

- **Hook:** Mauville's engineers keep logging a power draw nobody
  wired: two signals, perfectly out of phase, deep below the city. An
  engineer (guide, in Mauville) has traced the service shaft.
- **The two, then the husk:** Reshiram (west) and Zekrom (east) face
  each other across the hall. **Kyurem appears at the hall's cold
  north end once both are caught** — the empty third that remains
  when truth and ideals move on.
- **Reward:** all three caught → the engineer gives the **DNA
  Splicers** (bag-full retry), per the GDD.

## H9 — "The Old Heroes" (Zacian, Zamazenta, Glastrier, Spectrier, Calyrex, Kubfu) — Verdanturf

**Map: Hero's Meadow** — a walled meadow beyond Verdanturf's clean
air (General + Petalburg grammar like Littleroot Hollow, ~20×20).
The largest 70-tier arc: six species, three item rewards.

- **Hook:** Verdanturf's storyteller elder (guide) tells of the
  meadow where old heroes rest — two wolves who guarded people, a
  crowned king of harvests with his two steeds, and a student who
  still trains to earn its place.
- **Present from the start:** Zacian and Zamazenta (north, side by
  side), Glastrier (west) and Spectrier (east), and Kubfu training
  near the entrance. **Calyrex appears at the meadow's crown only
  once both steeds are caught.**
- **Reward:** all six caught → the elder gives the **Rusted Sword**,
  **Rusted Shield**, and **Reins of Unity** together (three-item
  give with bag-space check and retry). Journal runs the steeds beat
  then the king.

---

## Shared build notes

- `CITIES_ARC_H6`, `CITIES_ARC_H7`, `CITIES_ARC_H9` append to the
  postgame block; `fixedLevel = 70`.
- Save data (reserved ranges, no layout change): state vars from
  +0x15; hide/caught/cell/reward flags from +0x7C.
- Playtest sections mirror the earlier areas, plus: H6 cell pickups
  and cube give, H7 Kyurem gating and splicers, H9 Calyrex gating and
  the three-item give.
