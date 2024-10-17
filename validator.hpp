#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>
#include <cctype>
#include <vector>

class Validator {
public:
    // Function to check if input is valid
    static bool isValidInput(const std::string& input) {
        return input.length() == 1 && std::isdigit(input[0]) && std::stoi(input) >= 1 && std::stoi(input) <= 9;
    }

    // Function to check if a cell is already taken
    static bool isCellTaken(const std::vector<std::string>& board, int pos) {
        return board[pos - 1] == "X" || board[pos - 1] == "O";
    }
};

#endif // VALIDATOR_HPP

