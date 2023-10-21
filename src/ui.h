#pragma once

#include "point.h"
#include "cell.h"

typedef struct Ui
{
	// read-only
	WindowPoint mouse_position;
	Cell *selected_cell; // Just a reference, no need to destroy.
	bool is_mouse_on_selected_cell;
} Ui;

#include "graphics.h"
#include "board.h"

void ui_init( Ui *self );
void ui_destroy( Ui *self );

void ui_on_mouse_move( Ui *self, const Board *board, const Graphics *graphics, WindowPoint mouse_position );
void ui_on_left_mouse_down( Ui *self, Board *board, const Graphics *graphics, WindowPoint mouse_position );
void ui_on_left_mouse_up( Ui *self, Board *board, const Graphics *graphics, WindowPoint mouse_position );
void ui_on_right_mouse_down( Ui *self, Board *board, const Graphics *graphics, WindowPoint mouse_position );