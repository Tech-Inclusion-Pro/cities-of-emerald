# Cities of Emerald — Game Design Document

Version: 0.12 (ranking floor and Kai's redemption arc)
Owner: Rocco Catrone
Base: `rh-hideout/pokeemerald-expansion`, `upcoming` branch
Region: Hoenn (no second region)

---

## How to read this document

This document describes **what** the game is. The companion file `IMPLEMENTATION_PLAN.md` describes **how and in what order** to build it.

Every design item carries one of these status tags:

| Tag | Meaning |
|---|---|
| **[DECIDED]** | Rocco has approved this. Build it as written. |
| **[PROPOSED]** | A suggested default. Do not build until Rocco confirms. |
| **[OPEN]** | Needs a decision. Ask Rocco before touching related code. |
| **[LATER]** | Out of scope for the first release. Do not build. |

File paths and config names in this document are best-known references for pokeemerald-expansion. **Always verify them against the checked-out repo before editing.** If a named config does not exist, report that instead of inventing one.

---

## 1. Vision

Cities of Emerald is a modernized, accessibility-first Emerald that keeps Hoenn and its main story, then adds:

- Every non-legendary Pokémon from Generations 1–9, placed by habitat and progression
- Story-driven legendary arcs (no legendary is ever random)
- A deep postgame with two story threads, stronger gym and rival rematches, and a national ranking system
- The most complete accessibility options of any Emerald hack

Inspirations (structure only; all story, characters, and areas must be original):

- **Pokémon Emerald Squared:** hidden areas reached from existing towns, with legendary questlines
- **Pokémon Emerald Horizons:** a new postgame villain arc
- **Pokémon Modern Emerald:** encounter tables that change after the League

---

## 2. Platforms and distribution

- **[DECIDED]** Target platforms: GBA **emulators** on **iOS, Android, Mac, and PC**. Real GBA hardware is not a target.
- **[DECIDED]** Primary development emulator: mGBA (Mac and PC). Test each release on at least one Android emulator and one iOS emulator (for example, Delta), with special attention to the real-time clock that drives day/night.
- **[DECIDED]** Distribute only as a BPS patch applied to the player's own legally owned Emerald ROM. Never commit or distribute a ROM.
- **[DECIDED]** Name: **Cities of Emerald**. The sunken village of Coralmere (Section 7.2) is part of the name's meaning: one of Hoenn's "cities" can only be fully seen through a time rift.

---

## 3. Core systems toggled from the expansion

These are mostly config changes. **[DECIDED]** unless noted.

### Battle mechanics
- Physical/special split
- Fairy type
- Mega Evolution, Z-Moves, Dynamax, and Terastallization (all four)
- Latest-generation move, ability, and type data where the expansion supports it
- Double battles for trainers (per-trainer setting) and wild double battles

### Overworld
- Overworld Wild Encounters (OWE): visible wild Pokémon
- Day/night cycle with time-of-day encounter tables (morning, day, evening, night)
- Ambient cries based on active overworld encounters (`OW_AMBIENT_CRIES_OWE_PRIORITY` or equivalent)
- Follower Pokémon
- DexNav
- Encounter toggle flags (no wild encounters / no trainer sight), B2W2-style Repel prompt, Lures
- Running indoors and auto-run toggle

### Quality of life
- Reusable TMs
- Move relearner and move deleter in an easy-to-reach location **[PROPOSED: Oldale Town Pokémon Center]**
- Bag sorting and expanded bag capacity
- More PC storage **[PROPOSED: only if the expansion supports it without breaking saves]**
- PC access from the start menu **[PROPOSED: unlocked after badge 1]**
- National Pokédex available from the start

### Collecting
- Standard shiny rate (no change) **[DECIDED]**
- Shiny Charm as a reward **[PROPOSED: for completing the National Pokédex "seen" count]**
- Hidden abilities obtainable (wild chance and Ability Patch)

---

## 4. Starting the adventure

### 4.1 New-game flow **[DECIDED]**
1. Standard intro (name, appearance)
2. **Setup screen** before the player enters the truck:
   - Accessibility preset (Section 11)
   - Difficulty mode (Section 10)
   - Challenge options (Nuzlocke, randomizer)
3. Littleroot Town; a character explains accessibility options in-world (Section 11.7)

### 4.2 Starter selection **[DECIDED]**

Located in Birch's rescue scene (replace the vanilla three-ball bag screen).

**Step 1 — Pick a region** (vertical text list, cursor-driven):

| Option | Starters |
|---|---|
| Kanto | Bulbasaur, Charmander, Squirtle |
| Johto | Chikorita, Cyndaquil, Totodile |
| Hoenn | Treecko, Torchic, Mudkip |
| Sinnoh | Turtwig, Chimchar, Piplup |
| Unova | Snivy, Tepig, Oshawott |
| Kalos | Chespin, Fennekin, Froakie |
| Alola | Rowlet, Litten, Popplio |
| Galar | Grookey, Scorbunny, Sobble |
| Paldea | Sprigatito, Fuecoco, Quaxly |
| Special | Eevee |

**Step 2 — Pick a Pokémon:** show the region's three starters side by side. For each: front sprite, name, and type **as text** (for example, "Grass"). Pressing B returns to Step 1. For Special, show Eevee alone.

**Step 3 — Confirm:** "You chose [NAME], the [TYPE]-type Pokémon. Is that right?" Yes / No.

Requirements:
- Starter level matches vanilla (5).
- Rival (May/Brendan) picks a starter with a type advantage over the player's choice, drawn from the same region. If the player picks Eevee, the rival picks **[PROPOSED]** a random Hoenn starter.
- All rival teams that include a starter must branch on the player's choice (the vanilla game already branches on three options; extend to 28 combinations or map by type).
- The screen must be fully usable with text only (no information conveyed by sprite or color alone).

### 4.3 Eevee and Eeveelutions **[DECIDED]**

**Stone NPC (after badge 2)**
- Located in the Dewford Town Pokémon Center; appears after the player wins badge 2 (Brawly).
- Explains each stone in plain language before the player chooses: what the stone is, which Eeveelution it creates, and that Eeveelution's type (as text) and strengths.
- The player picks **one** stone.
- The NPC also explains the friendship evolutions (Espeon, Umbreon, Sylveon), which need no stone.

**Eeveelution trainer mini-story**
- A group of Eeveelution trainers across Hoenn, each using one Eeveelution.
- Beating a stone-Eeveelution trainer (Vaporeon, Jolteon, Flareon, Leafeon, Glaceon) earns that stone, so players can collect the rest over time.
- Espeon, Umbreon, and Sylveon trainers teach how friendship evolution works instead of giving a stone.
- Tracked in the quest journal; these trainers count toward rankings like other regular trainers.
- **[PROPOSED]** Trainer locations and unlock badges to be set when the quest is written.

**Evolution methods**
- Stone-based: Vaporeon (Water), Jolteon (Thunder), Flareon (Fire), Leafeon (Leaf), Glaceon (Ice). Enable Leaf and Ice Stone evolution for Leafeon and Glaceon through expansion config.
- Friendship-based: Espeon (day), Umbreon (night), Sylveon (Fairy move plus friendship).

---

## 5. Wild Pokémon

### 5.1 Principles **[DECIDED]**
1. **Habitat first:** species appear in maps that match their type and lore (water types on water routes, Ice types on mountains or Shoal Cave, Fire types near Mt. Chimney, and so on).
2. **Progression second:** early "beginner" Pokémon from every generation appear in early areas; evolutions and rarer species appear in later areas.
3. **Every non-story-only species is obtainable**, either in the wild or by evolving something found in the wild.
4. **No story-only species ever appears in any encounter table** (Section 6).

### 5.2 Progression tiers

Badge order: 1 Roxanne (Rustboro), 2 Brawly (Dewford), 3 Wattson (Mauville), 4 Flannery (Lavaridge), 5 Norman (Petalburg), 6 Winona (Fortree), 7 Tate & Liza (Mossdeep), 8 Juan (Sootopolis).

| Tier | Areas | Content |
|---|---|---|
| T1 | Routes 101–104, Petalburg Woods | Common early birds, bugs, rodents from all generations |
| T2 | Route 116, Rusturf Tunnel, Granite Cave, Routes 105–109 | Early cave, rock, and sea species |
| T3 | Routes 110, 117, 111, 112, 113, 114, Fiery Path, Meteor Falls | Mid-tier first stages, some middle stages |
| T4 | Routes 115, 118–121, Jagged Pass, Mt. Pyre, Safari Zone | Middle stages, uncommon species |
| T5 | Routes 122–134, Shoal Cave, Seafloor Cavern, Victory Road | Late species, some final stages |
| PG | All routes after the Champion (postgame tables) | Rare species, pseudo-legendary lines, final stages |

### 5.3 T1 beginner pool **[DECIDED concept, PROPOSED list]**

| Gen | Species |
|---|---|
| 1 | Pidgey, Rattata, Caterpie, Weedle, Pikachu (rare) |
| 2 | Hoothoot (night), Sentret, Ledyba (morning), Spinarak (night) |
| 3 | Zigzagoon, Wurmple, Poochyena, Taillow |
| 4 | Starly, Bidoof, Kricketot, Shinx |
| 5 | Patrat, Lillipup, Purrloin, Pidove, Sewaddle |
| 6 | Fletchling, Bunnelby, Scatterbug |
| 7 | Pikipek, Yungoos, Grubbin |
| 8 | Rookidee, Skwovet, Blipbug, Wooloo |
| 9 | Lechonk, Tarountula, Nymble, Pawmi, Fidough |

Use the time-of-day tables to fit more species per route (for example, nocturnal species at night).

### 5.4 Table budget
Each vanilla map has limited slots (land 12, water 5, rock smash 5, fishing 10). Four time-of-day tables multiply this. Plan distribution with a spreadsheet (see implementation plan) and generate `wild_encounters.json` from it rather than editing by hand.

### 5.5 Postgame encounters **[DECIDED]**
Following Modern Emerald's approach: each route has a main-game table set and a postgame table set. After the player becomes Champion, routes switch to postgame tables. Postgame tables emphasize rarer species, pseudo-legendary lines (Dratini, Larvitar, Bagon, Beldum, Gible, Deino, Goomy, Jangmo-o, Dreepy, Frigibax), and final evolutions.

### 5.6 Trade evolutions **[DECIDED concept]**
All trade evolutions must be possible in single-player.
- **[PROPOSED]** Use the Linking Cord item (if present in the expansion; verify) sold in Mauville after badge 3, which evolves any trade-evolution Pokémon, including item-trade ones when holding the required item.
- Karrablast and Shelmet: **[PROPOSED]** evolve with Linking Cord when the other species is in the party.

### 5.7 Version exclusives
Every species that was a version exclusive in its home game must have a home in Hoenn. Covered automatically by rule 5.1.3.

---

## 6. Story-only species (legendaries) **[DECIDED]**

### 6.1 Rule
The following are **story-only**. They are never found in grass, water, caves, overworld encounters, DexNav, random trades, randomizer output, Battle Frontier rental or random pools, or any other random source:

- Legendary Pokémon (including sub-legendaries)
- Mythical Pokémon
- Ultra Beasts (including Poipole and Naganadel)
- Paradox Pokémon
- Borderline cases: Type: Null, Silvally, Cosmog, Cosmoem, Kubfu, Urshifu, Meltan, Melmetal
- Regional forms of any of the above (for example, Galarian Articuno)

### 6.2 Implementation rule
One function, `IsStoryOnlySpecies(species)`, is the single source of truth. It checks the expansion's species flags (legendary, mythical, Ultra Beast, Paradox; verify field names) **plus** an explicit list for the borderline cases. Every random source calls this function.

### 6.3 Multiple arcs
Several legendary arcs can be open at the same time. Each arc has its own flags and a quest journal entry (Section 11.4).

### 6.4 Encounter levels **[DECIDED]**
- **Mid-game arcs:** the legendary's level equals the **current level cap** at the moment of the encounter. If the player arrives later, the level rises to match.
- **Postgame arcs:** fixed level per arc. Levels act as a difficulty guide, since hidden-area arcs can be played in any order. Champion Wallace's ace is level 58, so the postgame starts just above that.

| Level | Hidden-area and follow-up arcs | Villain arc (played in order) |
|---|---|---|
| 60 | M1-PG, H1, H5b, H10, H11 | V1 |
| 65 | H2a, H2b, H3, H4, H8 | V2 |
| 70 | H6, H7, H9 | V3 |
| 75 | H5a (Dialga, Palkia, Giratina) | V4 |
| 80 | H5a (Arceus) | V5 |

- **Mythical events:** levels **[OPEN]**; set when each event is written.
- The strongest legendaries are placed late (see 6.6).

### 6.5 Obedience **[DECIDED]**
- Custom **badge-based** rule for story-only species (vanilla obedience is level-based and would never trigger, since legendaries are always at the cap).
- A mid-game legendary obeys once the player earns the **badge after the one that opened its arc**.
- **M5 exception (lore-based):** Latias and Latios obey once the player has caught **both**. This is stored as a one-time flag, so obedience is never lost if one is later traded or released. Message example: "Latias won't listen until it's reunited with Latios." The quest journal shows the same hint while only one is caught.
- Postgame legendaries always obey.
- **Late catches:** if the required badge is already earned when the Pokémon is caught, it obeys immediately.
- **Disobedience behavior:** no random napping or random moves. The Pokémon does not act, and the battle shows a clear message, for example: "Zapdos won't listen until you earn the Dynamo Badge."
- The quest journal notes when each caught legendary will start obeying.

| Arc | Opens at | Obeys at |
|---|---|---|
| M1 | Badge 3 | Badge 4 |
| M2 | Badge 5 | Badge 6 |
| M3 | Badge 6 | Badge 7 |
| M4 | Badge 7 | Badge 8 |
| M5 | Badge 8 | After both Latias and Latios are caught |

### 6.6 Arc plan **[DECIDED]**

**Main story (vanilla, unchanged):** Groudon, Kyogre, Rayquaza

**Mid-game arcs** (unlock at the listed badge; can be completed any time after)

| ID | Badge | Species | Hook |
|---|---|---|---|
| M1 | 3 | Articuno, Zapdos, Moltres | Strange weather reports across Hoenn |
| M2 | 5 | Regirock, Regice, Registeel | Vanilla Sealed Chamber puzzle, expanded |
| M3 | 6 | Raikou, Entei, Suicune | Roaming sightings the player tracks |
| M4 | 7 | Uxie, Mesprit, Azelf | Three lakes or caves tied to Sootopolis lore |
| M5 | 8 | Latias, Latios | Existing Hoenn lore; Southern Island. Placed last because they are the strongest mid-game legendaries and can Mega Evolve |

**Postgame follow-up to M1**

| ID | Unlock | Species | Hook |
|---|---|---|---|
| M1-PG | After the League, with M1 complete | Galarian Articuno, Galarian Zapdos, Galarian Moltres | The birds' story continues |

**Postgame thread 1 — Hidden areas** (original areas, Emerald Squared structure)

| ID | Entry point | Species | Final reward |
|---|---|---|---|
| H1 | Littleroot | Cobalion, Terrakion, Virizion, Keldeo | — |
| H2a | Oldale | Wo-Chien, Chien-Pao, Ting-Lu, Chi-Yu | — |
| H2b | Oldale (same hidden area as H2a) | Okidogi, Munkidori, Fezandipiti, Ogerpon | — |
| H3 | Petalburg | Regigigas, Regieleki, Regidrago (follow-up to M2) | — |
| H4 | Fortree | Ho-Oh, Lugia, Celebi | — |
| H5a | Lilycove and Mt. Pyre (Giratina at Mt. Pyre) | Dialga, Palkia, Giratina, then Arceus | Adamant, Lustrous, and Griseous Crystals; completed Plate set |
| H5b | Dewford | Cresselia, Darkrai | — |
| H6 | Mossdeep | Xerneas, Yveltal, Zygarde | Zygarde Cube (Zygarde Cells collected during the arc) |
| H7 | Mauville | Reshiram, Zekrom, Kyurem | DNA Splicers, given after all three are caught |
| H8 | Fallarbor | Tornadus, Thundurus, Landorus, Enamorus | Reveal Glass |
| H9 | Verdanturf | Kubfu, Glastrier, Spectrier, Calyrex, Zacian, Zamazenta | Reins of Unity; Rusted Sword; Rusted Shield |
| H10 | Pacifidlog | Tapu Koko, Tapu Lele, Tapu Bulu, Tapu Fini | — |
| H11 | Mt. Chimney | Heatran | — |

**Postgame thread 2 — Villain arc** (original team, Horizons structure)

| ID | Species | Hook | Final reward |
|---|---|---|---|
| V1 | Mewtwo, Mew, Genesect | Products and targets of the team's experiments | — |
| V2 | Type: Null, Silvally, Magearna | Stolen research | — |
| V3 | Poipole, Naganadel, all Ultra Beasts, Cosmog line, Solgaleo, Lunala, Necrozma | Ultra Wormholes the team opens | N-Solarizer and N-Lunarizer |
| V4 | All Paradox Pokémon, Koraidon, Miraidon, Terapagos | Time rifts | — |
| V5 | Eternatus | Final boss of the arc | — |

**Mythical events** (small one-off events)

| Species | Location | Reward |
|---|---|---|
| Deoxys | Mossdeep Space Center, leading to Birth Island | — |
| Jirachi | Fallarbor (Professor Cozmo's meteorite research) | — |
| Diancie | Granite Cave | — |
| Manaphy, Phione | Underwater near Route 124 | — |
| Shaymin | Route 119 (story hook through the Weather Institute) | Gracidea |
| Hoopa | Trick House, Route 110, in a new postgame puzzle room (a strange ring appears; solving the room leads to Hoopa) | Prison Bottle |
| Victini | Mauville City | — |
| Meloetta | Fallarbor Contest Hall | — |
| Volcanion | Lavaridge Town | — |
| Marshadow | Sky Pillar | — |
| Zeraora | New Mauville | — |
| Zarude | Petalburg Woods (unlocks after the League) | — |
| Meltan, Melmetal | Slateport Shipyard; Meltan as a collection hunt, similar to Zygarde Cells | — |
| Pecharunt | Mt. Pyre outskirts | — |

All mythical events unlock after the League.

Design note: the Mt. Pyre area (Giratina, Pecharunt) and nearby Route 123 (Berry Master) become a busy postgame area. Treat it as a hub when designing maps.

### 6.7 Form-change items **[DECIDED]**
- Form-change items are the **final reward** of their arc (see tables above).
- **Arceus Plates:** all 17 are scattered across Hoenn as a collection hunt. Collecting them is tracked in the quest journal; the full set is completed as part of H5a.

### 6.8 Completeness rule
The build must include a test that every story-only species appears in **exactly one** arc or event.

---

## 7. Postgame

### 7.1 Structure **[DECIDED]**
After becoming Champion, the player unlocks:
1. Postgame encounter tables (5.5)
2. Thread 1 hidden areas (6.6), some from early towns and some from later towns
3. Thread 2 villain arc (6.6)
4. Stronger gym leader and rival rematches (7.3)
5. Champion defense (7.4)
6. Battle Frontier as the main competitive hub (vanilla, with expansion updates)

### 7.2 The villain team: Team Epoch **[DECIDED]**

**Theme:** rewriting history. Team Epoch is values-driven, not simply evil. Its members believe they are doing the right thing.

**Leader: the Archivist**
- **No name.** He lost his name when he lost his village; "the Archivist" is the only name he goes by. Pronouns: he/him.
- **True name: Kai.** Revealed only at the end of the arc. Kai must never appear in dialogue, menus, trainer names, or the quest journal before the ending scene. In code, use `EPOCH_ARCHIVIST` for his trainer and object constants.
- A scientist at the Weather Institute (Route 119) who studied Hoenn's weather long before the Groudon and Kyogre crisis.
- His hometown, the coastal village of **Coralmere**, sank during Kyogre's storms. The Institute tracked the storms but could not warn people in time.
- Goal: use time rifts to return to the day of the crisis and save Coralmere.
- Blind spot: he will not accept what else that change would erase.
- **[DECIDED 2026-09-17]** The Archivist's appearance: slate-gray coat, carries Coralmere's old harbor barometer; vanilla stand-in sprites until release-phase art.
- **[DECIDED 2026-09-17]** Admins: Meridian (the believer) and Gnomon (the engineer). Grunts are archivist-styled: coats, satchels; they catalogue, they don't menace. Full cast in docs/EPOCH_STORY_OUTLINE.md.
- Links to Shaymin's event (Section 6.6), which also uses the Weather Institute; the two can share characters or clues.

**Coralmere**
- A new, original coastal village that no longer exists in the present.
- **[DECIDED]** Located on Route 128, next to the Seafloor Cavern where Kyogre awoke.
- **[DECIDED]** Ruins hint that the village was there. Surface ruins are visible on Route 128 from the start of the game, before the player knows what they are; the full sunken village is reachable with Dive during the arc.
- **[DECIDED]** Ruin details: the top of a bell tower rising above the water; broken docks and posts on the surface; underwater streets, doorways, and a worn town sign reading CORALMERE.
- In V4, a time rift briefly shows Coralmere as it was, and the player can walk its streets before the crisis. This is the emotional center of the arc.

**Arc beats**

| Step | What Team Epoch is doing |
|---|---|
| V1 | Building or seeking powerful Pokémon (Mewtwo, Genesect) able to hold open a tear in time |
| V2 | Taking research (Type: Null, Magearna), believing the ends justify it |
| V3 | First attempts to reach the past fail and open Ultra Wormholes instead, letting Ultra Beasts into Hoenn |
| V4 | Breaking through; Paradox Pokémon from past and future spill into Hoenn; the Coralmere time-rift scene |
| V5 | Tapping Eternatus to make the change permanent, and losing control |

**Ending [DECIDED]**
- Resolution through acceptance, not punishment. The player helps the Archivist see that the crisis also shaped the people and the Hoenn they care about now.
- Reflects ACT themes (acceptance and values-based action). Team Epoch changes direction instead of being defeated and jailed.
- **[DECIDED]** The Archivist gets his name back. In the final scene, someone who remembers Coralmere calls him **Kai**, and from then on he is named Kai everywhere in the game (dialogue, trainer name, quest journal).
- **[DECIDED]** A **Coralmere survivor** speaks his name.
- **[DECIDED]** More people from Coralmere survived than Kai believed. He thinks the village was lost with everyone in it; learning otherwise is central to his acceptance.
- **[DECIDED]** Survivors are a **scattered group across many towns**, each referencing Coralmere in some way. The player meets them as ordinary NPCs, with hints that only make sense later. This echoes the game's name: Coralmere lives on in Hoenn's other cities.
- **[DECIDED 2026-09-17]** After the V4 time-rift scene, the quest journal gains a "Coralmere survivors" entry that lists the survivors the player has met, and revisiting them unlocks new dialogue.
- **[PROPOSED]** Survivor roster (hints are written so they read as ordinary flavor text before the reveal):

| Town | Survivor | Hint |
|---|---|---|
| Dewford | A fisher | Won't fish near Route 128 and changes the subject when asked why |
| Slateport | A market vendor | Sells shell charms "made the way they did back home" |
| Mauville | A street musician | Plays a song about bells ringing over the water |
| Fallarbor | A retired teacher | Keeps a hand-drawn map of a seaside village that isn't on any official map |
| Lilycove | A painter | A museum painting shows a village with a bell tower by the sea |
| Mossdeep | An old sailor | Keeps an old Coralmere town sign on the wall, like the one in the ruins |
| Sootopolis | A quiet resident | Asks the player whether the legendaries ever regret the storms |
| Pacifidlog | A family | Rebuilt their lives on the water; their home has a small bell by the door |

- **[DECIDED]** The **Pacifidlog family** speaks Kai's name in the ending. They rebuilt their lives on the water, the clearest sign that Coralmere's people carried on.
- **[DECIDED]** They are the family of Kai's **childhood best friend**. They kept his memory alive by telling stories about him, so they know his name when he has lost it.
- **[DECIDED]** The best friend survived the storm and lived a full life, but passed away years later. They live on through the family's stories.
- **[DECIDED]** The children of the family, who grew up hearing stories about Kai, are the ones who speak his name. The ending is bittersweet and centers acceptance: Kai cannot get the past back, but the people and memories he cared about continued.
- **[DECIDED] Why they never found him:** the family searched for Kai after the storm but could not find him.
- **[DECIDED] Why they held back:** once they learned the Archivist was Kai, they were worried he was acting for the wrong reasons and were afraid of what he had become, so they did not approach him.
- **[DECIDED] Redemption:** Kai performs a heroic act, and only then does the family feel safe approaching him. The name reveal follows.
- **[PROPOSED] Why the search failed:** Kai stopped using his name and lived only as "the Archivist," so nobody searching for "Kai" could find him.
- **[PROPOSED] How they learned who he was:** the scattered survivors recognized him over time (for example, the Lilycove painter spots his likeness in their painting, and word travels through the survivor group to Pacifidlog).
- **[DECIDED 2026-09-17] The heroic act (V5):** Eternatus's power spins out of control and sends a storm toward Pacifidlog, echoing the storm that took Coralmere. Kai shuts down the time rift to stop it, giving up his only chance to save Coralmere, without knowing his friend's family lives there. The family witnesses this, and it is what lets them approach him.
- Writing rule: handle the friend's death gently and without melodrama; the focus is on a life well lived and on connection, not tragedy.
- **[OPEN]** The family's other members (for example, the friend's partner or adult children).

**Writing rules**
- Grief and loss are handled with care and without melodrama.
- Plain language; no ableist or stigmatizing wording.
- Use constant prefix `EPOCH_` in code.

### 7.3 Gym leader and rival rematches **[DECIDED]**
- Each leader and rival has multiple rematch **versions**, each stronger and with different Pokémon.
- **[PROPOSED]** Three postgame versions per gym leader (V1 after Champion, V2 after Thread 1 midpoint, V3 after both threads).
- Each version counts as its own one-time battle for rankings (Section 8).

### 7.4 Champion defense **[DECIDED concept]**
- Challengers come to the Ever Grande League and battle the player.
- Challenges also appear from trainers throughout the game (Section 8.5).
- **[OPEN]** Frequency and challenger roster.

---

## 8. National rankings **[DECIDED]**

### 8.1 Goal
Become **Pokémon Master** by holding the top score in the national rankings.

### 8.2 Which battles count
- Trainer battles only. **[PROPOSED]** Wild battles and Battle Frontier battles do not count.
- **Regular trainers** (not part of the main story arc): points only on the **first** battle.
- **Gym leaders and rivals:** each rematch **version** earns points once.
- Before any battle that will not earn points, show:
  > "You've already earned ranking points from this trainer. This battle won't change your ranking."
- **[PROPOSED]** Losses always count, even against a trainer already beaten.

### 8.3 Scoring per battle

| Event | Points |
|---|---|
| Win | +2 |
| Loss | −1 |
| Each party Pokémon that **battled** and did not faint | +1 |
| Each party Pokémon that fainted | −1 |
| No Pokémon fainted (win only) | +3 |
| Quick win (win only) | +3 |

- "Battled" means the Pokémon **used at least one move** during the battle. **[PROPOSED]** Switching in without acting does not count.
- In double battles, every Pokémon that used a move counts.
- Best possible win: 14 points. Worst possible loss: −7.
- **[DECIDED]** The player's total never goes below zero. Losses at zero leave the score at zero.

### 8.4 Quick-win timer
- Base window: **60 seconds**.
- **+60 seconds** for each **pace-slowing** accessibility feature turned on:
  - Text speed set to Slow
  - "Wait for button" text
  - Hold-to-confirm inputs
  - Sound subtitles
- **+0 to +5 minutes** from the manual "Extra time" setting (Section 11.5).
- Timer runs from battle start to the final message. Measure in frames (GBA runs at about 60 frames per second).
- Features that do not slow pace (high contrast, type labels, and so on) add no time.

### 8.5 Ranked NPCs
- A leaderboard of NPCs, including the Elite Four, Champion Wallace, rivals, gym leaders, and original ranked trainers.
- NPC scores are scripted and increase at story milestones (badges, League, postgame steps) so the leaderboard feels alive.
- **[PROPOSED]** 20 ranked NPCs; the player starts at the bottom; Wallace starts at the top.
- Ranked trainers issue challenges across Hoenn via overworld events.
- Viewing: a "Rankings" option in the start menu showing rank, name, and score as text.

### 8.6 Data
- Player score: signed 16- or 32-bit value in save data.
- Regular trainers: reuse vanilla trainer-defeated flags to know if points were already earned.
- Rematch versions: one bit per leader/rival version.
- NPC scores: computed from story flags at display time where possible, to save space.

---

## 9. Battles and progression

### 9.1 Level caps **[DECIDED: soft caps]**
- Cap is tied to the next gym. Past the cap, experience gain is sharply reduced.
- **[PROPOSED]** Cap values = ace level of the next leader (vanilla: 15, 19, 24, 29, 31, 33, 42, 46, then 58 for the League). Recalculate after trainer rebalancing.
- Assist mode can raise or remove the cap.

### 9.2 Training tools **[DECIDED]**
- EV/IV display (summary screen or checker NPC)
- Nature Mints, Ability Capsule, Ability Patch
- Breeding: Everstone passes nature; Destiny Knot passes 5 IVs; egg-move tutor near the Day Care
- Gen 6+ EV cap

### 9.3 Other features **[DECIDED]**
- Random-trade NPC ("Wonder Trade" style); never gives story-only species
- Trainer card stamps and achievements, linked to rankings

---

## 10. Difficulty and challenge **[DECIDED]**

Chosen at the setup screen; difficulty can be changed later **[PROPOSED]** at any Pokémon Center.

| Mode | Summary |
|---|---|
| Easy | Lower trainer levels, simpler AI |
| Normal | Balanced baseline |
| Hard | Higher levels, full movesets, smarter AI |

**Assist mode** (separate toggle, combinable with any difficulty):
- No money lost after a loss
- Full party heal after a loss
- Level cap raised or removed (player's choice)

**Nuzlocke mode** (optional):
- First encounter per area only
- Fainted Pokémon cannot be used again
- **[PROPOSED]** Duplicates clause and shiny clause on by default

**Randomizer** (optional, seeded):
- Can randomize wild Pokémon, starters, trainer teams, and items, each toggled separately
- Story-only species always excluded

---

## 11. Accessibility **[DECIDED]**

Accessibility is a core feature, not an add-on. All options live in a dedicated Accessibility menu (separate from vanilla Options) reachable from the start menu and the setup screen.

### 11.1 Vision
- **Type labels:** types shown as text (and icons), never by color alone
- **High-contrast theme:** text boxes and menus
- **Effectiveness indicator:** on move selection, text such as "Super effective," "Not very effective," "No effect"
- **Numeric HP:** show HP as numbers for both sides
- **Patterned HP bars:** fill pattern changes at each threshold, not only color

### 11.2 Hearing
- **Visual sound cues:** a short on-screen icon/label when an ambient cry plays (with direction) and when a hidden item chimes
- **Sound subtitles:** text for important cries and sound effects in story scenes

### 11.3 Motor
- **Hold or toggle:** run and repeated actions can be toggles
- **Auto-run**
- **Fewer presses:** skip non-essential confirmations
- **Hold-to-confirm:** optional, to prevent accidental selections
- **No timed inputs anywhere** in the game (design rule)

### 11.4 Cognitive and reading
- **Quest journal:** lists every open storyline (main, legendary arcs, villain arc) with the next step in plain language
- **"Last time" recap:** short summary on loading a save
- **Hint guide:** an in-game character or menu that gives plain-language hints for the current goal
- **Replayable tutorials:** breeding, Mega Evolution, Z-Moves, Dynamax, Terastallization, overworld encounters, rankings
- **Text speed:** Slow, Normal, Fast, Instant, plus "wait for button"

### 11.5 Sensory and pacing
- **Reduced flashing** (move animations and screen flashes)
- **Reduced screen shake**
- **Battle speed** control
- **Skip animations** option
- **Extra time:** +0 to +5 minutes for the ranking quick-win window
- **Assist mode** (Section 10)

### 11.6 Presets
Chosen at the setup screen; every option stays adjustable afterward.

| Preset | Turns on |
|---|---|
| Low Vision | High contrast, type labels, numeric HP, patterned HP bars, effectiveness indicator |
| Reduced Motion | Reduced flashing, reduced shake, skip animations |
| Reading Support | Slow text, wait-for-button, quest journal hints, recap, hint guide |
| One-Handed | Auto-run, toggle instead of hold, fewer presses |

### 11.7 In-world guide
A Littleroot Town character introduces the Accessibility menu and can change settings through dialogue.

### 11.8 Player guide (outside the game)
- Patching instructions
- Emulator setup on iOS, Android, Mac, and PC, including controller support and remapping
- Documentation of emulator-level tools, such as RetroArch's AI Service text-to-speech (imperfect OCR-based reading)

### 11.9 Language
- English only for the first release. **[LATER]** Spanish translation.
- All new text should be written in plain language and stored so it can be translated later (no text baked into images).

---

## 12. Technical constraints

- **Save space:** plan early. Rankings, rematch version bits, accessibility settings, quest journal state, and arc flags all need room. Prefer flags and vars over new save structures; audit free flags/vars first.
- **ROM space:** time-of-day encounter tables and new maps increase size; monitor with each build.
- **Obedience:** custom badge-based check for story-only species (6.5); must not interfere with vanilla traded-Pokémon obedience.
- **Performance:** overworld encounters plus followers can be heavy on lower-end phones; test on mobile emulators.
- **Real-time clock:** day/night depends on emulator RTC support; verify on each platform.
- **Single source of truth:** story-only filtering (6.2), pace-slowing feature list (8.4), and rematch version data must each live in one place.

---

## 13. Later

- **[LATER]** Street Fighter-style fighting mode
- **[LATER]** Spanish translation
- **[LATER]** Second region

---

## 14. Open decisions (summary)

1. Champion defense frequency and roster
2. Mythical event levels (6.4)
3. The Archivist's appearance; Team Epoch admins and grunts (7.2)
4. The Pacifidlog family's other members (7.2)
5. Eeveelution trainer locations (4.3)
6. Kai's redemption details: why the search failed, how the family learned, the heroic act (7.2)
7. All other **[PROPOSED]** items
