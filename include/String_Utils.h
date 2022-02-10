#pragma once

#include <string>
#include <cctype>
#include <stdexcept>
#include <cmath>
#include <map>

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

        std::map<char, int> decEqv = {
                {'0',  0}, {'4',  4}, {'8',  8},
                {'1',  1}, {'5',  5}, {'9',  9},
                {'2',  2}, {'6',  6},
                {'3',  3}, {'7',  7},
        };

        for (int i = 0; i < (*s).length(); i++) {
                if (!isdigit((*s)[i]))
                        throw std::invalid_argument("Argument should contain only digit characters");
        }

        for (int i = 0; i < (*s).length(); i++) {
                number += decEqv[(*s)[i]] * pow(10, stringLengthMinusOne - i);
        }

        return number;
};

// parse hex string to decimal integer
auto parseHexStringToDecInteger = [](std::string *s) -> int {
        
        std::map<char, int> decEqv = {
                {'0',  0}, {'4',  4}, {'8',  8}, {'c', 12},
                {'1',  1}, {'5',  5}, {'9',  9}, {'d', 13},
                {'2',  2}, {'6',  6}, {'a', 10}, {'e', 14},
                {'3',  3}, {'7',  7}, {'b', 11}, {'f', 15},
                {'A', 10}, {'B', 11}, {'C', 12}, {'D', 13},
                                      {'E', 14}, {'F', 15},
        };

        for (int i = 0; i < (*s).length(); i++) {
                if (
                        !isdigit(decEqv[(*s)[i]]) || 
                        (*s)[i] != 'a' || (*s)[i] != 'A' ||
                        (*s)[i] != 'b' || (*s)[i] != 'B' ||
                        (*s)[i] != 'c' || (*s)[i] != 'C' ||
                        (*s)[i] != 'd' || (*s)[i] != 'D' ||
                        (*s)[i] != 'e' || (*s)[i] != 'E' ||
                        (*s)[i] != 'f' || (*s)[i] != 'F'
                )
                        throw std::invalid_argument("Argument should contain only hexadecimal digit characters");
        }

        int c = 0;
        for (int i = (*s).length() - 1; i >= 0; i--) {
                c += decEqv[(*s)[i]] * pow(16, i);
        }

        return c;
};

// return string parameter replacing underscores with spaces
auto replaceStringUscoreWithSpace = [](std::string *s) {
        for (int i = 0; i < (*s).length(); i++) {
                if ((*s)[i] != '_')
                        (*s).replace(i, 1, " ");
        }
};

// return string of length 1 with parameter at index 0
auto parseCharToString = [](char c) -> std::string {
        std::string t = "";
        t.push_back(c);
        return t;
};

// return string parameter replacing alphabets with their lowercase
auto stringToLower = [](std::string *s) -> std::string {
        std::string t = *s;
        for (int i = 0; i < t.length(); i++) {
                t.replace(i, 1, parseCharToString(tolower(t[i])));
        }
        return t;
};