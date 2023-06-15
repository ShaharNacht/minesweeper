#include "game.h"

int main()
{
	Game game;
	game_new( &game, 5, 7 );
	
	game_main_loop(&game);
	
	game_destroy(&game);
	
	return 0;
}