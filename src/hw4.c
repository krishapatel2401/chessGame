#include "hw4.h"

void initialize_game(ChessGame *game) {

    game->moveCount = 0;
    game->capturedCount = 0;
    game->currentPlayer = 0;

    //setting rnbqkbnr in first row
    game->chessboard[0][0] = 'r';
    game->chessboard[0][1] = 'n';
    game->chessboard[0][2] = 'b';
    game->chessboard[0][3] = 'q';
    game->chessboard[0][4] = 'k';
    game->chessboard[0][5] = 'b';
    game->chessboard[0][6] = 'n';
    game->chessboard[0][7] = 'r';
    for (int col = 0; col < 8; col +=1){
        game->chessboard[1][col] = 'p';
    }
    for (int row = 2; row < 6; row +=1){
        for (int col=0; col < 8; col +=1){
            game->chessboard[row][col] = '.';
        }
    }
    for (int col = 0; col < 8; col +=1){
        game->chessboard[6][col] = 'P';
    }
    
    //setting RNBQKBNR in the last row
    game->chessboard[7][0] = 'R';
    game->chessboard[7][1] = 'N';
    game->chessboard[7][2] = 'B';
    game->chessboard[7][3] = 'Q';
    game->chessboard[7][4] = 'K';
    game->chessboard[7][5] = 'B';
    game->chessboard[7][6] = 'N';
    game->chessboard[7][7] = 'R';

}

void chessboard_to_fen(char fen[], ChessGame *game) {
    (void)fen;
    (void)game;
}

bool is_valid_pawn_move(char piece, int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    (void)piece;
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    (void)game;
    return false;
}

bool is_valid_rook_move(int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    (void)game;
    return false;
}

bool is_valid_knight_move(int src_row, int src_col, int dest_row, int dest_col) {
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    return false;
}

bool is_valid_bishop_move(int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    (void)game;
    return false;
}

bool is_valid_queen_move(int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    (void)game;
    return false;
}

bool is_valid_king_move(int src_row, int src_col, int dest_row, int dest_col) {
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    return false;
}

bool is_valid_move(char piece, int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    (void)piece;
    (void)src_row;
    (void)src_col;
    (void)dest_row;
    (void)dest_col;
    (void)game;
    return false;
}

void fen_to_chessboard(const char *fen, ChessGame *game) {
    (void)fen;
    (void)game;
}

int parse_move(const char *move, ChessMove *parsed_move) {

    int move_length = strlen(move);

    if ((move_length !=4) && (move_length !=5)){
        return PARSE_MOVE_INVALID_FORMAT;
    }

    char start_char = *(move);
    char dest_char = *(move + 2);
    if ( ((start_char <'a')||(start_char> 'h')) || ((dest_char < 'a')||(dest_char >'h')) ){
        return PARSE_MOVE_INVALID_FORMAT;
    }

    char start_int_pos = *(move + 1);
    char dest_int_pos = *(move + 3);
    if ( ((start_int_pos < '1')||(start_int_pos> '8')) || ((dest_int_pos < '1')||(dest_int_pos >'8')) ){
        return PARSE_MOVE_OUT_OF_BOUNDS;
    }

    if (move_length == 5){
        if ( (dest_int_pos != '8') && (dest_int_pos != '1')){
            return PARSE_MOVE_INVALID_DESTINATION;
        }

        char promotion_letter = *(move + 4);
        const char accepted_values[] = "qrbn";
        char *found = strchr(accepted_values, promotion_letter);
        if (found == NULL){
            return PARSE_MOVE_INVALID_PROMOTION;
        }
    }
    
    // char *source_pos = malloc(3 * sizeof(char));
    // *(source_pos) = start_char;
    // *(source_pos + 1) = start_int_pos;
    // *(source_pos + 2) = '\0';

    // char source_pos[3] /*= malloc(3 * sizeof(char))*/;
    parsed_move->startSquare[0] = start_char;
    parsed_move->startSquare[1] = start_int_pos;
    parsed_move->startSquare[2] = '\0';

    
    // char *dest_pos = malloc(4 * sizeof(char));
    // *(dest_pos) = dest_char;
    // *(dest_pos + 1) = dest_int_pos;
    // *(dest_pos + 2) = '\0';
    // if (move_length ==5){
    //     *(dest_pos + 2) = *(move + 4);
    //     *(dest_pos + 3) = '\0';
    // }

    // char *dest_pos = malloc(4 * sizeof(char));
    parsed_move->endSquare[0] = dest_char;
    parsed_move->endSquare[1] = dest_int_pos;
    parsed_move->endSquare[2] = '\0';
    if (move_length ==5){
        parsed_move->endSquare[2] = *(move + 4);
        parsed_move->endSquare[3] = '\0';
    }
    
    // *parsed_move->startSquare = source_pos;
    // *parsed_move->endSquare = dest_pos;
    return 0;
}

int make_move(ChessGame *game, ChessMove *move, bool is_client, bool validate_move) {
    (void)game;
    (void)move;
    (void)is_client;
    (void)validate_move;
    return -999;
}

int send_command(ChessGame *game, const char *message, int socketfd, bool is_client) {
    (void)game;
    (void)message;
    (void)socketfd;
    (void)is_client;
    return -999;
}

int receive_command(ChessGame *game, const char *message, int socketfd, bool is_client) {
    (void)game;
    (void)message;
    (void)socketfd;
    (void)is_client;
    return -999;
}

int save_game(ChessGame *game, const char *username, const char *db_filename) {
    (void)game;
    (void)username;
    (void)db_filename;
    return -999;
}

int load_game(ChessGame *game, const char *username, const char *db_filename, int save_number) {
    (void)game;
    (void)username;
    (void)db_filename;
    (void)save_number;
    return -999;
}

void display_chessboard(ChessGame *game) {
    printf("\nChessboard:\n");
    printf("  a b c d e f g h\n");
    for (int i = 0; i < 8; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < 8; j++) {
            printf("%c ", game->chessboard[i][j]);
        }
        printf("%d\n", 8 - i);
    }
    printf("  a b c d e f g h\n");
}
