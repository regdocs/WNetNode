#include <string>

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