#ifndef WORD_INTERFACE_H_
#define WORD_INTERFACE_H_

#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

#include "sense_interface.h"
#include "string_utils.h"
#include "wn3_path.h"
#include "index.h"

namespace jay_io
{

class Acorn
{
        public:
                std::map<char, jay_io::Index> lookUpQuery(std::string);
                jay_io::Index binarySearchPOS(std::string, std::string);

                Acorn();
        
        private:
                std::string returnDatarowAtByte(int);
};

Acorn::Acorn()
{}

std::map<char, jay_io::Index> Acorn::lookUpQuery(std::string query)
{
        std::map<char, jay_io::Index> entryMap;
        
        stringToLower(&query);
        replaceStringSpaceWithUscore(&query);

        bool isMatchFound = true;
        try {
                std::string filename, fileroot = WN3DB_IDX_POS_PATH;
                
                // iterate through all available index.pos files
                for (auto i: {'n', 'v', 'a', 'r', 's'}) {
                        filename = posFile[i];
                        jay_io::Index entry = binarySearchPOS(query, fileroot + filename);
                        if (!entry.isEmpty) {
                                entryMap.insert({i, entry});
                        }
                }

                if (entryMap.empty())
                        throw std::domain_error("Entry not found :(");
        }
        catch (const std::domain_error &e) {
                isMatchFound = false;
        }
}

jay_io::Index Acorn::binarySearchPOS(std::string query, std::string filepath)
{
        std::fstream file(filepath, std::ios::binary | std::ios::in);
        
        auto tellFilesize = [] (std::fstream* f) -> int {
                (*f).seekg(0, std::ios::end);
                return (*f).tellg();
        };

        int filesize = tellFilesize(&file);
        
}

}

#endif /* WORD_INTERFACE_H_ */
