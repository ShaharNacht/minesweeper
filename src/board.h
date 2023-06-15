#pragma once

typedef struct Board
{
	// read-only
	int cols;
	int rows;
} Board;

void board_new( Board *self, int cols, int rows );
void board_destroy( Board *self );