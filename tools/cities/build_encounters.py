#!/usr/bin/env python3
"""Task 4.2: generate src/data/wild_encounters.json from the approved
species plan (docs/species_plan.csv, approved by Rocco 2026-09-16).

Reads:  tools/cities/base_wild_encounters.json  (pristine vanilla snapshot)
        docs/species_plan.csv                   (the approved plan)
Writes: src/data/wild_encounters.json

Output structure:
- Main group renamed to gWildMonHeaders_Main. For every map in the plan,
  planned tables replace vanilla ones; unplanned tables keep vanilla mons.
  Maps with time-specific species get _Day/_Evening/_Night entries (the
  unsuffixed entry is TIME_MORNING and the fallback).
- New mirrored group gWildMonHeaders_Postgame: every main-map entry copied;
  maps with PG plan rows get their land table replaced by the postgame pool
  (PG rows + the map's strongest main pool as filler) at postgame levels.

The gWildMonHeaders alias in include/wild_encounter.h switches between the
two arrays on FLAG_SYS_GAME_CLEAR (Task 4.3).

Validation: slot counts per table, every plan row placed at least once
(warn otherwise), and only species named in the plan or the vanilla base
ever appear (story-only exclusion is enforced upstream by the plan
generator and downstream by the test-suite sweep).

Deterministic: no randomness.
"""

import csv
import json
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
BASE_JSON = ROOT / "tools/cities/base_wild_encounters.json"
PLAN_CSV = ROOT / "docs/species_plan.csv"
OUT_JSON = ROOT / "src/data/wild_encounters.json"

TIER_LEVELS = {
    # T1 raised from (2, 5) after playtest feedback 2026-09-18: level-5
    # starters trivialized the first routes.
    "T1": (3, 6), "T2": (5, 11), "T3": (12, 19),
    "T4": (20, 29), "T5": (26, 38), "PG": (45, 55),
}

SLOT_LAYOUT = {
    # table -> (slot count, rarity band per slot index)
    "land_mons": (12, ["common"] * 6 + ["uncommon"] * 4 + ["rare"] * 2),
    "water_mons": (5, ["common", "common", "uncommon", "uncommon", "rare"]),
    "rock_smash_mons": (5, ["common", "common", "uncommon", "uncommon", "rare"]),
    "fishing_mons": (10, ["common"] * 2 + ["uncommon"] * 3 + ["rare"] * 5),
}
CSV_TABLE_TO_JSON = {"land": "land_mons", "water": "water_mons",
                     "rock smash": "rock_smash_mons", "fish": "fishing_mons"}
RARITY_ORDER = {"common": 0, "uncommon": 1, "rare": 2}
TIMES = ["day", "evening", "night"]  # suffixed entries; unsuffixed = morning+fallback


def load_plan():
    rows = []
    with open(PLAN_CSV) as f:
        for r in csv.DictReader(f):
            r["species"] = "SPECIES_" + r["species"]
            rows.append(r)
    return rows


def band_pool(pool, band):
    """Slot pool for a rarity band, spilling to neighbors when empty."""
    want = RARITY_ORDER[band]
    ranked = sorted(pool, key=lambda r: (abs(RARITY_ORDER[r["rarity"]] - want),
                                         RARITY_ORDER[r["rarity"]], r["species"]))
    return ranked


