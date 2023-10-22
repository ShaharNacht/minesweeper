#include "ui_type.h"
#include "board_type.h"
#include "cell_type.h"

#include "ui_methods.h"
#include "point_methods.h"
#include "board_methods.h"

static bool is_point_inside_window( Ui *self, WindowPoint point );

void ui_init( Ui *self, int window_width, int window_height )
{
	self->window_width = window_width;
	self->window_height = window_height;
	self->mouse_position = window_point_new( 0, 0 );
	self->selected_cell = nullptr;
	self->is_mouse_on_selected_cell = false;
}

void ui_destroy( Ui *self )
{
	window_point_destroy(&self->mouse_position);
	self->selected_cell = nullptr;
}

int ui_get_cell_width( const Ui *self, const Board *board )
{
	return self->window_width / board->cols;
}

int ui_get_cell_height( const Ui *self, const Board *board )
{
	return self->window_height / board->rows;
}

void ui_on_mouse_move( Ui *self, const Board *board, WindowPoint mouse_position )
{
	self->mouse_position = mouse_position;
	
	if ( self->selected_cell != nullptr && is_point_inside_window( self, mouse_position ) )
	{
		BoardPoint mouse_on_board = window_point_to_board_point( self->mouse_position, self, board );
		Cell *cell = board_get_cell( board, mouse_on_board );
		
		self->is_mouse_on_selected_cell = ( self->selected_cell == cell );
	}
	else
	{
		self->is_mouse_on_selected_cell = false;
	}
}

void ui_on_left_mouse_down( Ui *self, const Board *board, WindowPoint mouse_position )
{
	ui_on_mouse_move( self, board, mouse_position );
	
	if ( is_point_inside_window( self, mouse_position ) )
	{
		BoardPoint mouse_on_board = window_point_to_board_point( self->mouse_position, self, board );
		Cell *cell = board_get_cell( board, mouse_on_board );
		
		if (!cell->is_revealed)
		{
			self->selected_cell = cell;
			self->is_mouse_on_selected_cell = true;
		}
	}
}

void ui_on_left_mouse_up( Ui *self, const Board *board, WindowPoint mouse_position )
{
	ui_on_mouse_move( self, board, mouse_position );
	
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

void ui_on_right_mouse_down( Ui *self, const Board *board, WindowPoint mouse_position )
{
	ui_on_mouse_move( self, board, mouse_position );
}

static bool is_point_inside_window( Ui *self, WindowPoint point )
{
	return point.x >= 0 &&
		point.x < self->window_width &&
		point.y >= 0 &&
		point.y < self->window_height;
}