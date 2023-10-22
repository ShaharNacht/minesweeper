#pragma once

#include "ui_type.h"

#include "point_type.h"
#include "board_type.h"

void ui_init( Ui *self, int window_width, int window_height );
void ui_destroy( Ui *self );

int ui_get_cell_width( const Ui *self, const Board *board );
int ui_get_cell_height( const Ui *self, const Board *board );

void ui_on_mouse_move( Ui *self, const Board *board, WindowPoint mouse_position );
void ui_on_left_mouse_down( Ui *self, const Board *board, WindowPoint mouse_position );
void ui_on_left_mouse_up( Ui *self, const Board *board, WindowPoint mouse_position );
void ui_on_right_mouse_down( Ui *self, const Board *board, WindowPoint mouse_position );