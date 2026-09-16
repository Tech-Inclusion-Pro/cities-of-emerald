# Cities of Emerald — Implementation Plan

Companion to `CITIES_OF_EMERALD_GDD.md` (the design). This file is the build order for Claude Code.

---

## 0. Working agreement (read first, every session)

1. **Ask before acting.** Before editing anything, summarize the task, list the files you plan to change, and wait for Rocco's approval.
2. **Respect status tags** in the GDD. Build only **[DECIDED]** items. For **[PROPOSED]** or **[OPEN]** items, stop and ask.
3. **Verify, don't invent.** Config names and paths in these docs are best-known references. Search the repo to confirm them. If something doesn't exist, report it and propose options.
4. **One task at a time.** One task = one Git branch = one or more small commits.
5. **Every task ends with:** a successful build, the relevant tests passing, a short manual test checklist for Rocco to run in mGBA, and a summary of what changed.
6. **Flag decisions.** If a task forces a design choice, surface it instead of resolving it silently.
7. **Never commit ROM files** (`*.gba`, `*.sav` from real games) or copyrighted assets not already in the repo.
8. **Language:** all new player-facing text uses plain language and avoids ableist wording.
9. **Update the GDD** only when Rocco approves a design change, and change the status tag accordingly.

Tip: this section can be copied into a `CLAUDE.md` at the repo root so Claude Code loads it automatically.

---

## Phase 0 — Setup and baseline

**Task 0.1 — Clone and build**
- Clone `https://github.com/rh-hideout/pokeemerald-expansion`, check out `upcoming`.
- Follow the repo's `INSTALL.md` for macOS.
- Build with `make -j$(sysctl -n hw.ncpu)`.
- Done when: the ROM builds and boots in mGBA.

**Task 0.2 — Repository hygiene**
- Create a project branch `cities/main`.
- Add `.gitignore` entries for ROMs, saves, and emulator files.
- Add `docs/` with both design files.
- Add the `rh-hideout` remote for future upstream pulls.

**Task 0.3 — Test and debug tools**
- Confirm the expansion test runner works (`make check` or current equivalent).
- Enable the debug menu in the debug config for development builds only.

**Task 0.4 — Save and flag audit**
- Report: free flags, free vars, free save block space, and how the expansion allocates them.
- Produce `docs/SAVE_BUDGET.md` estimating space for: rankings, rematch version bits, accessibility settings, quest journal, arc flags, challenge modes.
- Stop and review with Rocco before Phase 1.

---

## Phase 1 — Config toggles (GDD Section 3)

Mostly edits in `include/config/*.h`. One task per group.

**Task 1.1 — Battle mechanics:** physical/special split, Fairy, Megas, Z-Moves, Dynamax, Terastallization, latest-generation data, wild double battles.
**Task 1.2 — Overworld:** Overworld Wild Encounters, time of day, ambient cries (OWE priority), followers, DexNav, encounter/trainer-sight toggle flags, Repel prompt, Lures, indoor running.
**Task 1.3 — Quality of life:** reusable TMs, bag sorting, bag capacity, National Dex from start.
**Task 1.4 — Level caps:** soft cap type, flag-list caps (values are [PROPOSED]; ask first).
**Task 1.5 — Training:** EV cap, hidden abilities, breeding improvements (Everstone, Destiny Knot).

Done when: each toggle is documented in `docs/CONFIG_CHANGES.md` (setting, old value, new value, reason) and the game builds and boots.

---

## Phase 2 — Story-only filter (GDD Section 6.2)

**Task 2.1 — `IsStoryOnlySpecies(species)`**
- Use species info flags for legendary, mythical, Ultra Beast, and Paradox (verify names).
- Add an explicit list: Type: Null, Silvally, Cosmog, Cosmoem, Kubfu, Urshifu (all forms), Meltan, Melmetal, Poipole, Naganadel.
- Include regional forms.

**Task 2.2 — Tests**
- Test that known legendaries return true and common species return false.
- Build-time check: fail the build if any story-only species appears in `wild_encounters.json`.

**Task 2.3 — Wire into random sources** (as each source is built): OWE spawning, DexNav, random trade, randomizer, Battle Frontier random pools, Battle Pyramid.

---

## Phase 3 — Starter selection (GDD Section 4.2)

**Task 3.1 — Data:** a table of 10 options (9 regions + Special) mapping to species.
**Task 3.2 — UI:** replace the vanilla starter screen (`src/starter_choose.c` or current equivalent) with the region list → Pokémon view → confirmation flow. Text labels for types. B goes back.
**Task 3.3 — Rival logic:** rival picks a type-advantaged starter; update every rival team that branches on starter choice.
**Task 3.4 — Tests:** each of the 28 choices produces the right species at level 5 and a valid rival team.

