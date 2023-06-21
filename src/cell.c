#include <stdlib.h>

#include "cell.h"

void cell_new( Cell *self )
{
	self->is_revealed = ( rand() % 2 ) == 1;
	self->is_mine = ( rand() % 2 ) == 1;
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