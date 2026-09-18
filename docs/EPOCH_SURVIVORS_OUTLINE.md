# Tasks 12.7 + 12.8 — The Survivors & The Name Check (outline)

**Status: APPROVED + BUILT 2026-09-18.** Closes Phase 12. Build note:
a vanilla Fisherman was named "KAI" (TRAINER_KAI, 713) — renamed to
KENJI (display only; constant unchanged) so the reveal stays clean and
the 12.8 gate passes. The GDD 7.2
survivor roster ([PROPOSED]) is confirmed here with concrete
placements; the Pacifidlog row is already built — the family IS the
eighth survivor.

## 12.7 — The scattered survivors

Seven ordinary NPCs, present from the START of the game, each with
three dialogue stages:
1. **The hint** (always): ordinary flavor that only makes sense
   later — exactly the GDD table's lines.
2. **After the rift walk** (V4 walked): the same person, one step
   more open — the player now knows what Coralmere was, and the
   words land differently.
3. **After the ending** (Kai named): they speak of Kai warmly, by
   name. (These texts live in cities_ending.inc, where all "Kai"
   text is quarantined — see 12.8.)

| # | Town | Who | Sprite | Hint |
|---|---|---|---|---|
| 1 | Dewford beach | a fisher | FISHERMAN | won't fish near Route 128, changes the subject |
| 2 | Slateport market | a vendor | WOMAN_4 | shell charms "made the way they did back home" |
| 3 | Mauville | a street musician | MAN_5 | plays a song about bells ringing over water |
| 4 | Fallarbor | a retired teacher | WOMAN_4 | keeps a hand-drawn map of a village on no official map |
| 5 | Lilycove museum 1F | a painter | ARTIST | one painting shows a bell tower by the sea |
| 6 | Mossdeep shore | an old sailor | SAILOR | keeps the old town sign on his wall at home |
| 7 | Sootopolis | a quiet resident | WOMAN_5 | asks if the legendaries ever regret the storms |
| 8 | Pacifidlog | the family | (built in 12.6) | the bell by the door |

Talking to a survivor (any stage) sets a MET flag (8 flags,
+0x134…+0x13B; the family's is set by the naming scene). Exact
coordinates verified against collision and existing objects at
build time.

**Journal:** a "Voices of Coralmere" entry appears after the rift
walk (V4 state ≥ 2): "{N} of 8 found", with a gentle pointer while
any are missing. It completes and drops off once all eight are met
and the ending has played.

## 12.8 — The name check

A build gate, not a runtime test: `tools/cities/check_kai.py` scans
every player-visible string in the repo — `.string` lines in all
.inc files, `COMPOUND_STRING(...)` contents in src/, `Name:` fields
in trainers.party — and FAILS the build if the word "Kai" appears
anywhere outside `data/scripts/cities_ending.inc` (the one file
whose every path is gated behind FLAG_CITIES_KAI_NAMED or is the
naming scene itself). Wired into `make check` so the suite goes red
if a future line slips.

## Decisions needed from Rocco

1. Confirm the survivor roster + placements above (the last
   [PROPOSED] content roster in Phase 12).
2. Approve the 12.8 mechanism (source-scan build gate in
   `make check`, single allowlisted file).
