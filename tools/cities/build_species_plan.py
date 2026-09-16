#!/usr/bin/env python3
"""Task 4.1: generate docs/species_plan.csv — the pre-filled wild encounter
plan for Rocco's review (GDD Section 5). No encounter data is modified.

Reads:  src/data/pokemon/species_info/gen_*_families.h  (species facts)
        src/data/wild_encounters.json                    (which maps have which tables)
Writes: docs/species_plan.csv

Deterministic: no randomness; re-running produces the same plan.
"""

import csv
import json
import re
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SPECIES_DIR = ROOT / "src/data/pokemon/species_info"
WILD_JSON = ROOT / "src/data/wild_encounters.json"
OUT_CSV = ROOT / "docs/species_plan.csv"

STORY_ONLY_FLAGS = (
    "isRestrictedLegendary", "isSubLegendary", "isMythical",
    "isUltraBeast", "isParadox",
)
SKIP_FORM_FLAGS = (
    "isMegaEvolution", "isPrimalReversion", "isUltraBurst",
    "isGigantamax", "isTeraForm", "isTotem",
)
REGIONAL_FLAGS = ("isAlolanForm", "isGalarianForm", "isHisuianForm", "isPaldeanForm")
STORY_ONLY_BASES = {
    "SPECIES_TYPE_NULL", "SPECIES_SILVALLY", "SPECIES_COSMOG", "SPECIES_COSMOEM",
    "SPECIES_KUBFU", "SPECIES_URSHIFU", "SPECIES_URSHIFU_SINGLE_STRIKE",
    "SPECIES_URSHIFU_RAPID_STRIKE", "SPECIES_MELTAN", "SPECIES_MELMETAL",
    "SPECIES_POIPOLE", "SPECIES_NAGANADEL",
}

# GDD 5.5 pseudo-legendary lines: postgame emphasis.
PSEUDO_BASES = {
    "SPECIES_DRATINI", "SPECIES_LARVITAR", "SPECIES_BAGON", "SPECIES_BELDUM",
    "SPECIES_GIBLE", "SPECIES_DEINO", "SPECIES_GOOMY", "SPECIES_JANGMO_O",
    "SPECIES_DREEPY", "SPECIES_FRIGIBAX",
}

# GDD 5.3 T1 beginner pool ([DECIDED concept, PROPOSED list]).
T1_POOL = {
    "SPECIES_PIDGEY", "SPECIES_RATTATA", "SPECIES_CATERPIE", "SPECIES_WEEDLE",
    "SPECIES_PIKACHU", "SPECIES_HOOTHOOT", "SPECIES_SENTRET", "SPECIES_LEDYBA",
    "SPECIES_SPINARAK", "SPECIES_ZIGZAGOON", "SPECIES_WURMPLE", "SPECIES_POOCHYENA",
    "SPECIES_TAILLOW", "SPECIES_STARLY", "SPECIES_BIDOOF", "SPECIES_KRICKETOT",
    "SPECIES_SHINX", "SPECIES_PATRAT", "SPECIES_LILLIPUP", "SPECIES_PURRLOIN",
    "SPECIES_PIDOVE", "SPECIES_SEWADDLE", "SPECIES_FLETCHLING", "SPECIES_BUNNELBY",
    "SPECIES_SCATTERBUG", "SPECIES_PIKIPEK", "SPECIES_YUNGOOS", "SPECIES_GRUBBIN",
    "SPECIES_ROOKIDEE", "SPECIES_SKWOVET", "SPECIES_BLIPBUG", "SPECIES_WOOLOO",
    "SPECIES_LECHONK", "SPECIES_TAROUNTULA", "SPECIES_NYMBLE", "SPECIES_PAWMI",
    "SPECIES_FIDOUGH",
}

MORNING_SPECIES = {"SPECIES_LEDYBA", "SPECIES_SUNKERN", "SPECIES_COMBEE", "SPECIES_PETILIL"}
NIGHT_SPECIES = {"SPECIES_HOOTHOOT", "SPECIES_SPINARAK", "SPECIES_ZUBAT", "SPECIES_NOIBAT",
                 "SPECIES_CUTIEFLY", "SPECIES_MORELULL", "SPECIES_IMPIDIMP"}

