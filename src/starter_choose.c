#include "global.h"
#include "battle_main.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "list_menu.h"
#include "main.h"
#include "menu.h"
#include "palette.h"
#include "pokedex.h"
#include "pokemon.h"
#include "random.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "starter_choose.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "trainer_pokemon_sprites.h"
#include "trig.h"
#include "window.h"
#include "constants/songs.h"
#include "constants/rgb.h"

// Cities of Emerald (GDD 4.2): the vanilla three-ball screen is replaced by
// a three-step, text-first flow — pick a region, pick a Pokémon (sprite,
// name, and type shown as text), confirm. B always goes back one step.

#define STARTER_MON_COUNT   3

#define TAG_POKEBALL_SELECT 0x1000

static void CB2_StarterChoose(void);
static void Task_OpenRegionList(u8 taskId);
static void Task_HandleRegionListInput(u8 taskId);
static void Task_OpenMonSelect(u8 taskId);
static void Task_HandleMonSelectInput(u8 taskId);
static void Task_AskConfirmStarter(u8 taskId);
static void Task_HandleConfirmStarterInput(u8 taskId);
static void SpriteCB_SelectionHand(struct Sprite *sprite);
static u8 CreatePokemonFrontSprite(enum Species species, u8 x, u8 y, u8 paletteSlot);
static enum Species GetDisplaySpecies(u8 taskId, u8 slot);
static void PrintMonInfoText(u8 taskId);
static void DestroyMonSprites(u8 taskId);

const u16 gBirchBagGrass_Pal[] = INCGFX_U16("graphics/starter_choose/tiles.png", ".gbapal");
static const u16 sPokeballSelection_Pal[] = INCGFX_U16("graphics/starter_choose/pokeball_selection.png", ".gbapal");
const u32 gBirchBagTilemap[] = INCGFX_U32("graphics/starter_choose/birch_bag.bin", ".smolTM");
const u32 gBirchGrassTilemap[] = INCGFX_U32("graphics/starter_choose/birch_grass.bin", ".smolTM");
const u32 gBirchBagGrass_Gfx[] = INCGFX_U32("graphics/starter_choose/tiles.png", ".4bpp.smol");
const u32 gPokeballSelection_Gfx[] = INCGFX_U32("graphics/starter_choose/pokeball_selection.png", ".4bpp.smol");

enum
{
    WIN_MSG,
};

static const struct WindowTemplate sWindowTemplates[] =
{
    [WIN_MSG] =
    {
        .bg = 0,
        .tilemapLeft = 3,
        .tilemapTop = 15,
        .width = 24,
        .height = 4,
        .paletteNum = 14,
        .baseBlock = 0x0200
    },
    DUMMY_WIN_TEMPLATE,
};

static const struct WindowTemplate sWindowTemplate_ConfirmStarter =
{
    .bg = 0,
    .tilemapLeft = 24,
    .tilemapTop = 9,
    .width = 5,
    .height = 4,
    .paletteNum = 14,
    .baseBlock = 0x0260
};

static const struct WindowTemplate sWindowTemplate_RegionList =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = 9,
    .height = 12,
    .paletteNum = 14,
    .baseBlock = 0x02B8
};

// Sprite positions for the three starters (matches the bag's ball spots).
static const u8 sMonCoords[STARTER_MON_COUNT][2] =
{
    {60, 64},
    {120, 88},
    {180, 64},
};

static const u8 sCursorCoords[STARTER_MON_COUNT][2] =
{
    {60, 32},
    {120, 56},
    {180, 32},
};

#define GRASS_STARTER (IS_FRLG ? SPECIES_BULBASAUR  : SPECIES_TREECKO)
#define FIRE_STARTER  (IS_FRLG ? SPECIES_CHARMANDER : SPECIES_TORCHIC)
#define WATER_STARTER (IS_FRLG ? SPECIES_SQUIRTLE   : SPECIES_MUDKIP )

// Vanilla fallback, used only while VAR_CITIES_STARTER_REGION is unset.
static const u16 sStarterMon[STARTER_MON_COUNT] =
{
    GRASS_STARTER,
    FIRE_STARTER,
    WATER_STARTER,
};

#include "data/cities_starters.h"

