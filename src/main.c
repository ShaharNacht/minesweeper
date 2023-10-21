#include "consts.h"
#include "game_type.h"
#include "game_methods.h"

int main()
{
	Game game;
	game_init( &game, BOARD_COLS, BOARD_ROWS );
	
	game_main_loop(&game);
	
	game_destroy(&game);
	
	return 0;
}