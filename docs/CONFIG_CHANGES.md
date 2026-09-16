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
