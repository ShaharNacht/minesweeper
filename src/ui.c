#include "point.h"
#include "graphics.h"
#include "board.h"
#include "cell.h"

#include "ui.h"

static bool is_point_inside_window( const Graphics *graphics, WindowPoint point );

void ui_init( Ui *self )
{
	self->mouse_position = window_point_new( 0, 0 );
	self->selected_cell = nullptr;
	self->is_mouse_on_selected_cell = false;
}

void ui_destroy( Ui *self )
{
	window_point_destroy(&self->mouse_position);
	self->selected_cell = nullptr;
}

void ui_on_mouse_move( Ui *self, const Board *board, const Graphics *graphics, WindowPoint mouse_position )
{
	self->mouse_position = mouse_position;
	
	if ( self->selected_cell != nullptr && is_point_inside_window( graphics, mouse_position ) )
	{
		BoardPoint mouse_on_board = window_point_to_board_point( self->mouse_position, board, graphics );
		Cell *cell = board_get_cell( board, mouse_on_board );
		
		self->is_mouse_on_selected_cell = ( self->selected_cell == cell );
	}
	else
	{
		self->is_mouse_on_selected_cell = false;
	}
}

void ui_on_left_mouse_down( Ui *self, Board *board, const Graphics *graphics, WindowPoint mouse_position )
{
	ui_on_mouse_move( self, board, graphics, mouse_position );
	
	if ( is_point_inside_window( graphics, mouse_position ) )
	{
		BoardPoint mouse_on_board = window_point_to_board_point( self->mouse_position, board, graphics );
		Cell *cell = board_get_cell( board, mouse_on_board );
		
		if (!cell->is_revealed)
		{
			self->selected_cell = cell;
			self->is_mouse_on_selected_cell = true;
		}
	}
}

void ui_on_left_mouse_up( Ui *self, Board *board, const Graphics *graphics, WindowPoint mouse_position )
{
	ui_on_mouse_move( self, board, graphics, mouse_position );
	
	if ( self->selected_cell != nullptr )
	{
		if (self->is_mouse_on_selected_cell)
		{
			self->selected_cell->is_revealed = true;
		}
		
		self->selected_cell = nullptr;
		self->is_mouse_on_selected_cell = false;
	}
}

void ui_on_right_mouse_down( Ui *self, Board *board, const Graphics *graphics, WindowPoint mouse_position )
{
	ui_on_mouse_move( self, board, graphics, mouse_position );
}

static bool is_point_inside_window( const Graphics *graphics, WindowPoint point )
{
	return point.x >= 0 &&
		point.x < graphics->window_width &&
		point.y >= 0 &&
		point.y < graphics->window_height;
}