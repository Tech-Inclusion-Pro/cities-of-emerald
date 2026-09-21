# Cities of Emerald

**An accessibility-first Pokémon Emerald ROM hack.** Every Pokémon from all nine generations, every legendary woven into a story you can actually follow, a new villain arc about memory and loss — and a game that meets players where they are, whatever their access needs.

> ⚠️ **Status: in development.** All content through Phase 15 is built and passing the automated test suite (5,500+ tests). A public release patch (BPS) will follow the final playtest pass. **No ROMs are or ever will be distributed from this repository** — see [Legal](#legal--license).

---

## What makes this hack special

### Accessibility is the design center, not an afterthought

Cities of Emerald was built by [Tech Inclusion Pro](https://github.com/Tech-Inclusion-Pro) with disabled players in mind from the first design document. Accessibility features are first-class systems with their own save data, menus, and automated tests:

- **The ACCESS menu** — a dedicated start-menu entry with player-adjustable options: instant text, auto-run, toggle-run, reduced screen shake, skippable battle animations, high-contrast text boxes, adjustable battle speed, wait-for-button message pacing ("messages never advance until you say so"), fewer required button presses, reduced flashing, and a toggle for plain-language type-effectiveness hints in battle.
- **Accessibility presets** offered during the opening (in the moving truck) and changeable any time via a guide NPC in Littleroot — you don't have to dig through menus to get a comfortable setup.
- **Assist Mode** — removes the money penalty for losing battles, so experimenting is never punished.
- **Flexible level caps** — automatic badge-based caps, a softer "+10" mode, fixed caps, or none, chosen by the player.
- **Difficulty choice at the start** (with per-difficulty trainer parties), not locked behind a completed save.
- **Plain language everywhere.** All new text follows a plain-language style guide and avoids ableist wording — this is enforced as a written rule of the project. The Braille chambers from the original game now display a plain-text translation after every Braille message, so the Regi questline is fully playable without outside guides.
- **No trade-locked Pokémon.** A purchasable Linking Cord and partner-in-party evolution methods mean every evolution is reachable by a solo player on a single device.
- **A free move relearner and move deleter** (no Heart Scale grinding) in Mauville.
- **In-game journal and tutorials.** A quest journal tracks the main story and side arcs in plain language, and a guide NPC offers seven optional tutorials — nobody should need a wiki to finish this game.

Planned (menu space reserved, pending art/engine work): numeric HP display, patterned HP bars, visual sound cues, and hold-to-confirm.

### Inclusive by default

- **Character setup doesn't ask your gender.** The intro asks *"Which of these styles feels like you?"* with **STYLE 1 / STYLE 2** options — same classic sprites, no boy/girl framing.
- **Pronoun choice** — He / She / They / or type your own, chosen during the opening and fully decoupled from which sprite you picked.
- A third avatar and fuller character customization (hair, clothing) are on the roadmap, pending sprite art.

### Every legendary has a story

Vanilla Emerald scatters a handful of legendaries around; most games since make them random encounters. Cities of Emerald makes **every legendary and mythical Pokémon a story-only species** — none appear as random wilds, and each is placed in exactly *one* arc, event, or hidden area (there's an automated "completeness test" that fails the build if any species is unobtainable or placed twice):

- **Five mid-game arcs** — the Kanto birds tracked with a Slateport reporter; the Regi ruins with a Pacifidlog archaeologist (and readable Braille); the roaming Johto beasts with a chase-and-corner mechanic; the lake trio hidden in the **restored, never-used Ruby/Sapphire chambers of the Cave of Origin** (the original maps were still in the game data — we reconnected them rather than building replacements); and the Eon pair on Southern Island.
- **Twelve hidden postgame areas**, seven of them brand-new maps built tile-by-tile in the original tilesets — the Swords of Justice in a hollow behind Littleroot, a moonlit cove for Cresselia and Darkrai, a Tapu shrine atoll, Heatran's ember vault, the elder colossi, an old-growth canopy for Ho-Oh, Lugia, and Celebi, the forces of nature on a windswept rise, Zygarde cell-collecting under Mossdeep, the Tao trio in a resonance hall, the hero duo and Calyrex in a meadow, the Treasures of Ruin and Loyal Three past Oldale, and the creation trio plus a 17-plate hunt across all of Hoenn ending at Arceus's altar.
- **Sixteen mythical events** — from Jirachi at the Cozmos' house to a Trick House ring puzzle for Hoopa and a Meltan nut-hunt on the Slateport docks.
- **Per-arc level tiers and obedience rules** keep the postgame challenging without artificial gates.

### A new villain: Team Epoch

A five-part postgame story about a quiet team buying up old weather records — leading to the Weather Institute's hidden history, ultra wormhole cleanup, paradox Pokémon, a sunken village called **Coralmere** you visit both as present-day ruins *and* through a rift to its past, an Eternatus storm over Pacifidlog, and an ending that comes down to speaking one person's name. Eight survivor NPCs scattered across Hoenn carry the memory of what happened, if you take the time to listen.

### Systems, not just content

- **Trainer Rankings** — a region-wide battle-performance leaderboard against 19 ranked NPCs. Winning cleanly matters; becoming the **Pokémon Master** is a real, tracked achievement with a ceremony.
- **Three-stage gym rematches** (with doubles formats), rival rematches that adapt to your starter, roaming overworld challengers, and an on-demand **Champion title defense**.
- **Challenge modes** chosen at new game: a built-in **Nuzlocke mode** (first-encounter catch rule enforced by the engine, dupes and shiny clauses, fainted partners moved to a locked memorial box) and a built-in **seeded randomizer** (wild, starter, and/or trainer Pokémon — deterministic per seed).
- **Starters from all nine regions** — pick your region, then your partner, or take a special option (Eevee, Pikachu, or Ditto). Your rival adapts.
- Modern quality-of-life throughout: visible overworld encounters, follower Pokémon, day/night with time-of-day encounters, DexNav, reusable TMs, National Dex from the start.

---

## What this is built on (credit where it's due)

Cities of Emerald stands on a lot of other people's work. This section is the honest map of what came from where.

### The foundations

| Project | Authors | What it provides |
|---|---|---|
| [pret/pokeemerald](https://github.com/pret/pokeemerald) | the **pret** team | The complete decompilation of Pokémon Emerald — the reason ROM hacks like this can exist at all. Years of painstaking reverse engineering, freely shared. |
| [rh-hideout/pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion) (v1.17.0+, `upcoming` branch) | **RHH (Rom Hacking Hideout)** and [all contributors](CREDITS.md) | The engine this hack runs on: the modern battle engine, all Pokémon/moves/items/abilities through Generation IX, the automated test framework, debug tools, and hundreds of quality-of-life features. |

The expansion is a *developer base*, not a playable game — Cities of Emerald is one game built on top of it. Per RHH's request: **Based off RHH's pokeemerald-expansion 1.17.0+ — https://github.com/rh-hideout/pokeemerald-expansion/**. The expansion's own README is preserved here as [`EXPANSION_README.md`](EXPANSION_README.md), its full feature list as [`FEATURES.md`](FEATURES.md), and its complete contributor list as [`CREDITS.md`](CREDITS.md).

### Features that began life in other people's hacks and branches

These systems were created by individual hackers, later integrated into pokeemerald-expansion, and are used (and in places re-tuned) by this hack:

- **Overworld follower Pokémon, visible overworld wild encounters, and the day/night system** — originally by **[@aarant / merrp](https://github.com/aarant/pokeemerald)** (the famous `followers-expanded-id` and `lighting-expanded-id` branches, first built for FireRed followers). *How Cities differs:* overworld encounters are filtered through our story-only species system so legendaries never pop as random overworld spawns, and time-of-day encounter tables were authored for every route from a single species-plan spreadsheet.
- **DexNav** — originally by **[@ghoulslash](https://github.com/ghoulslash/pokeemerald)**, integrated into the expansion in [PR #4818](https://github.com/rh-hideout/pokeemerald-expansion/pull/4818). An ORAS-style search tool, here also taught to respect story-only species. ghoulslash also authored the expansion's NPC "follow me" system, obtained-item descriptions, and saveblock cleansing.
- **Overworld debug menu** — originally by **[@TheXaman](https://github.com/TheXaman/pokeemerald)** (`tx_debug_system`). Used constantly during development; stripped from release builds.
- **Dynamic multichoice menus** — by **[@SBird1337](https://github.com/SBird1337/pokeemerald)**. Cities' region-starter picker, accessibility presets, and guide menus are built with it.
- **BW-style map pop-ups** — by **@BSBob** (via [@ravepossum](https://github.com/ravepossum/pokeemerald)).

The full attribution list for everything inside the expansion lives in [`FEATURES.md`](FEATURES.md) and [`CREDITS.md`](CREDITS.md) — if you build on this repo, please keep crediting all of those people.

### Ideas borrowed from the wider community

- **Nuzlocke mode** implements the community ruleset first popularized by **Nick Franco's Nuzlocke comics** (2010) and refined by fifteen years of community play. Our engine-enforced version (catch-blocking, memorial box) is original code, but the rules belong to the community.
- **The built-in randomizer** follows the tradition established by tools like the **Universal Pokémon Randomizer** — ours is an in-engine, seeded implementation so runs are shareable and race-able, but the *idea* of randomized playthroughs is community heritage.
- The restored Cave of Origin chambers use map data Game Freak shipped but never used — we reconnected what was already there.

### Original to Cities of Emerald

The accessibility system, rankings/Master system, story-only species framework and completeness test, all story arcs (M1–M5, the hidden areas, Team Epoch V1–V5 and the Coralmere maps), the Nuzlocke/randomizer engine code, the pronoun and style-based intro, the journal, the level-cap and obedience systems, and seven new maps — written for this project, and MIT-licensed (see below) so other hacks can take them.

---

## Building from source

You need your own legally obtained copy of Pokémon Emerald to play the result. This repo contains no ROMs and no Nintendo-owned assets beyond what the pret decompilation reconstructs.

```bash
# Toolchain: ARM GNU Toolchain (arm-none-eabi), plus the standard pokeemerald prerequisites
# See INSTALL.md (from pokeemerald-expansion) for full setup on your platform.
make -j$(nproc)          # produces pokeemerald.gba (the Cities of Emerald build)
make check -j$(nproc)    # run the full automated test suite
```

Development docs live in [`docs/`](docs/): the game design document (`CITIES_OF_EMERALD_GDD.md`), the phase-by-phase implementation plan, per-arc story outlines, the config change log, and the manual playtest checklist.

---

## Legal & license

- Pokémon, Pokémon character names, and all related assets are © Nintendo, Creatures Inc., and GAME FREAK Inc. This is an unofficial fan project, **not** affiliated with, endorsed by, or sponsored by any of them.
- **This repository does not distribute ROMs.** The eventual release will be a **BPS patch** that requires your own legally obtained copy of Pokémon Emerald.
- The decompiled base game code (from pret/pokeemerald, via pokeemerald-expansion) carries no license, because it is a reconstruction of copyrighted game code — it is used here under the same community conventions as every other pret-based project.
- **Original Cities of Emerald contributions** — the new C systems (`src/cities_*.c` and friends), scripts, story text, original map data, documentation, and tools written for this project — are released under the **MIT License**. See [`LICENSE.md`](LICENSE.md) for the exact scope.

## Thanks

To **pret**, for the decomp. To **RHH**, for the expansion and for building it in the open with tests. To **merrp/aarant**, **ghoulslash**, **TheXaman**, **SBird1337**, **BSBob**, and every contributor in [`CREDITS.md`](CREDITS.md). To the Nuzlocke and randomizer communities for two decades of showing how players remake games into their own. And to every disabled player who has ever bounced off a game that couldn't be bothered — this one's for you.
