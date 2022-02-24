#ifndef WORD_LOG_H_
#define WORD_LOG_H_

#include <vector>
#include <string>

#include "sense_interface.h"
#include "string_utils.h"
#include "pos_group.h"
#include "wn3_path.h"

namespace jay_io
{

class Word_Log
{
	public:
		std::string word;
                std::vector<POS_Group> posGroups;
        
        private:
                jay_io::Disambiguation lookUp(std::string, bool*);
};

}

#endif /* WORD_LOG_H_ */