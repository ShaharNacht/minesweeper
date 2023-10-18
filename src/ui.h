#pragma once

#include "point.h"
#include "board.h"

typedef struct Ui
{
	// read-only
	WindowPoint mouse_position;
} Ui;

void ui_init( Ui *self );
void ui_destroy( Ui *self );

void ui_on_mouse_move( Ui *self, WindowPoint mouse_position );
void ui_on_left_mouse_down( Ui *self, Board *board, WindowPoint mouse_position );
void ui_on_left_mouse_up( Ui *self, Board *board, WindowPoint mouse_position );
void ui_on_right_mouse_down( Ui *self, Board *board, WindowPoint mouse_position );