static const u8 sText_Kanto[] = _("Kanto");
static const u8 sText_Johto[] = _("Johto");
static const u8 sText_Hoenn[] = _("Hoenn");
static const u8 sText_Sinnoh[] = _("Sinnoh");
static const u8 sText_Unova[] = _("Unova");
static const u8 sText_Kalos[] = _("Kalos");
static const u8 sText_Alola[] = _("Alola");
static const u8 sText_Galar[] = _("Galar");
static const u8 sText_Paldea[] = _("Paldea");
static const u8 sText_Special[] = _("Special");

static const u8 sText_ChooseRegion[] = _("Choose a region.\nPress A to select.");
static const u8 sText_MonInfo[] = _("{STR_VAR_1}: {STR_VAR_2} type\nA: choose   B: go back");
static const u8 sText_ConfirmChoice[] = _("You chose {STR_VAR_1}, the {STR_VAR_2}-type\nPokémon. Is that right?");
static const u8 sText_TypeSlash[] = _("/");

static const struct ListMenuItem sRegionListItems[] =
{
    {sText_Kanto,   CITIES_STARTER_REGION_KANTO},
    {sText_Johto,   CITIES_STARTER_REGION_JOHTO},
    {sText_Hoenn,   CITIES_STARTER_REGION_HOENN},
    {sText_Sinnoh,  CITIES_STARTER_REGION_SINNOH},
    {sText_Unova,   CITIES_STARTER_REGION_UNOVA},
    {sText_Kalos,   CITIES_STARTER_REGION_KALOS},
    {sText_Alola,   CITIES_STARTER_REGION_ALOLA},
    {sText_Galar,   CITIES_STARTER_REGION_GALAR},
    {sText_Paldea,  CITIES_STARTER_REGION_PALDEA},
    {sText_Special, CITIES_STARTER_REGION_SPECIAL},
};

static const struct ListMenuTemplate sRegionListMenuTemplate =
{
    .items = sRegionListItems,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = NULL,
    .totalItems = ARRAY_COUNT(sRegionListItems),
    .maxShowed = 5,
    .windowId = 0, // set at runtime
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = FALSE,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = FONT_NORMAL,
    .cursorKind = CURSOR_BLACK_ARROW,
};

static const struct BgTemplate sBgTemplates[3] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 7,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    },
    {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 6,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
};

