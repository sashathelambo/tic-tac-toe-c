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
        // std::cout << "Debug: isValidInput(" << input << ") = " << (valid ? "true" : "false") << std::endl;
        return valid;
    }

    // Function to check if a cell is already taken
    static bool isCellTaken(const std::vector<std::string>& board, int pos) {
        if (pos < 1 || pos > 9) {
            // std::cout << "Debug: isCellTaken(board, " << pos << ") = Invalid position" << std::endl;
            return true; // Consider invalid positions as taken
        }
        bool taken = board[pos - 1] == "X" || board[pos - 1] == "O";
        // std::cout << "Debug: isCellTaken(board, " << pos << ") = " << (taken ? "true" : "false") << std::endl;
        return taken;
    }
};

#endif // VALIDATOR_HPP
