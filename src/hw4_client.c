#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "hw4.h"

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    ChessGame game;
    int connfd = 0;
    struct sockaddr_in serv_addr;

    char buffer[BUFFER_SIZE] = {0};

    // Connect to the server
    if ((connfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(connfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    initialize_game(&game);
    display_chessboard(&game);

    while (1) {

        printf("[Client] Enter message: ");
        memset(buffer, 0, BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strlen(buffer)-1] = '\0';
        int new_answer = send_command(&game, buffer, connfd, true);
        while( (new_answer == COMMAND_ERROR) || (new_answer == COMMAND_UNKNOWN) || (new_answer== COMMAND_DISPLAY) ||
                (new_answer == COMMAND_SAVE)){
            printf("[Client] Enter message: ");
            memset(buffer, 0, BUFFER_SIZE);
            fgets(buffer, BUFFER_SIZE, stdin);
            buffer[strlen(buffer)-1] = '\0';
            new_answer = send_command(&game, buffer, connfd, true);
        }
        if (new_answer == COMMAND_FORFEIT){
            printf("[Client] Client chatter quitting...\n");
            // send_command(&game, buffer, connfd, false);
            break;
        }

        memset(buffer, 0, BUFFER_SIZE);
        int nbytes = read(connfd, buffer, BUFFER_SIZE);
        if (nbytes <= 0) {
            perror("[Client] read() failed.");
            exit(EXIT_FAILURE);
        }
        
        printf("[Server] Received from client: %s\n", buffer);
        int answer = receive_command(&game, buffer, connfd, true );
        if (answer == COMMAND_FORFEIT){
            printf("[Client] Client chatter quitting...\n");
            break;
        }

        // Fill this in
    }

    // Please ensure that the following lines of code execute just before your program terminates.
    // If necessary, copy and paste it to other parts of your code where you terminate your program.
    FILE *temp = fopen("./fen.txt", "w");
    char fen[200];
    chessboard_to_fen(fen, &game);
    fprintf(temp, "%s", fen);
    fclose(temp);
    close(connfd);
    return 1;
}
