#include "../include/acorn.hpp"
int main()
{
        while (true) {
                std::cout << "Enter query +:> ";
                std::string query;
                std::getline(std::cin, query);
                jay_io::Acorn acorn(ACORN_MODE_EXECMD);
                acorn.lookUpQuery(query).previewWordLog();
        }
}