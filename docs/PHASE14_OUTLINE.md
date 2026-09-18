# Phase 14 — Remaining Postgame Features (outline, for approval)

**Status: APPROVED + BUILT 2026-09-18** (menu title defense; flag-
computed achievements; Slateport trader). All four design decisions are locked
(docs/PHASE_13_14_DECISIONS.md); this is the assembly plan. Five small
tasks, no new mechanics.

## 14.1 — Champion title defense (GDD 7.4)
The League lobby already has a Cities official (EverGrande League 1F,
13,4). Postgame, once FLAG_CITIES_POKEMON_MASTER-eligible (actually:
once Champion / game clear), he offers a **title defense on demand**.

Key simplification the scout found: **every ranked NPC already has a
postgame-tier trainer team** (Elite Four `_2` versions, gym-leader
rematch versions, and the four Cities challengers Bram/Ilaria/Corsen/
Vesper at IDs 173/462/568/581). So title defense reuses those IDs — no
new trainers.

Proposed flow: the official presents a **menu of challengers** —
Bram, Ilaria, Corsen, Vesper, and the Elite Four (Sidney/Phoebe/
Glacia/Drake). Pick one → full battle against their postgame team →
win scores ranking points (the existing per-battle scoring already
fires on any trainer battle). Repeatable.

## 14.2 — Random-trade NPC (GDD 9.3)
A "Wonder Trade"-style NPC (proposed: Slateport market, the trade
town). Hand over any Pokémon → receive a **random enabled species
that is not story-only** (IsStoryOnlySpecies filter). New special
`Script_CitiesRandomTradeSpecies` picks the species; the NPC uses the
vanilla trade/give flow. Never gives legendaries/mythicals/UBs/paradox.

## 14.3 — Trainer-card stamps / achievements (GDD 9.3)
Rather than modify the vanilla trainer-card render or spend save
space, **achievements are computed from existing flags/state** (the
same trick the quest journal uses) — e.g. Champion, Pokémon Master,
300 caught, each postgame thread cleared (M/H arcs, Team Epoch, all
mythicals), all starters seen. Surfaced as an **"Achievements" list**
on a new NPC beside the ranking board (or a page appended to the
Ranking screen). No new save data; nothing to migrate.

## 14.4 — Shiny Charm (GDD, [DECIDED]: Birch at 300 caught)
Birch (his lab) hands over the **Shiny Charm** once the player has
caught **300 species**, one time. Simple caught-count check + giveitem.

## 14.5 — Move relearner + deleter (GDD, [DECIDED])
A **free** relearner and deleter **side by side in Mauville's central
plaza** (~16–18, 8), no Heart Scales. They reuse the vanilla
relearner/deleter logic; the original Fallarbor/Lilycove NPCs stay.

## Decisions needed from Rocco
1. Title defense: a **menu** of named challengers + Elite Four
   (recommended), or a **random** opponent each time?
2. Achievements: **computed from flags, shown by an NPC / ranking
   page** (recommended, no save cost), or invest in real trainer-card
   stamp rendering?
3. Random-trade NPC location: **Slateport market** (recommended) or
   elsewhere?
