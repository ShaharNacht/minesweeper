#pragma once

#include "include_sdl2.h"

#include "graphics_type.h"

#include "ui_type.h"
#include "board_type.h"

void graphics_init( Graphics *self, SDL_Renderer *renderer );
void graphics_destroy( Graphics *self );

void graphics_draw( const Graphics *self, SDL_Renderer *renderer, const Ui *ui, const Board *board );