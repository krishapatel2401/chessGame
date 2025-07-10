# Networked Chess Game

A client-server Chess game implemented in C using the sockets API. The game allows two players to play over a network, with synchronized game state management and command-based interactions. 

## Features

- Real-time gameplay over TCP between a client (White) and server (Black)
- Custom chess move engine with rule validation for all standard pieces
- Structured command parsing (`/move`, `/chessboard`, `/save`, `/load`, etc.)
- Game state serialization via FEN (Forsyth–Edwards Notation)
- Support for saving/loading games tied to usernames
- Text-based interface with clear prompts and board display

## Technologies Used

- C (POSIX sockets)
- UNIX system calls (`send`, `recv`, `read`, `write`)
- File I/O for saving/loading game states
- FEN parsing/generation for board representation

## Build & Run Instructions

### 1. Build the project
cmake -S . -B build

cmake --build build


### 2. Run server and client (in separate terminals)
./build/hw4_server    # Run in one terminal

./build/hw4_client    # Run in another


### 3. Play the game using commands
Start with /chessboard to view the board, then use commands like:

/move e2e4

/save yourname

/load yourname 1

/forfeit

/import FEN_STRING


### Notes
The client always plays White, and the server plays Black.

Invalid commands or moves will be rejected with error messages.

Saved games are appended to game_database.txt.

Example Save Format
username:rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w
