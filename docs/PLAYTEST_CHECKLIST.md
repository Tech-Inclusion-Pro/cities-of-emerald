# Cities of Emerald — Playtest Checklist (Phases 0–7)

Run: `open -a mGBA ~/Projects/cities-of-emerald/pokeemerald.gba`
Debug menu: hold R + press START in the overworld (badges, flags, warp, items).
Keys: X = A, Z = B, Enter = Start (rebind in mGBA → Settings → Keyboard).

## New game flow
- [ ] Truck setup runs before Littleroot: accessibility preset → difficulty → Assist (+ level cap choice if Assist on)
- [ ] Starter screen: 10-region list scrolls; 3 starters show sprite + name + "type as text"; B steps back; confirm wording matches GDD; starter is level 5
- [ ] Special region shows Eevee / Pikachu / Ditto side by side; each can be chosen; rival later has a random Hoenn starter
- [ ] Route 103 rival carries the type-advantaged starter FROM YOUR REGION (e.g., Kanto grass pick → rival Charmander)

## Wild encounters (Phase 4)
- [ ] Route 101: multi-gen beginners (Bunnelby, Skwovet, Patrat, Taillow…), visible walking in grass (OWE)
- [ ] Night: Hoothoot/Spinarak appear; morning: Ledyba
- [ ] Route 105 fishing: Arrokuda/Feebas/Horsea pool
- [ ] Debug-set game-clear flag → Route 101 spawns level ~45 postgame species
- [ ] Starter follows you (follower Pokémon)

## Eevee content (Phase 4)
- [ ] After badge 2: stone expert appears in Dewford Pokémon Center; explains all stones + friendship evolutions; gives exactly ONE stone
- [ ] Eeveelution trainers REACHABILITY (coords were placed heuristically — verify each is visible, reachable, sane):
  - [ ] Maren (Vaporeon) Route 110 · [ ] Joule (Jolteon) Route 117 (badge 3)
  - [ ] Cinder (Flareon) Fiery Path (badge 4)
  - [ ] Aurelia (Espeon) Route 115, DAY only (badge 5)
  - [ ] Linden (Leafeon) Route 119 · [ ] Faye (Sylveon) Route 121 (badge 6)
  - [ ] Nox (Umbreon) Mt. Pyre exterior, NIGHT only · [ ] Neve (Glaceon) Shoal Cave ice room (badge 7)
- [ ] Stone trainers award stone on first win; bag-full retried on re-talk
- [ ] Badge 3 + Mauville mart stocks Linking Cord (8,000); using it: Machoke evolves; Onix only w/ Metal Coat; Karrablast needs Shelmet in party

## Difficulty & Assist (Phase 5)
- [ ] Hard/Easy chosen in truck persists (debug: check VAR_CITIES_DIFFICULTY)
- [ ] Assist on: lose a battle → no money lost
- [ ] Cap "Raise": over-cap exp penalty starts 10 levels later; "None": never

## Accessibility (Phase 6)
- [ ] START → Access: 4 pages, L/R switches, changes apply instantly
- [ ] High contrast: overworld text boxes turn black w/ white text
- [ ] Instant text: dialogue renders instantly
- [ ] Auto-run: walk = run, holding B walks; Toggle run: B flips it
- [ ] Battle speed Fast/Fastest: battle text pauses visibly shorter
- [ ] Wait for button: battle messages hold until A/B
- [ ] Fewer presses: no nickname question after catching
- [ ] Reduced shake/flashing: use a move like Earthquake / Explosion and compare
- [ ] Effect indicator ON: move select shows effectiveness even vs. new species
- [ ] Littleroot guide NPC (woman near center of town) explains + applies presets

## Rankings (Phase 7)
- [ ] START → Ranking: 20-row board, you at #20/0 on fresh save, view opens on your row
- [ ] Beat a trainer cleanly (all mons acted, none fainted, fast) → score jumps ~6–14
- [ ] Rematch same trainer: win adds nothing; a LOSS still subtracts
- [ ] Debug-give badges → whole board climbs (Wallace +40/badge, Rival +150)
- [ ] Turn on slow text + wait-for-button + extra time → quick-win window grows (hard to eyeball; spot-check that quick wins still register)

