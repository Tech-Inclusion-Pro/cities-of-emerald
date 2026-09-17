# Arc Outline — H1 (for approval)

**Status: APPROVED 2026-09-17 (guide-NPC entry + as drafted) —
implementing on cities/task-11-h1.**

The first hidden area (Phase 11, GDD 6.6 thread 1). This is also the
project's **first original map**, which is the main new ground here —
everything else reuses the proven M-arc patterns. Fixed level 60
(GDD 6.4 tier), always obeys (GDD 6.5 postgame rule), no item reward
(GDD 6.6).

---

## H1 — "The Swords of Justice" (Cobalion, Terrakion, Virizion, Keldeo)

**Opens:** after the League · **Entry:** Littleroot ·
**Levels:** fixed 60 · **Obeys:** always · **Reward:** none.

*(Quest name "The Swords of Justice" is [PROPOSED] — it is the group's
official name. Area name "Littleroot Hollow" is [PROPOSED].)*

### Design notes

- **The town you started in has one more secret.** H1 anchors the
  "hidden areas reached from existing towns" structure in the most
  familiar town of all. The hook is gentle and fits the group's lore:
  the guardians shelter Pokémon that were hurt or displaced — including
  by the Groudon/Kyogre crisis the player just resolved.
- **Entry via a guide NPC, not a layout edit [PROPOSED].** A ranger
  stands at Littleroot's tree line (post-League only, hide-flag). She
  tells of a hollow deep in the woods where hurt Pokémon are taken in,
  and walks the player up the trail — fade out, `warp` in, exactly the
  M5 sailor pattern. The hollow's exit warps back to her spot.
  - Why: editing Littleroot's tree line (layout + collision + a warp
    tile) is the riskier build for zero story gain. The scripted walk
    keeps the first original map self-contained. If you'd rather have
    a real visible entrance in town, say so and I'll scope the layout
    edit instead.
- **One new map: Littleroot Hollow.** A small forest clearing
  (~20×22), built on the existing Petalburg Woods tileset — no new
  art. A stream corner, a few sheltering nooks with resting wild-less
  Pokémon flavor objects, and open space so nothing is maze-like
  (accessibility: no puzzles, no required Cut/Strength, flat ground).
  No wild encounters; the area is a sanctuary.
- **The caretaker.** Inside the hollow, one caretaker NPC (the
  ranger's counterpart) explains the guardians: three protectors who
  keep this place, and a fourth — a student — who comes and goes.
- **The trio, then the student.** Cobalion, Terrakion, and Virizion
  stand at three points of the clearing as statics — M1-pattern
  battles (KO'd guardian returns on re-entry, only catching removes
  it), fixed level 60. **Keldeo appears only after all three are
  caught:** it comes looking for its teachers. Same static pattern,
  same level. This gives the arc a two-beat rhythm without any new
  mechanics — Keldeo's visibility script just checks the trio's
  caught flags.
- **Tone.** The guardians are not angry at the player; the caretaker
  frames each battle as the guardians testing whether the player is
  someone Pokémon can trust. Catching them is joining them, not
  taking them away. Plain language throughout.

### Story beats

1. **The trail.** Post-League, the ranger appears at Littleroot's
   tree line: hurt Pokémon around Hoenn have been disappearing —
   carried off, gently, by something strong. She knows where they go,
   and the Champion has earned the introduction. She walks the player
   to the hollow. The journal quest opens.
2. **The hollow.** The caretaker explains the three guardians. Each
   can be challenged where it stands. All three are reachable
   immediately; any order.
3. **The student.** With all three caught, Keldeo appears near the
   stream — the caretaker remarks that the student has come to find
   out where its teachers went.
4. **The wrap.** All four caught → the caretaker's closing words: the
   hollow will stay a sanctuary, and now its guardians travel with
   someone who protects things the same way. Journal quest completes
   and drops off. (No reward item, per the GDD.)

### Mechanics

- **Arc table:** `CITIES_ARC_H1` (4 species) joins the shared table
  with the same always-obeys postgame rule as M1-PG.
- **Levels:** fixed 60. The existing legendary-level special already
  yields 60 post-Champion, so H1 reuses it unchanged. (Note for
  later: H2+ sit at 65/70/75 and will need a per-arc fixed level —
  that lands with H2, not now.)
- **Story-only:** all four are already story-only species; the wild
  sweep test keeps them out of random sources.
- **New-map plumbing (the real work):** layout + border in
  `data/layouts/`, map group entry, `MAP_LITTLEROOT_HOLLOW` constant,
  region-map section reuses `MAPSEC_LITTLEROOT_TOWN` [PROPOSED],
  Petalburg Woods music [PROPOSED], indoor-style no-encounters, no
  heal location, exit warp back to Littleroot at the ranger's spot.
- **Journal:** "The Swords of Justice" activates post-League once the
  ranger is met, shows N of 4 (worded so Keldeo's late arrival makes
  sense: "the student appears when the three are with you").

### Save data

- `VAR_CITIES_H1_STATE`: 0 = not started, 1 = ranger met / hollow
  open, 2 = complete
- `FLAG_CITIES_HIDE_H1_RANGER`,
  `FLAG_CITIES_HIDE_H1_COBALION/TERRAKION/VIRIZION/KELDEO`,
  `FLAG_CITIES_H1_COBALION/TERRAKION/VIRIZION/KELDEO_CAUGHT`
- No save-layout change (reserved ranges only).

### Playtest items

- Ranger appears at Littleroot's tree line only after the League
- Ranger walks you to the hollow; the hollow's exit returns you to
  her spot; re-entry works any time via the ranger
- Trio visible at their spots, fight at level 60, KO'd guardian
  returns on re-entry, only catching removes it
- Keldeo absent until all three are caught, then appears by the
  stream; same battle rules
- All four obey immediately at any badge count (no disobedience
  message ever)
- No wild encounters anywhere in the hollow
- Journal quest opens with the ranger, shows N of 4, completes and
  drops off after the caretaker's closing line
- Wild sweep: none of the four appear in any random source (existing
  test gate)
