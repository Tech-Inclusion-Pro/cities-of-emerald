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