---

## Phase 4 — Wild encounters (GDD Section 5)

**Task 4.1 — Species planning sheet**
- Generate `docs/species_plan.csv` with columns: species, generation, evolution stage, habitat, tier (T1–T5 or PG), map, table (land/water/fish/rock smash), time of day, rarity.
- Pre-fill habitat and tier suggestions; Rocco reviews before any encounter data changes.

**Task 4.2 — Generator script**
- Python script `tools/cities/build_encounters.py` that reads the CSV and writes `src/data/wild_encounters.json` (time-of-day groups, main and postgame sets).
- Validates: slot counts, story-only exclusion, every non-story-only species obtainable (wild or by evolution).

**Task 4.3 — Postgame table switch:** swap to postgame tables once the Champion flag is set.
**Task 4.4 — Trade evolution alternatives:** Linking Cord or equivalent ([PROPOSED]; ask first).
**Task 4.5 — Eevee stone NPC** in Dewford after badge 2: plain-language explanation of each stone and Eeveelution (type as text), player picks one stone (GDD 4.3).
**Task 4.6 — Eeveelution trainer mini-story:** trainers who award their stone when beaten; friendship-evolution trainers explain instead; quest journal entries. Trainer locations are [PROPOSED]; ask first.

---

## Phase 5 — Difficulty, assist, and setup screen (GDD Sections 4.1 and 10)

**Task 5.1 — New-game setup screen:** accessibility preset, difficulty, challenge toggles.
**Task 5.2 — Difficulty modes:** use expansion trainer difficulty support if present; otherwise propose an approach.
**Task 5.3 — Assist mode:** no money loss, heal after loss, level cap adjustment.

---

## Phase 6 — Accessibility (GDD Section 11)

**Task 6.1 — Settings storage:** accessibility settings struct in save data (bitfields), with defaults and presets defined in one file.
**Task 6.2 — Accessibility menu:** new menu (separate from vanilla Options), multiple pages, all text-based.
**Task 6.3 — Vision:** type text labels, high-contrast palettes, effectiveness indicator, numeric HP, patterned HP bars.
**Task 6.4 — Motor:** toggle run, auto-run, fewer confirmations, hold-to-confirm.
**Task 6.5 — Sensory:** reduced flashing, reduced shake, battle speed, skip animations.
**Task 6.6 — Text:** slow/instant speeds and wait-for-button.
**Task 6.7 — Hearing:** visual cues for ambient cries and hidden items; sound subtitles.
**Task 6.8 — Presets:** Low Vision, Reduced Motion, Reading Support, One-Handed.
**Task 6.9 — Pace-slowing list:** a single function `CountPaceSlowingFeatures()` used by rankings (GDD 8.4).
**Task 6.10 — In-world guide NPC** in Littleroot.

Manual test for each task: a checklist Rocco can run with each option on and off.

---

## Phase 7 — Rankings (GDD Section 8)

**Task 7.1 — Battle tracking:** per battle, record which party slots used a move and which fainted; record battle duration in frames.
**Task 7.2 — Eligibility:** regular trainers use trainer-defeated flags; gym leader/rival versions use version bits; show the "won't change your ranking" notice before ineligible battles.
**Task 7.3 — Scoring:** implement the table in GDD 8.3 and the timer rule in 8.4 (base 60 s + 60 s per pace-slowing feature + manual extra time).
**Task 7.4 — Unit tests:** cover best win (14), worst loss (−7), the zero floor (total never below 0), doubles, a Pokémon that switched in without acting, repeat battles, and timer extensions.
**Task 7.5 — Ranked NPCs:** leaderboard data and milestone-based NPC scores ([PROPOSED] roster; ask first).
**Task 7.6 — Rankings screen:** start-menu entry, text-based list.
**Task 7.7 — Pokémon Master:** event when the player reaches the top.
**Task 7.8 — Challenges:** overworld challenge events from ranked trainers.

---

## Phase 8 — Rematches (GDD Section 7.3)

**Task 8.1 — Version system:** each gym leader and rival has numbered rematch versions unlocked by story flags.
**Task 8.2 — Teams:** stronger, different teams per version (drafted in `src/data/trainers.party` or current format; Rocco reviews teams).
**Task 8.3 — Ranking hook:** each version earns points once.

---

## Phase 9 — Quest journal, recap, hints (GDD Section 11.4)

**Task 9.1 — Quest data:** one table listing each quest, its flags, and a plain-language next-step string per stage.
**Task 9.2 — Journal UI** in the start menu.
**Task 9.3 — "Last time" recap** on load.
**Task 9.4 — Hint guide.**
**Task 9.5 — Replayable tutorials.**

