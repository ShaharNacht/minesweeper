#pragma once

typedef struct Cell
{
	// public
	bool is_revealed;
	
	// read-only
	bool is_mine;
	int mine_neighbor_count;
} Cell;