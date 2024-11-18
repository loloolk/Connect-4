#include <iostream>
#include <string>
#include <random>
#include <ctime>

// breaks after a full column is reached

char board[7][9] = {
    {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
    {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
    {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
    {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
    {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
    {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
    {' ', '1', '2', '3', '4', '5', '6', '7', ' '}
};

// checks if a line of 4 pieces has been made based on the given direction (a and b)
int check_line(int row, int column, int a, int b) {
    int count = 1;
    int row_copy = row;
    int column_copy = column;

    while (board[row][column] == board[row + a][column + b]) {
        count++;
        row += a;
        column += b;
    }

    row = row_copy;
    column = column_copy;

    while (board[row][column] == board[row - a][column - b]) {
        count++;
        row -= a;
        column -= b;
    }

    return count;
}

// checks if the game has been won
bool gameWon(int row, int column) {
    // check vertical
    if (check_line(row, column, 1, 0) > 3)
        return true;

    // check horizontal
    else if (check_line(row, column, 0, 1) > 3)
        return true;

    // check NW-SE diagonal
    else if (check_line(row, column, 1, 1) > 3)
        return true;

    // check NE-SW diagonal
    else if (check_line(row, column, -1, 1) > 3)
        return true;

    return false;
}


// handles the placement of the current player's piece
int placePiece(int column, char piece) {
    int i;

    for (i = 5; i >= 0; i--) {
        if (board[i][column] == '-') {
            board[i][column] = piece;
            break;
        }
    }

    return i;
}

// checks if the board is full
bool isTie() {
    for (int i = 0; i < 7; i++) {
        if (board[0][i] == '-') {
            return false;
        }
    }

    return true;
}

// prints the board's current gamescape to the console
void printBoard() {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << board[i][j] << " ";
        }

        std::cout << std::endl;
    }
}

// handles restarting the game
bool restart(std::string text) {
    printBoard();
    std::cout << text;

    char play_again;

    std::cout << "Play again? (y/n)\n";
    std::cin >> play_again;

    bool play_game = play_again == 'y' ? true : false;

    if (play_game) {
        for (int i = 0; i < 6; i++) {
            board[i][0] = '|';
            board[i][8] = '|';

            for (int j = 1; j < 8; j++)
                board[i][j] = '-';
        }

        for (int j = 1; j < 8; j++)
            board[6][j] = char(48 + j);

        return true;
    }

    return false;
}


// decides the computer's move
int computerMove() {
    for (int i = 1; i < 8; i++) {
        if (board[0][i] != '-') {
            continue;
        }

        int j = placePiece(i, 'O');
        bool game_status = gameWon(j, i);

        if (game_status) {
            board[j][i] = '-';
            return i;
        }
        else {
            board[j][i] = '-';
        }
    }

    for (int i = 1; i < 8; i++) {
        if (board[0][i] != '-') {
            continue;
        }

        int j = placePiece(i, 'X');
        bool game_status = gameWon(j, i);

        if (game_status) {
            board[j][i] = '-';
            return i;
        }
        else {
            board[j][i] = '-';
        }
    }

    int move = rand() % 7 + 1;

    while (board[0][move] != '-') {
        move = rand() % 7 + 1;
    }

    return move;
}


// ensures the input is valid
bool validInput(int input) {
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "Invalid input. Please try again.\n";
        return false;
    }

    else if (input < 1 || input > 7) {
        std::cout << "Input out of range. Please try again.\n";
        return false;
    }

    else if (board[0][input] != '-') {
        std::cout << "Column is full. Please try again.\n";
        return false;
    }

    return true;
}


int main() {
    std::cout << "Welcome to...\nConnect 4!!!\nEveryone knows how to play, so just input a number to begin!\n";
    srand(time(0));

    bool play_game = true;
    int input;

    while (play_game) {
        printBoard();

        std::cin >> input;
        if (!validInput(input)) {
            continue;
        }

        int i = placePiece(input, 'X');
        bool game_status = gameWon(i, input);

        if (game_status) {
            play_game = restart("Player wins!\n");
        }

        else if (isTie()) {
            play_game = restart("Tie game!\n");
        }

        else { // computer's turn
            printBoard();

            int computer_input = computerMove();

            int i = placePiece(computer_input, 'O');
            bool game_status = gameWon(i, computer_input);

            if (game_status) {
                play_game = restart("Computer wins!\n");
            }

            else if (isTie()) {
                play_game = restart("Tie game!\n");
            }
        }
    }

    std::cout << "Thanks for playing!\n";
    return 0;
}
