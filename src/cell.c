#include <stdlib.h>

#include "cell_type.h"

#include "cell_methods.h"

void cell_init( Cell *self, bool is_mine, int mine_neighbor_count )
{
	self->is_revealed = ( rand() % 2 ) != 0;
	// self->is_revealed = true;
	self->is_mine = is_mine;
	self->mine_neighbor_count = mine_neighbor_count;
}

void cell_destroy( [[maybe_unused]] Cell *self )
{
	// Intentional no-op, so that this function can already be called wherever necessary,
	// in case code will be added to it in the future.
}

void cell_set_mine( Cell *self, bool is_mine )
{
	self->is_mine = is_mine;
}