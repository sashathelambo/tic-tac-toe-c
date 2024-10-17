#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <memory>

//https://gist.github.com/JBlond/2fea43a3049b38287e5e9cefc87b2124

using namespace std;

// Global flags for exiting and returning to menu
bool exitFlag = false;
bool returnToMenuFlag = false;

// Function to set console text color without using windows.h
int setColor(int color) {
    if (color == 12) { // Red for X
        cout << "\033[31m";
    } else if (color == 9) { // Blue for O
        cout << "\033[34m";
    } else if (color == 7) { // Default color for numbers
        cout << "\033[0m";
    } else if (color == 10) { // Green for welcome message
        cout << "\033[32m";
    } else if (color == 11) { // Cyan for menu message
        cout << "\033[36m";
    } else if (color == 14) { // Yellow for player prompt and draw message
        cout << "\033[33m";
    }
    return 0;
}

// Function to display the Tic-Tac-Toe board
int displayBoard(const vector<string>& board) {
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 3; ++j) {
            setColor(board[i + j] == "X" ? 12 : board[i + j] == "O" ? 9 : 7);
            cout << board[i + j];
            setColor(7); // Reset to default color
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 6) cout << "---------" << endl;
    }
    return 0;
}

// Function to check if input is valid
bool isValidInput(const string& input) {
    return input.length() == 1 && isdigit(input[0]) && stoi(input) >= 1 && stoi(input) <= 9;
}

// Function to check if a cell is already taken
bool isCellTaken(const vector<string>& board, int pos) {
    return board[pos - 1] == "X" || board[pos - 1] == "O";
}

// Function to check if a player has won
bool checkWin(const vector<string>& board, const string& marker) {
    int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6}             // diagonals
    };
    for (int i = 0; i < 8; i++) {
        if (board[winPatterns[i][0]] == marker && board[winPatterns[i][1]] == marker && board[winPatterns[i][2]] == marker) {
            return true;
        }
    }
    return false;
}

// Function to check if the game is a draw
bool isDraw(const vector<string>& board) {
    for (int i = 0; i < 9; i++) {
        if (board[i] != "X" && board[i] != "O") {
            return false;
        }
    }
    return true;
}

// Function to reset the board
int resetBoard(vector<string>& board) {
    for (int i = 0; i < 9; ++i) {
        board[i] = to_string(i + 1);
    }
    return 0;
}

// Function to get player input
int getPlayerInput(const vector<string>& board) {
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 27) { // ESC key
                exitFlag = true;
                setColor(12); // Red color for exit message
                cout << "ESC clicked. Exiting the game..." << endl;
                setColor(7); // Reset to default color
                return -1;
            }
            if (ch == 'm' || ch == 'M') { // Menu key
                returnToMenuFlag = true;
                setColor(11); // Cyan color for menu message
                cout << "Menu clicked. Returning to menu..." << endl;
                setColor(7); // Reset to default color
                return -1;
            }
            if (ch >= '1' && ch <= '9') {
                int position = ch - '0';
                if (!isCellTaken(board, position)) {
                    cout << ch << endl; // Echo the valid input
                    return position;
                } else {
                    setColor(12); // Red color for error message
                    cout << "\nCell already taken. Please choose another position: ";
                    setColor(7); // Reset to default color
                }
            } else {
                setColor(12); // Red color for error message
                cout << "\nInvalid input. Please enter a number between 1 and 9: ";
                setColor(7); // Reset to default color
            }
        }
    }
}

// Function to get computer input
int getComputerInput(const vector<string>& board) {
    srand(time(0));
    int pos;
    do {
        pos = rand() % 9 + 1;
    } while (isCellTaken(board, pos));
    cout << pos << endl; // Echo the computer's move
    return pos;
}

