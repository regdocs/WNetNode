#ifndef WORD_INTERFACE_H_
#define WORD_INTERFACE_H_

#include <vector>
#include <string>

#include "Sense_Interface.h"
#include "String_Utils.h"
#include "WN3_Path.h"

namespace jay_io
{

class Acorn
{
};

Acorn::Acorn(std::string query)
{
        stringToLower(&query);
        replaceStringSpaceWithUscore(&query);

        bool isMatchFound = false;

}

}

#endif /* WORD_INTERFACE_H_ */