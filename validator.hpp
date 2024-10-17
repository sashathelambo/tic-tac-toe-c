#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>
#include <cctype>
#include <vector>
#include <iostream>

class Validator {
public:
    // Function to check if input is valid
    static bool isValidInput(const std::string& input) {
        bool valid = input.length() == 1 && std::isdigit(input[0]) && std::stoi(input) >= 1 && std::stoi(input) <= 9;
        return valid;
    }

    // Function to check if a cell is already taken
    static bool isCellTaken(const std::vector<std::string>& board, int pos) {
        if (pos < 1 || pos > 9) {
            return true; // Consider invalid positions as taken
        }
        bool taken = board[pos - 1] == "X" || board[pos - 1] == "O";
        return taken;
    }
};

#endif 
