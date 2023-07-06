#pragma once

typedef struct Board Board; // Fixes cyclic dependency

#include "board.h"
#include "graphics.h"

typedef struct BoardPoint
{
	// public
	int x;
	int y;
} BoardPoint;

typedef struct WindowPoint
{
	// public
	int x;
	int y;
} WindowPoint;

BoardPoint board_point_new( int x, int y );
void board_point_destroy( BoardPoint *self );

WindowPoint window_point_new( int x, int y );
void window_point_destroy( WindowPoint *self );

WindowPoint board_point_to_window_point( BoardPoint self, const Board *board, const Graphics *graphics );
BoardPoint window_point_to_board_point( WindowPoint self, const Board *board, const Graphics *graphics );

int window_cell_width( const Board *board, const Graphics *graphics );
int window_cell_height( const Board *board, const Graphics *graphics );