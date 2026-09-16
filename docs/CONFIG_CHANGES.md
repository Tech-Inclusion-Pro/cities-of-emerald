# Cities of Emerald — Config Changes

Every Phase 1 toggle: setting, old value, new value, reason. "Already default" rows document GDD items that needed no change. See GDD Section 3.

## Task 1.1 — Battle mechanics

| Setting | File | Old | New | Reason |
|---|---|---|---|---|
| `B_FLAG_DYNAMAX_BATTLE` | include/config/battle.h | 0 (disabled) | `FLAG_CITIES_DYNAMAX_BATTLE` | Wires Dynamax to a flag so story scripts can enable it per battle/area (GDD 3) |
| `B_FLAG_TERA_ORB_CHARGED` | include/config/battle.h | 0 (disabled) | `FLAG_CITIES_TERA_ORB_CHARGED` | Enables Tera Orb charge tracking (auto-set on heal, cleared on Tera) |
| `WE_DOUBLE_WILD_CHANCE` | include/config/wild_encounter.h | 0% | 5% | Wild double battles [DECIDED]; 5% is provisional — **value flagged for Rocco** |
| `WE_DOUBLE_WILD_REQUIRE_2_MONS` | include/config/wild_encounter.h | FALSE | TRUE | Never force a 2-on-1 when the player has one usable Pokémon |

Already default (no change): `B_PHYSICAL_SPECIAL_SPLIT` = GEN_LATEST; Fairy type (built-in, `P_UPDATED_TYPES` = GEN_LATEST); `P_MEGA_EVOLUTIONS` = TRUE; `B_UPDATED_MOVE_DATA` / `B_UPDATED_MOVE_TYPES` / `B_UPDATED_ABILITY_DATA` = GEN_LATEST.

Notes:
- **Z-Moves** have no config toggle; support is built-in and access comes from the Z-Power Ring + Z Crystal items, granted via story scripts in later phases.
- **Mega/Dynamax/Tera player access** likewise comes from key items (Mega Ring, Dynamax Band, Tera Orb) given by scripts; the arcs decide when (later phases).
- **Per-trainer double battles** are set per trainer in the trainer data files, not a global config — handled during trainer rebalancing.

## Task 1.2 — Overworld

| Setting | File | Old | New | Reason |
|---|---|---|---|---|
| `WE_OW_ENCOUNTERS` | include/config/wild_encounter.h | FALSE | TRUE | Overworld Wild Encounters — visible wild Pokémon (GDD 3) |
| `OW_GFX_COMPRESS` | include/config/overworld.h | TRUE | FALSE | Repo recommends FALSE with OWE enabled to prevent VRAM issues |
| `OW_FOLLOWERS_ENABLED` | include/config/overworld.h | FALSE | TRUE | HGSS-style follower Pokémon |
| `OW_TIME_OF_DAY_ENCOUNTERS` | include/config/overworld.h | FALSE | TRUE | Morning/day/evening/night encounter tables |
| `OW_AMBIENT_CRIES` | include/config/overworld.h | VANILLA | OWE_PRIORITY | Ambient cries follow active overworld encounters, per GDD |
| `DEXNAV_ENABLED` | include/config/dexnav.h | FALSE | TRUE | DexNav |
| `DN_FLAG_*` (3), `DN_VAR_*` (2) | include/config/dexnav.h | 0 | Cities flags/vars | Required non-zero assignments for DexNav |
| `WE_FLAG_NO_ENCOUNTER` | include/config/wild_encounter.h | 0 | `FLAG_CITIES_NO_WILD_ENCOUNTERS` | Player-facing encounter toggle (accessibility menu, Phase 6) |
| `OW_FLAG_NO_TRAINER_SEE` | include/config/overworld.h | 0 | `FLAG_CITIES_NO_TRAINER_SIGHT` | Trainer-sight toggle |
| `VAR_LAST_REPEL_LURE_USED` | include/config/item.h | 0 | `VAR_CITIES_LAST_REPEL_LURE_USED` | Saves Repel/Lure menu cursor position |

Already default (no change): `OW_TIMES_OF_DAY` = GEN_LATEST (day/night cycle); `OW_USE_FAKE_RTC` = FALSE (real RTC, per GDD platform testing note); `I_REPEL_LURE_MENU` = TRUE (B2W2 Repel prompt); Lures built into the item system; `OW_RUNNING_INDOORS` = GEN_LATEST; `OW_POKEMON_OBJECT_EVENTS` = TRUE; `OW_ENABLE_DNS` = TRUE (day/night tinting).

Notes:
- `USE_DEXNAV_SEARCH_LEVELS` stays FALSE per the approved save budget (would need ~1,500+ bytes of save space).
- **Auto-run does not exist in the expansion** — it will be custom work in Phase 6 (motor accessibility, Task 6.4), as the GDD anticipated.
- The DexNav start-menu entry appears once `FLAG_CITIES_DEXNAV_GET` is set by a script (decide when during story work; vanilla hacks give it early).

## Task 1.3 — Quality of life

