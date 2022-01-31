#include <string>
#include <cctype>
#include <stdexcept>
#include <cmath>

// left-trim string
auto leftTrim = [](std::string *s) {
        for (int i = 0; (*s)[i] == ' '; i++) {
                (*s).erase(i, 1);
        }
};

// right-trim string
auto rightTrim = [](std::string *s) {
        for (int i = (*s).length() - 1; (*s)[i] == ' '; i--) {
                (*s).erase(i, 1);
        }
};

// left-trim and right-trim string
auto trim = [](std::string *s) {
        for (int i = 0; (*s)[i] == ' '; i++) {
                (*s).erase(i, 1);
        }
        for (int i = (*s).length() - 1; (*s)[i] == ' '; i--) {
                (*s).erase(i, 1);
        }
};

// parse string to integer
auto parseStringToInteger = [](std::string *s) -> int {
        int number = 0, stringLengthMinusOne = (*s).length() - 1;

        for (int i = 0; i < (*s).length(); i++) {
                if (!isdigit((*s)[i]))
                        throw std::invalid_argument("Argument should contain only digit characters");
        }

        for (int i = 0; i < (*s).length(); i++) {
                number += (*s)[i] * pow(10, stringLengthMinusOne - i);
        }

        return number;
};