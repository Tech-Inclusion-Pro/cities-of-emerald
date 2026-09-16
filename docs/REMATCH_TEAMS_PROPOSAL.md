# Rematch Version Teams — Proposal for Review (Task 8.2)

**Status: APPROVED 2026-09-16 — implemented in trainers.party and cities_rival_rematch_parties.h.**

## Ground rules used in this draft

- **Levels:** V1 = 62–65 (just past the Champion, ace at 65), V2 = 72–75, V3 = 82–85.
  Postgame, so level caps are already off.
- **Format:** gym leaders are double battles (approved); the rival stays single,
  matching every rival fight so far.
- **Teams:** V1 has 5 Pokémon, V2 and V3 have 6. Aces are listed last and sit
  2 levels above the rest. Every leader keeps their vanilla ace so the character
  reads the same.
- **Moves:** Pokémon without listed moves use their level-up movesets. Aces and
  doubles-synergy pieces get curated moves at implementation time — those will be
  visible in the trainers.party diff, which you can review again before merge.
- **Difficulty:** teams are defined for Normal. Easy/Hard fall back to Normal for
  now; per-difficulty variants can come later without touching the version system.
- **No box legendaries.** Cross-gen species are fair game (the whole dex is in
  the wild tables already); each leader keeps a Hoenn core so they still feel
  like Emerald.

## Roxanne — Rock

| | Team (ace last) |
|---|---|
| V1 | Probopass, Armaldo, Cradily, Golem, **Aggron 65** |
| V2 | Probopass, Rhyperior, Armaldo, Cradily, Lycanroc, **Aggron 75** |
| V3 | Gigalith, Tyranitar, Rhyperior, Cradily, Archeops, **Aggron 85** |

Doubles idea: Probopass Wide Guard early; V3 becomes a sand team (Gigalith sets
sand, Tyranitar/Rhyperior enjoy it, Cradily doesn't care).

## Brawly — Fighting

| | Team |
|---|---|
| V1 | Hitmontop, Medicham, Breloom, Machamp, **Hariyama 65** |
| V2 | Hitmontop, Machamp, Medicham, Breloom, Conkeldurr, **Hariyama 75** |
| V3 | Hitmontop, Conkeldurr, Mienshao, Gallade, Kommo-o, **Hariyama 85** |

Doubles idea: Hitmontop Intimidate + Fake Out is the classic doubles opener;
Breloom Spore for chaos. Hariyama ace with Guts.

## Wattson — Electric

| | Team |
|---|---|
| V1 | Magneton, Electrode, Ampharos, Galvantula, **Manectric 65** |
| V2 | Electrode, Magnezone, Ampharos, Galvantula, Eelektross, **Manectric 75** |
| V3 | Magnezone, Eelektross, Galvantula, Rotom, Toxtricity, **Manectric 85** |

Doubles idea: Electrode speed + Ampharos power; Galvantula Electroweb speed
control; Eelektross has no weaknesses (Levitate) — a fun "wait, what?" moment.

## Flannery — Fire

| | Team |
|---|---|
| V1 | Magcargo, Camerupt, Houndoom, Arcanine, **Torkoal 65** |
| V2 | Camerupt, Arcanine, Houndoom, Chandelure, Talonflame, **Torkoal 75** |
| V3 | Chandelure, Arcanine, Volcarona, Camerupt, Talonflame, **Torkoal 85** |

Doubles idea: Torkoal Drought anchors every version; Camerupt is slow but hits
both foes with Eruption under sun; V3 Volcarona is the scary wallbreaker.

## Norman — Normal

| | Team |
|---|---|
| V1 | Vigoroth, Kangaskhan, Blissey, Staraptor, **Slaking 65** |
| V2 | Kangaskhan, Blissey, Porygon-Z, Obstagoon, Braviary, **Slaking 75** |
| V3 | Porygon-Z, Obstagoon, Indeedee, Ursaluna, Kangaskhan, **Slaking 85** |

Doubles idea: Slaking + a partner that can use its Truant turn (Indeedee
support in V3); Blissey is the wall the player has to play around.

## Winona — Flying

| | Team |
|---|---|
| V1 | Swellow, Pelipper, Skarmory, Tropius, **Altaria 65** |
| V2 | Pelipper, Skarmory, Togekiss, Gliscor, Swellow, **Altaria 75** |
| V3 | Pelipper, Corviknight, Togekiss, Salamence, Swellow, **Altaria 85** |

Doubles idea: Pelipper Drizzle + Hurricane accuracy for the whole team;
Tailwind on Togekiss/Corviknight; Altaria ace kept loyal to Winona.

## Tate & Liza — Psychic (already a double battle by nature)

| | Team |
|---|---|
| V1 | Claydol, Xatu, Grumpig, **Solrock 65 + Lunatone 65** |
| V2 | Claydol, Bronzong, Gardevoir, Gallade, **Solrock 75 + Lunatone 75** |
| V3 | Metagross, Gardevoir, Bronzong, Armarouge, **Solrock 85 + Lunatone 85** |

Doubles idea: the twins keep both aces on the field together; Trick Room on
Bronzong in V2/V3 flips the speed game, Claydol/Xatu support early.

## Juan — Water

| | Team |
|---|---|
| V1 | Ludicolo, Whiscash, Crawdaunt, Sealeo, **Kingdra 65** |
| V2 | Politoed, Ludicolo, Walrein, Crawdaunt, Gorebyss, **Kingdra 75** |
| V3 | Politoed, Ludicolo, Milotic, Barraskewda, Walrein, **Kingdra 85** |

Doubles idea: V2+ is a rain team — Politoed Drizzle, Ludicolo/Barraskewda
Swift Swim, Kingdra ace with rain-boosted Muddy Water. Elegant and very Juan.

## Rival — single battle, Route 103

The starter slot (marked ★) is filled at battle time with the rival's
type-advantage starter from your chosen region, fully evolved — same rule as
every rival fight.

| | Team |
|---|---|
| V1 | ★ Starter 65, Swellow 62, Magnezone 62, Breloom 63, Wailord 63 |
| V2 | ★ Starter 75, Swellow 72, Magnezone 72, Breloom 73, Flygon 73, Wailord 73 |
| V3 | ★ Starter 85, Swellow 82, Magnezone 82, Flygon 83, Ludicolo 83, Wailord 83 |

The crew is the Ruby/Sapphire rival's classic circle all grown up — Swellow,
Wailord, the Magnemite line — plus Flygon and Ludicolo as their postgame
catches.

## What happens after approval

1. Teams land in `src/data/trainers.party` as the `_2`/`_3`/`_4` parties for
   each leader (replacing the vanilla match-call rematch parties) and in
   `src/data/cities_rival_rematch_parties.h` for the rival.
2. Curated moves/items/abilities for aces and synergy pieces get written at the
   same time and show up in the diff for a second look.
3. This file gets updated to APPROVED with any changes you asked for.