# GDD 5.2 tier -> map prefixes (multi-room dungeons match by prefix).
TIER_MAP_PREFIXES = {
    "T1": ["MAP_ROUTE101", "MAP_ROUTE102", "MAP_ROUTE103", "MAP_ROUTE104", "MAP_PETALBURG_WOODS"],
    "T2": ["MAP_ROUTE116", "MAP_RUSTURF_TUNNEL", "MAP_GRANITE_CAVE",
           "MAP_ROUTE105", "MAP_ROUTE106", "MAP_ROUTE107", "MAP_ROUTE108", "MAP_ROUTE109"],
    "T3": ["MAP_ROUTE110", "MAP_ROUTE117", "MAP_ROUTE111", "MAP_ROUTE112", "MAP_ROUTE113",
           "MAP_ROUTE114", "MAP_FIERY_PATH", "MAP_METEOR_FALLS"],
    "T4": ["MAP_ROUTE115", "MAP_ROUTE118", "MAP_ROUTE119", "MAP_ROUTE120", "MAP_ROUTE121",
           "MAP_JAGGED_PASS", "MAP_MT_PYRE", "MAP_SAFARI_ZONE"],
    "T5": ["MAP_ROUTE122", "MAP_ROUTE123", "MAP_ROUTE124", "MAP_ROUTE125", "MAP_ROUTE126",
           "MAP_ROUTE127", "MAP_ROUTE128", "MAP_ROUTE129", "MAP_ROUTE130", "MAP_ROUTE131",
           "MAP_ROUTE132", "MAP_ROUTE133", "MAP_ROUTE134", "MAP_SHOAL_CAVE",
           "MAP_SEAFLOOR_CAVERN", "MAP_VICTORY_ROAD"],
}
CAVE_PREFIXES = ("MAP_RUSTURF_TUNNEL", "MAP_GRANITE_CAVE", "MAP_FIERY_PATH", "MAP_METEOR_FALLS",
                 "MAP_JAGGED_PASS", "MAP_MT_PYRE", "MAP_SHOAL_CAVE", "MAP_SEAFLOOR_CAVERN",
                 "MAP_VICTORY_ROAD")


def parse_species_files():
    species = {}
    order = []
    for gen in range(1, 10):
        path = SPECIES_DIR / f"gen_{gen}_families.h"
        text = path.read_text()
        # Split into blocks: [SPECIES_X] = { ... } at 4-space indent.
        blocks = re.split(r"\n    \[(SPECIES_[A-Z0-9_]+)\]\s*=", text)
        for i in range(1, len(blocks), 2):
            name, body = blocks[i], blocks[i + 1]
            if name in species:
                continue
            entry = {"name": name, "gen": gen, "body_flags": set(), "types": [],
                     "bst": 0, "dex": None, "evos": []}
            for flag in STORY_ONLY_FLAGS + SKIP_FORM_FLAGS + REGIONAL_FLAGS:
                if re.search(rf"\.{flag}\s*=\s*TRUE", body):
                    entry["body_flags"].add(flag)
            m = re.search(r"\.types\s*=\s*MON_TYPES\(\s*TYPE_([A-Z]+)(?:\s*,\s*TYPE_([A-Z]+))?\s*\)", body)
            if m:
                entry["types"] = [t for t in m.groups() if t]
            stats = re.findall(r"\.base(?:HP|Attack|Defense|Speed|SpAttack|SpDefense)\s*=\s*(\d+)", body)
            entry["bst"] = sum(int(s) for s in stats[:6])
            m = re.search(r"\.natDexNum\s*=\s*NATIONAL_DEX_([A-Z0-9_]+)", body)
            entry["dex"] = m.group(1) if m else None
            evo = re.search(r"\.evolutions\s*=\s*EVOLUTION\(", body)
            if evo:
                # balanced-paren scan
                start = evo.end() - 1
                depth, j = 0, start
                while j < len(body):
                    if body[j] == "(":
                        depth += 1
                    elif body[j] == ")":
                        depth -= 1
                        if depth == 0:
                            break
                    j += 1
                entry["evos"] = re.findall(r"SPECIES_[A-Z0-9_]+", body[start:j])
            species[name] = entry
            order.append(name)
    return species, order


