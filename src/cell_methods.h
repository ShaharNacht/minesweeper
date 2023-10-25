#pragma once

#include "cell_type.h"

#include "point_type.h"

void cell_init( Cell *self, BoardPoint position );
void cell_destroy( Cell *self );

void cell_generate( Cell *self, bool is_mine, int mine_neighbor_count );