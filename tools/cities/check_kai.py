#!/usr/bin/env python3
"""Task 12.8 — the name check (Cities of Emerald, GDD 7.2).

The Archivist's true name, "Kai", must never appear in text the player
can reach before the ending. Every path in the one allowlisted file,
data/scripts/cities_ending.inc, is gated behind FLAG_CITIES_KAI_NAMED
(or is the naming scene itself), so that file may say the name; nowhere
else may.

This scans player-visible strings across the repo and exits non-zero if
"Kai" (as a whole word, any case) appears outside the allowlist. Wired
into `make check`.

Scanned:
  - .string "..."          in every .inc / .s under data/
  - COMPOUND_STRING("...")  in every .c under src/
  - Name: ...               in src/data/trainers.party
"""

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
ALLOWLIST = {ROOT / "data/scripts/cities_ending.inc"}

# whole-word "kai", case-insensitive; avoids matching e.g. "Kailua" if it
# ever appeared, and does not match substrings inside other words.
KAI = re.compile(r"\bkai\b", re.IGNORECASE)

STRING_RE = re.compile(r'\.string\s+"([^"]*)"')
COMPOUND_RE = re.compile(r'COMPOUND_STRING\(\s*"((?:[^"\\]|\\.)*)"')
NAME_RE = re.compile(r'^Name:\s*(.+)$')


def visible_strings(path: Path):
    text = path.read_text(errors="replace")
    if path.suffix in (".inc", ".s"):
        for m in STRING_RE.finditer(text):
            yield m.group(1)
    elif path.suffix == ".c":
        for m in COMPOUND_RE.finditer(text):
            yield m.group(1)
    elif path.name == "trainers.party":
        for line in text.splitlines():
            m = NAME_RE.match(line)
            if m:
                yield m.group(1)


def main():
    targets = []
    targets += (ROOT / "data").rglob("*.inc")
    targets += (ROOT / "data").rglob("*.s")
    targets += (ROOT / "src").rglob("*.c")
    party = ROOT / "src/data/trainers.party"
    if party.exists():
        targets.append(party)

    violations = []
    for path in targets:
        if path in ALLOWLIST:
            continue
        for s in visible_strings(path):
            if KAI.search(s):
                violations.append((path.relative_to(ROOT), s))

    if violations:
        print("Task 12.8 name check FAILED: \"Kai\" appears in text reachable")
        print("before the ending. Move it behind FLAG_CITIES_KAI_NAMED, or into")
        print("data/scripts/cities_ending.inc.\n")
        for rel, s in violations:
            print(f"  {rel}: {s}")
        return 1

    print("Task 12.8 name check passed: the name is kept until it is given.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
