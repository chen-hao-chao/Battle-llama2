#include "Game_window.h"

int main(void){
    Game_window* game=new Game_window;
    game->game_play();
    delete game;
    return 0;
}