// Function to play the game
int playGame(bool isComputerOpponent) {
    auto board = make_unique<vector<string>>(9);
    resetBoard(*board);

    setColor(10); // Green color for welcome message
    cout << "Welcome to Tic-Tac-Toe! Player 1 is X, Player 2 is O. Let's begin!" << endl;
    setColor(11); // Light cyan color for exit message
    cout << "Press ESC at any time to exit the game." << endl;
    cout << "Press 'M' at any time to return to the menu." << endl;
    setColor(7); // Reset to default color
    displayBoard(*board);

    string currentPlayer = "X";
    while (!exitFlag && !returnToMenuFlag) {
        int pos;
        bool validMove = false;

        while (!validMove && !exitFlag && !returnToMenuFlag) {
            setColor(14); // Yellow color for player prompt
            cout << "Player " << (currentPlayer == "X" ? "1 (X)" : "2 (O)") << ", choose a position (1-9): ";
            setColor(7); // Reset to default color

            // Display available cells
            cout << "Available cells: ";
            for (int i = 0; i < 9; ++i) {
                if ((*board)[i] != "X" && (*board)[i] != "O") {
                    cout << (*board)[i] << " ";
                }
            }
            cout << endl;

            if (currentPlayer == "O" && isComputerOpponent) {
                pos = getComputerInput(*board);
            } else {
                pos = getPlayerInput(*board);
            }

            if (pos == -1) {
                break;
            }

            if (isCellTaken(*board, pos)) {
                setColor(12); // Red color for error message
                cout << "Cell already taken. Please choose another position." << endl;
                setColor(7); // Reset to default color
                continue;
            }

            validMove = true;
        }

        if (exitFlag || returnToMenuFlag) break;

        (*board)[pos - 1] = currentPlayer;
        displayBoard(*board);

        if (checkWin(*board, currentPlayer)) {
            setColor(10); // Green color for win message
            cout << "Player " << (currentPlayer == "X" ? "1 (X)" : "2 (O)") << " wins!" << endl;
            setColor(7); // Reset to default color
            break;
        }

        if (isDraw(*board)) {
            setColor(14); // Yellow color for draw message
            cout << "It's a draw!" << endl;
            setColor(7); // Reset to default color
            break;
        }

        currentPlayer = (currentPlayer == "X") ? "O" : "X";
    }

    if (!exitFlag && !returnToMenuFlag) {
        setColor(11); // Cyan color for exit message
        cout << "Press any key to continue..." << endl;
        setColor(7); // Reset to default color
        _getch(); // Wait for any key press
    }
    return 0;
}

// Function to show the menu
int showMenu() {
    char choice;
    bool isComputerOpponent = false;

    setColor(11); // Cyan color for the prompt
    cout << "Do you want to play against the computer or another player?" << endl;
    cout << "1. Play against the computer" << endl;
    cout << "2. Play against another player" << endl;
    cout << "Enter your choice (1 or 2, ESC to exit or M to go back to menu): ";
    setColor(7); // Reset to default color
    while (true) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 27) { // ESC key
                exitFlag = true;
                setColor(12); // Red color for exit message
                cout << "ESC clicked. Exiting the game..." << endl;
                setColor(7); // Reset to default color
                return 0;
            }
            if (ch == '1') {
                isComputerOpponent = true;
                break;
            } else if (ch == '2') {
                isComputerOpponent = false;
                break;
            } else if (ch == 'm' || ch == 'M') {
                returnToMenuFlag = true;
                setColor(11); // Cyan color for menu message
                cout << "Menu clicked. Returning to menu..." << endl;
                setColor(7); // Reset to default color
                return 0;
            } else {
                setColor(12); // Red color for error message
                cout << "Invalid choice. Please enter 1, 2, or M or esc: ";
                setColor(7); // Reset to default color
            }
        }
    }

    while (!exitFlag && !returnToMenuFlag) {
        if (!exitFlag && !returnToMenuFlag) {
            playGame(isComputerOpponent);
        }

        if (!exitFlag && !returnToMenuFlag) {
            setColor(11); // Cyan color for play again prompt
            cout << "Do you want to play again? (y for yes, n for no, and m for menu, ESC to exit): ";
            setColor(7); // Reset to default color
            char playAgain;
            while (true) {
                if (_kbhit()) {
                    playAgain = _getch();
                    if (playAgain == 'n' || playAgain == 'N') {
                        exitFlag = true;
                        break;
                    } else if (playAgain == 'm' || playAgain == 'M') {
                        returnToMenuFlag = true;
                        break;
                    } else if (playAgain == 27) { // ESC key
                        exitFlag = true;
                        break;
                    } else if (playAgain == 'y' || playAgain == 'Y') {
                        break;
                    } else {
                        setColor(12); // Red color for error message
                        cout << "Invalid choice. Please enter y, n, m, or ESC: ";
                        setColor(7); // Reset to default color
                    }
                }
            }
        }
    }
    return 0;
}

int main() {
    while (!exitFlag) {
        returnToMenuFlag = false;
        showMenu();
    }
    return 0;
}