#ifndef POS_GROUP_H_
#define POS_GROUP_H_

#include <string>
#include <vector>
#include "Sense_Interface.h"

namespace jay_io
{

struct POS_Group
{
        std::string prettyPos;
        std::vector<std::string> inflections;
        std::vector<std::string> pronunciation;
        std::vector<Sense_Interface> prettySenses;
};

}

#endif /* POS_GROUP_H_ */