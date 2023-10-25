#pragma once

#include "point_type.h"

typedef struct Cell
{
	// public
	bool is_revealed;
	
	// read-only
	BoardPoint position;
	bool is_mine;
	int mine_neighbor_count;
} Cell;