| Setting | File | Old | New | Reason |
|---|---|---|---|---|
| `I_REUSABLE_TMS` | include/config/item.h | FALSE | TRUE | Reusable TMs (GDD 3) |
| `NewGameInitData()` | src/new_game.c | — | calls `EnableNationalPokedex()` | National Dex from the start; no config toggle exists, so it is enabled at new-game init |

Already present (no change): **bag sorting** is built into the expansion (bag context menu → "Sort items how?"); item stack capacity is already 999 (`MAX_BAG_ITEM_CAPACITY`).

## Task 1.4 — Level caps (approved by Rocco 2026-09-16)

| Setting | File | Old | New | Reason |
|---|---|---|---|---|
| `B_EXP_CAP_TYPE` | include/config/caps.h | EXP_CAP_NONE | EXP_CAP_SOFT | Soft caps [DECIDED]: sharply reduced exp above the cap |
| `B_LEVEL_CAP_TYPE` | include/config/caps.h | LEVEL_CAP_NONE | LEVEL_CAP_VARIABLE | Variable-based (approved): Assist mode can raise/remove the cap at runtime |
| `B_LEVEL_CAP_VARIABLE` | include/config/caps.h | 0 | `VAR_CITIES_LEVEL_CAP` | New Cities var |
| `GetCurrentLevelCap()` | src/caps.c | variable mode returned the var directly | var 0 = automatic badge-based table; non-zero = override | Works with no badge-script edits; the override is the Assist hook (Phase 5) |

Cap values: the expansion's built-in badge table already matches the approved values (15, 19, 24, 29, 31, 33, 42, 46, League 58). Recalculate during trainer rebalancing.
`B_RARE_CANDY_CAP` stays FALSE (candies can pass the soft cap — consistent with "soft" philosophy; revisit if abused).

## Task 1.5 — Training

No changes needed — all GDD Section 9.2 items are already the modern defaults:

| Feature | Setting | Value | Behavior |
|---|---|---|---|
| Everstone nature pass | `P_NATURE_INHERITANCE` (pokemon.h:31) | GEN_LATEST | 100% nature inheritance |
| Destiny Knot | hardcoded modern (src/daycare.c:636) | — | passes 5 IVs |
| Ability inheritance | `P_ABILITY_INHERITANCE` (pokemon.h:32) | GEN_LATEST | 80%/60% HA pass-down |
| EV cap | `P_EV_CAP` (pokemon.h:54) | GEN_LATEST | 252 per stat (Gen 6+) |
| Ability Patch | `ITEM_ABILITY_PATCH` | exists | grants hidden ability |
| Hidden abilities in the wild | via DexNav search chances (dexnav.h) | enabled in Task 1.2 | no generic wild-HA% config exists |

Note: EV/IV summary-screen display and the egg-move tutor NPC (GDD 9.2) are UI/NPC work for later phases, not configs.

**Bag pocket expansion (approved by Rocco 2026-09-16):**

| Setting | File | Old | New | Reason |
|---|---|---|---|---|
| `FREE_MYSTERY_GIFT` | include/config/save.h | FALSE | TRUE | Frees 876 B — link-era feature, dead weight in a single-player emulator hack |
| `BAG_ITEMS_COUNT` | include/constants/global.h | 30 | 60 | Expanded bag [DECIDED] |
| `BAG_POKEBALLS_COUNT` | include/constants/global.h | 16 | 32 | More ball variety across 9 generations |
| `BAG_TMHM_COUNT` | include/constants/global.h | 64 | 112 | Room for the expanded TM set |

Net SaveBlock1: 15,760 → 15,260 B measured (612 B free). Save-size test baseline updated accordingly.

**Bug found upstream:** `FREE_MYSTERY_EVENT_BUFFERS = TRUE` causes heap-corruption crashes in the expansion's own test suite (26 CRASHes in one runner shard, `malloc.c` block-magic assertions). Isolated by A/B bisect on 2026-09-16; `FREE_MYSTERY_GIFT` alone is clean. Left DISABLED — its 1,104 B stays in reserve. Worth reporting to rh-hideout.

`Higher leveled Pokemon give more exp` (test/battle/exp.c) now carries `ASSUME(B_EXP_CAP_TYPE == EXP_CAP_NONE)`: with a soft cap and no badges, both parametrizations scale to near-zero exp and the comparison is meaningless. Skipped, not failed, under Cities config.

## Phase 5 — Difficulty and Assist (GDD 4.1/10)

| Setting | File | Old | New | Reason |
|---|---|---|---|---|
| `B_VAR_DIFFICULTY` | include/config/battle.h | 0 (disabled) | `VAR_CITIES_DIFFICULTY` | Activates the expansion's per-difficulty trainer parties; set by the truck setup conversation (0 Easy / 1 Normal / 2 Hard) |

New-game setup runs inside the moving truck: difficulty choice, Assist mode yes/no, and (if Assist) a level-cap choice stored in `VAR_CITIES_LEVEL_CAP` (0 auto / 1 auto+10 / 100 none). `FLAG_CITIES_ASSIST_MODE` suppresses the whiteout money penalty (src/battle_script_commands.c); the party heal on whiteout is vanilla behavior and already satisfies the assist heal requirement.
