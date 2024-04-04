#include "hw4.h"

void initialize_game(ChessGame *game) {

    game->moveCount = 0;
    game->capturedCount = 0;
    game->currentPlayer = 0;

    //setting rnbqkbnr in first row
    char *black_row_0 = "rnbqkbnr";
    for (int col = 0; col< 8; col +=1){
        game->chessboard[0][col] = *(black_row_0 + col);
    }

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
    char *white_row_7 = "RNBQKBNR";
    for (int col = 0; col< 8; col +=1){
        game->chessboard[7][col] = *(white_row_7 + col);
    }

}

void chessboard_to_fen(char fen[], ChessGame *game) {
    int row_ctr = 0;
    int col_ctr = 0;
    int spaces = 0; int index_ctr = 0;
    
    while ( (row_ctr<8) && (col_ctr<8)){  //iterating through board
        char piece = game->chessboard[row_ctr][col_ctr]; //what is the piece at current location
        if (piece=='.'){ //if there's no piece
            spaces+=1;
        }
        if (piece!='.'){
            if (spaces==0){  //if there were no spaces before this piece
                *(fen + index_ctr)  = piece;
                index_ctr +=1;
            }
            if (spaces!=0){ //if there were spaces
                char num_char = spaces + '0'; //converting int to char
                *(fen + index_ctr) = num_char;  //adding the number of spaces that were present before this piece
                index_ctr+=1;
                spaces = 0;  //set spaces back to 0
                *(fen + index_ctr) = piece;  //add the piece
                index_ctr +=1;
            }
        }
        col_ctr +=1;
        if (col_ctr==8){  //if we reached the end of the row
            if (spaces!=0){  //if any spaces were encountered after the last piece
                char num_char = spaces + '0';  //add the number of spaces
                *(fen + index_ctr) = num_char;
                index_ctr+=1;
                spaces = 0;
            }
            row_ctr +=1; col_ctr=0;  //update coordinates
            *(fen + index_ctr) = '/'; index_ctr +=1;
        }
    }

    *(fen + index_ctr -1) =' ';  //since a '/' is currently stored there
    if (game->currentPlayer ==1){ //current black
        *(fen + index_ctr) = 'b';  
    }
    if (game->currentPlayer ==0){ //current white
        *(fen + index_ctr) = 'w';  
    }
    *(fen + index_ctr +1) = '\0';
    printf("fen string =%s\n",fen);
    display_chessboard(game);


}

