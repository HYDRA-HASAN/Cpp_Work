#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void printBoard(char board[3][3]);
bool isMoveValid(int row, int col, char board[3][3]);
bool isBoardFull(char board[3][3]);
bool checkWin(char board[3][3], char player);
void playerMove(char board[3][3]);
void computerMove(char board[3][3]);
int main() {
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    srand(static_cast<unsigned int>(time(nullptr))); 
    while (true) {
        printBoard(board);
        playerMove(board);
        if (checkWin(board, 'X')) {
            cout << "Congratulations! You win!" << endl;
            break;
        }
        if (isBoardFull(board)) {
            cout << "It's a draw!" << endl;
            break;
        }
        printBoard(board);
        computerMove(board);
        if (checkWin(board, 'O')) {
            cout << "Sorry, you lose. Try again!" << endl;
            break;
        }
        if (isBoardFull(board)) {
            cout << "It's a draw!" << endl;
            break;
        }
    }
    return 0;
}
void printBoard(char board[3][3]) {
    cout << "  1 2 3" << endl;
    for (int i = 0; i < 3; ++i) {
        cout << i + 1 << " ";
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << "|";
        }
        cout << endl;
        if (i < 2) cout << "  -----" << endl;
    }
    cout << endl;
}
bool isMoveValid(int row, int col, char board[3][3]) {
    return (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ');
}
bool isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}
bool checkWin(char board[3][3], char player) {
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;
    return false;
}
void playerMove(char board[3][3]) {
    int row, col;
    cout << "Enter your move (row and column): ";
    cin >> row >> col;
    while (!isMoveValid(row - 1, col - 1, board)) {
        cout << "Invalid move! Try again: ";
        cin >> row >> col;
    }
    board[row - 1][col - 1] = 'X';
}
void computerMove(char board[3][3]) {
    cout << "Computer's move:" << endl;
    int row, col;
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while (!isMoveValid(row, col, board));
    board[row][col] = 'O';
}