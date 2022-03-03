#ifndef WORD_INTERFACE_H_
#define WORD_INTERFACE_H_

// relative path to project root from this file
#define PATH_TO_ROOT "../"

// UNIX-style line ending
#define UNIX_EOL '\n'

#include <map>
#include <vector>
#include <string>
#include <cstring>
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
                jay_io::Index returnIndexObjAtByte_InStream_(int, std::fstream*);
};

std::map<char, jay_io::Index> Acorn::lookUpQuery(std::string query)
{
        std::map<char, jay_io::Index> entryMap;
        
        stringToLower(&query);
        replaceStringSpaceWithUscore(&query);

        bool isMatchFound = true;
        try {
                std::string filename, pathToRoot = PATH_TO_ROOT, fileroot = WN3DB_IDX_POS_PATH;
                
                // iterate through all available index.pos files
                for (auto i: {'n', 'v', 'a', 'r', 's'}) {
                        filename = posFile[i];
                        jay_io::Index entry = binarySearchPOS(query, pathToRoot + fileroot + filename);
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
        
        auto returnFinalByteOffset = [] (std::fstream* f) -> int {
                (*f).seekg(0, std::ios::end);
                std::streampos pos = (*f).tellg();
                (*f).seekg(0);
                return pos;
        };

        auto findStartByteOfIndexPOS = [] (std::fstream* f) -> std::streamoff {
                std::string s;
                std::streamoff tempOffset, startOffset;
                bool isStartByteFound = false;

                (*f).seekg(0);
                while (!isStartByteFound) {
                        std::streamoff tempOffset = (*f).tellg(); 
                        std::getline(*f, s, '\n');
                        (*f).clear();

                        if (s[0] == ' ' && s[1] == ' ')
                                continue;
                        else {
                                isStartByteFound = true;
                                startOffset = tempOffset;
                        }
                }

                (*f).seekg(0);
                return startOffset;
        };

        bool isEntryFound = false;
        jay_io::Index t, i;
        std::streamoff start = findStartByteOfIndexPOS(&file), stop = returnFinalByteOffset(&file);

        while (!isEntryFound) {
                int mean = (start + stop)/2;
                i = returnIndexObjAtByte_InStream_(mean, &file);
                int diff = strcmp(i.lemma.c_str(), query.c_str());

                if (diff < 0)
                        start = mean;
                
                else if (diff > 0)
                        stop = mean;
                
                else /* if (diff == 0) */ {
                        t = i;
                        isEntryFound = true;
                }
        }

        return t;
}

jay_io::Index Acorn::returnIndexObjAtByte_InStream_(int offset, std::fstream *fs)
{
        bool isExtracted = false;
        std::string extr;
        char c = 0;
        int i = offset;

        while (!isExtracted) {
                (*fs).get(c);
                (*fs).clear();
                if (c == '\n') {
                        std::getline(*fs, extr, '\n');
                        (*fs).clear();
                        isExtracted = true;
                }
                else {
                        i--;
                        (*fs).seekg(i);
                }
        }

        return jay_io::Index(extr);
}

}

#endif /* WORD_INTERFACE_H_ */
