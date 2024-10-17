#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <iostream> // Added for debug output

class Validator {
public:
    // Function to check if input is valid
    static bool isValidInput(const std::string& input) {
        bool valid = input.length() == 1 && std::isdigit(input[0]) && std::stoi(input) >= 1 && std::stoi(input) <= 9;
        std::cout << "Debug: isValidInput(" << input << ") = " << valid << std::endl; // Debug output
        return valid;
    }

    // Function to check if a cell is already taken
    static bool isCellTaken(const std::vector<std::string>& board, int pos) {
        bool taken = board[pos - 1] == "X" || board[pos - 1] == "O";
        std::cout << "Debug: isCellTaken(board, " << pos << ") = " << taken << std::endl; // Debug output
        return taken;
    }
};

#endif // VALIDATOR_HPP
