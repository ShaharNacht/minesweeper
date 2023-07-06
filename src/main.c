#include "consts.h"
#include "game.h"

int main()
{
	Game game;
	game_init( &game, BOARD_COLS, BOARD_ROWS );
	
	game_main_loop(&game);
	
	game_destroy(&game);
	
	return 0;
}