## Rematch versions (Phase 8) — needs a post-Champion save (debug: set FLAG_SYS_GAME_CLEAR)
- [ ] Gym leader (e.g. Roxanne) offers a rematch after the badge dialogue; it's a DOUBLE battle with the new V1 team (levels 63/65)
- [ ] Beat V1, talk again → notice "won't change your ranking" appears, then the SAME V1 team repeats (V2 stays locked)
- [ ] Debug-set FLAG_CITIES_POSTGAME_THREAD1_MIDPOINT → next gym rematch serves the V2 team (73/75)
- [ ] Debug-set both THREAD COMPLETE flags → V3 team (83/85); after beating V3, repeats stay V3 (never the reserved _5 party)
- [ ] Winning a NEW version adds ranking points; repeating a beaten version adds none (loss still subtracts)
- [ ] Route 103: rival appears at the first-battle spot post-Champion (correct Brendan/May sprite), asks before battling, declining works
- [ ] Rival team: 5 mons at V1 with YOUR region's counter-starter fully evolved in slot 1
- [ ] Rival V1 beaten → repeat shows the no-points notice; V2/V3 unlock with the same debug flags
- [ ] Match call PokéNav: gym leaders may still announce "wants a rematch" — cosmetic, ignore

## Challengers & Master (Phase 7 leftovers)
- [ ] Bram appears on Route 110 (near the south camper) after badge 3; challenge dialogue, points once, friendly after
- [ ] Ilaria on Route 119 (south grass, near the bug catcher) after badge 5
- [ ] Corsen on Route 121 (west end, near the woman) after badge 7
- [ ] Vesper in Ever Grande City (upper plateau by the League doors) once Champion
- [ ] All four: reachable/not walled in (coords placed from data, not eyes)
- [ ] Reach No. 1 (debug: give badges + win battles, or set score) → fanfare + MASTER message on regaining control
- [ ] League lobby: official (gentleman, mid-lobby) holds the ceremony, gives MASTER BALL; bag-full retry works; repeat dialogue after
- [ ] Ranking screen: your row reads "You - MASTER" once titled; title survives dropping below No. 1

## Quest journal & guide (Phase 9)
- [ ] START → Journal: pages through active quests (main story first), each as name then plain-language next step
- [ ] Journal main-story step matches where you actually are (check at 2-3 different save points)
- [ ] Eevee quest appears after badge 2, shows "N of 8", disappears when all 8 experts are beaten
- [ ] Challenger quest appears after badge 3 with "N of 4"; rematch + Master quests appear once Champion
- [ ] Load a save → "Welcome back!" recap shows the current main-story step once you have control
- [ ] If you earned MASTER and saved before the fanfare showed, loading shows the announcement instead
- [ ] Littleroot guide: menu offers Presets / What's next? / Tutorials / Goodbye; all loop back to the menu
- [ ] All 7 tutorials read correctly (Breeding, Mega, Z-Moves, Dynamax, Terastal, Wild Pokémon, Rankings)

## Legendary arcs M1 & M2 (Phase 10)
- [ ] Reporter appears in Slateport Pokémon Center at badge 3 (left side, near the sailor); intro lists the three sites
- [ ] Moltres visible in Fiery Path mid-cave at badge 3; scientist near the south entrance — check both are reachable
- [ ] Articuno in Shoal Cave ice room (low tide), Zapdos in New Mauville inner room — check spots once you have Surf
- [ ] Bird level = your current auto cap (e.g. 24 at 3 badges); rises if you come back later
- [ ] KO a bird → "slipped away" message; leave and re-enter → it's back; catch → gone for good
- [ ] Caught bird at 3 badges disobeys with the exact HEAT BADGE message; obeys the moment you have badge 4
- [ ] All 3 caught → reporter celebration (M1-PG tease); journal quest completes and drops off
- [ ] Archaeologist appears in Pacifidlog House 1 (Regi-lore house) at badge 5, gives the plain-language route
- [ ] Every braille sign in Sealed Chamber + the three ruins shows a plain-text translation box after the braille
- [ ] Regis fight at auto-cap level (not 40); KO'd Regi returns on re-entry
- [ ] All 3 Regis caught → archaeologist celebration ("colossus" H3 tease)
- [ ] M5 note for later: Latias/Latios obedience pair-rule messages (needs both caught to verify)

