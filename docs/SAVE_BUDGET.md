# Cities of Emerald — Save Budget

Task 0.4 deliverable. Measured on `upcoming` (commit at clone, 2026-09-16) with the **default config** via a compile probe (`sizeof` of each struct, arm-none-eabi-gcc 14.3.1). Re-measure after any config change: enabling followers, DexNav search levels, apricorn trees, or fake RTC grows SaveBlock3.

> **Update 2026-09-16 (post Phase 1):** the Cities flag/var ranges (+192 B), bag expansion (+376 B), and `FREE_MYSTERY_GIFT` (−876 B) are live. SaveBlock1 measured: **15,260 B used, 612 B free**. `FREE_MYSTERY_EVENT_BUFFERS` was tried and REVERTED — it crashes the expansion's test suite (heap corruption; see CONFIG_CHANGES.md). Its 1,104 B plus the other FREE_* options remain in reserve. Numbers below are the original pre-Phase-1 audit.

## 1. Current state (measured)

| Block | Used | Capacity | Free | Enforced by |
|---|---|---|---|---|
| SaveBlock1 | 15,568 B (0x3CD0) | 15,872 B (4 sectors) | **304 B** | `STATIC_ASSERT` in `src/save.c:82` |
| SaveBlock2 | 3,884 B (0xF2C) | 3,968 B (1 sector) | **84 B** | `src/save.c:81` |
| SaveBlock3 | 4 B | 1,624 B (116 B × 14 sectors) | **1,620 B** | `src/save.c:80` |

Build fails at compile time if any block overflows — we cannot silently corrupt saves.

**Reserve capacity via `include/config/save.h` `FREE_*` toggles** (single-player hack; link-era features are dead weight):
- SaveBlock1: up to ~2,516 B (mystery event/gift buffers, match call, union room chat, enigma berry, link battle records, trainer hill/tower)
- SaveBlock2: up to ~1,274 B (e-reader, record-mixing hall records, Pokémon Jump)

Caution: `FREE_TRAINER_HILL`/`FREE_TRAINER_TOWER` remove those facilities; the GDD keeps the Battle Frontier, so leave these alone unless space runs out. Mystery gift/event, record mixing, union room, e-reader are safe to free for an emulator-only single-player hack — **flagged for Rocco's approval before enabling any.**

## 2. Flags and vars (in SaveBlock1)

- **Flags:** 2,400 total (`FLAGS_COUNT` 0x960, 300 B). ~372 unused vanilla IDs, largest clean runs: 0x8E3–0x8FF (29), 0x920–0x95F daily block (~55). Temp flags cleared per map load: 0x0–0x1F.
- **Vars:** 256 total (512 B). Only ~30 unused vanilla IDs — this is the scarce resource.

**Recommendation:** don't scavenge scattered vanilla IDs. Raise `FLAGS_COUNT` and `VARS_COUNT` to create contiguous, named Cities ranges:
- `+512 flags` (`CITIES_FLAGS_START`) → +64 B in SaveBlock1
- `+64 vars` (`CITIES_VARS_START`) → +128 B in SaveBlock1
- Total +192 B — fits in today's 304 B free with 112 B margin.

## 3. Feature-by-feature estimate

| Feature (GDD §) | Storage | Estimate |
|---|---|---|
| Rankings — player score (8.6) | s32 in new struct | 4 B |
| Rankings — regular trainers already counted (8.6) | reuse vanilla trainer-defeated flags | 0 B |
| Rankings — rematch version bits (7.3, 8.6) | 8 leaders × 3 versions + rivals ≈ 32 bits | 4 B |
| Rankings — NPC leaderboard scores (8.5) | computed from story flags at display time | 0 B |
| Accessibility settings (11) | bitfield struct: ~16 toggles + text speed, battle speed, extra time, preset | 8 B |
| Quest journal (11.4) | ~45 quests × 4-bit stage + unread bits | 32 B |
| Arc flags (6.3, 6.6) | ~10 flags × 22 arcs + ~8 × 14 events ≈ 330 flags | from new flag range |
| Arc vars (encounter state, roamers) | ~1–2 vars per arc ≈ 40 vars | from new var range |
| Plate hunt (6.7), survivors met (7.2), M5 obedience (6.5), Kai name flag (12.6) | ~30 flags | from new flag range |
| Challenge modes (10) | Nuzlocke per-area bits (~130 areas) + clauses + randomizer seed u32 + toggles + difficulty/assist | 32 B |
| **New struct total** | | **~80 B → budget 128 B** |
| **Flag/var range growth** | | **+192 B** |

## 4. Recommended layout

1. **`struct CitiesSave` (~128 B) in SaveBlock3** — 1,620 B free today, and it exists precisely for hack additions. Holds: ranking score, rematch bits, accessibility settings, quest stages, challenge state.
2. **Flag/var range growth (+192 B) in SaveBlock1** — flags/vars must stay in SaveBlock1 (script engine reads them there).
3. **Keep `FREE_*` toggles as reserve** — don't spend them yet.

Projected after Phase 1+: SaveBlock1 ~112 B free, SaveBlock3 ~1,490 B free (before follower/DexNav config growth — re-probe when Phase 1 config lands).

## 5. Risks and open items

- **DexNav search levels** (`USE_DEXNAV_SEARCH_LEVELS`): `u8 × NUM_SPECIES` (~1,500+ B with forms) — would overflow SaveBlock3 on its own. GDD wants DexNav; search levels are an optional sub-feature. **Recommend OFF; needs Rocco's call in Phase 1 (Task 1.2).**
- **Followers / fake RTC / apricorn trees** each add small SaveBlock3 fields when enabled — re-run the probe after Task 1.2.
- Quest journal text (next-step strings) lives in ROM, not save — no save cost.
- Battle-in-progress ranking tallies (which mon acted/fainted, frame timer) are runtime-only — no save cost.