def main():
    species, order = parse_species_files()

    # Keep: first species per dex number (default form) + regional forms.
    seen_dex = set()
    kept = []
    for name in order:
        e = species[name]
        if e["body_flags"] & set(SKIP_FORM_FLAGS):
            continue
        is_regional = bool(e["body_flags"] & set(REGIONAL_FLAGS))
        if e["dex"] in seen_dex and not is_regional:
            continue  # cosmetic form (Unown letters, Vivillon patterns, ...)
        seen_dex.add(e["dex"])
        kept.append(name)
        e["regional"] = is_regional

    def story_only(name):
        e = species[name]
        return bool(e["body_flags"] & set(STORY_ONLY_FLAGS)) or name in STORY_ONLY_BASES

    # Evolution stages over ALL parsed species (forms included).
    targets = set()
    for e in species.values():
        targets.update(e["evos"])
    stage = {}
    frontier = [n for n in species if n not in targets]
    for n in frontier:
        stage[n] = 0
    while frontier:
        nxt = []
        for n in frontier:
            for t in species[n]["evos"]:
                if t in species and stage.get(t, 99) > stage[n] + 1:
                    stage[t] = stage[n] + 1
                    nxt.append(t)
        frontier = nxt

    def line_of(base):
        out = [base]
        for t in species[base]["evos"]:
            if t in species:
                out += line_of(t)
        return out

    # Map/table availability from vanilla data.
    wild = json.load(open(WILD_JSON))
    headers = next(g for g in wild["wild_encounter_groups"] if g["label"] == "gWildMonHeaders")
    map_tables = defaultdict(set)
    for enc in headers["encounters"]:
        for tbl, label in (("land_mons", "land"), ("water_mons", "water"),
                           ("rock_smash_mons", "rock smash"), ("fishing_mons", "fish")):
            if tbl in enc:
                map_tables[enc["map"]].add(label)

    tier_maps = {}
    for tier, prefixes in TIER_MAP_PREFIXES.items():
        maps = []
        for p in prefixes:
            maps += sorted(m for m in map_tables if m == p or m.startswith(p + "_"))
        tier_maps[tier] = maps
    # PG rows land on the postgame table set of any tier map (GDD 5.5).
    tier_maps["PG"] = [m for t in ("T3", "T4", "T5") for m in tier_maps[t]]

    def habitat_of(name):
        e = species[name]
        t = e["types"]
        prim = t[0] if t else "NORMAL"
        both = set(t)
        if "WATER" in both:
            return "water"
        if both & {"ROCK", "GROUND", "STEEL"}:
            return "cave"
        if "ICE" in both:
            return "ice"
        if "FIRE" in both:
            return "volcanic"
        if both & {"GHOST", "DARK"}:
            return "night-spooky"
        if "DRAGON" in both:
            return "dragon"
        if "ELECTRIC" in both:
            return "urban-electric"
        if both & {"BUG", "GRASS"}:
            return "forest"
        if "FLYING" in both or prim == "NORMAL":
            return "field"
        return "field"

    def tier_of(name):
        e = species[name]
        base = name
        if name in T1_POOL:
            return "T1"
        if base in PSEUDO_BASES:
            return "PG"
        hab = habitat_of(name)
        bst = e["bst"]
        if hab == "ice":
            return "T5"
        if hab == "dragon":
            return "T5"
        if hab == "volcanic":
            return "T3" if bst <= 400 else "T4"
        if e.get("regional"):
            return "PG"  # regional forms are postgame flavor by default
        if bst <= 300:
            return "T2"
        if bst <= 360:
            return "T3"
        if bst <= 430:
            return "T4"
        return "T5"

    def table_of(name, mapname):
        hab = habitat_of(name)
        avail = map_tables[mapname]
        if hab == "water":
            if "fish" in avail and species[name]["bst"] <= 360:
                return "fish"
            if "water" in avail:
                return "water"
        if hab == "cave" and "rock smash" in avail and species[name]["bst"] <= 350:
            return "rock smash"
        return "land"

    def pick_map(tier, name, load):
        hab = habitat_of(name)
        maps = tier_maps[tier] or tier_maps["T5"]
        prefer = []
        for m in maps:
            is_cave = m.startswith(CAVE_PREFIXES)
            if hab == "water" and not ({"water", "fish"} & map_tables[m]):
                continue
            if hab in ("cave", "night-spooky") and not is_cave:
                prefer.append((1, m))
                continue
            if hab in ("forest", "field", "urban-electric") and is_cave:
                prefer.append((1, m))
                continue
            prefer.append((0, m))
        if not prefer:
            prefer = [(0, m) for m in maps]
        # least-loaded among preferred rank 0, then rank 1
        prefer.sort(key=lambda pm: (pm[0], load[pm[1]], pm[1]))
        return prefer[0][1]

    def time_of(name):
        if name in MORNING_SPECIES:
            return "morning"
        if name in NIGHT_SPECIES or habitat_of(name) == "night-spooky":
            return "night"
        return "any"

    def rarity_of(name, tier):
        bst = species[name]["bst"]
        if tier == "PG":
            return "rare" if bst >= 500 else "uncommon"
        if name in T1_POOL and name == "SPECIES_PIKACHU":
            return "rare"  # GDD 5.3 marks Pikachu rare
        if bst <= 310:
            return "common"
        if bst <= 400:
            return "uncommon"
        return "rare"

    rows = []
    load = defaultdict(int)

    def add_row(name, tier):
        mapname = pick_map(tier, name, load)
        tbl = table_of(name, mapname)
        load[mapname] += 1
        e = species[name]
        rows.append({
            "species": name.replace("SPECIES_", ""),
            "generation": e["gen"],
            "evolution stage": stage.get(name, 0),
            "habitat": habitat_of(name),
            "tier": tier,
            "map": mapname,
            "table": tbl,
            "time of day": time_of(name),
            "rarity": rarity_of(name, tier),
        })

    placed = set()
    # 1) Every non-story-only base-stage kept species gets a placement.
    for name in kept:
        if story_only(name) or stage.get(name, 0) != 0:
            continue
        add_row(name, tier_of(name))
        placed.add(name)

    # 2) Middle stages of 3-stage lines appear in T4/T5 as uncommon spice.
    for name in kept:
        if story_only(name) or stage.get(name, 0) != 1:
            continue
        if not species[name]["evos"]:
            continue  # only mids that evolve further
        if species[name]["bst"] < 380:
            continue
        add_row(name, "T5" if species[name]["bst"] >= 430 else "T4")
        placed.add(name)

    # 3) PG extras: pseudo-legendary mids/finals and strong finals (GDD 5.5).
    for base in sorted(PSEUDO_BASES):
        if base not in species:
            continue
        for member in line_of(base):
            if member in placed or member not in species:
                continue
            add_row(member, "PG")
            placed.add(member)
    finals = [n for n in kept
              if not story_only(n) and n not in placed
              and stage.get(n, 0) == 2 and species[n]["bst"] >= 520]
    for name in sorted(finals, key=lambda n: -species[n]["bst"])[:30]:
        add_row(name, "PG")
        placed.add(name)

    # Coverage check: every kept non-story-only species must be obtainable.
    reachable = set(placed)
    changed = True
    while changed:
        changed = False
        for n in list(reachable):
            for t in species[n]["evos"]:
                if t in species and t not in reachable:
                    reachable.add(t)
                    changed = True
    missing = [n for n in kept if not story_only(n) and n not in reachable]
    # Fallback: anything unreachable (e.g., evolves from a skipped cosmetic
    # form) gets a direct postgame placement, then re-check.
    for n in missing:
        add_row(n, "PG")
        placed.add(n)
        reachable.add(n)
    missing = [n for n in kept if not story_only(n) and n not in reachable]

    rows.sort(key=lambda r: (r["tier"], r["map"], r["table"], r["rarity"], r["species"]))
    OUT_CSV.parent.mkdir(exist_ok=True)
    with open(OUT_CSV, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=["species", "generation", "evolution stage", "habitat",
                                          "tier", "map", "table", "time of day", "rarity"])
        w.writeheader()
        w.writerows(rows)

    # Report
    per_tier = defaultdict(int)
    for r in rows:
        per_tier[r["tier"]] += 1
    print(f"wrote {len(rows)} placements to {OUT_CSV.relative_to(ROOT)}")
    print("per tier:", dict(sorted(per_tier.items())))
    print(f"kept species: {len(kept)}  story-only excluded: {sum(1 for n in kept if story_only(n))}")
    print(f"coverage: {'OK — every non-story-only species obtainable' if not missing else 'MISSING:'}")
    for n in missing:
        print("  ", n)
    heavy = sorted(load.items(), key=lambda kv: -kv[1])[:5]
    print("busiest maps:", heavy)
    return 0 if not missing else 1


if __name__ == "__main__":
    sys.exit(main())
