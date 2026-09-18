# Phase 15 — Challenge Modes (outline, for approval)

**Status: APPROVED + BUILT 2026-09-18** (randomizer = wild+starters+
trainers; first-encounter enforced; faint = memorial-box lock; clauses
default-on). Build notes: struct CitiesChallenge in SaveBlock3
(SaveBlock3 12→40 B); memorial = the last PC box (14), grab-blocked
while Nuzlocke is on. Known cosmetic gap: under wild randomization an
OWE overworld sprite shows the original species (battle gives the
randomized one). GDD Section 10. Neither Nuzlocke nor
a randomizer exists in the base; both are built from scratch. Hook
points are clean. This is the most engine-invasive phase, so the
depth choices below are real — I want them settled before building.

## Shared: save state + setup

- **New `struct CitiesChallenge` in SaveBlock3** (SaveBlock3 has
  ~1,620 B free; budget reserves 32 B): mode bits (nuzlocke on,
  dupes clause, shiny clause, randomizer on + per-category toggles),
  a `u32 randomizerSeed`, and a **17-byte per-MAPSEC first-encounter
  bitfield** (~134 areas). Updates T_SAVEBLOCK3_SIZE in test/save.c.
- **Setup:** the existing truck setup already asks difficulty/assist
  (Phase 5). Add two prompts there — "Nuzlocke mode?" and
  "Randomizer?" (with a seed rolled from the RTC/keypress). Chosen
  once at new game; immutable after (standard for these modes).

## 15.2 Randomizer (seeded, story-only always excluded)

Core: `CitiesRandomizeSpecies(original)` — a **deterministic** remap
(hash of original species + the saved seed → the Nth enabled,
non-story, own-base species). Same original always maps to the same
replacement for a given seed; never outputs a story-only species.

Per-category toggles, each a small hook:
- **Wild** — in `TryGenerateWildMon` (before the story-only check).
- **Starters** — in `CB2_GiveStarter` (the player's pick is remapped).
- **Trainers** — in the NPC party build (`CreateNPCTrainerParty*`),
  each team member remapped; keeps levels/movesets sane.
- **Items** — **[scope choice]** overworld item-ball pickups only
  (bounded), or defer items to keep the phase tight.

## 15.1 Nuzlocke

- **First encounter per area:** on the first wild encounter in a
  MAPSEC, record it (the bit). **Enforcement [depth choice]:** either
  (A) the catch is blocked for any later, different species in that
  area (a hook in the ball-throw path — true enforcement), or (B)
  tracked only, shown as a notice, honor-system. Dupes clause: a
  species already owned doesn't consume the area's "first." Shiny
  clause: shinies are always allowed.
- **Fainted Pokémon can't be used again [depth choice]:** either
  (A) hard lock — a fainted mon is moved to a locked "memorial" box
  and can't re-enter the party (a PC-withdraw + battle hook), or
  (B) release-on-faint (simplest, brutal, irreversible), or (C)
  tracked/marked only. (A) is the classic mechanic and the one I'd
  build, but it's the most invasive hook.

## Decisions needed from Rocco

1. **Randomizer categories now:** wild + starters + trainers
   (recommended), and items = overworld item balls, or defer items?
2. **Nuzlocke first-encounter:** enforce the catch limit (A), or
   track-and-notify (B)?
3. **Nuzlocke faint rule:** hard memorial-box lock (A, recommended),
   release-on-faint (B), or tracked-only (C)?
4. Clauses (dupes + shiny) **on by default** when Nuzlocke is on
   (GDD [PROPOSED])? (recommended: yes)

Heads-up: the enforcing options (catch-block, faint-lock) touch the
battle/PC code and carry the most regression risk of anything left in
the project. I'll build them carefully behind the mode flag so they're
inert unless Nuzlocke is on — but wanted that visible before I start.
