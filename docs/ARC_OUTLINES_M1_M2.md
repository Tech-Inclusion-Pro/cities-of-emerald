# Arc Outlines — M1 & M2 (for approval)

**Status: APPROVED 2026-09-16 — both arcs implemented on cities/task-10-shared.**

Both arcs use **existing maps only** — no Porymap work needed. Encounter
levels come from the shared 10.0a special (auto badge cap); obedience is the
shared 10.0b rule; final "all caught" beats use the 10.0c hook.

---

## M1 — "Strange Weather" (Articuno, Zapdos, Moltres)

**Opens:** badge 3 · **Obeys:** badge 4 (Heat Badge) · **Reward:** none
(completing M1 is the postgame key to M1-PG, the Galarian birds).

### Story beats

1. **The reports.** After badge 3, a weather reporter appears in the
   Slateport Pokémon Center, worried about three anomalies: an ice storm
   deep in Shoal Cave, electrical surges under New Mauville, and a heat
   bloom inside Fiery Path. The journal quest "Strange Weather" opens with
   all three sites listed.
2. **The sites.** At each location a field scientist NPC stands near the
   entrance describing the anomaly in plain language. Deep inside, the bird
   waits as a visible static encounter (new object on the existing map):
   - **Moltres — Fiery Path** (reachable immediately at badge 3)
   - **Articuno — Shoal Cave, ice room** (needs Surf → badge 5)
   - **Zapdos — New Mauville, generator room** (needs Surf → badge 5)
3. **Pacing note.** One bird is reachable the moment the arc opens; the
   other two arrive naturally with Surf. The journal marks the two
   Surf-gated sites clearly ("You'll need SURF to reach it.").
4. **The wrap.** With all three caught, the reporter celebrates: the
   weather has settled — "though I wonder where storms like that come
   from…" (M1-PG hook, postgame).

### Mechanics

- Statics: level = shared 10.0a special; battle music + standard legendary
  encounter flow; fainting a bird does NOT lose it (it returns when you
  re-enter the map) — accessibility-friendly, no permanent misses.
- Catch hides that bird's object (per-bird hide flag set on catch only).
- Journal: "Strange Weather" shows N of 3 and, while any caught bird is
  still badge-gated, the obedience note ("Your bird won't listen until you
  earn the HEAT BADGE.").

### Save data

- `VAR_CITIES_M1_STATE`: 0 = not started, 1 = reporter met, 2 = complete
- `FLAG_CITIES_HIDE_M1_REPORTER`, `..._HIDE_M1_ARTICUNO/ZAPDOS/MOLTRES`
  (+ 3 site-scientist hide flags)

---

## M2 — "The Sealed Chamber, Opened" (Regirock, Regice, Registeel)

**Opens:** badge 5 · **Obeys:** badge 6 (Feather Badge) · **Reward:** none
(M2 completion is the postgame key to H3, Regigigas's arc).

### Story beats

1. **The archaeologist.** After badge 5, an archaeologist NPC appears in a
   Pacifidlog house. She's spent years on the Sealed Chamber and shares her
   field notes — the journal quest "The Sealed Door" opens with the full
   route written in plain language (this is the vanilla Relicanth/Wailord
   puzzle, made legible; the braille stays for flavor, but every braille
   sign now also shows a plain-text translation box after it).
2. **The trail.** The vanilla Sealed Chamber flow, unchanged mechanically:
   dive on Route 134, read the chamber, bring Relicanth (front) and Wailord
   (last), open the three ruins. Since Dive arrives with badge 7, the
   badge-5 opening is the *hint trail* — the journal says exactly what
   you'll eventually need, so nothing is a wiki lookup.
3. **The giants.** Desert Ruins / Island Cave / Ancient Tomb statics now
   use the shared level special instead of fixed level 40, and the same
   no-permanent-miss rule as M1.
4. **The wrap.** All three caught → the archaeologist celebrates and reads
   one more line from her notes: something about a "colossus that moved
   whole continents" (H3 hook, postgame).

### Mechanics

- Vanilla puzzle scripts stay; Cities adds the archaeologist, the journal
  quest, plain-language braille translations, and the level/respawn changes
  to the three statics.
- By the time the chambers can physically open (badge 7), the Feather
  Badge obedience threshold is already met — late catches obey immediately,
  per GDD 6.5.

### Save data

- `VAR_CITIES_M2_STATE`: 0 = not started, 1 = archaeologist met, 2 = complete
- `FLAG_CITIES_HIDE_M2_ARCHAEOLOGIST`

---

## Shared playtest items (both arcs)

- NPC reachability at all sites (coords placed from data)
- Static levels rise correctly with badges; obedience messages correct
- Fainted legendary returns on map re-entry; caught one never returns
- Journal counts and Surf/Dive gating notes read correctly
