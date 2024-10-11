#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <conio.h>

using namespace std;

void displayBoard(const vector<string>& board) {
    for (int i = 0; i < 9; i += 3) {
        cout << board[i] << " | " << board[i + 1] << " | " << board[i + 2] << endl;
        if (i < 6) cout << "---------" << endl;
    }
}

bool isValidInput(const string& input) {
    if (input.length() != 1 || !isdigit(input[0])) return false;
    int pos = stoi(input);
    return pos >= 1 && pos <= 9;
}

bool isCellTaken(const vector<string>& board, int pos) {
    return board[pos - 1] == "X" || board[pos - 1] == "O";
}

bool checkWin(const vector<string>& board, const string& marker) {
    const int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6}             // diagonals
    };
    for (const auto& pattern : winPatterns) {
        if (board[pattern[0]] == marker && board[pattern[1]] == marker && board[pattern[2]] == marker) {
            return true;
        }
    }
    return false;
}

bool isDraw(const vector<string>& board) {
    for (const auto& cell : board) {
        if (cell != "X" && cell != "O") return false;
    }
    return true;
}

void resetBoard(vector<string>& board) {
    for (int i = 0; i < 9; ++i) {
        board[i] = to_string(i + 1);
    }
}

int main() {
    vector<string> board(9);
    resetBoard(board);

    cout << "Welcome to Tic-Tac-Toe! Player 1 is X, Player 2 is O. Let's begin!" << endl;
    displayBoard(board);

    string currentPlayer = "X";
    while (true) {
        string input;
        int pos;
        bool validMove = false;

        while (!validMove) {
            cout << "Player " << (currentPlayer == "X" ? "1 (X)" : "2 (O)") << ", choose a position (1-9): ";
            cin >> input;

            if (!isValidInput(input)) {
                cout << "Invalid input. Please enter a number (1-9)." << endl;
                continue;
            }

            pos = stoi(input);
            if (isCellTaken(board, pos)) {
                cout << "Cell already taken. Please choose another position." << endl;
                continue;
            }

            validMove = true;
        }

        board[pos - 1] = currentPlayer;
        displayBoard(board);

        if (checkWin(board, currentPlayer)) {
            cout << "Player " << (currentPlayer == "X" ? "1 (X)" : "2 (O)") << " wins!" << endl;
            break;
        }

        if (isDraw(board)) {
            cout << "It's a draw!" << endl;
            break;
        }

        currentPlayer = (currentPlayer == "X") ? "O" : "X";
    }

    cout << "Press any key to continue or Esc to exit..." << endl;
    char key = _getch();
    if (key == 27) { // 27 is the ASCII code for the Esc key
        return 0;
    } else {
        resetBoard(board);
        main();
    }

    return 0;
}