bool is_valid_pawn_move(char piece, int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {

    if ( (src_row <1) || (src_col<0) || (dest_row>7) || (dest_col>7)){
        return false;
    }
    if (piece == 'p'){ //black pawn
        if (src_row ==1){  //moving forward in start position
            //advance one step forward to an empty spot
            if ( (dest_row == 2) && (src_col == dest_col) && (game->chessboard[dest_row][dest_col] == '.') ){
                return true;
            }
            //advance 2 steps forward to an empty spot
            if ( (dest_row == 3) && (src_col == dest_col) && (game->chessboard[2][dest_col] == '.') 
                    && (game->chessboard[3][dest_col] == '.')  ){
                return true;
            }
        }
        //for any other row, moving forward by one spot only:
        if ( (src_col==dest_col) && ( (src_row +1)==dest_row) && (game->chessboard[dest_row][dest_col] == '.') ){
            return true;
        }

        //capturing:
        if (src_col ==0){  //no left col
            if ( (dest_col==1) && ( (src_row +1)==dest_row) && (game->chessboard[dest_row][dest_col] != '.')){
                return true;
            }
        }
        if (src_col ==7){  //no right col
            if ( (dest_col==6) && ( (src_row +1)==dest_row) && (game->chessboard[dest_row][dest_col] != '.')){
                return true;
            }
        }
        //if one of the middle columns:
        if ( ( ( (src_col+1)==dest_col) || ( (src_col-1)==dest_col) ) &&
                ( (src_row +1)==dest_row) && (game->chessboard[dest_row][dest_col] != '.')){
            return true;
        }

    }

    if (piece == 'P'){ //white pawn
        if (src_row ==6){  //moving forward in start position
            //advance one step forward to an empty spot
            if ( (dest_row == 5) && (src_col == dest_col) && (game->chessboard[dest_row][dest_col] == '.') ){
                return true;
            }
            //advance 2 steps forward to an empty spot
            if ( (dest_row == 4) && (src_col == dest_col) && (game->chessboard[5][dest_col] == '.') 
                    && (game->chessboard[4][dest_col] == '.')  ){
                return true;
            }
        }
        //for any other row, moving forward by one spot only:
        if ( (src_col==dest_col) && ( (src_row -1)==dest_row) && (game->chessboard[dest_row][dest_col] == '.') ){
            return true;
        }

        //capturing:
        if (src_col ==0){  //no left col
            if ( (dest_col==1) && ( (src_row -1)==dest_row) && (game->chessboard[dest_row][dest_col] != '.')){
                return true;
            }
        }
        if (src_col ==7){  //no right col
            if ( (dest_col==6) && ( (src_row -1)==dest_row) && (game->chessboard[dest_row][dest_col] != '.')){
                return true;
            }
        }
        //if one of the middle columns:
        if ( ( ( (src_col+1)==dest_col) || ( (src_col-1)==dest_col) ) &&
                ( (src_row -1)==dest_row) && (game->chessboard[dest_row][dest_col] != '.')){
            return true;
        }

    }

    return false;
}

bool is_valid_rook_move(int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    
    if ( (src_row <0) || (src_col <0) || (dest_row >7) || (dest_col >7)){  //invalid src or dest
        return false;
    }
    if (src_row==dest_row){  //horizontal move
        if (src_col <= dest_col){  //moving to right
            int ctr = src_col +1;
            while (ctr < dest_col){
                if (game->chessboard[src_row][ctr] != '.'){
                    return false;
                }
                ctr +=1;
            }
            return true;
        }
        if (src_col >= dest_col){  //moving to left
            int ctr = src_col -1;
            while (ctr > dest_col){
                if (game->chessboard[src_row][ctr] != '.'){
                    return false;
                }
                ctr -=1;
            }
            return true;
        }
    }
    if (src_col==dest_col){  //vertical move
        if (src_row <= dest_row){  //moving to bottom
            int ctr = src_row +1;
            while (ctr < dest_row){
                if (game->chessboard[ctr][src_col] != '.'){
                    return false;
                }
                ctr +=1;
            }
            return true;
        }
        if (src_row >= dest_row){  //moving to top
            int ctr = src_row-1;
            while (ctr > dest_row){
                if (game->chessboard[ctr][src_row] != '.'){
                    return false;
                }
                ctr -=1;
            }
            return true;
        }
    }
    return false;
}

bool is_valid_knight_move(int src_row, int src_col, int dest_row, int dest_col) {
    
    if ( (src_row <0) || (src_col <0) || (dest_row >7) || (dest_col >7)){  //invalid src or dest
        return false;
    }

    if ( (src_row +2)==dest_row){  //2 verti 1 hori
        if ( ((src_col +1)==dest_col) || ((src_col -1)==dest_col) ){
            return true;
        }
    }
    if ( (src_row +1)==dest_row){ //1 verti 2 hori
        if ( ((src_col +2)==dest_col) || ((src_col -2)==dest_col) ){
            return true;
        }
    }
    if ( (src_row -2)==dest_row){  //2 verti 1 hori
        if ( ((src_col +1)==dest_col) || ((src_col -1)==dest_col) ){
            return true;
        }
    }
    if ( (src_row -1)==dest_row){ //1 verti 2 hori
        if ( ((src_col +2)==dest_col) || ((src_col -2)==dest_col) ){
            return true;
        }
    }

    return false;
}

bool is_valid_bishop_move(int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    
    if ( (src_row <0) || (src_col <0) || (dest_row >7) || (dest_col >7)){  //invalid src or dest
        return false;
    }

    if (src_row > dest_row){ //upward diagonal
        if (src_col < dest_col){ //rightward diagonal
            int row_ctr = src_row -1;
            int col_ctr = src_col +1;
            while( (row_ctr > dest_row) && (col_ctr < dest_col) ){
                if (game->chessboard[row_ctr][col_ctr] != '.'){
                    return false;
                }
                row_ctr -=1;
                col_ctr +=1;
            }
            if ( (row_ctr==dest_row) && (col_ctr==dest_col)){
                return true;
            }
        }
        if (src_col > dest_col){ //leftward diagonal
            int row_ctr = src_row -1;
            int col_ctr = src_col -1;
            while( (row_ctr > dest_row) && (col_ctr > dest_col) ){
                if (game->chessboard[row_ctr][col_ctr] != '.'){
                    return false;
                }
                row_ctr -=1;
                col_ctr -=1;
            }
            if ( (row_ctr==dest_row) && (col_ctr==dest_col)){
                return true;
            }
        }
    }
    if (src_row < dest_row){ //downward diagonal
        if (src_col < dest_col){ //rightward diagonal
            int row_ctr = src_row +1;
            int col_ctr = src_col +1;
            while( (row_ctr < dest_row) && (col_ctr < dest_col) ){
                if (game->chessboard[row_ctr][col_ctr] != '.'){
                    return false;
                }
                row_ctr +=1;
                col_ctr +=1;
            }
            if ( (row_ctr==dest_row) && (col_ctr==dest_col)){
                return true;
            }
        }
        if (src_col > dest_col){ //leftward diagonal
            int row_ctr = src_row +1;
            int col_ctr = src_col -1;
            while( (row_ctr < dest_row) && (col_ctr > dest_col) ){
                if (game->chessboard[row_ctr][col_ctr] != '.'){
                    return false;
                }
                row_ctr +=1;
                col_ctr -=1;
            }
            if ( (row_ctr==dest_row) && (col_ctr==dest_col)){
                return true;
            }
        }
    }
    return false;
}

bool is_valid_queen_move(int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    
    //basically just a combination of the rook and the bishop 
    if ( (src_row <0) || (src_col <0) || (dest_row >7) || (dest_col >7)){  //invalid src or dest
        return false;
    }
    //rook tests
    if (src_row==dest_row){  //horizontal move
        if (src_col <= dest_col){  //moving to right
            int ctr = src_col +1;
            while (ctr < dest_col){
                if (game->chessboard[src_row][ctr] != '.'){
                    return false;
                }
                ctr +=1;
            }
            return true;
        }
        if (src_col >= dest_col){  //moving to left
            int ctr = src_col -1;
            while (ctr > dest_col){
                if (game->chessboard[src_row][ctr] != '.'){
                    return false;
                }
                ctr -=1;
            }
            return true;
        }
    }
    if (src_col==dest_col){  //vertical move
        if (src_row <= dest_row){  //moving to bottom
            int ctr = src_row +1;
            while (ctr < dest_row){
                if (game->chessboard[ctr][src_col] != '.'){
                    return false;
                }
                ctr +=1;
            }
            return true;
        }
        if (src_row >= dest_row){  //moving to top
            int ctr = src_row-1;
            while (ctr > dest_row){
                if (game->chessboard[ctr][src_row] != '.'){
                    return false;
                }
                ctr -=1;
            }
            return true;
        }
    }

    //bishop tests
    if (src_row > dest_row){ //upward diagonal
        if (src_col < dest_col){ //rightward diagonal
            int row_ctr = src_row -1;
            int col_ctr = src_col +1;
            while( (row_ctr > dest_row) && (col_ctr < dest_col) ){
                if (game->chessboard[row_ctr][col_ctr] != '.'){
                    return false;
                }
                row_ctr -=1;
                col_ctr +=1;
            }
            if ( (row_ctr==dest_row) && (col_ctr==dest_col)){
                return true;
            }
        }
        if (src_col > dest_col){ //leftward diagonal
            int row_ctr = src_row -1;
            int col_ctr = src_col -1;
            while( (row_ctr > dest_row) && (col_ctr > dest_col) ){
                if (game->chessboard[row_ctr][col_ctr] != '.'){
                    return false;
                }
                row_ctr -=1;
                col_ctr -=1;
            }
            if ( (row_ctr==dest_row) && (col_ctr==dest_col)){
                return true;
            }
        }
    }
    if (src_row < dest_row){ //downward diagonal
        if (src_col < dest_col){ //rightward diagonal
            int row_ctr = src_row +1;
            int col_ctr = src_col +1;
            while( (row_ctr < dest_row) && (col_ctr < dest_col) ){
                if (game->chessboard[row_ctr][col_ctr] != '.'){
                    return false;
                }
                row_ctr +=1;
                col_ctr +=1;
            }
            if ( (row_ctr==dest_row) && (col_ctr==dest_col)){
                return true;
            }
        }
        if (src_col > dest_col){ //leftward diagonal
            int row_ctr = src_row +1;
            int col_ctr = src_col -1;
            while( (row_ctr < dest_row) && (col_ctr > dest_col) ){
                if (game->chessboard[row_ctr][col_ctr] != '.'){
                    return false;
                }
                row_ctr +=1;
                col_ctr -=1;
            }
            if ( (row_ctr==dest_row) && (col_ctr==dest_col)){
                return true;
            }
        }
    }

    return false;
}

bool is_valid_king_move(int src_row, int src_col, int dest_row, int dest_col) {
    
    if ( (src_row <0) || (src_col <0) || (dest_row >7) || (dest_col >7)){  //invalid src or dest
        return false;
    }
    
    if (src_row==dest_row){  //same row
        if ( ( (src_col +1)==dest_col) || ( (src_col -1)==dest_col)){
            return true;
        }
    }
    if ((src_row +1)==dest_row){  //lower diagonal row
        if ( ( (src_col +1)==dest_col) || (src_col==dest_col) || ( (src_col -1)==dest_col)){
            return true;
        }
    }
    if ((src_row -1)==dest_row){  //upper diagonal row
        if ( ( (src_col +1)==dest_col) || (src_col==dest_col) || ( (src_col -1)==dest_col)){
            return true;
        }
    }    

    return false;
}

bool is_valid_move(char piece, int src_row, int src_col, int dest_row, int dest_col, ChessGame *game) {
    
    if (game->chessboard[src_row][src_col]=='.'){ //no piece at given source
        return false;
    }
    if ( (piece=='p') || (piece=='P')){
        return is_valid_pawn_move(piece, src_row, src_col, dest_row, dest_col, game);
    }
    if ( (piece=='r') || (piece=='R')){
        return is_valid_rook_move(src_row, src_col, dest_row, dest_col, game);
    }
    if ( (piece=='n') || (piece=='N')){
        return is_valid_knight_move(src_row, src_col, dest_row, dest_col);
    }
    if ( (piece=='b') || (piece=='B')){
        return is_valid_bishop_move(src_row, src_col, dest_row, dest_col, game);
    }
    if ( (piece=='q') || (piece=='Q')){
        return is_valid_queen_move(src_row, src_col, dest_row, dest_col, game);
    }
    if ( (piece=='k') || (piece=='K')){
        return is_valid_king_move(src_row, src_col, dest_row, dest_col);
    }


    return false;
}

void fen_to_chessboard(const char *fen, ChessGame *game) {

    int row_ctr = 0;  int col_ctr = 0;
    int spaces = 0; int index = 0; 
    char letter=' '; 
    // int exist_pieces = 0;
    
    
    while ( (row_ctr<8) && (col_ctr<8)){
        letter = *(fen + index);
        index +=1;
        // printf("letter=%c  ind=%d    ",letter, index-1);
        if ( (letter >='0') && (letter <='8')){ //letter is (char) 0 to 8
            spaces = (int)(letter - '0');
            // printf("spaces.1=%d ", spaces);
            while (spaces >0){
                // printf("spaces=%d ", spaces);
                game->chessboard[row_ctr][col_ctr] = '.';
                spaces -=1;
                col_ctr +=1;
                if (col_ctr==8){
                    row_ctr +=1; col_ctr=0;
                    // printf("\n");
                }
            }
            
        }
      
        // if (letter =='/'){  //just ignore this and move on
            
        // }
        if (letter ==' '){  //space character means fen string is kinda over for the main part
            // letter = *(fen + strlen(fen));  //store the last char, i.e 'b' or 'w'
            break;
        }
        if ( ((letter>'a')&&(letter<'z')) || ((letter>'A')&&(letter<'Z'))){ //if the letter is alphabetical, i.e. a chess piece
            game->chessboard[row_ctr][col_ctr] = letter;
            // exist_pieces +=1;
            col_ctr +=1;
            if (col_ctr==8){
                row_ctr +=1; col_ctr=0;
                // printf("\n");
            }
        }
        
    }
    int length = strlen(fen) -1;
    letter = *(fen + length);  //store the last char, i.e 'b' or 'w'
    if (letter =='b'){
        game->currentPlayer = 1;
    }
    if (letter == 'w'){
        game->currentPlayer = 0;
    }
    game->capturedCount = 0;
    
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
    
    parsed_move->startSquare[0] = start_char;
    parsed_move->startSquare[1] = start_int_pos;
    parsed_move->startSquare[2] = '\0';

    parsed_move->endSquare[0] = dest_char;
    parsed_move->endSquare[1] = dest_int_pos;
    parsed_move->endSquare[2] = '\0';
    if (move_length ==5){
        parsed_move->endSquare[2] = *(move + 4);
        parsed_move->endSquare[3] = '\0';
    }
    
    return 0;
}

int make_move(ChessGame *game, ChessMove *move, bool is_client, bool validate_move) {
    
    //variable declarations
    char row_letters[] = "87654321";
    char col_letters[] = "abcdefgh";
    int move_length = strlen(move->endSquare);
    // printf("move length=%d\n", move_length);
    char src_row_char = *(move->startSquare+1);
    int src_row =0;
    for (int i = 0; i < 8; i+=1){
        if ( src_row_char == *(row_letters + i)){
            src_row = i;
            break;
        }
    }

    char src_col_char = *(move->startSquare);
    int src_col = 0;
    for (int i = 0; i < 8; i+=1){
        if ( src_col_char == *(col_letters + i)){
            src_col = i;
            break;
        }
    }

    char dest_row_char = *(move->endSquare+1);
    int dest_row = 0;
    for (int i = 0; i < 8; i+=1){
        if ( dest_row_char == *(row_letters + i)){
            dest_row = i;
            break;
        }
    }
    char dest_col_char = *(move->endSquare);
    int dest_col = 0;
    for (int i = 0; i < 8; i+=1){
        if ( dest_col_char == *(col_letters + i)){
            dest_col = i;
            break;
        }
    }

    printf("src pos=%s row=%d col=%d\n", move->startSquare, src_row, src_col);
    printf("dest pos=%s row=%d col=%d\n", move->endSquare, dest_row, dest_col);

    char piece = game->chessboard[src_row][src_col];
    int current_player = game->currentPlayer;
    const char white_pieces[] = "RNBQKP";
    const char black_pieces[] = "rnbqkp";

    // printf("is client=%d\n",is_client);
    //     printf("current player=%d\n", current_player);

    if(validate_move){
        //error checks go here
        /*printf("is client=%d\n",is_client); //1
        printf("current player=%d\n", current_player); //0  */
        if (is_client == current_player){  //since white in is_client is true, but white in current_player is 0
            return MOVE_OUT_OF_TURN;
        }
        if (piece== '.'){
            return MOVE_NOTHING;
        }
        
        char p = game->chessboard[src_row][src_col];
            // printf("the char p 556=%c\n", p);
            // printf("is client =%d\n", is_client);
            // printf("is not present?=%d\n", (strchr(white_pieces, p)==NULL ));
        if (current_player == 0){  //white player
            p = game->chessboard[src_row][src_col];
            printf("the char p 560=%c\n", p);
            if (strchr(white_pieces, (game->chessboard[src_row][src_col]))==NULL ){
                printf("move wrong color\n");
                return MOVE_WRONG_COLOR;
            }
            p = game->chessboard[dest_row][dest_col];
            if (strchr(white_pieces, p) != NULL){
                return MOVE_SUS; //trying to capture your own piece
            }
        }
        if (current_player == 1){  //black player
            p = game->chessboard[src_row][src_col];
            if (strchr(black_pieces, (game->chessboard[src_row][src_col]))==NULL ){
                return MOVE_WRONG_COLOR;
            }
            p = game->chessboard[dest_row][dest_col];
            if (strchr(black_pieces, p) != NULL){
                return MOVE_SUS; //trying to capture your own piece
            }
        }

        if ( (move_length==3) && (piece != 'p') && (piece !='P')){ //trying to promote a piece that isn't a pawn
            return MOVE_NOT_A_PAWN;
        }
        if (move_length==2){
            if ( ((piece=='p') && (dest_col==7)) || ( (piece=='P') && (dest_col==0)) ){
                return MOVE_MISSING_PROMOTION;  //piece is pawn but you ain't promoting
            }
        }

        if (is_valid_move(piece, src_row, src_col, dest_row, dest_col, game) == false){
            return MOVE_WRONG;
        }
        
    } //end of validate move

    

    char captured_piece = game->chessboard[dest_row][dest_col];
    int capt_count = game->capturedCount;
    *(game->capturedPieces + capt_count) = captured_piece;
    *(game->capturedPieces + capt_count + 1) = '\0';
    game->capturedCount = capt_count + 1;
    
    int m_count = game->moveCount;
    game->moves[m_count] = *move;
    game->moveCount = m_count +1;

    if (move_length==3){
        printf("promoting pawn 607\n");
        char promotion = *(move->endSquare +2);
        printf("pawn is promoted to=%c\n", promotion);
        if (is_client ==true){  //white piece promoted
            promotion = toupper(promotion);
            printf("pawn is promoted to=%c\n", promotion);
        }
        if (is_client ==false){ //black piece
            promotion = tolower(promotion);
            printf("pawn is promoted to=%c\n", promotion);
        }
        game->chessboard[dest_row][dest_col] = promotion;
        game->chessboard[src_row][src_col] = '.';
    }
    if (move_length ==2){
        game->chessboard[dest_row][dest_col] = game->chessboard[src_row][src_col];
        game->chessboard[src_row][src_col] = '.';
    }

    
    if (current_player ==0){
        game->currentPlayer = 1;
    }
    if (current_player==1){
        game->currentPlayer = 0;
    }

    return 0;
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
