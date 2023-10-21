#pragma once

#include "point_type.h"
#include "cell_type.h"

typedef struct Ui
{
	// read-only
	WindowPoint mouse_position;
	Cell *selected_cell; // Just a reference, no need to destroy.
	bool is_mouse_on_selected_cell;
} Ui;