## Legendary arc M3 (Phase 10)
- [ ] Ranger appears in the Fortree Pokémon Center at badge 6 (left side, below the boy); intro releases the beasts
- [ ] Journal "On the Trail" shows one line per beast; the route named matches where you actually find it
- [ ] Beast battles start on the named route at the auto-cap level; level rises if you come back with more badges
- [ ] Beast HP/status carry over between meetings; a KO'd beast keeps roaming at full health (never lost)
- [ ] Third battle meeting (any outcome) → "worn out" notice appears once you're back in control
- [ ] Cornered beast waits in its den: Raikou in Altering Cave, Entei in Scorched Slab, Suicune in Meteor Falls (up past the waterfall, 1F back room)
- [ ] Den battle: beast can't flee; KO → "slipped away", re-enter → it's back; catch → gone for good
- [ ] Caught beast at 6 badges disobeys with the exact MIND BADGE message; obeys the moment you have badge 7
- [ ] All 3 caught → ranger celebration ("rainbow wings" H4 tease); journal quest completes and drops off
- [ ] Post-League scene at home: SS Ticket scene plays normally with NO Latias/Latios TV broadcast (M5 owns them now)
- [ ] Old saves from before this build are NOT compatible (ROAMER_COUNT save layout change) — start fresh

## Legendary arc M4 (Phase 10)
- [ ] Keeper appears inside the Cave of Origin entrance at badge 7 (left wall of the corridor); intro opens the passage
- [ ] 1F far-right alcove: stepping into the end tiles warps to chamber 1 ("parted wall" message) — only after meeting the keeper
- [ ] Chamber 1 ladder (top-left) returns to the 1F alcove, NOT the B1F staircase
- [ ] Chain works both ways: 1F alcove ↔ chamber 1 ↔ chamber 2 ↔ chamber 3 → B1F stairs
- [ ] Uxie / Mesprit / Azelf visible in chambers 1/2/3; fight at the auto-cap level; KO'd spirit returns on re-entry; catch removes it
- [ ] Each chamber's inscription reads correctly (mind / heart / will)
- [ ] No wild encounters inside the three chambers
- [ ] During the crisis: Wallace's B1F scene still plays normally, whether you enter from the stairs or from chamber 3
- [ ] Caught spirit at 7 badges disobeys with the exact RAIN BADGE message; obeys after beating Juan
- [ ] All 3 caught → keeper's closing line; journal quest completes and drops off

## Legendary arc M5 (Phase 10)
- [ ] Sailor appears in the Lilycove harbor terminal at badge 8 (right side of the dock); intro gives the EON TICKET
- [ ] Sailor sails you to Southern Island on request (works BEFORE the League — no SS Tidal needed); island sailor sails you back
- [ ] Post-League: the ferry attendant also lists Southern Island (Eon Ticket + enable flag), with the vanilla first-time ticket scene
- [ ] Both Latias and Latios visible in the grove, flanking the Eon stone; each fights at the auto-cap level
- [ ] KO'd Lati returns on re-entry; catching removes only that one; the old TV-pick cutscene never plays
- [ ] Caught single Lati disobeys with the exact reunion message ("…until it's reunited with…"); both caught → both obey
- [ ] Trade one away after both caught → the remaining one still obeys (sticky pair flag)
- [ ] Eon stone: "waiting" text before both caught; hums and gives LATIASITE + LATIOSITE once; quiet afterward; bag-full retry works
- [ ] Journal quest opens at badge 8, names the missing partner while one is caught, completes and drops off

## Legendary arc M1-PG (Phase 10, postgame)
- [ ] Reporter's follow-up appears only when you are Champion AND M1 is complete (Champion with M1 unfinished -> her old dialogue)
- [ ] Galarian Articuno / Zapdos / Moltres visible at the M1 sites (Shoal Cave ice room / New Mauville / Fiery Path), standing where the originals stood
- [ ] Each fights at level 60; a KO'd bird returns on re-entry; only catching removes it
- [ ] Caught Galarian birds obey immediately, at any badge count (no disobedience message ever)
- [ ] Journal "Stranger Weather" opens with the reporter, shows N of 3, completes and drops off after her closing line
- [ ] The Kantonian M1 birds never overlap the Galarian ones (M1 must be complete before these appear)

## Hidden area H1 (Phase 11)
- [ ] Ranger appears at Littleroot's tree line (top-left, below the trees) only after the League
- [ ] Ranger's intro plays once; saying yes walks you into Littleroot Hollow; saying no leaves her available
- [ ] Littleroot Hollow looks right: solid tree walls all around, no way to walk out of bounds, no wild encounters, forest music
- [ ] Stepping into the south alcove returns you to Littleroot next to the ranger
- [ ] Cobalion (west), Terrakion (east), Virizion (north) visible; each fights at level 60; KO'd guardian returns on re-entry; only catching removes it
- [ ] Keldeo absent until all three are caught, then appears at the clearing's center; same battle rules
- [ ] All four obey immediately at any badge count (no disobedience message ever)
- [ ] Caretaker's dialogue tracks progress: guardians intro -> Keldeo notice -> closing thanks -> quiet after
- [ ] Journal "The Swords of Justice" opens after meeting the ranger, shows N of 4, completes and drops off
- [ ] Wild sweep: none of the four appear in any random source (existing test gate)

