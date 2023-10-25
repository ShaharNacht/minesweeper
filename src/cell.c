#include <stdlib.h>

#include "cell_type.h"
#include "point_type.h"

#include "cell_methods.h"
#include "point_methods.h"

void cell_init( Cell *self, BoardPoint position )
{
	self->position = position;
	
	self->is_revealed = false;
	
	self->is_mine = false;
	self->mine_neighbor_count = 0;
}

void cell_destroy( Cell *self )
{
	board_point_destroy(&self->position);
}

void cell_generate( Cell *self, bool is_mine, int mine_neighbor_count )
{
	self->is_mine = is_mine;
	self->mine_neighbor_count = mine_neighbor_count;
}