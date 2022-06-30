#include "../include/acorn.hpp"
int main()
{
        while (true) {
                std::cout << "\x1b[34;1mEnter query: \x1b[0m ";
                std::string query;
                std::getline(std::cin, query);
                jay_io::Acorn acorn(ACORN_MODE_EXECMD);
                acorn.lookUpQuery(query).previewWordLog();
        }
}