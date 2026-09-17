# Cities of Emerald — Playtest Checklist (Phases 0–7)

Run: `open -a mGBA ~/Projects/cities-of-emerald/pokeemerald.gba`
Debug menu: hold R + press START in the overworld (badges, flags, warp, items).
Keys: X = A, Z = B, Enter = Start (rebind in mGBA → Settings → Keyboard).

## New game flow
- [ ] Truck setup runs before Littleroot: accessibility preset → difficulty → Assist (+ level cap choice if Assist on)
- [ ] Starter screen: 10-region list scrolls; 3 starters show sprite + name + "type as text"; B steps back; confirm wording matches GDD; starter is level 5
- [ ] Special region gives Eevee; rival later has a random Hoenn starter
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

## Known-pending (do not report as bugs)
- Access menu: numeric HP, patterned bars, sound cues, subtitles, hold-to-confirm are hidden until wired (6.3/6.7 follow-ups)
- Difficulty change at Pokémon Centers: [PROPOSED], not built
- Rematch teams are Normal difficulty only for now; Easy/Hard fall back to Normal
