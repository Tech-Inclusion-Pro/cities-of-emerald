# Arc Outline — M1-PG (for approval)

**Status: APPROVED 2026-09-17 (name + same-sites reuse as proposed) —
implementing on cities/task-10-m1pg.**

The first postgame arc. Existing maps only — in fact, the same three
maps as M1, on purpose. Levels use the fixed postgame tier (GDD 6.4:
level 60), which the existing 10.0a special already produces after the
Champion. Postgame legendaries always obey (GDD 6.5), so there is no
obedience wiring.

---

## M1-PG — "Stranger Weather" (Galarian Articuno, Zapdos, Moltres)

**Opens:** after the League, with M1 complete · **Obeys:** always
(postgame rule) · **Reward:** none (GDD 6.6).

*(Quest name "Stranger Weather" is [PROPOSED].)*

### Design notes

- **Same sites, wrong readings.** M1 ended with the reporter musing "I
  wonder where storms like that come from…" — M1-PG answers by
  echoing. The three anomalies return to the exact same places, but
  every reading is wrong: cold that registers as silence, storms with
  no charge, fire that doesn't burn. The birds' story continues —
  through their Galarian counterparts *(sites [PROPOSED]: reusing the
  M1 trio keeps the "story continues" hook literal and needs zero new
  wiring risk)*:
  - **Galarian Moltres — Fiery Path** (dark flame; the fire that
    doesn't burn)
  - **Galarian Articuno — Shoal Cave, ice room** (psychic chill; the
    cold that reads as silence)
  - **Galarian Zapdos — New Mauville** (fighting gusts; the storm
    with no charge)
- **The reporter reprises.** No new NPC: the M1 reporter in the
  Slateport Pokémon Center gets a postgame branch. Once the player is
  Champion with M1 complete, her "where do storms come from" musing
  becomes the arc opener: her old story got a sequel.

### Story beats

1. **The follow-up.** Champion + M1 complete → the reporter's new
   report: all three anomalies are back, and her instruments must be
   broken, because every reading is impossible. The journal quest
   "Stranger Weather" opens with the three familiar sites.
2. **The sites.** Each Galarian bird waits as a visible static where
   its counterpart stood — same encounter flow, fixed level 60, KO'd
   bird returns on re-entry, only catching removes it. All three are
   reachable immediately (the player has had Surf and the postgame for
   a while).
3. **The wrap.** All three caught → the reporter retires the story:
   "Two sets of three. Same sky, different songs. Best story of my
   career — twice." (No further tease; the GDD keys nothing to
   M1-PG's completion.)

### Mechanics

- **Levels:** the existing `Script_CitiesGetLegendaryLevel` special
  already settles at the 60 tier once the automatic cap ends
  post-Champion (GDD 6.4) — the site scripts reuse it unchanged.
- **Arc table:** `CITIES_ARC_M1PG` joins the shared arc table with
  `FLAG_SYS_GAME_CLEAR` as its "obey" flag — always set by the time
  these can be fought, so the postgame always-obeys rule falls out of
  the existing 10.0b check with no special case. This also gives the
  reporter's wrap the standard 10.0c all-caught special.
- **Story-only:** the Galarian forms are already covered by
  `IsStoryOnlySpecies` (regional forms of legendaries) and the wild
  sweep test.
- **Journal:** "Stranger Weather" activates post-League with M1
  complete, shows N of 3, no obedience note (never needed).
- Site maps already call M1's visibility/on-resume hooks — the new
  bird objects ride the same pattern with their own flags.

### Save data

- `VAR_CITIES_M1PG_STATE`: 0 = not started, 1 = reporter met,
  2 = complete
- `FLAG_CITIES_HIDE_M1PG_ARTICUNO/ZAPDOS/MOLTRES`,
  `..._M1PG_ARTICUNO/ZAPDOS/MOLTRES_CAUGHT`
- No save-layout change (reserved ranges only).

### Playtest items

- Reporter's postgame branch appears only when Champion AND M1 is
  complete (check: Champion with M1 unfinished → old dialogue)
- All three Galarian birds visible at their sites, fight at level 60,
  return after a KO, disappear only on catch
- Galarian birds obey immediately when caught (no disobedience
  message ever)
- Journal quest opens with the reporter, shows N of 3, completes and
  drops off after her closing line
- Wild sweep: no Galarian bird appears in any random source (existing
  test suite gate)
