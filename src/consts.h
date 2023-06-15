#pragma once

#include <stdint.h>

static const int BOARD_COLS = 12;
static const int BOARD_ROWS = 12;

static const int WINDOW_WIDTH = 768;
static const int WINDOW_HEIGHT = 768;
static const int TARGET_FPS = 60;

static const uint8_t GFX_BACKGROUND_COLOR[3] = { 0xAA, 0xAA, 0xAA };
static const uint8_t GFX_GRID_COLOR[3] = { 0x66, 0x66, 0x66 };
static const int GFX_GRID_LINE_THICKNESS = 4;