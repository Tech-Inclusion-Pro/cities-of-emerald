# Arc Outlines — H2a, H2b, H5a + Plate Hunt (for approval)

**Status: APPROVED 2026-09-17 (all as drafted) — implementing on
cities/task-11-h2 and cities/task-11-h5a.**

The last of Phase 11: the Oldale pair (one shared hidden area, two
questlines, tier 65 — split approved 2026-09-17) and the H5a finale
(tiers 75/80) with the 17-Plate hunt (Task 11.x). All names
[PROPOSED].

---

## The Forgotten Garden (shared area for H2a + H2b) — Oldale

**Map:** a walled, overgrown garden past Oldale (General + Petalburg
meadow grammar, ~22×20). North half: a ruin courtyard with **four
worn stelae**. South half: a wild grove with **three flower perches**
and a small **mask shrine**. One guide: an old gardener in Oldale
(post-League) who tends what's left of the place and walks you in.
Both quests run in the same space, in any order.

### H2a — "The Chained Ruin" (Wo-Chien, Chien-Pao, Ting-Lu, Chi-Yu)

- **Hook:** the gardener's warning — the four stelae in the north
  courtyard were seals once. The chains rusted through years ago,
  and what was sealed now stands beside its stone, waiting.
- **Statics:** one Treasure at each stela, all present from the
  first visit, any order, level 65. Plain-language stela text keeps
  the tone gentle: these are old grudges, not monsters — each one
  eased when someone finally faces it.
- **Wrap:** all four caught → the gardener: four grudges laid down;
  the courtyard is just a garden again. No reward (GDD).

### H2b — "The Mask in the Grove" (Okidogi, Munkidori, Fezandipiti, Ogerpon)

- **Hook:** the grove's three "heroes" — the villagers' old statues
  called them the Loyal Three, but the gardener knows the true
  story: they took what wasn't theirs, and the real hero has hidden
  in the grove ever since, wearing a mask.
- **Statics:** Okidogi, Munkidori, Fezandipiti on the flower
  perches from the start, level 65. **Ogerpon appears at the mask
  shrine only after all three are caught** — it comes out of hiding
  once the false heroes are gone. Its dialogue beat frames catching
  it as befriending, not capturing (accessibility-of-tone rule).
- **Wrap:** the gardener sets the story right: the village owed the
  masked one an apology, and it finally got a friend instead. No
  reward (GDD).

## H5a — "The Making of Everything" (Dialga, Palkia, Giratina, then Arceus) — Lilycove + Mt. Pyre

The finale of thread 1. Two sites plus the Plate hunt.

- **Guide:** a historian in Lilycove (post-League) studying the
  oldest story there is — time, space, and what lies between. She
  has found a **rift vestibule** behind the city.
- **Map: Rift Vestibule** (General + Cave, ~18×16): a hall where
  time and space thin — Dialga (west) and Palkia (east) as statics
  at **level 75**, plus an inner sanctum with an altar, sealed at
  first (state-gated notice).
- **Giratina on the existing Mt. Pyre summit** (M1 birds pattern —
  a static on an existing map, no new map): the historian points
  you there; the world's other side leaks through where Hoenn
  honors its dead. Level 75.
- **The Plate hunt (Task 11.x):** all **17 Plates as item balls
  across Hoenn** — one per major area, placed on existing maps in
  reachable spots (list in the implementation, journal-tracked via
  their item flags: "Plates found: N of 17"). The hunt quest opens
  with the historian and can be worked any time post-League.
- **Arceus:** with the creation trio caught AND all 17 Plates
  found, the sanctum opens. Arceus has **no overworld sprite** in
  the expansion, so it manifests at the altar — examine the altar
  (M5 Eon-stone script pattern), the light gathers, and the battle
  starts. **Level 80.** Only catching ends it; a KO lets you try
  again (LegendWithdrew pattern, "the light recedes into the
  altar").
- **Rewards:** the historian gives the **Adamant Crystal, Lustrous
  Globe, and Griseous Core** (the expansion's origin items) at the
  trio wrap; the completed Plate set is the hunt's own reward
  (GDD 6.7).

---

## Shared build notes

- `CITIES_ARC_H2A`, `CITIES_ARC_H2B` (tier 65), `CITIES_ARC_H5A`
  (tier 75; Arceus's level-80 battle is scripted directly, keeping
  the arc-table tier for the trio).
- Save data continues from +0x9F (flags) and +0x18 (vars); no
  layout change.
- Journal: three quests ("The Chained Ruin", "The Mask in the
  Grove", "The Making of Everything" including the plate count).
- Playtest sections for all three, incl. plate-count tracking and
  the altar battle loop.