## Hidden area H5b (Phase 11)
- [ ] Fisher appears on Dewford's south beach (left side) only after the League
- [ ] Fisher's intro plays once; saying yes rows you to Moonrise Cove; saying no leaves him available
- [ ] Moonrise Cove looks right: cave walls all around, moonpool in the outer chamber, dark-floored nook up top, no way out of bounds, no wild encounters
- [ ] Stepping into the south alcove returns you to Dewford's beach next to the fisher
- [ ] Cresselia by the pool and Darkrai in the nook both visible from the first visit; each fights at level 60; KO returns on re-entry; only catching removes it
- [ ] Both obey immediately at any badge count
- [ ] Keeper's dialogue tracks progress: pair intro -> closing thanks -> quiet after
- [ ] Journal "The Lunar Duo" opens after meeting the fisher, names the remaining one while one is caught, completes and drops off
- [ ] Wild sweep: neither appears in any random source (existing test gate)

## Hidden area H10 (Phase 11)
- [ ] Elder appears on Pacifidlog's south-east platform (by the south bridge) only after the League
- [ ] Elder's intro plays once; saying yes rafts you to Shrine Atoll; saying no leaves her available
- [ ] Shrine Atoll looks right: five log platforms over open sea, bridges N/E/S/W from the center, no way to walk into open water, no wild encounters
- [ ] Stepping onto the moored-raft plank (center platform's south-east corner) returns you to Pacifidlog next to the elder
- [ ] All four Tapu visible on their islets from the first visit (Koko north, Lele east, Bulu south, Fini west); each fights at level 60; KO returns on re-entry; only catching removes it
- [ ] All four obey immediately at any badge count
- [ ] Caretaker's dialogue tracks progress: shrines intro -> closing thanks -> quiet after
- [ ] Journal "The Island Guardians" opens after meeting the elder, shows N of 4, completes and drops off
- [ ] Wild sweep: no Tapu appears in any random source (existing test gate)

## Hidden area H11 (Phase 11)
- [ ] Volcanologist appears on the Mt. Chimney summit (right of the cable car station door) only after the League
- [ ] Her intro plays once; saying yes climbs down to Ember Vault; saying no leaves her available
- [ ] Ember Vault looks right: rock walls, lava pools along both sides, basalt floor, no way out of bounds, no wild encounters
- [ ] Stepping into the south alcove returns you to the summit beside her
- [ ] Heatran visible on the central floor; fights at level 60; KO returns on re-entry; only catching removes it
- [ ] Heatran obeys immediately at any badge count
- [ ] Her vault dialogue tracks progress: pulse intro -> closing thanks -> quiet after
- [ ] Journal "The Heart of the Mountain" opens after meeting her, completes and drops off
- [ ] Wild sweep: Heatran appears in no random source (existing test gate)

## Hidden area H3 (Phase 11)
- [ ] Archaeologist appears at Petalburg's west tree line ONLY when you are Champion AND M2 is complete (Champion with M2 unfinished -> nobody there)
- [ ] Her intro references the Pacifidlog braille chambers; saying yes takes you into Colossus Vault
- [ ] Colossus Vault looks right: main hall + two side alcoves, dark stone dais, no way out of bounds, no wild encounters
- [ ] South alcove returns you to Petalburg beside her spot
- [ ] Regieleki (west alcove) and Regidrago (east alcove) visible from the first visit; each fights at level 65; KO returns on re-entry; only catching removes it
- [ ] Dais is EMPTY until both wardens are caught; then Regigigas appears there; same battle rules at level 65
- [ ] All three obey immediately at any badge count
- [ ] In-vault archaeologist tracks progress: wardens intro -> giant-awake notice -> closing thanks -> quiet after
- [ ] Journal "The Colossus Wakes" opens after meeting her, runs both beats, completes and drops off
- [ ] Wild sweep: none of the three appear in any random source (existing test gate)

## Hidden area H4 (Phase 11)
- [ ] Hiker appears in Fortree (west side, ground level below the tree houses) only after the League - no M3 requirement
- [ ] His intro plays once; saying yes climbs to Old-Growth Canopy; saying no leaves him available
- [ ] Old-Growth Canopy looks right: wooden decks and walkways in the treetops, rails above, canopy all around, no way off the decks, no wild encounters
- [ ] South walkway returns you to Fortree beside the hiker
- [ ] Ho-Oh on the high sun deck and Lugia in the shaded east corner both visible from the first visit; each fights at level 65; KO returns on re-entry; only catching removes it
- [ ] Celebi absent until BOTH are caught, then appears on the moss shrine (west); same rules at level 65
- [ ] All three obey immediately at any badge count
- [ ] Journal "Rainbow Wings" opens after meeting the hiker, runs both beats, completes and drops off
- [ ] Wild sweep: none of the three appear in any random source (existing test gate)

## Hidden area H8 (Phase 11)
- [ ] Researcher appears in Fallarbor (south-west of the contest hall area) only after the League
- [ ] Her intro plays once; saying yes climbs to Windswept Rise; saying no leaves her available
- [ ] Windswept Rise looks right: open ash moor ringed by rocky mounds, falling ash weather, four stone perches at the corners, no way out except the south gap, no wild encounters
- [ ] South gap returns you to Fallarbor beside her
- [ ] Tornadus (NW), Thundurus (NE), Landorus (SW) visible from the first visit; each fights at level 65; KO returns on re-entry; only catching removes it
- [ ] SE perch is EMPTY until the three are caught; then Enamorus appears there; same rules at level 65
- [ ] All four obey immediately at any badge count
- [ ] All four caught -> researcher's thanks + REVEAL GLASS handed over exactly once; bag-full retry works; glass switches the genies' Therian forms
- [ ] Journal "The Weather Menders" opens after meeting her, runs both beats, completes after the glass
- [ ] Wild sweep: none of the four appear in any random source (existing test gate)

## Hidden area H6 (Phase 11)
- [ ] Ecologist appears at Mossdeep's cliff edge (below the ninja boy's ledge area) only after the League
- [ ] Her intro plays once; saying yes climbs down to Mossdeep Undercliff; saying no leaves her available
- [ ] Undercliff looks right: spring pool chamber + dark nook, cave walls, no way out of bounds, no wild encounters
- [ ] South alcove returns you to the cliff edge beside her
- [ ] Xerneas (by the pool) and Yveltal (dark nook) visible from the first visit; each fights at level 70; KO returns on re-entry; only catching removes it
- [ ] Zygarde absent until BOTH are caught, then appears at the center floor; same rules at level 70
- [ ] All three obey immediately at any badge count
- [ ] Five cell pickups glow in the cavern; each collects once with a chime and never returns
- [ ] Trio caught but cells missing -> ecologist points back down (with a lift offer); all five + trio -> ZYGARDE CUBE given once, bag-full retry works
- [ ] Journal "The Balance Below" opens after meeting her, shows trio and cell counts, completes after the cube
- [ ] Wild sweep: none of the three appear in any random source (existing test gate)

