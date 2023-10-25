#pragma once

#include "game_type.h"

void game_init( Game *self, int board_cols, int board_rows, int mine_count );
void game_destroy( Game *self );

void game_main_loop( Game *self );