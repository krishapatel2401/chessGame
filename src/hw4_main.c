#include "hw4.h"


int main(){

    const char *move = "e2e456";
    ChessGame exp_game;
    initialize_game_soln(&exp_game);
    ChessMove exp_move;
    int exp_ret = parse_move_soln(move, &exp_move);
    ChessGame act_game;
    initialize_game_soln(&act_game);
    ChessMove act_move;
    int act_ret = parse_move(move, &act_move);

    printf("exp_ret=%d\n", exp_ret);
    printf("act_ret=%d\n", act_ret);

    return 0;
}