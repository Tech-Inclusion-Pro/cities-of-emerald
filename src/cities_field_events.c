#include "global.h"
#include "cities_field_events.h"
#include "script.h"

static const u8 *sQueuedFieldScript = NULL;

void CitiesQueueFieldScript(const u8 *script)
{
    sQueuedFieldScript = script;
}

// Called from ProcessPlayerFieldInput, in the same slot where sight
// trainers start their scripts — so this can never interrupt another
// script or a locked field.
bool8 CitiesTryStartQueuedFieldScript(void)
{
    const u8 *script = sQueuedFieldScript;

    if (script == NULL)
        return FALSE;
    sQueuedFieldScript = NULL;
    ScriptContext_SetupScript(script);
    return TRUE;
}
