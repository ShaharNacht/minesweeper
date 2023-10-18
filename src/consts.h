#pragma once

#include <stdint.h>

static constexpr int BOARD_COLS = 12;
static constexpr int BOARD_ROWS = 12;

static const char * const WINDOW_TITLE = "Minesweeper";
static constexpr int WINDOW_WIDTH = 768;
static constexpr int WINDOW_HEIGHT = 768;
static constexpr int TARGET_FPS = 60;

static constexpr uint8_t GFX_BACKGROUND_COLOR[3] = { 0xAA, 0xAA, 0xAA };
static constexpr uint8_t GFX_GRID_COLOR[3] = { 0x66, 0x66, 0x66 };
static constexpr int GFX_GRID_LINE_THICKNESS = 4;

static const char * const GFX_CELL_TEXTURE_PATH = "assets/cell.png";
static const char * const GFX_MINE_TEXTURE_PATH = "assets/mine.png";
static const char * const GFX_NUMBERS_TEXTURE_PATH = "assets/numbers.png";
static constexpr int GFX_NUMBERS_TEXTURE_SUBTEXTURE_COUNT = 9;