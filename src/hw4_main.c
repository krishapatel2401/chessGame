#include "hw4.h"

int main(){

    ChessGame game;
    initialize_game(&game);

    // Save a game
    const char *username = "testuser";
    const char *db_filename = "game_database.txt";
    save_game(&game, username, db_filename);

    ChessMove move1 = {"e2", "e4"};
    make_move(&game, &move1, true, true);
    ChessMove move2 = {"e7", "e5"};
    make_move(&game, &move2, false, true);

    // Save the game again
    save_game(&game, username, db_filename);

    // Load the second save file
    ChessGame loaded_game;
    int save_number = 2;
    int result = load_game(&loaded_game, username, db_filename, save_number);

    // ASSERT_EQ(result, 0);

    // Check if the loaded game state matches the expected state
    char expected_board[8][8] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', '.', 'p', 'p', 'p'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', 'p', '.', '.', '.'},
        {'.', '.', '.', '.', 'P', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'P', 'P', 'P', 'P', '.', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    display_chessboard(&loaded_game);

    // for (int i = 0; i < 8; i++) {
    //     for (int j = 0; j < 8; j++) {
    //         ASSERT_EQ(loaded_game.chessboard[i][j], expected_board[i][j]);
    //     }
    // }


    return 0;
}