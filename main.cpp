
#include <stdlib.h>
#include <stdio.h>

#include "game.h"

int main(int argc, char **argv)
{
    printf("Strategy game 0.1\n");

    Game *game = new Game(800, 600);
    if(game->Init(argc, argv) == 0)
	   game->Run();
    
    return(0);
}
