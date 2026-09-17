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

## Known-pending (do not report as bugs)
- Access menu: numeric HP, patterned bars, sound cues, subtitles, hold-to-confirm are hidden until wired (6.3/6.7 follow-ups)
- Difficulty change at Pokémon Centers: [PROPOSED], not built
- Rematch teams are Normal difficulty only for now; Easy/Hard fall back to Normal
