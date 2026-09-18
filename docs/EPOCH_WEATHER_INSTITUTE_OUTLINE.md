# Task 12.2 — Weather Institute Changes (outline, for approval)

**Status: APPROVED 2026-09-18 (outline + the name Halley + trainer
table growth 864→928).** Builds from the approved Task 12.1 spine
(docs/EPOCH_STORY_OUTLINE.md) and GDD 7.2. No trainer battles in
this task. "Kai" appears nowhere (Task 12.8 rule).

## Goal

Plant the Archivist's history at the Weather Institute (Route 119)
so that V2's letter and V3's in-person meeting land with weight, and
leave a one-line hook for Shaymin's Phase 13 event. Everything here
is quiet, pre-thread flavor in the survivor-hint style: it reads as
ordinary color before the V arcs, and differently after.

## New content

### 1. Forecaster Halley (new NPC, 2F)

A senior forecaster (she/her) who was the Archivist's colleague
before Coralmere sank. Named for the comet — the thing that always
returns. Vanilla WOMAN_5-style sprite; stands near the 2F research
consoles. Present from the first visit (she is staff, not gated on
the Aqua event).

Dialogue stages:
- **Before the League:** ordinary flavor. The Institute's proudest
  and worst season was "the year of the great storms." A colleague
  from those days "took the failure personally" and left. No names,
  no village.
- **Postgame (FLAG_SYS_GAME_CLEAR):** the full history, told
  plainly: the brilliant researcher who tracked the storm cells the
  year Kyogre woke; the warning that went out hours too late for
  one small coastal village; how he packed one instrument — an old
  harbor barometer — and never came back. "He stopped using his
  name around then. I won't guess at what he goes by now."
  Sets FLAG_CITIES_EPOCH_WI_HISTORY (so V arcs and the journal can
  react to whether the player has heard it).
- **V-arc reactive lines:** hooks only — written in 12.5/12.6, not
  here. (After V3 she recognizes the description; after the ending
  she uses his name.)

### 2. Archive clues (1F, three readable objects)

Bg-events in the survivor-hint style:
- **Storm logbook:** the Kyogre-era storm logs, complete except one
  page — the entry for a single night is torn out.
- **Staff photo:** a framed photo from the storm year; one
  researcher stands half-turned from the camera, a small instrument
  in his hand.
- **Empty wall mount:** a bracket by the stairs; the paint around
  it is darker, "the shape of something that hung there for years."

### 3. Shaymin hook (one line)

Halley's pre-League dialogue ends with: the meadow south of the
Institute "bloomed like a thank-you" the spring after the storms —
she thinks the flowers remember kindness. Phase 13's Shaymin event
(GDD 6.6: Route 119, story hook through the Institute) attaches to
her; nothing mechanical is built now.

## Implementation

- `data/maps/Route119_WeatherInstitute_2F/`: Halley object (appended
  LAST in map.json — no local-ID shift), her staged script.
- `data/maps/Route119_WeatherInstitute_1F/`: three bg-events + texts.
- `include/constants/flags.h`: FLAG_CITIES_EPOCH_WI_HISTORY at the
  next free Cities flag.
- No new maps, no save-size change, no trainer IDs.

## Decisions needed from Rocco

1. Approve this outline (NPC, clues, staging, Shaymin hook).
2. Approve the name **Forecaster Halley** (or supply another).
3. Trainer IDs for the V arcs (separate finding, presented with
   this outline): approve growing the trainer table for `EPOCH_`
   trainers per the investigation, so 12.5 isn't blocked.
