#pragma once

#include "cell_type.h"

void cell_init( Cell *self, bool is_mine, int mine_neighbor_count );
void cell_destroy( Cell *self );

void cell_set_mine( Cell *self, bool is_mine );