## Hidden area H7 (Phase 11)
- [ ] Engineer appears in Mauville (south of the central plaza) only after the League
- [ ] His intro plays once; saying yes climbs down to Resonance Hall; saying no leaves him available
- [ ] Resonance Hall looks right: single vault, dark cold patch at the north end, no way out of bounds, no wild encounters
- [ ] South alcove returns you to Mauville beside him
- [ ] Reshiram (west) and Zekrom (east) face each other, visible from the first visit; each fights at level 70; KO returns on re-entry; only catching removes it
- [ ] Kyurem absent until BOTH are caught, then appears at the cold north end; same rules at level 70
- [ ] All three obey immediately at any badge count
- [ ] All three caught -> engineer's thanks + DNA SPLICERS given once; bag-full retry works; splicers fuse/split Kyurem properly
- [ ] Journal "Truth and Ideals" opens after meeting him, runs both beats, completes after the splicers
- [ ] Wild sweep: none of the three appear in any random source (existing test gate)

## Hidden area H9 (Phase 11)
- [ ] Storyteller elder appears in Verdanturf (south-west, near the town's lower path) only after the League
- [ ] His intro plays once; saying yes walks you into Hero's Meadow; saying no leaves him available
- [ ] Hero's Meadow looks right: walled meadow like Littleroot Hollow, no way out of bounds, no wild encounters
- [ ] South gap returns you to Verdanturf beside him
- [ ] Five heroes visible from the first visit: Zacian + Zamazenta (north pair), Glastrier (west), Spectrier (east), Kubfu (near the entrance); each fights at level 70; KO returns on re-entry; only catching removes it
- [ ] Calyrex absent until BOTH steeds are caught, then appears at the meadow's crown (top center); same rules at level 70
- [ ] All six obey immediately at any badge count
- [ ] All six caught -> elder's thanks + RUSTED SWORD, RUSTED SHIELD, and REINS OF UNITY given together exactly once; bag-full refuses all three and retries
- [ ] Journal "The Old Heroes" opens after meeting him, runs the steeds beat then the king, completes after the relics
- [ ] Wild sweep: none of the six appear in any random source (existing test gate)

## Hidden areas H2a + H2b (Phase 11)
- [ ] Gardener appears in Oldale (east side, below the mart row) only after the League
- [ ] His intro opens BOTH journal quests; saying yes walks you into the Forgotten Garden; saying no leaves him available
- [ ] Forgotten Garden looks right: walled meadow, four stelae stones up north, grove + mask shrine down south, no way out of bounds, no wild encounters
- [ ] South gap returns you to Oldale beside him
- [ ] H2a: all four Treasures visible beside their stelae from the first visit; each fights at level 65; KO returns on re-entry; only catching removes it; stela signs read correctly (curly quotes render)
- [ ] H2b: the Loyal Three visible on their perches; Ogerpon ABSENT until all three are caught, then appears at the mask shrine with its greeting line; level 65
- [ ] All eight obey immediately at any badge count
- [ ] Gardener wraps each quest separately (courtyard wrap, mask-story wrap), then offers visits; both journal quests complete and drop off independently
- [ ] Wild sweep: none of the eight appear in any random source (existing test gate)

## Hidden area H5a + Plate hunt (Phase 11 finale)
- [ ] Historian appears in Lilycove (east side, below the museum area) only after the League
- [ ] Her intro plays once; saying yes enters the Rift Vestibule; saying no leaves her available
- [ ] Rift Vestibule looks right: hall + dark north sanctum with the altar, no way out of bounds, no wild encounters
- [ ] South alcove returns you to Lilycove beside her
- [ ] Dialga (west) and Palkia (east) visible from the first visit; each fights at level 75; KO returns on re-entry; only catching removes it
- [ ] Giratina appears on Mt. Pyre's summit only AFTER meeting the historian; fights at level 75; same rules
- [ ] All 17 Plate item balls are reachable and collect once each (list: Fiery Path, Shoal Cave entrance + ice room, New Mauville, Petalburg Woods, Granite Cave 1F, Jagged Pass, Route 111, Sky Pillar 1F, Mt. Pyre summit + 3F, Route 119, Meteor Falls 1F + B1F, Abandoned Ship B1F, Mt. Chimney, Route 117) - note: plates are collectible even before the postgame; only the journal quest is postgame
- [ ] Trio caught -> historian gives ADAMANT CRYSTAL + LUSTROUS GLOBE + GRISEOUS CORE together exactly once; bag-full refuses all three and retries
- [ ] Altar: quiet text before the trio; plate-count text (N of 17) with trio but missing plates; with trio + all 17 -> Arceus battle at level 80
- [ ] Arceus KO/flee -> "light recedes", altar can be tried again; only catching sets it done; altar quiet afterward
- [ ] Historian's finale line plays once after Arceus; journal "The Making of Everything" completes and drops off
- [ ] All four obey immediately at any badge count
- [ ] Wild sweep: none of the four appear in any random source (existing test gate)

## Playtest fixes 1 (2026-09-18)
- [ ] Special starter: pick each of Eevee / Pikachu / Ditto on separate new games; the picked species is what Birch hands over (level 5)
- [ ] With a Special pick, the Route 103 rival has a random HOENN starter (first stage)
- [ ] Route 101/102/103/104, Petalburg Woods, Rusturf Tunnel: wilds are level 3–6 (was 2–5)
- [ ] Busy route with follower + several visible wilds: no "too many object events" crash screen in the dev build; spawns just pause
- [ ] Start menu: first entry sits close under the window's top border (list moved up 4px, window 1 tile shorter)

## Task 12.2 — Weather Institute (Phase 12)
- [ ] 2F: Forecaster Halley stands in the console aisle (left side); pre-League she tells the "year of the great storms" story ending with the blooming meadow line
- [ ] Postgame (game-clear flag): Halley tells the full history (storm, late warning, the barometer, "he stopped using his name") — no name is ever spoken
- [ ] 1F: three readable clues — storm logbook with a torn-out page (left machine block), staff photo with one researcher half-turned (right machine block), empty wall bracket near the stairs
- [ ] The word "Kai" appears nowhere in any of this content

## Task 12.3 — Coralmere, present (Phase 12)
- [ ] Route 128 east: rock island reads as ruins — tower-top sign on the south face of the tall rocks (read from the water below), stone-post rows sign east of the island (4 new posts in two lines)
- [ ] Dive on the dark 2×2 patch at the posts (86,17)-ish lands in a small underwater pocket; cut-stone sign next to a made stone opening
- [ ] Pre-flag: swimming into the opening gets 2 tiles inside, then "the current … too strong" and you're back outside (debug: FLAG_CITIES_CORALMERE_OPEN toggles this)
- [ ] Flag set: full village — street, square with the CO…ALME…E sign stone, carved doorway (east house), bell tower base (north), swept house floor with hearth (west house); no encounters, no items
- [ ] Emerging from the pocket surfaces you at the dive patch

## Task 12.4 — Coralmere, past (Phase 12; debug-warp only until 12.5)
- [ ] Debug warp to CORALMERE PAST: walled village, tower top-center, sandy square + street, two log houses, beach, dock into the cove
- [ ] The five readables mirror the ruins at the same spots: town sign whole ("May every boat come home"), bell rope + chalk scoreboard (tower), fresh lintel (east house door), stew on the hearth (west house door), brass barometer reading FAIR (stone post by the dock)
- [ ] Six villagers, all unnamed, everyday lines; the elder mentions the young researcher who checks the barometer; the kids' "four rings" matches the tower scoreboard
- [ ] Music is the Pacifidlog/Lilycove theme; weather sunny; no encounters, no exits (dev warp out)

## Task 12.5 — Team Epoch V1–V5 (Phase 12)
- [ ] V1: postgame, Devon researcher in Space Center lobby → annex door appears on 2F back wall → 2 grunt battles + Meridian (lv60 team) → Mewtwo in the ring; Genesect wakes after; Mew outside the door after both; Epoch gone once all three caught
- [ ] V2: Devon aide (Devon Corp 3F) → Route 115 cliff camp (Mach Bike/Meteor Falls) → grunts + Gnomon → Type: Null → Silvally → sealed crate opens from inside (Magearna gift) → the letter completes the arc AND opens the sunken village
- [ ] V3: researcher reports six wormholes + Cosmog gift → UB statics at R124/R119/New Mauville/R120/Jagged Pass/Mt. Pyre; Poipole gift after Guzzlord; Naganadel after; Necrozma at R124 after Sol+Lun; Archivist scene at Mt. Pyre (he closes a hole, leaves); Gnomon gives N-Solarizer/Lunarizer when all 16 obtained; Halley has a new line after the Mt. Pyre scene
- [ ] V4: Gnomon reports the breakthrough → paradox pockets (R111 x4, Woods x3, R119 x3, New Mauville x3, R110 x3, Ship deck x4) → Meridian at the R128 anchors, Gnomon at New Mauville → entering the sunken square warps to living Coralmere; walk to the sea ends it → Terapagos in the square after → arc completes on Koraidon+Miraidon+Terapagos (pockets stay open)
- [ ] V5: arriving at Pacifidlog after V4 starts the storm (downpour) → the Archivist at the dock sails you to the Storm's Eye islet → Eternatus (lv80; catch or defeat both trigger the heroic act) → rift shut, storm stops, quiet boat ride home; if Eternatus wasn't caught, he ferries you back out until it is
- [ ] All Epoch battles award ranking points once; no battle anywhere with the Archivist; "Kai" appears nowhere

## Task 12.6 — The ending (Phase 12)
- [ ] After V5: sun out at Pacifidlog, the family (Marisol, Nico, Bay) stands on the planks behind the Archivist at the dock; each has a "before" line
- [ ] Talking to him plays the scene: Nico runs to him and says the name; the bell rings once; Marisol's speech; his answer; white fade — from here he is KAI
- [ ] After: the family is home outside the bell house (House 3) with new lines; Kai still ferries to the Storm's Eye if Eternatus is uncaught
- [ ] Epilogues: Kai at the Weather Institute 2F window (desk faces the sea; Halley has a final line); the annex is the Coralmere Archive — Meridian teaching, Gnomon labeling crates "NEVER AGAIN (PROBABLY)"
- [ ] Journal: "The Quiet Buyers" quest tracked the whole thread and drops off at the ending; Halley's history now says "the year the great storms came" (timeline fix)
- [ ] "Kai" is not spoken anywhere before the naming scene

## Task 12.7 — The Coralmere survivors (Phase 12)
- [ ] Seven survivors readable from game start: Dewford fisher (beach), Slateport vendor (market), Mauville musician, Fallarbor teacher, Lilycove museum painter (1F), Mossdeep sailor, Sootopolis resident — each gives an ordinary hint
- [ ] After the rift walk (V4): each says one step more, naming Coralmere
- [ ] After the ending: each speaks of Kai by name, warmly
- [ ] Journal "Voices of Coralmere" appears after the rift walk, counts up to 8 of 8 (the Pacifidlog family is the eighth), drops off when all met + ending done

## Task 12.8 — The name check
- [ ] `make check` runs tools/cities/check_kai.py and stays green; deliberately adding "Kai" to any non-ending string should turn it red

## Phase 13 — Mythical events (all postgame, all L70)
- [ ] Simple statics appear postgame and return if they flee: Jirachi (Cozmo's House), Diancie (Granite Cave B2F), Manaphy then Phione (Underwater Route 124), Victini (Mauville), Meloetta (Fallarbor Town), Volcanion (Lavaridge), Marshadow (Sky Pillar 1F), Zeraora (New Mauville), Zarude (Petalburg Woods), Pecharunt (Mt. Pyre Summit)
- [ ] Deoxys: postgame sailor at Lilycove Harbor sails to Birth Island; the vanilla triangle puzzle runs; Deoxys is L70
- [ ] Shaymin: telling Halley's history postgame reveals the Route 119 meadow (south of the Institute); Shaymin there gives the Gracidea
- [ ] Hoopa: a ring appears in the Trick House entrance postgame → Ring Chamber; plaque order SUN/SEA/SKY opens Hoopa + Prison Bottle
- [ ] Meltan: Slateport dockworker starts the hunt; 6 nuts across town; all 6 → Meltan; catching it → Melmetal
- [ ] Journals "Whispers and Wishes" (mythicals) shows postgame
- [ ] `make check` completeness tests stay green (every story-only species obtainable, none placed twice)

## Phase 14 — Remaining postgame features
- [ ] Title defense: postgame, the League lobby official offers a defense; menu of Bram/Ilaria/Corsen/Vesper/Elite Four; battles are repeatable and each win adds ranking points; challengers stay "beaten" in the world afterward; the Master ceremony still runs once
- [ ] Random-trade NPC (Slateport market, ~23,13): hand over a party mon → receive a random non-legendary species at the same level; never gives story-only species; won't take an Egg
- [ ] Achievements: the Mauville records-keeper (~19,8) reports "X of Y earned" and lists them (Champion, Master, 300 caught, Walked Coralmere, Team Epoch's Peace, Arceus)
- [ ] Shiny Charm: at 300 caught, Birch (his lab) hands over the Shiny Charm, once
- [ ] Mauville plaza: free move relearner (~15,8) and deleter (~17,8), no Heart Scale; Fallarbor/Lilycove NPCs still work

## Phase 15 — Challenge modes (new game, truck setup)
- [ ] Truck setup asks Nuzlocke? then Randomizer? after difficulty/assist; both default off if you say no
- [ ] Randomizer on: wild encounters, your starter, and trainer teams are shuffled to random non-legendary species; the same original always maps to the same replacement; no legendaries/mythicals/UBs/paradox ever appear
- [ ] Nuzlocke on: after your first catch in an area, a Poké Ball on a different species there is refused ("the NUZLOCKE rule holds"); dupes (already-owned) and shinies are still catchable
- [ ] Nuzlocke faint: a Pokémon that faints (and you survive the battle) is moved to the last PC box (memorial); it can't be moved, shifted, or withdrawn from that box (fail beep)
- [ ] Total party wipe still white-outs and heals normally (run-ending, no permadeath applied)
- [ ] A normal (no-challenge) save behaves exactly as before

## Pronouns (new-game setup)
- [ ] Birch's intro asks "Which of these looks feels like you?" (reworded from boy/girl); the sprite still previews and sets your look
- [ ] Truck setup asks "What pronouns do you use?" with He/She/They/Enter my own, separate from the look
- [ ] "Enter my own" opens a text-entry screen and returns to setup cleanly
- [ ] Any look pairs with any pronoun (e.g. Brendan-look + they/them works)

## Known-pending (do not report as bugs)
- Access menu: numeric HP, patterned bars, sound cues, subtitles, hold-to-confirm are hidden until wired (6.3/6.7 follow-ups)
- Difficulty change at Pokémon Centers: [PROPOSED], not built
- Rematch teams are Normal difficulty only for now; Easy/Hard fall back to Normal
