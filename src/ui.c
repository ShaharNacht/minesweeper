#include <stdio.h>

#include "point.h"
#include "board.h"

#include "ui.h"

void ui_init( Ui *self )
{
	self->mouse_position = window_point_new( 0, 0 );
}

void ui_destroy( Ui *self )
{
	window_point_destroy(&self->mouse_position);
}

void ui_on_mouse_move( Ui *self, WindowPoint mouse_position )
{
	self->mouse_position = mouse_position;
}

void ui_on_left_mouse_down( Ui *self, Board *board, WindowPoint mouse_position )
{
	self->mouse_position = mouse_position;
	
	printf("Left press\n");
}

void ui_on_left_mouse_up( Ui *self, Board *board, WindowPoint mouse_position )
{
	self->mouse_position = mouse_position;
	
	printf("Left release\n");
}

void ui_on_right_mouse_down( Ui *self, Board *board, WindowPoint mouse_position )
{
	self->mouse_position = mouse_position;
	
	printf("Right press\n");
}