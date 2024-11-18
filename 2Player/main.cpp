#include <iostream>
#include <string>
#include <vector>

using std::vector;

vector<vector<char>> board = {
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
    if (check_line(row, column, 1, 0) > 3) {
        return true;
    }
    // check horizontal
    else if (check_line(row, column, 0, 1) > 3) {
        return true;
    }
    // check NW-SE diagonal
    else if (check_line(row, column, 1, 1) > 3) {
        return true;
    }
    // check NE-SW diagonal
    else if (check_line(row, column, -1, 1) > 3) {
        return true;
    }
    return false;
}

// handles the placement of the current player's piece
bool placePiece(int column, char piece) {
    int i;

    for (i = 5; i >= 0; i--) {
        if (board[i][column] == '-') {
            board[i][column] = piece;
            break;
        }
    }

    return gameWon(i, column);
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
bool restart() {
    printBoard();

    char play_again;
    std::cout << "Play again? (y/n)\n";
    std::cin >> play_again;

    bool play_game = play_again == 'y' ? true : false;

    if (play_game) {
        board = {
            {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
            {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
            {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
            {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
            {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
            {'|', '-', '-', '-', '-', '-', '-', '-', '|'},
            {' ', '1', '2', '3', '4', '5', '6', '7', ' '}
        };
        return true;
    }

    return false;
}

int main() {
    std::cout << "Welcome to...\nConnect 4!!!\nEveryone knows how to play, so just input a number to begin!\n";

    bool play_game = true;
    int player = 1;
    int input;

    while (play_game) {
        printBoard();

        std::cin >> input;
        if (std::cin.fail()) { // checks if input is an integer
            std::cin.clear();
            std::cin.ignore(32767, '\n');
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }
        else if (input < 1 || input > 7) { // checks if input is within range
            std::cout << "Input out of range. Please try again.\n";
            continue;
        }
         else if (board[0][input] != '-') { // checks if column is full
            std::cout << "Column is full. Please try again.\n";
            continue;
        }

        bool game_status = placePiece(input, player == 1 ? 'X' : 'O');
        
        if (game_status) {
            std::cout << "Player " << player << " wins!\n";
            
            play_game = restart();
            player = 1;
        }
        else if (isTie()) {
            std::cout << "Tie game!\n";
            
            play_game = restart();
            player = 1;
        }
        else {
            player = player == 1 ? 2 : 1;
        }
    }

    std::cout << "Thanks for playing!\n";
}