def fill_table(pool, table, tier):
    """Deterministically fill a table's slots from plan rows."""
    count, bands = SLOT_LAYOUT[table]
    lo, hi = TIER_LEVELS[tier]
    span = hi - lo
    mons = []
    used = defaultdict(int)
    for idx in range(count):
        ranked = band_pool(pool, bands[idx])
        # pick the least-used candidate to spread species across slots
        pick = min(ranked, key=lambda r: (used[r["species"]],
                                          abs(RARITY_ORDER[r["rarity"]] - RARITY_ORDER[bands[idx]]),
                                          r["species"]))
        used[pick["species"]] += 1
        third = max(1, span // 3)
        if bands[idx] == "common":
            mn, mx = lo, min(hi, lo + 2 * third)
        elif bands[idx] == "uncommon":
            mn, mx = lo + third, hi
        else:
            mn, mx = min(hi - third, lo + third), hi
        mons.append({"min_level": mn, "max_level": mx, "species": pick["species"]})
    return mons


def main():
    plan = load_plan()
    base = json.load(open(BASE_JSON))
    groups = base["wild_encounter_groups"]
    main_group = next(g for g in groups if g["label"] == "gWildMonHeaders")
    main_group["label"] = "gWildMonHeaders_Main"

    # plan rows grouped per (map, json_table)
    per_map_table = defaultdict(list)
    tiers_by_map = defaultdict(set)
    for r in plan:
        per_map_table[(r["map"], CSV_TABLE_TO_JSON[r["table"]])].append(r)
        tiers_by_map[r["map"]].add(r["tier"])

    def main_tier(mapname):
        tiers = tiers_by_map[mapname] - {"PG"}
        return sorted(tiers)[0] if tiers else None

    placed_rows = set()
    new_entries = []
    maps_in_main = set()
    for entry in main_group["encounters"]:
        mapname = entry["map"]
        maps_in_main.add(mapname)
        tier = main_tier(mapname)
        time_variants = {}
        for table in SLOT_LAYOUT:
            key = (mapname, table)
            rows = [r for r in per_map_table.get(key, []) if r["tier"] != "PG"]
            if not rows or tier is None:
                continue  # keep vanilla table
            rate = entry.get(table, {}).get("encounter_rate", 20)
            any_rows = [r for r in rows if r["time of day"] == "any"]
            for tod in ["morning"] + TIMES:
                tod_rows = [r for r in rows if r["time of day"] == tod]
                pool = any_rows + tod_rows
                if not pool:
                    pool = any_rows
                if not pool:
                    continue
                mons = fill_table(pool, table, tier)
                for m in mons:
                    placed_rows.update(r["species"] for r in pool)
                if tod == "morning":
                    entry[table] = {"encounter_rate": rate, "mons": mons}
                else:
                    has_specific = bool(tod_rows) or any(r["time of day"] != "any" for r in rows)
                    if has_specific:
                        time_variants.setdefault(tod, {})[table] = {"encounter_rate": rate, "mons": mons}
        new_entries.append(entry)
        for tod, tables in time_variants.items():
            suffix = tod.title()
            variant = {"map": mapname,
                       "base_label": entry["base_label"] + "_" + suffix}
            variant.update(tables)
            new_entries.append(variant)
    main_group["encounters"] = new_entries

    # Postgame mirror group.
    pg_entries = []
    for entry in main_group["encounters"]:
        if "_Day" in entry["base_label"] or "_Evening" in entry["base_label"] \
           or "_Night" in entry["base_label"]:
            continue  # postgame tables are time-uniform for the first release
        mapname = entry["map"]
        pg_entry = {"map": mapname,
                    "base_label": entry["base_label"].replace("g", "gCitiesPG_", 1)}
        for table in SLOT_LAYOUT:
            if table not in entry:
                continue
            rows = [r for r in per_map_table.get((mapname, table), []) if r["tier"] == "PG"]
            if rows:
                # postgame pool: PG rows plus the map's main rows as filler
                filler = [r for r in per_map_table.get((mapname, table), []) if r["tier"] != "PG"]
                pool = rows + filler
                mons = fill_table(pool, table, "PG")
                placed_rows.update(r["species"] for r in rows)
                pg_entry[table] = {"encounter_rate": entry[table]["encounter_rate"], "mons": mons}
            else:
                # unchanged: copy the main-game table at higher levels
                mons = [dict(m) for m in entry[table]["mons"]]
                for m in mons:
                    m["min_level"] = max(m.get("min_level", 2), 40)
                    m["max_level"] = max(m.get("max_level", 5), 50)
                pg_entry[table] = {"encounter_rate": entry[table]["encounter_rate"], "mons": mons}
        pg_entries.append(pg_entry)
    groups.append({
        "label": "gWildMonHeaders_Postgame",
        "for_maps": True,
        # jsonproc's constants template requires fields on every map group;
        # identical values produce identical (legal) macro redefinitions.
        "fields": main_group["fields"],
        "encounters": pg_entries,
    })

    # Validation
    problems = []
    for g in groups:
        for entry in g["encounters"]:
            for table, (count, _) in SLOT_LAYOUT.items():
                if table in entry and len(entry[table]["mons"]) != count:
                    problems.append(f"{entry['base_label']}.{table}: {len(entry[table]['mons'])} slots (want {count})")
    unplaced = sorted({r["species"] for r in plan} - placed_rows)
    ghost_maps = sorted({r["map"] for r in plan} - maps_in_main)

    with open(OUT_JSON, "w") as f:
        json.dump(base, f, indent=2)
        f.write("\n")

    print(f"wrote {OUT_JSON.relative_to(ROOT)}")
    print(f"main entries: {len(main_group['encounters'])}  postgame entries: {len(pg_entries)}")
    if problems:
        print("SLOT PROBLEMS:")
        for p in problems[:10]:
            print("  ", p)
    if ghost_maps:
        print("PLAN MAPS NOT IN VANILLA HEADERS (rows skipped):", ghost_maps)
    if unplaced:
        print(f"WARNING: {len(unplaced)} plan species never placed:")
        for s in unplaced[:15]:
            print("  ", s)
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
