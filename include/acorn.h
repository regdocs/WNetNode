#ifndef WORD_INTERFACE_H_
#define WORD_INTERFACE_H_

#include <vector>
#include <string>

#include "sense_interface.h"
#include "string_utils.h"
#include "wn3_path.h"

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
