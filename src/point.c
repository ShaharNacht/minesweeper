#include "utils.h"

#include "point_type.h"
#include "ui_type.h"
#include "board_type.h"

#include "point_methods.h"
#include "ui_methods.h"

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

WindowPoint board_point_to_window_point( BoardPoint self, const Ui *ui, const Board *board )
{
	return (WindowPoint)
	{
		.x = self.x * ui_get_cell_width( ui, board ),
		.y = self.y * ui_get_cell_height( ui, board )
	};
}

BoardPoint window_point_to_board_point( WindowPoint self, const Ui *ui, const Board *board )
{
	return (BoardPoint)
	{
		.x = clamp( self.x / ui_get_cell_width( ui, board ), 0, board->cols - 1 ),
		.y = clamp( self.y / ui_get_cell_height( ui, board ), 0, board->rows - 1 )
	};
}