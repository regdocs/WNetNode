#include "../include/acorn.hpp"
int main()
{
        jay_io::Acorn acorn(ACORN_MODE_EXECMD);
        acorn.lookUpQuery("act").previewWordLog();
}