static const struct OamData sOam_Hand =
{
    .y = DISPLAY_HEIGHT,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sAnim_Hand[] =
{
    ANIMCMD_FRAME(48, 30),
    ANIMCMD_END,
};

static const union AnimCmd *const sAnims_Hand[] =
{
    sAnim_Hand,
};

static const struct CompressedSpriteSheet sSpriteSheet_PokeballSelect[] =
{
    {
        .data = gPokeballSelection_Gfx,
        .size = 0x0800,
        .tag = TAG_POKEBALL_SELECT
    },
    {}
};

static const struct SpritePalette sSpritePalettes_StarterChoose[] =
{
    {
        .data = sPokeballSelection_Pal,
        .tag = TAG_POKEBALL_SELECT
    },
    {},
};

static const struct SpriteTemplate sSpriteTemplate_Hand =
{
    .tileTag = TAG_POKEBALL_SELECT,
    .paletteTag = TAG_POKEBALL_SELECT,
    .oam = &sOam_Hand,
    .anims = sAnims_Hand,
    .callback = SpriteCB_SelectionHand
};

// .text
u16 GetStarterPokemon(u16 chosenStarterId)
{
    u16 region = VarGet(VAR_CITIES_STARTER_REGION);

    if (chosenStarterId >= STARTER_MON_COUNT)
        chosenStarterId = 0;
    if (region == CITIES_STARTER_REGION_SPECIAL)
    {
        // chosenStarterId holds the rival's encoded roll here; the player's
        // actual pick lives in VAR_CITIES_STARTER_SPECIAL.
        u16 specialSlot = VarGet(VAR_CITIES_STARTER_SPECIAL);
        if (specialSlot >= STARTER_MON_COUNT)
            specialSlot = 0;
        return gCitiesSpecialStarters[specialSlot];
    }
    if (region >= CITIES_STARTER_REGION_KANTO && region <= CITIES_STARTER_REGION_PALDEA)
        return gCitiesStarterStages[region - 1][chosenStarterId][0];
    return sStarterMon[chosenStarterId];
}

// Maps a Hoenn starter-line species to the same evolution stage of the
// same-region line, based on the player's chosen region. Used for rival
// teams (GDD 4.2): scripts still pick the vanilla 3-way trainer variant,
// and this swap keeps the type advantage while matching the region.
enum Species CitiesGetRivalStarterSpecies(enum Species species)
{
    u32 line, stage;
    u16 region = VarGet(VAR_CITIES_STARTER_REGION);

    if (region < CITIES_STARTER_REGION_KANTO || region > CITIES_STARTER_REGION_PALDEA
     || region == CITIES_STARTER_REGION_HOENN)
        return species; // Hoenn, Special, or unset: vanilla teams are already right.

    for (line = 0; line < 3; line++)
    {
        for (stage = 0; stage < 3; stage++)
        {
            if (gCitiesStarterStages[CITIES_STARTER_REGION_HOENN - 1][line][stage] == species)
                return gCitiesStarterStages[region - 1][line][stage];
        }
    }
    return species;
}

static void VblankCB_StarterChoose(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

// Task data
#define tState          data[0]  // unused directly; states are task funcs
#define tRegion         data[1]  // CITIES_STARTER_REGION_*
#define tMonSelection   data[2]  // 0..2
#define tListTaskId     data[3]
#define tRegionWindowId data[4]
#define tHandSpriteId   data[5]
#define tMonCount       data[6]
#define tSpriteBase     7        // data[7..9]: mon pic sprite ids

// Sprite data
#define sTaskId data[0]

void CB2_ChooseStarter(void)
{
    u8 taskId;
    u8 spriteId;

    SetVBlankCallback(NULL);

    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG3CNT, 0);
    SetGpuReg(REG_OFFSET_BG2CNT, 0);
    SetGpuReg(REG_OFFSET_BG1CNT, 0);
    SetGpuReg(REG_OFFSET_BG0CNT, 0);

    ChangeBgX(0, 0, BG_COORD_SET);
    ChangeBgY(0, 0, BG_COORD_SET);
    ChangeBgX(1, 0, BG_COORD_SET);
    ChangeBgY(1, 0, BG_COORD_SET);
    ChangeBgX(2, 0, BG_COORD_SET);
    ChangeBgY(2, 0, BG_COORD_SET);
    ChangeBgX(3, 0, BG_COORD_SET);
    ChangeBgY(3, 0, BG_COORD_SET);

    DmaFill16(3, 0, VRAM, VRAM_SIZE);
    DmaFill32(3, 0, OAM, OAM_SIZE);
    DmaFill16(3, 0, PLTT, PLTT_SIZE);

    DecompressDataWithHeaderVram(gBirchBagGrass_Gfx, (void *)VRAM);
    DecompressDataWithHeaderVram(gBirchBagTilemap, (void *)(BG_SCREEN_ADDR(6)));
    DecompressDataWithHeaderVram(gBirchGrassTilemap, (void *)(BG_SCREEN_ADDR(7)));

    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
    InitWindows(sWindowTemplates);

    DeactivateAllTextPrinters();
    LoadUserWindowBorderGfx(0, 0x2A8, BG_PLTT_ID(13));
    ClearScheduledBgCopiesToVram();
    ScanlineEffect_Stop();
    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ResetAllPicSprites();

    LoadPalette(GetOverworldTextboxPalettePtr(), BG_PLTT_ID(14), PLTT_SIZE_4BPP);
    LoadPalette(gBirchBagGrass_Pal, BG_PLTT_ID(0), sizeof(gBirchBagGrass_Pal));
    LoadCompressedSpriteSheet(&sSpriteSheet_PokeballSelect[0]);
    LoadSpritePalettes(sSpritePalettes_StarterChoose);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, RGB_BLACK);

    EnableInterrupts(DISPSTAT_VBLANK);
    SetVBlankCallback(VblankCB_StarterChoose);
    SetMainCallback2(CB2_StarterChoose);

    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);

    ShowBg(0);
    ShowBg(2);
    ShowBg(3);

    taskId = CreateTask(Task_OpenRegionList, 0);
    gTasks[taskId].tRegion = CITIES_STARTER_REGION_KANTO;
    gTasks[taskId].tMonSelection = 0;
    gTasks[taskId].tRegionWindowId = WINDOW_NONE;

    // Selection hand cursor, hidden until the Pokémon step.
    spriteId = CreateSprite(&sSpriteTemplate_Hand, 120, 56, 2);
    gSprites[spriteId].sTaskId = taskId;
    gSprites[spriteId].invisible = TRUE;
    gTasks[taskId].tHandSpriteId = spriteId;
}

