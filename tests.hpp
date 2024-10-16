#include <iostream>
#include <vector>
#include <string>

using namespace std;

extern bool exitFlag;
extern bool returnToMenuFlag;

void resetBoard(vector<string>& board);
bool checkWin(const vector<string>& board, const string& marker);
bool isDraw(const vector<string>& board);

void runTests() {
    vector<string> board(9);
    resetBoard(board);

    for (int i = 0; i < 9; ++i) {
        if (exitFlag || returnToMenuFlag) return; // Exit if Esc or Menu is pressed
        if (board[i] != to_string(i + 1)) {
            cout << "Test 1 Failed: Initial board state is incorrect." << endl;
            return;
        }
    }
    cout << "Test 1 Passed: Initial board state is correct." << endl;

    board = {"X", "X", "X", "4", "5", "6", "7", "8", "9"};
    if (exitFlag || returnToMenuFlag) return; // Exit if Esc or Menu is pressed
    if (!checkWin(board, "X")) {
        cout << "Test 2 Failed: Win condition for rows is incorrect." << endl;
        return;
    }
    cout << "Test 2 Passed: Win condition for rows is correct." << endl;

    board = {"X", "2", "3", "X", "5", "6", "X", "8", "9"};
    if (exitFlag || returnToMenuFlag) return; // Exit if Esc or Menu is pressed
    if (!checkWin(board, "X")) {
        cout << "Test 3 Failed: Win condition for columns is incorrect." << endl;
        return;
    }
    cout << "Test 3 Passed: Win condition for columns is correct." << endl;

    board = {"X", "2", "3", "4", "X", "6", "7", "8", "X"};
    if (exitFlag || returnToMenuFlag) return; // Exit if Esc or Menu is pressed
    if (!checkWin(board, "X")) {
        cout << "Test 4 Failed: Win condition for diagonals is incorrect." << endl;
        return;
    }
    cout << "Test 4 Passed: Win condition for diagonals is correct." << endl;

    board = {"X", "O", "X", "X", "O", "O", "O", "X", "X"};
    if (exitFlag || returnToMenuFlag) return; // Exit if Esc or Menu is pressed
    if (!isDraw(board)) {
        cout << "Test 5 Failed: Draw condition is incorrect." << endl;
        return;
    }
    cout << "Test 5 Passed: Draw condition is correct." << endl;
}
