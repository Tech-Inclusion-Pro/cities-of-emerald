#ifndef GUARD_CITIES_QUESTS_H
#define GUARD_CITIES_QUESTS_H

#include "global.h"

// Cities of Emerald quest journal, recap, and hints (GDD 11.4, Phase 9).
void CitiesOnContinueGame(void);

// Script specials
bool8 Script_CitiesBufferNextJournalEntry(void);
void Script_CitiesBufferMainQuestStep(void);

#endif // GUARD_CITIES_QUESTS_H
