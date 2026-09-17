#include "global.h"
#include "cities_rankings.h"
#include "bg.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/songs.h"
#include "constants/rgb.h"

// Task 7.6 (GDD 8.5): the Rankings screen. Text-only scrolling list of
// rank, name, and score; the player's row is marked. UP/DOWN scrolls,
// B exits.

#define ROWS_PER_PAGE 6
#define TOTAL_ENTRIES (CitiesRanking_GetNpcCount() + 1)

enum
{
    WIN_HEADER,
    WIN_LIST,
};

struct RankEntry
{
    const u8 *name; // NULL = the player
    s32 score;
};

static EWRAM_DATA struct RankEntry sEntries[24];
static EWRAM_DATA u8 sEntryCount = 0;

static const u8 sText_You[] = _("You");
static const u8 sText_YouMaster[] = _("You - MASTER"); // GDD 8.1 title (Task 7.7)

static const struct WindowTemplate sWinTemplates[] =
{
    [WIN_HEADER] = {
        .bg = 1, .tilemapLeft = 2, .tilemapTop = 1, .width = 26, .height = 2,
        .paletteNum = 1, .baseBlock = 2
    },
    [WIN_LIST] = {
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

#define tScroll data[0]

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

static void BuildEntries(void)
{
    u32 i, j;
    s32 playerScore = CitiesRanking_GetScore();
    bool32 playerPlaced = FALSE;

    sEntryCount = 0;
    // NPC scores are already in descending roster order by design, but
    // sort defensively so milestone bumps can never disorder the board.
    for (i = 0; i < CitiesRanking_GetNpcCount(); i++)
    {
        struct RankEntry e = { CitiesRanking_GetNpcName(i), CitiesRanking_GetNpcScore(i) };
        for (j = sEntryCount; j > 0 && sEntries[j - 1].score < e.score; j--)
            sEntries[j] = sEntries[j - 1];
        sEntries[j] = e;
        sEntryCount++;
    }
    // Insert the player below any NPC with an equal score (ties go to NPCs).
    for (j = sEntryCount; j > 0 && sEntries[j - 1].score < playerScore; j--)
        sEntries[j] = sEntries[j - 1];
    sEntries[j] = (struct RankEntry){ NULL, playerScore };
    sEntryCount++;
    (void)playerPlaced;
}

static void DrawList(u32 scroll)
{
    u32 i;
    u8 buf[16];

    FillWindowPixelBuffer(WIN_HEADER, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL,
        COMPOUND_STRING("NATIONAL RANKINGS"), 8, 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_HEADER, COPYWIN_FULL);

    FillWindowPixelBuffer(WIN_LIST, PIXEL_FILL(1));
    for (i = 0; i < ROWS_PER_PAGE && scroll + i < sEntryCount; i++)
    {
        u32 idx = scroll + i;
        u8 y = i * 16 + 1;
        const struct RankEntry *e = &sEntries[idx];

        ConvertIntToDecimalStringN(buf, idx + 1, STR_CONV_MODE_RIGHT_ALIGN, 2);
        AddTextPrinterParameterized(WIN_LIST, FONT_NORMAL, buf, 4, y, TEXT_SKIP_DRAW, NULL);
        AddTextPrinterParameterized(WIN_LIST, FONT_NORMAL,
            e->name != NULL ? e->name
                : FlagGet(FLAG_CITIES_POKEMON_MASTER) ? sText_YouMaster : sText_You,
            28, y, TEXT_SKIP_DRAW, NULL);
        ConvertIntToDecimalStringN(buf, e->score, STR_CONV_MODE_RIGHT_ALIGN, 6);
        AddTextPrinterParameterized(WIN_LIST, FONT_NORMAL, buf, 150, y, TEXT_SKIP_DRAW, NULL);
        if (e->name == NULL)
            AddTextPrinterParameterized(WIN_LIST, FONT_NORMAL, gText_SelectorArrow2, 0, y, TEXT_SKIP_DRAW, NULL);
    }
    CopyWindowToVram(WIN_LIST, COPYWIN_FULL);
}

static void Task_RankingsFadeIn(u8 taskId);
static void Task_RankingsInput(u8 taskId);
static void Task_RankingsFadeOut(u8 taskId);

void CB2_InitCitiesRankingsScreen(void)
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
        u8 taskId = CreateTask(Task_RankingsFadeIn, 0);
        u32 rank = CitiesRanking_GetPlayerRank();

        BuildEntries();
        // Open scrolled so the player's row is visible.
        gTasks[taskId].tScroll = (rank > ROWS_PER_PAGE) ? rank - ROWS_PER_PAGE : 0;
        PutWindowTilemap(WIN_HEADER);
        PutWindowTilemap(WIN_LIST);
        DrawList(gTasks[taskId].tScroll);
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

static void Task_RankingsFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_RankingsInput;
}

static void Task_RankingsInput(u8 taskId)
{
    s16 *scroll = &gTasks[taskId].tScroll;

    if (JOY_NEW(B_BUTTON) || JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_RankingsFadeOut;
    }
    else if (JOY_REPEAT(DPAD_UP) && *scroll > 0)
    {
        (*scroll)--;
        DrawList(*scroll);
    }
    else if (JOY_REPEAT(DPAD_DOWN) && *scroll + ROWS_PER_PAGE < sEntryCount)
    {
        (*scroll)++;
        DrawList(*scroll);
    }
}

static void Task_RankingsFadeOut(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        SetMainCallback2(gMain.savedCallback);
    }
}
