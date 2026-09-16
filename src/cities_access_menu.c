#include "global.h"
#include "cities_accessibility.h"
#include "bg.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/flags.h"
#include "constants/songs.h"
#include "constants/rgb.h"

// Task 6.2 (GDD 11): the Accessibility menu. Separate from vanilla Options,
// reachable from the start menu, multiple pages, all text-based. Changes
// apply immediately (no separate save step to forget).

enum
{
    WIN_HEADER,
    WIN_OPTIONS,
};

#define MAX_ROWS_PER_PAGE 6 // + Back row

struct CitiesAccessMenuItem
{
    const u8 *name;
    u8 valueCount;
    const u8 *const *valueNames;
    u8 (*get)(void);
    void (*set)(u8 value);
};

static void MainCB2(void);
static void VBlankCB(void);
static void Task_AccessMenuFadeIn(u8 taskId);
static void Task_AccessMenuProcessInput(u8 taskId);
static void Task_AccessMenuFadeOut(u8 taskId);
static void DrawPage(u8 page, u8 row);

static const u8 sText_Off[] = _("Off");
static const u8 sText_On[] = _("On");
static const u8 *const sValues_OffOn[] = {sText_Off, sText_On};

static const u8 sText_SpeedNormal[] = _("Normal");
static const u8 sText_SpeedFast[] = _("Fast");
static const u8 sText_SpeedFastest[] = _("Fastest");
static const u8 *const sValues_BattleSpeed[] = {sText_SpeedNormal, sText_SpeedFast, sText_SpeedFastest};

static const u8 sText_Time0[] = _("0 min");
static const u8 sText_Time1[] = _("1 min");
static const u8 sText_Time2[] = _("2 min");
static const u8 sText_Time3[] = _("3 min");
static const u8 sText_Time4[] = _("4 min");
static const u8 sText_Time5[] = _("5 min");
static const u8 *const sValues_ExtraTime[] = {sText_Time0, sText_Time1, sText_Time2, sText_Time3, sText_Time4, sText_Time5};

#define ACCESS_BIT(field)                                    \
    static u8 Get_##field(void)                              \
    { return gSaveBlock3Ptr->citiesAccess.field; }           \
    static void Set_##field(u8 value)                        \
    { gSaveBlock3Ptr->citiesAccess.field = value; }

ACCESS_BIT(typeLabels)
ACCESS_BIT(highContrast)
ACCESS_BIT(effectivenessIndicator)
ACCESS_BIT(numericHp)
ACCESS_BIT(patternedHpBars)
ACCESS_BIT(visualSoundCues)
ACCESS_BIT(soundSubtitles)
ACCESS_BIT(autoRun)
ACCESS_BIT(toggleRun)
ACCESS_BIT(fewerPresses)
ACCESS_BIT(holdToConfirm)
ACCESS_BIT(waitForButton)
ACCESS_BIT(reducedFlashing)
ACCESS_BIT(reducedShake)
ACCESS_BIT(battleSpeed)
ACCESS_BIT(extraTimeMinutes)

static u8 Get_instantText(void) { return FlagGet(FLAG_CITIES_ACCESS_INSTANT_TEXT); }
static void Set_instantText(u8 value) { if (value) FlagSet(FLAG_CITIES_ACCESS_INSTANT_TEXT); else FlagClear(FLAG_CITIES_ACCESS_INSTANT_TEXT); }

static u8 Get_skipAnims(void) { return gSaveBlock2Ptr->optionsBattleSceneOff; }
static void Set_skipAnims(u8 value) { gSaveBlock2Ptr->optionsBattleSceneOff = value; }

// Rows appear only once their effect is wired; stored bits for the rest
// are reserved (numeric HP, patterned bars return in Task 6.3 follow-up).
static const struct CitiesAccessMenuItem sPage_Vision[] =
{
    {COMPOUND_STRING("High contrast"),      2, sValues_OffOn, Get_highContrast, Set_highContrast},
    {COMPOUND_STRING("Effect indicator"),   2, sValues_OffOn, Get_effectivenessIndicator, Set_effectivenessIndicator},
};

static const struct CitiesAccessMenuItem sPage_Motor[] =
{
    {COMPOUND_STRING("Auto-run"),           2, sValues_OffOn, Get_autoRun, Set_autoRun},
    {COMPOUND_STRING("Toggle run"),         2, sValues_OffOn, Get_toggleRun, Set_toggleRun},
    {COMPOUND_STRING("Fewer presses"),      2, sValues_OffOn, Get_fewerPresses, Set_fewerPresses},
};

static const struct CitiesAccessMenuItem sPage_Sensory[] =
{
    {COMPOUND_STRING("Reduced flashing"),   2, sValues_OffOn, Get_reducedFlashing, Set_reducedFlashing},
    {COMPOUND_STRING("Reduced shake"),      2, sValues_OffOn, Get_reducedShake, Set_reducedShake},
    {COMPOUND_STRING("Battle speed"),       3, sValues_BattleSpeed, Get_battleSpeed, Set_battleSpeed},
    {COMPOUND_STRING("Skip animations"),    2, sValues_OffOn, Get_skipAnims, Set_skipAnims},
};

static const struct CitiesAccessMenuItem sPage_TextSound[] =
{
    {COMPOUND_STRING("Instant text"),       2, sValues_OffOn, Get_instantText, Set_instantText},
    {COMPOUND_STRING("Wait for button"),    2, sValues_OffOn, Get_waitForButton, Set_waitForButton},
    {COMPOUND_STRING("Extra time"),         6, sValues_ExtraTime, Get_extraTimeMinutes, Set_extraTimeMinutes},
};

