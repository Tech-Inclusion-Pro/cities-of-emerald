#include "global.h"
#include "gpu_regs.h"
#include "main.h"
#include "palette.h"
#include "task.h"
#include "title_screen.h"
#include "constants/rgb.h"
#include "cities_title_splash.h"

// Cities of Emerald title splash (GDD 2): shown between the intro and the
// vanilla title screen. The source art is an 800-frame looping GIF; it is
// played back pixel-exactly as a tile-delta video. VRAM keeps one fixed
// 8bpp tile slot per screen position (30x20), the tilemap never changes
// after init, and every tick the changed positions get their new pixels
// copied in from a tile atlas in ROM. Assets are generated from
// graphics/cities_title/source.gif by tools/cities/gen_title_splash.py.

#define SPLASH_POSITIONS   600
#define SPLASH_TICKS       800
#define SPLASH_TICK_FRAMES 5              // 5 vblanks ~ the GIF's 80 ms
#define SPLASH_TIMEOUT     (10 * 60)      // auto-advance after ~10 seconds

static const u16 sSplashPalette[] = INCBIN_U16("graphics/cities_title/palette.bin");
static const u16 sSplashFrame0Map[] = INCBIN_U16("graphics/cities_title/frame0map.bin");
static const u8 sSplashAtlas[] = INCBIN_U8("graphics/cities_title/atlas.bin");
// Stream: per tick a u16 count, then count * (u16 position, u16 atlas tile).
// Tick f holds the changes from frame f-1 to f; tick 0 is the loop's wrap.
static const u16 sSplashStream[] = INCBIN_U16("graphics/cities_title/stream.bin");

static EWRAM_DATA u32 sStreamPos = 0;
static EWRAM_DATA u32 sTick = 0;

static void Task_CitiesSplash(u8 taskId);

#define tFrameTimer data[0]
#define tTimeout    data[1]
#define tFadingOut  data[2]

static void VBlankCB_CitiesSplash(void)
{
    TransferPlttBuffer();
}

static void CB2_CitiesSplash(void)
{
    RunTasks();
    UpdatePaletteFade();
}

static void DrawTileToSlot(u32 pos, u32 tileId)
{
    CpuCopy16(&sSplashAtlas[tileId * 64], (void *)(BG_CHAR_ADDR(0) + pos * 64), 64);
}

// Applies the next tick's changed tiles; sStreamPos wraps past the end.
static void ApplyNextDelta(void)
{
    u32 count, i;

    sTick++;
    if (sTick == SPLASH_TICKS)
    {
        sTick = 0;
        sStreamPos = 0;
    }
    count = sSplashStream[sStreamPos++];
    for (i = 0; i < count; i++)
    {
        u32 pos = sSplashStream[sStreamPos++];
        u32 tileId = sSplashStream[sStreamPos++];
        DrawTileToSlot(pos, tileId);
    }
}

void CB2_InitCitiesTitleSplash(void)
{
    u32 i;

    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        SetGpuReg(REG_OFFSET_BG0CNT, 0);
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        DmaFill16(3, 0, (void *)VRAM, VRAM_SIZE);
        DmaFill32(3, 0, (void *)OAM, OAM_SIZE);
        DmaFill16(3, 0, (void *)PLTT, PLTT_SIZE);
        ResetPaletteFade();
        ResetTasks();
        gMain.state = 1;
        break;
    case 1:
        // Sequential tilemap: position (x, y) always shows tile y*30+x.
        for (i = 0; i < SPLASH_POSITIONS; i++)
        {
            u16 entry = i;
            CpuCopy16(&entry, (void *)(BG_SCREEN_ADDR(20) + ((i / 30) * 32 + (i % 30)) * 2), 2);
        }
        for (i = 0; i < SPLASH_POSITIONS; i++)
            DrawTileToSlot(i, sSplashFrame0Map[i]);
        sTick = 0;
        sStreamPos = 0;
        gMain.state = 2;
        break;
    case 2:
        LoadPalette(sSplashPalette, BG_PLTT_ID(0), sizeof(sSplashPalette));
        SetGpuReg(REG_OFFSET_BG0CNT, BGCNT_PRIORITY(0) | BGCNT_CHARBASE(0)
                                   | BGCNT_SCREENBASE(20) | BGCNT_256COLOR);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_BG0_ON);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB_CitiesSplash);
        CreateTask(Task_CitiesSplash, 0);
        SetMainCallback2(CB2_CitiesSplash);
        break;
    }
}

static void Task_CitiesSplash(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (++tFrameTimer >= SPLASH_TICK_FRAMES)
    {
        tFrameTimer = 0;
        ApplyNextDelta();
    }

    if (tFadingOut)
    {
        if (!gPaletteFade.active)
        {
            DestroyTask(taskId);
            SetMainCallback2(CB2_InitTitleScreen);
        }
        return;
    }

    tTimeout++;
    if (tTimeout >= SPLASH_TIMEOUT
     || (JOY_NEW(A_BUTTON | B_BUTTON | START_BUTTON) && !gPaletteFade.active))
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        tFadingOut = TRUE;
    }
}
