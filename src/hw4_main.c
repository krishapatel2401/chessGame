#include "hw4.h"


int main(){

    ChessGame game;
    initialize_game_soln(&game);
    ChessMove move;
    parse_move("e7e5", &move);
    int result = make_move(&game, &move, 1, 1);

    printf("result=%d\n", result);
    pritnf("move count=%d\n", game.moveCount);
    printf("current player=%d\n", game.currentPlayer);

    return 0;
}