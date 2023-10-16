#pragma once

typedef struct Cell
{
	// public
	bool is_revealed;
	
	// read-only
	bool is_mine;
	int mine_neighbor_count;
} Cell;

void cell_init( Cell *self, bool is_mine, int mine_neighbor_count );
void cell_destroy( Cell *self );

void cell_set_mine( Cell *self, bool is_mine );