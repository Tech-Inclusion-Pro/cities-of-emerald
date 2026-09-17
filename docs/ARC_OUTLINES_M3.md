# Arc Outline — M3 (for approval)

**Status: APPROVED 2026-09-17 (dens as proposed; vanilla Lati TV event
disabled; H4 hook added) — implementing on cities/task-10-m3.**

Like M1 and M2, this arc uses **existing maps only** — no Porymap work.
Encounter levels come from the shared 10.0a special (auto badge cap);
obedience is the shared 10.0b rule; the final "all caught" beat uses the
10.0c hook.

---

## M3 — "On the Trail" (Raikou, Entei, Suicune)

**Opens:** badge 6 · **Obeys:** badge 7 (Mind Badge) · **Reward:** none
(GDD 6.6 lists no follow-up keyed to M3).

### Design goal

Keep the classic "roaming legendary" identity — the chase across routes —
while removing the three things that make vanilla roamers a wiki-and-luck
grind: not knowing where the roamer is, endless fleeing, and permanent
loss on a KO. The fix is a two-phase arc: an honest **chase phase** with
live tracking, then a guaranteed **cornered phase** with a normal static
battle.

### Story beats

1. **The ranger.** After badge 6, a Pokémon Ranger appears in the Fortree
   Pokémon Center (badge 6 city). She's tracking three fast-moving Pokémon
   that crossed into Hoenn and asks for help. The journal quest "On the
   Trail" opens, and all three beasts begin roaming the route network.
2. **The chase.** Each beast roams the existing route sets. The journal
   shows a live position for each ("Last seen: ROUTE 119"), updated the
   same way the vanilla PokéNav MATCH CALL map would be — no guessing.
   Meeting a beast in the wild starts a battle; the beast can flee
   (vanilla behavior), and its HP and status persist between meetings.
3. **The cornering.** After the player has met a beast in battle **3
   times** (catching it earlier ends its chase early, of course), the
   ranger calls: the beast is exhausted and has settled in a den. It
   becomes a visible static encounter that no longer flees, at:
   - **Raikou — Altering Cave** (unused vanilla map, Route 103 shore)
   - **Entei — Scorched Slab** (Route 120's fire cave, nearly unused)
   - **Suicune — Meteor Falls, waterfall back chamber**

   *(Den choices APPROVED 2026-09-17.)*
4. **The wrap.** With all three caught, the ranger celebrates and heads
   home — but not before one last musing: "Three beasts, running together
   all this way… you know the old story? Something with rainbow wings
   revived them. I'd love to see whatever THAT was." (H4 hook, postgame.)

### Mechanics

- **Roamer engine:** raise `ROAMER_COUNT` from 1 to 3 in
  `include/constants/global.h` — the expansion's roamer code already
  loops over the array, and the Hoenn location table exists. Save cost:
  +56 B in SaveBlock1 (28 B per `struct Roamer`), against 612 B measured
  free (SAVE_BUDGET.md, post-Phase-1).
- **Levels:** a roamer's level is fixed at creation, so to honor GDD 6.4
  ("level rises if the player arrives later") the 10.0a special re-applies
  the current cap when a roamer battle starts, scaling remaining HP
  proportionally. Cornered statics use 10.0a directly, like M1/M2.
- **No permanent misses:** a KO'd or Roar'd-away beast keeps roaming
  (vanilla expansion behavior already does this for fleeing; the KO case
  respawns the roamer at full HP, matching the M1/M2 rule).
- **Encounter counting:** each battle meeting increments that beast's
  chase counter (0–3). Fleeing, KO, and running away all count — only
  meetings matter, so the player is never punished for a bad battle.
- **Journal:** "On the Trail" shows each beast's live route, its chase
  count in plain language ("You've met it up close twice. One more and
  it will tire."), den directions once cornered, and the standard
  obedience note ("Your Raikou won't listen until you earn the MIND
  BADGE.").
- **Vanilla conflict to resolve:** Emerald's post-League TV event releases
  a roaming Latias/Latios. M5 places both on Southern Island instead, so
  the vanilla TV roamer event should be disabled now (one line) rather
  than left to fight M5 later. **[APPROVED 2026-09-17: disable.]**

### Save data

- `VAR_CITIES_M3_STATE`: 0 = not started, 1 = ranger met / beasts roaming,
  2 = complete
- `VAR_CITIES_M3_CHASE`: packed chase counters, 2 bits per beast
- `FLAG_CITIES_HIDE_M3_RANGER`,
  `FLAG_CITIES_M3_RAIKOU/ENTEI/SUICUNE_CORNERED` (shows den static),
  `..._HIDE_M3_RAIKOU/ENTEI/SUICUNE` (set on catch)
- `ROAMER_COUNT` 1 → 3 (+56 B SaveBlock1)

### Playtest items

- All three beasts appear on routes after the ranger scene; journal
  positions match actual encounters
- Chase counter increments once per battle regardless of outcome; ranger
  call fires at 3; den static appears and never flees
- KO'd beast returns (roaming or in den); caught beast never returns
- Roamer level tracks the cap between badge 6 and badge 8 saves
- Obedience message names the Mind Badge; late catches obey immediately
- Vanilla Latias/Latios TV event no longer fires post-League
