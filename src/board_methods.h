#pragma once

#include "board_type.h"

#include "point_type.h"

void board_init( Board *self, int cols, int rows, int mine_count );
void board_destroy( Board *self );

Cell *board_get_cell( const Board *self, BoardPoint position );

void board_reveal_cell( Board *self, Cell *cell );