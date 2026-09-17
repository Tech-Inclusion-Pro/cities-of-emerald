# Arc Outline — M4 (for approval)

**Status: APPROVED 2026-09-17 (name, keeper placement, chamber order,
silent chambers — all as proposed) — implementing on cities/task-10-m4.**

No new maps after all: the three **unused Ruby/Sapphire Cave of Origin
chambers** still exist in the repo with layouts, music, and their full
warp chain intact (1F → chamber 1 → chamber 2 → chamber 3 → B1F — the
descent path Emerald cut). M4 brings them back to life. Encounter
levels come from the shared 10.0a special; obedience is the shared
10.0b rule (Rain Badge, already wired); the final beat uses the 10.0c
hook.

---

## M4 — "The Three Lights" (Uxie, Mesprit, Azelf)

**Opens:** badge 7 · **Obeys:** badge 8 (Rain Badge) · **Reward:** none
(GDD 6.6 lists none for M4).

*(Quest name "The Three Lights" is [PROPOSED].)*

### Design notes

- Badge 7 is exactly when DIVE arrives, so the arc opens the moment
  Sootopolis becomes reachable — no waiting, no backtracking.
- The obey badge is Juan's own Rain Badge, so the whole arc lives and
  resolves in Sootopolis. Catch the spirits during the crisis window,
  and they start listening when you beat the city's gym.
- The trio IS Sootopolis lore here: mind, heart, and will settling in
  the mountain "where life began" fits the Cave of Origin exactly.

### Story beats

1. **The keeper.** After badge 7, an elderly keeper appears inside the
   Cave of Origin's entrance chamber *(placement [PROPOSED]: inside the
   entrance cave, not the busy city map — quieter, and clear of every
   crisis cutscene)*. Her lore, in plain language: when the crater rose
   from the sea, three lights followed the fire down into the mountain
   — a light of MIND, a light of HEART, and a light of WILL. She opens
   the sealed way: "They've waited long enough for a visitor."
2. **The passage.** A parted wall appears in the 1F dead-end alcove
   (the right-side nook at (16,14) — currently a pointless dead end,
   now its reason to exist). It leads into the three restored chambers
   in sequence:
   - **Chamber 1 — Uxie** (the light of MIND)
   - **Chamber 2 — Mesprit** (the light of HEART)
   - **Chamber 3 — Azelf** (the light of WILL)

   *(Order is [PROPOSED]: Uxie/knowledge first as the "gatekeeper of
   memory", Azelf/willpower deepest — the classic Sinnoh framing.)*
3. **The chambers.** Each chamber holds one plain-language inscription
   near the entry (the keeper's ancestors' writing) and its spirit as a
   visible static — same rules as M1's birds: 10.0a level, standard
   legendary flow, a KO'd spirit returns on re-entry, only catching
   removes it. The chain exits into B1F, tying the loop back to the
   mountain's heart.
4. **The wrap.** All three caught → the keeper: "Mind, heart, and will…
   you carry all three now. Treat them as one." (No postgame tease —
   M4 has no follow-up arc in the GDD.)

### Mechanics

- **Map restoration, not map making:** the chambers' warps already
  chain correctly. Changes are: one "parted wall" object + script warp
  in 1F (shown at VAR_CITIES_M4_STATE ≥ 1), one arrival-anchor warp
  event added in 1F at the alcove, and chamber 1's return warp
  retargeted to that anchor (it currently drops you on the B1F
  staircase tile, which would be confusing). Chamber 3's exit already
  lands on B1F's staircase — correct as-is.
- **No wild encounters in the chambers** *([PROPOSED])*: the spirit
  rooms stay silent. They're not in the species plan, so this is the
  default — flagging it as a choice, not an accident.
- **Crisis safety:** the passage only opens via the keeper (badge 7+),
  and the chambers bypass nothing — the vanilla 1F → B1F descent is
  untouched, so the Wallace crisis scene plays exactly as before.
  Entering B1F from chamber 3 during the crisis just means meeting
  Wallace from the other side; playtest item, expected harmless.
- **Journal:** "The Three Lights" opens at badge 7, shows N of 3 in
  mind/heart/will language, the standard obedience note ("Your spirit
  won't listen until you earn the RAIN BADGE."), and completes on the
  keeper's final word.

### Save data

- `VAR_CITIES_M4_STATE`: 0 = not met, 1 = keeper met / passage open,
  2 = complete
- `FLAG_CITIES_HIDE_M4_KEEPER`, `FLAG_CITIES_HIDE_M4_PASSAGE`,
  `..._HIDE_M4_UXIE/MESPRIT/AZELF`, `..._M4_UXIE/MESPRIT/AZELF_CAUGHT`
- No save-layout change this time (flags/vars only, from the reserved
  Cities ranges).

### Playtest items

- Keeper appears in the Cave of Origin entrance at badge 7; intro
  opens the passage and the journal quest
- Parted wall visible in the 1F alcove only at state ≥ 1; warps into
  chamber 1; chamber 1's back-warp returns to the alcove (not the B1F
  stairs)
- All three spirits reachable, fight at the auto-cap level, return
  after a KO, disappear only on catch
- Chamber 3 exit lands in B1F; during the crisis, Wallace's scene
  still plays normally from either direction
- Caught spirit at 7 badges disobeys with the exact RAIN BADGE
  message; obeys the moment you beat Juan
- All 3 caught → keeper's closing line; journal quest completes and
  drops off