Build this before the story phases so every new arc registers its quest entries as it is written.

---

## Phase 10 — Mid-game legendary arcs (GDD Sections 6.4–6.7, M1–M5 and M1-PG)

The arc plan is [DECIDED]. Shared systems come first:

**Task 10.0a — Level-matched static encounters:** mid-game legendary level = current level cap at encounter time.
**Task 10.0b — Badge-based obedience** for story-only species (GDD 6.5): check required badge per arc, clear battle message instead of random disobedience, obey immediately if the badge is already earned. M5 exception: Latias and Latios obey once both have been caught (one-time flag, never revoked). Unit tests for each arc's rule, late catches, and the M5 flag surviving a trade or release.
**Task 10.0c — Arc reward hook:** reusable script pattern for giving an arc's final reward after all its Pokémon are caught.

Then, for each arc:
1. Outline (story beats, maps, flags, unlock badge) for approval
2. Maps in Porymap
3. Scripts (poryscript if adopted, otherwise the repo's script format)
4. Quest journal entries
5. Static encounter setup
6. Playtest checklist

---

## Phase 11 — Postgame thread 1: hidden areas (H1–H11)

Same per-arc steps as Phase 10. All areas and characters are original. Postgame encounter levels follow the fixed tiers in GDD 6.4.

**Task 11.x — Plate hunt:** place all 17 Arceus Plates across Hoenn, tracked in the quest journal (GDD 6.7).

---

## Phase 12 — Postgame thread 2: Team Epoch (V1–V5)

Team Epoch's identity is [DECIDED] (GDD 7.2). Items still [OPEN] or [PROPOSED] (the Archivist's appearance, admins and grunts, the Coralmere survivors) must be confirmed before the related scripts are written.

**Task 12.1 — Story outline:** full beat sheet for V1–V5 for Rocco's review.
**Task 12.2 — Weather Institute changes:** the Archivist's history and clues; coordinate with Shaymin's event.
**Task 12.3 — Coralmere (present):** surface ruins on Route 128 visible from the start of the game; sunken village map reachable with Dive.
**Task 12.4 — Coralmere (past):** time-rift version of the village for the V4 scene.
**Task 12.5 — Arcs V1–V5:** same per-arc steps as Phase 10.
**Task 12.6 — Ending:** Kai's heroic act (shutting down the time rift to save Pacifidlog, GDD 7.2), the family approaching him, and an acceptance-based resolution; Team Epoch changes direction instead of being defeated. The Archivist's name, Kai, is spoken and a flag switches his displayed name to Kai everywhere afterward.
**Task 12.7 — Coralmere survivors:** a scattered group of survivor NPCs across many towns, each with an early hint about Coralmere and new dialogue after the V4 reveal (roster [PROPOSED] in GDD 7.2; confirm before writing).
**Task 12.8 — Name check:** a test or script that fails if "Kai" appears in any text shown before the ending flag is set.

## Phase 13 — Mythical events and completeness

**Task 13.1 — Mythical events** (locations in GDD 6.6; all unlock after the League; levels are [OPEN], so ask before setting). Includes the new postgame Trick House room for Hoopa and the Meltan collection hunt.
**Task 13.2 — Completeness test:** every story-only species appears in exactly one arc or event.

---

## Phase 14 — Remaining postgame features

**Task 14.1 — Champion defense** (details [OPEN]).
**Task 14.2 — Random-trade NPC** (uses the story-only filter).
**Task 14.3 — Trainer card stamps and achievements.**
**Task 14.4 — Shiny Charm reward** ([PROPOSED]).
**Task 14.5 — Move relearner/deleter placement** ([PROPOSED]).

---

## Phase 15 — Challenge modes (GDD Section 10)

**Task 15.1 — Nuzlocke mode:** first-encounter-per-area tracking, fainted Pokémon locked, clauses.
**Task 15.2 — Randomizer:** seeded; separate toggles for wild, starters, trainers, items; always uses the story-only filter.

---

## Phase 16 — Release

**Task 16.1 — Full playtest checklist** (main story, each arc, each accessibility preset, each challenge mode), run on mGBA plus at least one Android and one iOS emulator.
**Task 16.2 — Patch:** create a BPS patch against a clean Emerald ROM (for example, with Floating IPS or `flips`), and record the expected ROM checksum.
**Task 16.3 — Player guide:** patching, mGBA setup, controller setup, accessibility options, emulator text-to-speech notes.
**Task 16.4 — Encounter and item documentation** generated from the species plan.

---

## Later (do not build)

- Street Fighter-style fighting mode
- Spanish translation
- Second region