static void CB2_StarterChoose(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void Task_OpenRegionList(u8 taskId)
{
    u8 windowId;

    DrawStdFrameWithCustomTileAndPalette(WIN_MSG, FALSE, 0x2A8, 0xD);
    FillWindowPixelBuffer(WIN_MSG, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_MSG, FONT_NORMAL, sText_ChooseRegion, 0, 1, 0, NULL);
    PutWindowTilemap(WIN_MSG);

    windowId = AddWindow(&sWindowTemplate_RegionList);
    gTasks[taskId].tRegionWindowId = windowId;
    DrawStdFrameWithCustomTileAndPalette(windowId, FALSE, 0x2A8, 0xD);

    gMultiuseListMenuTemplate = sRegionListMenuTemplate;
    gMultiuseListMenuTemplate.windowId = windowId;
    gTasks[taskId].tListTaskId = ListMenuInit(&gMultiuseListMenuTemplate, 0, 0);

    ScheduleBgCopyTilemapToVram(0);
    gTasks[taskId].func = Task_HandleRegionListInput;
}

static void Task_HandleRegionListInput(u8 taskId)
{
    s32 input = ListMenu_ProcessInput(gTasks[taskId].tListTaskId);

    switch (input)
    {
    case LIST_NOTHING_CHOSEN:
    case LIST_CANCEL: // Choosing a starter is required; B does nothing here.
        break;
    default:
        PlaySE(SE_SELECT);
        gTasks[taskId].tRegion = input;
        gTasks[taskId].tMonSelection = 0;
        DestroyListMenuTask(gTasks[taskId].tListTaskId, NULL, NULL);
        ClearStdWindowAndFrameToTransparent(gTasks[taskId].tRegionWindowId, FALSE);
        ClearWindowTilemap(gTasks[taskId].tRegionWindowId);
        RemoveWindow(gTasks[taskId].tRegionWindowId);
        gTasks[taskId].tRegionWindowId = WINDOW_NONE;
        ScheduleBgCopyTilemapToVram(0);
        gTasks[taskId].func = Task_OpenMonSelect;
        break;
    }
}

static enum Species GetDisplaySpecies(u8 taskId, u8 slot)
{
    u16 region = gTasks[taskId].tRegion;

    if (region == CITIES_STARTER_REGION_SPECIAL)
        return gCitiesSpecialStarters[slot];
    return gCitiesStarterStages[region - 1][slot][0];
}

static void Task_OpenMonSelect(u8 taskId)
{
    u8 i;

    gTasks[taskId].tMonCount = STARTER_MON_COUNT;

    for (i = 0; i < gTasks[taskId].tMonCount; i++)
    {
        gTasks[taskId].data[tSpriteBase + i] =
            CreatePokemonFrontSprite(GetDisplaySpecies(taskId, i), sMonCoords[i][0], sMonCoords[i][1], 13 + i);
    }

    gSprites[gTasks[taskId].tHandSpriteId].invisible = FALSE;
    PrintMonInfoText(taskId);
    gTasks[taskId].func = Task_HandleMonSelectInput;
}

static void PrintMonInfoText(u8 taskId)
{
    enum Species species = GetDisplaySpecies(taskId, gTasks[taskId].tMonSelection);
    enum Type type1 = GetSpeciesType(species, 0);
    enum Type type2 = GetSpeciesType(species, 1);

    StringCopy(gStringVar1, GetSpeciesName(species));
    StringCopy(gStringVar2, gTypesInfo[type1].name);
    if (type2 != type1)
    {
        StringAppend(gStringVar2, sText_TypeSlash);
        StringAppend(gStringVar2, gTypesInfo[type2].name);
    }
    StringExpandPlaceholders(gStringVar4, sText_MonInfo);

    FillWindowPixelBuffer(WIN_MSG, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_MSG, FONT_NORMAL, gStringVar4, 0, 1, 0, NULL);
    PutWindowTilemap(WIN_MSG);
    ScheduleBgCopyTilemapToVram(0);
}

static void DestroyMonSprites(u8 taskId)
{
    u8 i;

    for (i = 0; i < gTasks[taskId].tMonCount; i++)
        FreeAndDestroyMonPicSprite(gTasks[taskId].data[tSpriteBase + i]);
}

static void Task_HandleMonSelectInput(u8 taskId)
{
    u8 selection = gTasks[taskId].tMonSelection;
    u8 count = gTasks[taskId].tMonCount;

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        gTasks[taskId].func = Task_AskConfirmStarter;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        DestroyMonSprites(taskId);
        gSprites[gTasks[taskId].tHandSpriteId].invisible = TRUE;
        gTasks[taskId].func = Task_OpenRegionList;
    }
    else if (JOY_NEW(DPAD_LEFT) && selection > 0)
    {
        PlaySE(SE_SELECT);
        gTasks[taskId].tMonSelection--;
        PrintMonInfoText(taskId);
    }
    else if (JOY_NEW(DPAD_RIGHT) && selection < count - 1)
    {
        PlaySE(SE_SELECT);
        gTasks[taskId].tMonSelection++;
        PrintMonInfoText(taskId);
    }
}

