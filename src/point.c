#include "consts.h"
#include "board.h"
#include "graphics.h"

#include "point.h"

BoardPoint board_point_new( int x, int y )
{
	return (BoardPoint) { .x = x, .y = y };
}

void board_point_destroy( [[maybe_unused]] BoardPoint *self )
{
	// Intentional no-op, so that this function can already be called wherever necessary,
	// in case code will be added to it in the future.
}

WindowPoint window_point_new( int x, int y )
{
	return (WindowPoint) { .x = x, .y = y };
}

void window_point_destroy( [[maybe_unused]] WindowPoint *self )
{
	// Intentional no-op, so that this function can already be called wherever necessary,
	// in case code will be added to it in the future.
}

WindowPoint board_point_to_window_point( BoardPoint self, const Board *board, const Graphics *graphics )
{
	return (WindowPoint)
	{
		.x = self.x * window_cell_width( board, graphics ),
		.y = self.y * window_cell_height( board, graphics )
	};
}

BoardPoint window_point_to_board_point( WindowPoint self, const Board *board, const Graphics *graphics )
{
	return (BoardPoint)
	{
		.x = self.x / window_cell_width( board, graphics ),
		.y = self.y / window_cell_height( board, graphics )
	};
}

int window_cell_width( const Board *board, const Graphics *graphics )
{
	return graphics->window_width / board->cols;
}

int window_cell_height( const Board *board, const Graphics *graphics )
{
	return graphics->window_height / board->rows;
}