#ifndef WORD_LOG_H_
#define WORD_LOG_H_

#include <vector>
#include <string>

#include "Sense_Interface.h"
#include "String_Utils.h"
#include "POS_Group.h"
#include "WN3_Path.h"

namespace jay_io
{

class Word_Log
{
	public:
		std::string word;
                std::vector<POSGroup> posGroups;
        
        private:
                jay_io::Disambiguation lookUp(std::string, bool*);
};

}

#endif /* WORD_LOG_H_ */