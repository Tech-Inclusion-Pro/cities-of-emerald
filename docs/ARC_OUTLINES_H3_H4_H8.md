# Arc Outlines — H3, H4, H8 (for approval)

**Status: APPROVED 2026-09-17 (all three as drafted; H4 open post-League) —
implementing on cities/task-11-h3 / -h4 / -h8.**

The first three level-65 hidden areas (GDD 6.4; the per-arc tier
mechanism is live). Same proven shape as H1/H5b/H10/H11: post-League
guide NPC, one original map, M1-pattern statics, always-obeys,
journal quest, exit alcove. Two of these pay off standing teases, and
H8 is the project's first arc reward item. All names [PROPOSED].

---

## H3 — "The Colossus Wakes" (Regigigas, Regieleki, Regidrago) — Petalburg

**Follow-up to M2** (GDD 6.6): opens post-League **and only once M2 is
complete** — the archaeologist's colossus tease finally lands.

**Map: Colossus Vault** — a buried titan-hall in the hills above
Petalburg (General + Cave tilesets, M2's ruin mood, ~18×16): a main
hall with a great dais, and two small side alcoves.

- **The archaeologist returns.** The same character from M2's
  Pacifidlog house has moved her dig to Petalburg — the trail of the
  sealed chambers pointed here all along. She is the guide (new NPC
  placement in Petalburg, near the city's west tree line) and walks
  the player into the dig. Continuity, not a new stranger.
- **Two keys, then the giant.** Regieleki and Regidrago wait in the
  side alcoves — the vault's "lightning and dragon" wardens. The dais
  stands empty-looking: Regigigas sleeps there, and **only wakes once
  both wardens are caught** (H1's Keldeo rhythm, scaled up: its
  visibility script checks the two caught flags). Inscription text
  ties back to M2's plain-language translations.
- **Statics:** all three at level 65.
- **Wrap:** all three caught → her closing line: the sealed chambers,
  the vault, the titans — the same story, finally whole. She's
  writing the paper of her career. Journal "The Colossus Wakes" shows
  progress in two beats (wardens, then the giant).

## H4 — "Rainbow Wings" (Ho-Oh, Lugia, Celebi) — Fortree

**Pays off M3's tease**: the ranger's "rainbow wings" line. Opens
post-League (no M3 requirement — the tease is flavor, not a lock;
say the word if you'd rather gate it on M3 complete).

**Map: Old-Growth Canopy** — a treetop grove above Fortree (General +
Fortree tilesets: bridges and platforms in a giant tree, ~20×18): a
high sun platform, a shaded spring hollow at the base, and a small
mossy shrine.

- **The ranger reprises.** M3's ranger in the Fortree Pokémon Center
  gets a postgame branch (M1-PG's reporter pattern — same NPC, new
  story): hikers keep reporting a rainbow that lands in the deep
  canopy. She knows the tree it lands on.
- **Sky, sea, and time.** Ho-Oh waits on the high sun platform; Lugia
  in the shaded spring hollow below (sky and sea, kept apart by the
  tree itself). **Celebi appears at the mossy shrine only after both
  are caught** — the forest's timekeeper shows itself last, to see
  who calmed the other two.
- **Statics:** all three at level 65.
- **Wrap:** all three caught → the ranger: three legends and one
  tree; some stories you chase, and some land next to you. Journal
  "Rainbow Wings" runs two beats (the pair, then Celebi).

## H8 — "The Weather Menders" (Tornadus, Thundurus, Landorus, Enamorus) — Fallarbor

**First arc reward: the Reveal Glass** (GDD 6.6/6.7).

**Map: Windswept Rise** — a high ash moor above Fallarbor (General +
Fallarbor/Route-113 tilesets: ash grass and drifts, ~20×16), open and
wind-blasted, four low stone perches at its corners... but only three
are occupied at first.

- **Hook: the weather station's puzzle.** Fallarbor's ash researcher
  (guide NPC near the Cozmo house) has charts showing the town's
  weather correcting itself — squalls that stop mid-gust, as if
  something keeps mending the sky. The trails all climb to the rise.
- **The forces of storm.** Tornadus, Thundurus, and Landorus each
  hold a perch, any order, level 65. **Enamorus arrives at the empty
  fourth perch once the three are caught** — spring follows when the
  storms are settled (canon Hisui lore, and the H1 rhythm again).
- **The Reveal Glass.** All four caught → the researcher gives the
  Reveal Glass at the wrap (checkitemspace + bag-full retry, the M5
  Eon-stone pattern; FLAG_CITIES_H8_GLASS_GIVEN) so the genies'
  Therian forms are usable. Journal "The Weather Menders" runs two
  beats and completes after her closing line.

---

## Shared build notes

- `CITIES_ARC_H3`, `CITIES_ARC_H4`, `CITIES_ARC_H8` append to the
  postgame block; `fixedLevel = 65` in the arc table.
- H3's opening gate: `FLAG_SYS_GAME_CLEAR` AND `VAR_CITIES_M2_STATE == 2`.
- Save data (reserved ranges, no layout change): three state vars
  continuing from +0x12; hide/caught flags continuing from +0x64.
- Playtest sections mirror the level-60 areas, plus: H3 wardens-then-
  giant gating, H4 Celebi gating, H8 Enamorus gating + Reveal Glass
  give/bag-full retry.
