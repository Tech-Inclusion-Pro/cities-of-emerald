#ifndef GUARD_CITIES_FIELD_EVENTS_H
#define GUARD_CITIES_FIELD_EVENTS_H

#include "global.h"

// One-slot queue for a field script that should run the next time the
// player has full overworld control (used by the Pokémon Master event and
// the "last time" recap). Queued from C, drained by ProcessPlayerFieldInput.
void CitiesQueueFieldScript(const u8 *script);
bool8 CitiesTryStartQueuedFieldScript(void);

#endif // GUARD_CITIES_FIELD_EVENTS_H
