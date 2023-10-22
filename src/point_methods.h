#pragma once

#include "point_type.h"

#include "ui_type.h"
#include "board_type.h"

BoardPoint board_point_new( int x, int y );
void board_point_destroy( BoardPoint *self );

WindowPoint window_point_new( int x, int y );
void window_point_destroy( WindowPoint *self );

WindowPoint board_point_to_window_point( BoardPoint self, const Ui *ui, const Board *board );
BoardPoint window_point_to_board_point( WindowPoint self, const Ui *ui, const Board *board );