static void Task_AskConfirmStarter(u8 taskId)
{
    enum Species species = GetDisplaySpecies(taskId, gTasks[taskId].tMonSelection);
    enum Type type1 = GetSpeciesType(species, 0);
    enum Type type2 = GetSpeciesType(species, 1);

    PlayCry_Normal(species, 0);

    StringCopy(gStringVar1, GetSpeciesName(species));
    StringCopy(gStringVar2, gTypesInfo[type1].name);
    if (type2 != type1)
    {
        StringAppend(gStringVar2, sText_TypeSlash);
        StringAppend(gStringVar2, gTypesInfo[type2].name);
    }
    StringExpandPlaceholders(gStringVar4, sText_ConfirmChoice);

    FillWindowPixelBuffer(WIN_MSG, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_MSG, FONT_NORMAL, gStringVar4, 0, 1, 0, NULL);
    ScheduleBgCopyTilemapToVram(0);
    CreateYesNoMenu(&sWindowTemplate_ConfirmStarter, 0x2A8, 0xD, 0);
    gTasks[taskId].func = Task_HandleConfirmStarterInput;
}

static void Task_HandleConfirmStarterInput(u8 taskId)
{
    u16 region = gTasks[taskId].tRegion;

    switch (Menu_ProcessInputNoWrapClearOnChoose())
    {
    case 0:  // YES
        VarSet(VAR_CITIES_STARTER_REGION, region);
        if (region == CITIES_STARTER_REGION_SPECIAL)
        {
            // Special picks (Eevee/Pikachu/Ditto) have no type triangle, so
            // the rival gets a random Hoenn starter (approved 2026-09-16).
            // Scripts derive the rival's pick as (VAR_STARTER_MON + 1) % 3, so
            // encode the rolled pick there and keep the player's actual pick
            // in VAR_CITIES_STARTER_SPECIAL.
            u16 rivalSlot = Random() % 3;
            VarSet(VAR_CITIES_STARTER_SPECIAL, gTasks[taskId].tMonSelection);
            gSpecialVar_Result = (rivalSlot + 2) % 3;
        }
        else
        {
            gSpecialVar_Result = gTasks[taskId].tMonSelection;
        }
        ResetAllPicSprites();
        SetMainCallback2(gMain.savedCallback);
        break;
    case 1:  // NO
    case MENU_B_PRESSED:
        PlaySE(SE_SELECT);
        PrintMonInfoText(taskId);
        gTasks[taskId].func = Task_HandleMonSelectInput;
        break;
    }
}

static u8 CreatePokemonFrontSprite(enum Species species, u8 x, u8 y, u8 paletteSlot)
{
    u8 spriteId;

    spriteId = CreateMonPicSprite_Affine(species, FALSE, 0, MON_PIC_AFFINE_FRONT, x, y, paletteSlot, TAG_NONE);
    gSprites[spriteId].oam.priority = 0;
    return spriteId;
}

static void SpriteCB_SelectionHand(struct Sprite *sprite)
{
    // Float up and down above the selected Pokémon.
    u8 taskId = sprite->sTaskId;
    u8 coordIndex = gTasks[taskId].tMonSelection;

    sprite->x = sCursorCoords[coordIndex][0];
    sprite->y = sCursorCoords[coordIndex][1];
    sprite->y2 = Sin(sprite->data[1], 8);
    sprite->data[1] = (u8)(sprite->data[1]) + 4;
}
