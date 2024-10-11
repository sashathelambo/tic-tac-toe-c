#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>
#include <atomic>
#include <cstdlib>
#include <ctime>

using namespace std;

atomic<bool> exitFlag(false);
atomic<bool> returnToMenuFlag(false);

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void displayBoard(const vector<string>& board) {
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 3; ++j) {
            if (board[i + j] == "X") {
                setColor(12); // Red for X
            } else if (board[i + j] == "O") {
                setColor(9); // Blue for O
            } else {
                setColor(7); // Default color for numbers
            }
            cout << board[i + j];
            setColor(7); // Reset to default color
            if (j < 2) cout << " | ";
        }
        cout << endl;
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
    for (int i = 0; i < 8; ++i) {
        if (board[winPatterns[i][0]] == marker && board[winPatterns[i][1]] == marker && board[winPatterns[i][2]] == marker) {
            return true;
        }
    }
    return false;
}

bool isDraw(const vector<string>& board) {
    for (int i = 0; i < 9; ++i) {
        if (board[i] != "X" && board[i] != "O") return false;
    }
    return true;
}

void resetBoard(vector<string>& board) {
    for (int i = 0; i < 9; ++i) {
        board[i] = to_string(i + 1);
    }
}

int getPlayerInput() {
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
                cout << ch << endl; // Echo the valid input
                return position;
            } else {
                setColor(12); // Red color for error message
                cout << "\nInvalid input. Please enter a number between 1 and 9: ";
                setColor(7); // Reset to default color
            }
        }
    }
}

int getComputerInput(const vector<string>& board) {
    // Predict the player's move and block it or try to win if possible
    for (int i = 0; i < 9; ++i) {
        if (board[i] != "X" && board[i] != "O") {
            vector<string> tempBoard = board;
            tempBoard[i] = "X";
            if (checkWin(tempBoard, "X")) {
                cout << i + 1 << endl; // Echo the computer's move
                return i + 1;
            }
            tempBoard[i] = "O";
            if (checkWin(tempBoard, "O")) {
                cout << i + 1 << endl; // Echo the computer's move
                return i + 1;
            }
        }
    }

    // If no prediction, make a random move
    srand(time(0));
    int pos;
    do {
        pos = rand() % 9 + 1;
    } while (isCellTaken(board, pos));
    cout << pos << endl; // Echo the computer's move
    return pos;
}

void playGame(bool isComputerOpponent) {
    vector<string> board(9);
    resetBoard(board);

    setColor(10); // Green color for welcome message
    cout << "Welcome to Tic-Tac-Toe! Player 1 is X, Player 2 is O. Let's begin!" << endl;
    setColor(11); // Light cyan color for exit message
    cout << "Press ESC at any time to exit the game." << endl;
    cout << "Press 'M' at any time to return to the menu." << endl;
    setColor(7); // Reset to default color
    displayBoard(board);

    string currentPlayer = "X";
    while (!exitFlag && !returnToMenuFlag) {
        int pos;
        bool validMove = false;

        while (!validMove && !exitFlag && !returnToMenuFlag) {
            setColor(14); // Yellow color for player prompt
            cout << "Player " << (currentPlayer == "X" ? "1 (X)" : "2 (O)") << ", choose a position (1-9): ";
            setColor(7); // Reset to default color

            if (currentPlayer == "O" && isComputerOpponent) {
                pos = getComputerInput(board);
            } else {
                pos = getPlayerInput();
            }

            if (pos == -1) {
                break;
            }

            if (isCellTaken(board, pos)) {
                setColor(12); // Red color for error message
                cout << "Cell already taken. Please choose another position." << endl;
                setColor(7); // Reset to default color
                continue;
            }

            validMove = true;
        }

        if (exitFlag || returnToMenuFlag) break;

        board[pos - 1] = currentPlayer;
        displayBoard(board);

        if (checkWin(board, currentPlayer)) {
            setColor(10); // Green color for win message
            cout << "Player " << (currentPlayer == "X" ? "1 (X)" : "2 (O)") << " wins!" << endl;
            setColor(7); // Reset to default color
            break;
        }

        if (isDraw(board)) {
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
}

void runTests() {
    vector<string> board(9);
    resetBoard(board);

    // Test 1: Check initial board state
    for (int i = 0; i < 9; ++i) {
        if (exitFlag || returnToMenuFlag) return; // Exit if Esc or Menu is pressed
        if (board[i] != to_string(i + 1)) {
            cout << "Test 1 Failed: Initial board state is incorrect." << endl;
            return;
        }
    }
    cout << "Test 1 Passed: Initial board state is correct." << endl;

    // Test 2: Check win condition for rows
    board = {"X", "X", "X", "4", "5", "6", "7", "8", "9"};
    if (exitFlag || returnToMenuFlag) return; // Exit if Esc or Menu is pressed
    if (!checkWin(board, "X")) {
        cout << "Test 2 Failed: Win condition for rows is incorrect." << endl;
        return;
    }
    cout << "Test 2 Passed: Win condition for rows is correct." << endl;

    // Test 3: Check win condition for columns
    board = {"X", "2", "3", "X", "5", "6", "X", "8", "9"};
    if (exitFlag || returnToMenuFlag) return; // Exit if Esc or Menu is pressed
    if (!checkWin(board, "X")) {
        cout << "Test 3 Failed: Win condition for columns is incorrect." << endl;
        return;
    }
    cout << "Test 3 Passed: Win condition for columns is correct." << endl;

    // Test 4: Check win condition for diagonals
    board = {"X", "2", "3", "4", "X", "6", "7", "8", "X"};
    if (exitFlag || returnToMenuFlag) return; // Exit if Esc or Menu is pressed
    if (!checkWin(board, "X")) {
        cout << "Test 4 Failed: Win condition for diagonals is incorrect." << endl;
        return;
    }
    cout << "Test 4 Passed: Win condition for diagonals is correct." << endl;

    // Test 5: Check draw condition
    board = {"X", "O", "X", "X", "O", "O", "O", "X", "X"};
    if (exitFlag || returnToMenuFlag) return; // Exit if Esc or Menu is pressed
    if (!isDraw(board)) {
        cout << "Test 5 Failed: Draw condition is incorrect." << endl;
        return;
    }
    cout << "Test 5 Passed: Draw condition is correct." << endl;
}

void showMenu();

int main() {
    while (!exitFlag) {
        returnToMenuFlag = false;
        showMenu();
    }
    return 0;
}

void showMenu() {
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
                return;
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
                return;
            } else {
                setColor(12); // Red color for error message
                cout << "Invalid choice. Please enter 1, 2, or M: ";
                setColor(7); // Reset to default color
            }
        }
    }

    while (!exitFlag && !returnToMenuFlag) {
        if (!exitFlag && !returnToMenuFlag) {
            runTests();
        }

        if (!exitFlag && !returnToMenuFlag) {
            playGame(isComputerOpponent);
        }

        if (!exitFlag && !returnToMenuFlag) {
            setColor(11); // Cyan color for play again prompt
            cout << "Do you want to play again? (y for yes, n for no, and m for menu): ";
            setColor(7); // Reset to default color
            char playAgain;
            cin >> playAgain;
            if (playAgain == 'n' || playAgain == 'N') {
                exitFlag = true;
            } else if (playAgain == 'm' || playAgain == 'M') {
                returnToMenuFlag = true;
            }
        }
    }
}