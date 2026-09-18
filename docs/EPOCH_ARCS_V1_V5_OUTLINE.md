# Task 12.5 — Arcs V1–V5, Implementation Outline (for approval)

**Status: APPROVED + BUILT 2026-09-18** (all four decisions as
recommended: gifts for Magearna/Cosmog/Poipole; V4 completes on the
trio; new Storm's Eye islet for V5). Build notes: Epoch trainer pics
use Psychic M/F + Hex Maniac (Emerald has no Scientist pic); V3
entry and Cosmog live on the V1 researcher NPC; journal quest
entries for the V thread are deferred to a 12.5 polish pass together
with 12.6. Implements the approved 12.1 beat
sheet (docs/EPOCH_STORY_OUTLINE.md). Story is settled; this decides
sites, trainers, and mechanics. "Kai" appears nowhere; grunts
catalogue, they don't menace.

## Shared systems (built first)

- **Vars:** VAR_CITIES_V1_STATE … V5_STATE (+0x1C…+0x20). Postgame
  → a Devon researcher in the Space Center lobby opens V1; each arc
  opens when the previous completes.
- **Arcs:** CITIES_ARC_V1…V5 appended to the enum (postgame block,
  always-obeys). Fixed levels 60/65/70/75/80 (GDD 6.4). Encounters
  are M1-pattern statics: defeated legends return, only catching
  sets the flag; catch flags from +0xCC.
- **Trainers (reserved block, IDs 863+):**
  | ID | Who | Appears | Team identity |
  |---|---|---|---|
  | EPOCH_GRUNT_1–5 | archivist-styled grunts | V1×2, V2×2, V4×1 | relic-keepers: Bronzong, Claydol, Beheeyem, Runerigus, Golurk, Sigilyph, Porygon2 (levels per arc tier) |
  | EPOCH_MERIDIAN_1 / _2 | the believer | V1 debut, V4 | Musharna, Grumpig, Reuniclus, ace **Gardevoir** |
  | EPOCH_GNOMON_1 / _2 | the engineer | V2 debut, V4 | Klinklang, Porygon-Z, Magnezone, ace **Metagross** |
  | EPOCH_ARCHIVIST | reserved, **never battled** | — | — |
  V3 has no Epoch battles by design (the cooperative arc); V5 has
  no trainer battles at all. Epoch battles score ranking points
  automatically (vanilla trainer flags).
- **Journal:** one quest per arc; Halley gains a post-V3 line (she
  recognizes the man who closed a wormhole by hand).

## V1 — "Products and Targets" (lv 60)

New indoor map **MossdeepAnnex** (~14×10, General + Facility — the
Space Center's own look), behind a door in the Space Center 2F's
sparse SE corner. A Devon researcher in the 1F lobby (postgame)
mentions the wing Epoch quietly bought. Inside: two grunt battles,
Meridian's courteous debut (scene + battle), **Mewtwo** in a
containment ring; **Genesect** wakes once Mewtwo is caught; **Mew**
appears outside the annex door once both are caught — drawn to the
player, not the lab.

## V2 — "Stolen Research" (lv 65)

Mr. Stone (Devon, Rustboro) asks the Champion for help → Epoch
field camp on the Route 115 cliffs near the Meteor Falls upper
mouth (~x27–32, y35–45; exact tiles at build; no tent sprites exist
— the camp is people, crates, and labeled boxes as readables). Two
grunts, Gnomon's apologetic debut battle. **Type: Null** static;
**Silvally** appears after it; **Magearna** wakes when both are
caught and CHOOSES the player — proposed as a **gift**, not a
battle (it walked out of Epoch's hands). Then the Archivist's
letter, left at the camp: the first plain WHY. Completing V2 sets
**FLAG_CITIES_CORALMERE_OPEN** (the sunken village).

## V3 — "The Wrong Doors" (lv 70)

Six wormhole sites on existing maps, each a UB static group:
Nihilego → Route 124; Buzzwole + Pheromosa → Route 119; Xurkitree →
New Mauville; Celesteela + Kartana → Route 120; Guzzlord → Jagged
Pass; Stakataka + Blacephalon → Mt. Pyre exterior. Grunts at the
sites help civilians (dialogue only). **Cosmog** shelters with the
player (gift, Space Center scene); **Solgaleo**/**Lunala** statics
at the last two sites; **Necrozma** appears at the first site once
the light duo is caught; **Poipole** a thank-you gift from a grunt,
**Naganadel** static at the Guzzlord site after. The Archivist
appears in person at the final wormhole — closes it by hand,
apologizes, does not stop. Reward: N-Solarizer + N-Lunarizer from
Gnomon.

## V4 — "The Day of the Storm" (lv 75)

Time-rift pockets with **Paradox statics** across ~6 existing maps
— past-paradox in old places (Route 111 desert, Petalburg Woods,
Route 119), future-paradox in machine places (New Mauville, Route
110, Abandoned Ship). **Koraidon**/**Miraidon** anchor the rift at
Route 128 (surface island + underwater pocket); **Terapagos** at
the deepest point — the Coralmere square. Meridian's second battle
defends the Route 128 anchors; Gnomon's second the New Mauville
pocket. **The scene:** stepping into the sunken square during V4
opens the rift → CoralmerePast → the walk → the rift closes on its
own and returns the player. Arc completes on Koraidon + Miraidon +
Terapagos; the paradox pockets stay open as optional catches (all
remain available for the 13.2 completeness rule). Survivors journal
entry lands in 12.7.

## V5 — "The Anchor" (lv 80)

Storm over Pacifidlog: evacuation scene (the family with the bell
by their door), then the Archivist arrives and takes the player
out himself. New small map — a bare rock islet in the storm's eye
(~16×14, General rocks + sea, WEATHER_DOWNPOUR): the walk through
the wind with him, then **Eternatus** (static, returns until
caught; the story advances after the first battle either way). The
heroic act — he shuts the rift to save Pacifidlog, giving up
Coralmere — plays here; the family, the name, and everything after
belong to 12.6.

## Decisions needed from Rocco

1. Approve the overall plan (roster, sites, per-arc mechanics).
2. Magearna / Cosmog / Poipole as **gifts** rather than battles?
3. V4 completes on the trio (paradox optional)?
4. New V5 storm islet map (Sky Pillar stays vanilla Rayquaza's)?