struct CitiesAccessMenuPage
{
    const u8 *title;
    const struct CitiesAccessMenuItem *items;
    u8 count;
};

static const struct CitiesAccessMenuPage sPages[] =
{
    {COMPOUND_STRING("ACCESSIBILITY: Vision (1/4)"),        sPage_Vision,    ARRAY_COUNT(sPage_Vision)},
    {COMPOUND_STRING("ACCESSIBILITY: Movement (2/4)"),      sPage_Motor,     ARRAY_COUNT(sPage_Motor)},
    {COMPOUND_STRING("ACCESSIBILITY: Comfort (3/4)"),       sPage_Sensory,   ARRAY_COUNT(sPage_Sensory)},
    {COMPOUND_STRING("ACCESSIBILITY: Text/Sound (4/4)"),    sPage_TextSound, ARRAY_COUNT(sPage_TextSound)},
};

static const u8 sText_Back[] = _("Back");

static const struct WindowTemplate sWinTemplates[] =
{
    [WIN_HEADER] = {
        .bg = 1, .tilemapLeft = 2, .tilemapTop = 1, .width = 26, .height = 2,
        .paletteNum = 1, .baseBlock = 2
    },
    [WIN_OPTIONS] = {
        .bg = 0, .tilemapLeft = 2, .tilemapTop = 5, .width = 26, .height = 14,
        .paletteNum = 1, .baseBlock = 0x36
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sBgTemplates[] =
{
    { .bg = 1, .charBaseIndex = 1, .mapBaseIndex = 30, .priority = 0 },
    { .bg = 0, .charBaseIndex = 1, .mapBaseIndex = 31, .priority = 1 },
};

static const u16 sBg_Pal[] = {RGB(17, 18, 31)};
static const u16 sText_Pal[] = INCGFX_U16("graphics/interface/option_menu_text.pal", ".gbapal");

#define tPage data[0]
#define tRow  data[1]

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_InitCitiesAccessMenu(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
        ChangeBgX(0, 0, BG_COORD_SET);
        ChangeBgY(0, 0, BG_COORD_SET);
        ChangeBgX(1, 0, BG_COORD_SET);
        ChangeBgY(1, 0, BG_COORD_SET);
        InitWindows(sWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        LoadPalette(sBg_Pal, BG_PLTT_ID(0), sizeof(sBg_Pal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        LoadPalette(sText_Pal, BG_PLTT_ID(1), sizeof(sText_Pal));
        gMain.state++;
        break;
    case 4:
    {
        u8 taskId = CreateTask(Task_AccessMenuFadeIn, 0);
        gTasks[taskId].tPage = 0;
        gTasks[taskId].tRow = 0;
        PutWindowTilemap(WIN_HEADER);
        PutWindowTilemap(WIN_OPTIONS);
        DrawPage(0, 0);
        gMain.state++;
        break;
    }
    case 5:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void DrawPage(u8 page, u8 row)
{
    u8 i;
    const struct CitiesAccessMenuPage *p = &sPages[page];

    FillWindowPixelBuffer(WIN_HEADER, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, p->title, 8, 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_HEADER, COPYWIN_FULL);

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < p->count; i++)
    {
        const struct CitiesAccessMenuItem *item = &p->items[i];
        u8 y = i * 16 + 1;
        AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, item->name, 8, y, TEXT_SKIP_DRAW, NULL);
        AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, item->valueNames[item->get()], 140, y, TEXT_SKIP_DRAW, NULL);
    }
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, sText_Back, 8, p->count * 16 + 1, TEXT_SKIP_DRAW, NULL);
    // Cursor arrow on the selected row.
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, gText_SelectorArrow2, 0, row * 16 + 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

static void Task_AccessMenuFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_AccessMenuProcessInput;
}

static void Task_AccessMenuProcessInput(u8 taskId)
{
    u8 page = gTasks[taskId].tPage;
    u8 row = gTasks[taskId].tRow;
    const struct CitiesAccessMenuPage *p = &sPages[page];
    u8 backRow = p->count; // Back sits after the items

    if (JOY_NEW(B_BUTTON) || (JOY_NEW(A_BUTTON) && row == backRow))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_AccessMenuFadeOut;
    }
    else if (JOY_NEW(L_BUTTON))
    {
        PlaySE(SE_SELECT);
        gTasks[taskId].tPage = (page + ARRAY_COUNT(sPages) - 1) % ARRAY_COUNT(sPages);
        gTasks[taskId].tRow = 0;
        DrawPage(gTasks[taskId].tPage, 0);
    }
    else if (JOY_NEW(R_BUTTON))
    {
        PlaySE(SE_SELECT);
        gTasks[taskId].tPage = (page + 1) % ARRAY_COUNT(sPages);
        gTasks[taskId].tRow = 0;
        DrawPage(gTasks[taskId].tPage, 0);
    }
    else if (JOY_NEW(DPAD_UP))
    {
        gTasks[taskId].tRow = (row == 0) ? backRow : row - 1;
        DrawPage(page, gTasks[taskId].tRow);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        gTasks[taskId].tRow = (row == backRow) ? 0 : row + 1;
        DrawPage(page, gTasks[taskId].tRow);
    }
    else if (row < backRow && (JOY_NEW(DPAD_LEFT) || JOY_NEW(DPAD_RIGHT) || JOY_NEW(A_BUTTON)))
    {
        const struct CitiesAccessMenuItem *item = &p->items[row];
        u8 value = item->get();

        if (JOY_NEW(DPAD_LEFT))
            value = (value == 0) ? item->valueCount - 1 : value - 1;
        else
            value = (value + 1) % item->valueCount;
        item->set(value);
        PlaySE(SE_SELECT);
        DrawPage(page, row);
    }
}

static void Task_AccessMenuFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}
