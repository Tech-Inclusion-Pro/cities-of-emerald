# Arc Outline — M5 (for approval)

**Status: APPROVED 2026-09-17 (name, mega stones as reward, Eon Ticket
beat — all as proposed) — implementing on cities/task-10-m5.**

Southern Island exists in vanilla (exterior + interior grove) and is
normally locked behind the Eon Ticket event item. With the TV roamer
event already removed (M3), the whole island belongs to M5. Encounter
levels come from the shared 10.0a special; obedience is the shared
10.0b **pair rule** (already live: neither obeys until both are
caught, sticky forever after).

---

## M5 — "The Eon Pair" (Latias & Latios)

**Opens:** badge 8 · **Obeys:** when both are caught (GDD 6.5's M5
exception) · **Reward:** see [PROPOSED] below.

*(Quest name "The Eon Pair" is [PROPOSED].)*

### Story beats

1. **The sailor's tale.** After badge 8, a weathered sailor appears in
   the Lilycove harbor terminal: old sailors tell of two lights that
   dance over the southern sea — one red, one blue — always together,
   never close enough to touch. He's finally tracked the island they
   circle and offers the trip. He hands over the **EON TICKET** (the
   vanilla event item, now earnable in-game) and the ferry route
   opens (`FLAG_ENABLE_SHIP_SOUTHERN_ISLAND`, the vanilla gate).
2. **The island.** The ferry sails to Southern Island as in vanilla.
   In the interior grove, **both** Latias and Latios wait near the Eon
   stone — the pair replaces vanilla's single "unchosen" Lati and its
   TV-pick cutscene. Each is a visible static with the standard arc
   rules: 10.0a level (the cap at badge 8 — the strongest mid-game
   encounter, as the GDD intends), KO'd → returns on re-entry, only
   catching removes it.
3. **The pair rule in play.** Catch one and it won't listen — the
   battle message and the journal both say why ("Latias won't listen
   until it's reunited with Latios."). Catch the second and the sticky
   flag sets: both obey, forever, even if one is later traded or
   released.
4. **The wrap.** With both caught, the Eon stone in the grove
   "hums" — reading it yields **Latiasite and Latiosite**
   *([PROPOSED]: the GDD lists no M5 reward but notes the pair "can
   Mega Evolve"; the stones make that real without a held-item
   giveaway. Alternative: vanilla-style Soul Dew instead — say the
   word.)* The sailor has a closing line back at the harbor.

### Mechanics

- **Vanilla replacement, not addition:** the interior's TV-pick
  cutscene flow (`VAR_ROAMER_POKEMON`, the camera pan, the single
  VAR-gfx object, `FLAG_DEFEATED/CAUGHT_LATIAS_OR_LATIOS`) is retired
  along with its trigger; the pair are two plain statics in the grove,
  M1-pattern scripts. The exterior sailor and SS Tidal stay as-is.
- **Ferry plumbing reused:** the sailor beat sets the vanilla
  enable-ship flag, so the Lilycove ferry menu gains the Southern
  Island route exactly as the Eon Ticket event did. The ticket item is
  flavor + key-item record of the beat.
- **Journal:** "The Eon Pair" opens at badge 8 with the sailor's
  rumor, shows which of the pair is caught, and carries the reunion
  hint while only one is caught (mirrors the battle message per GDD
  6.5). Completes after the stones (or the closing line, if Soul Dew
  is chosen).
- No engine work: the pair obedience, sticky flag, level special, and
  all-caught hook shipped with the Phase 10 shared systems.

### Save data

- `VAR_CITIES_M5_STATE`: 0 = not met, 1 = sailor met / route open,
  2 = complete
- `FLAG_CITIES_HIDE_M5_SAILOR`, `..._HIDE_M5_LATIAS/LATIOS`,
  `..._M5_LATIAS/LATIOS_CAUGHT`, `..._M5_STONES_TAKEN` (if the mega
  stones are approved)
- No save-layout change (reserved ranges only).

### Playtest items

- Sailor appears in the Lilycove harbor terminal at badge 8; gives the
  EON TICKET; ferry menu now lists Southern Island
- Both statics visible in the grove; each fights at the auto-cap
  level; KO'd one returns on re-entry; catching removes only that one
- Caught single Lati disobeys with the exact reunion message; both
  caught → both obey; trade one away → the keeper still obeys (sticky)
- Eon stone yields Latiasite + Latiosite once, only after both caught
- Journal quest opens at badge 8, tracks the pair, completes and drops
  off
- Old TV-pick flow is fully gone: no camera-pan cutscene, no
  VAR_ROAMER_POKEMON dependency anywhere on the island
