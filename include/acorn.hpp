#ifndef ACORN_H_
#define ACORN_H_

#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <stdexcept>

#include "sense-interface.hpp"
#include "string-utils.hpp"
#include "acorn-utils.hpp"
#include "inflection.hpp"
#include "pos-group.hpp"
#include "wn3-path.hpp"
#include "word-log.hpp"
#include "index.hpp"      

// relative path to project root from this file
#define PATH_TO_ROOT "../"

// UNIX-style line ending
#define UNIX_EOL '\n'

// Cmd line & GTK modes
#define ACORN_MODE_EXECMD 0
#define ACORN_MODE_EXEGTK 1

namespace jay_io
{

class Acorn
{
        public:
                Acorn(short);
                jay_io::Word_Log lookUpQuery(std::string);
                jay_io::Index binarySearchDataPOS(std::string, std::string);
                jay_io::Inflection binarySearchExcPOS(std::string, std::string);
        
        private:
                jay_io::Index returnIndexObjAtByteOffset_InStream_(int, std::fstream*);
                jay_io::Inflection returnInflectionObjAtByteOffset_InStream_(int, std::fstream*);
                // jay_io::Inflection returnInflectionObjBeforeByteOffset_InStream_(int, std::fstream*);
                // jay_io::Inflection returnInflectionObjAfterByteOffset_InStream_(int, std::fstream*);
                Sense_Interface returnSenseInterfaceObjAtByteOffset_InStream_(std::string, int, std::fstream*);
                std::vector<Sense_Interface> vectoriseSenseInterfaces(std::string, std::vector<int>*, std::fstream*);
};

Acorn::Acorn(short MODE = ACORN_MODE_EXECMD)
{
        if (MODE == ACORN_MODE_EXEGTK) {
                ;
        }
        else {
                ;
        }
}

jay_io::Word_Log Acorn::lookUpQuery(std::string query)
{
        struct matchRet { bool isMatchFound; std::map<char, jay_io::Index> idxObjMapMatch; };
        
        stringToLower(&query);
        replaceStringSpaceWithUscore(&query);

        auto searchIndexPOS = [&] (std::string query) -> matchRet {
                bool isMatchFound = true;
                std::map<char, jay_io::Index> entryMap;

                try {
                        std::string filename, pathToRoot = PATH_TO_ROOT, fileroot = WN3DB_IDX_POS_PATH;  
                        // iterate through all available index.pos files
                        for (auto i: {'n', 'v', 'a', 'r'}) {
                                filename = dataPosFileNameFromChar[i];
                                jay_io::Index entry = binarySearchDataPOS(query, pathToRoot + fileroot + filename);
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

                matchRet mr = {isMatchFound, entryMap};
                return mr;
        };

        auto searchExcPOS = [&] (std::string query) -> matchRet {
                bool isMatchFound = true;
                std::map<char, jay_io::Index> entryMap;

                try {
                        std::string excFilename, pathToRoot = PATH_TO_ROOT, 
                                        excFileroot = WN3DB_EXC_POS_PATH, dataFileroot = WN3DB_DAT_POS_PATH;  
                        // iterate through all available pos.exc files
                        for (auto i: {'n', 'v', 'a', 'r'}) {
                                excFilename = excPosFileNameFromChar[i];
                                jay_io::Inflection entry = binarySearchExcPOS(query, pathToRoot + excFileroot + excFilename);
                                if (!entry.isEmpty) {
                                        std::string dataFilename = dataPosFileNameFromChar[i];
                                        entryMap.insert({i, binarySearchDataPOS(entry.rootWords[0], pathToRoot + dataFileroot + dataFilename)});
                                }
                        }
                        if (entryMap.empty())
                                throw std::domain_error("Entry not found :(");
                }
                catch (const std::domain_error &e) {
                        isMatchFound = false;
                }

                matchRet mr = {isMatchFound, entryMap};
                return mr;
        };

        bool notFoundFlag = false;
        matchRet result = searchIndexPOS(query);

        if (!result.isMatchFound)
                result = searchExcPOS(query);
        else
                notFoundFlag = true;
        
        std::vector<jay_io::POS_Group> posGroups;
        if (!notFoundFlag) {
                for (auto i: {'n', 'v', 'a', 'r'}) {
                        std::string filepath = std::string(PATH_TO_ROOT) + std::string(WN3DB_DAT_POS_PATH) + dataPosFileNameFromChar[i];
                        std::fstream datapos(filepath.c_str(), std::ios::binary | std::ios::in);
                        posGroups.push_back({
                                parseSynsetTypeExpanded(&i),
                                {}, // write lookForInflections()
                                {}, // write lookForPronunciations()
                                vectoriseSenseInterfaces(query, &result.idxObjMapMatch[i].synsetOffsets, &datapos)
                        });
                }
        
                jay_io::Word_Log wordLog = {true, query, posGroups, {}};
                return wordLog;
        }
        else {
                std::vector<jay_io::POS_Group> nullPosGroups;
                jay_io::Word_Log wordLog = {false, query, nullPosGroups, {}};
                return wordLog;
        }
}

jay_io::Index Acorn::binarySearchDataPOS(std::string query, std::string filepath)
{
        std::fstream file(filepath, std::ios::binary | std::ios::in);
        
        auto returnFinalByteOffset = [] (std::fstream* f) -> int {
                (*f).seekg(0, std::ios::end);
                std::streampos pos = (*f).tellg();
                (*f).seekg(0);
                return pos;
        };

        auto returnFirstByteOffset = [] (std::fstream* f) -> std::streamoff {
                std::string s;
                std::streamoff tempOffset, startOffset;
                bool isStartByteFound = false;

                (*f).seekg(0);
                while (!isStartByteFound) {
                        std::streamoff tempOffset = (*f).tellg(); 
                        std::getline(*f, s, UNIX_EOL);
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
        std::streamoff start = returnFirstByteOffset(&file), stop = returnFinalByteOffset(&file);

        while (!isEntryFound) {
                int mean = (start + stop)/2;
                i = returnIndexObjAtByteOffset_InStream_(mean, &file);
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

        file.close();
        return t;
}

jay_io::Index Acorn::returnIndexObjAtByteOffset_InStream_(int offset, std::fstream *fs)
{
        bool isExtracted = false;
        std::string extr;
        char c = 0;
        int i = offset;

        while (!isExtracted) {
                (*fs).get(c);
                (*fs).clear();
                if (c == UNIX_EOL) {
                        std::getline(*fs, extr, UNIX_EOL);
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

jay_io::Inflection Acorn::binarySearchExcPOS(std::string query, std::string filepath)
{
        std::fstream file(filepath, std::ios::binary | std::ios::in);
        
        auto returnFinalByteOffset = [] (std::fstream* f) -> int {
                (*f).seekg(0, std::ios::end);
                std::streampos pos = (*f).tellg();
                (*f).seekg(0);
                return pos;
        };

        bool isEntryFound = false;
        jay_io::Inflection t, i;
        std::streamoff start = 0, stop = returnFinalByteOffset(&file);

        while (!isEntryFound) {
                int mean = (start + stop)/2;
                i = returnInflectionObjAtByteOffset_InStream_(mean, &file);
                int diff = strcmp(i.inflection.c_str(), query.c_str());

                if (diff < 0)
                        start = mean;
                
                else if (diff > 0)
                        stop = mean;
                
                else /* if (diff == 0) */ {
                        t = i;
                        isEntryFound = true;
                }
        }

        file.close();
        return t;
}

jay_io::Inflection Acorn::returnInflectionObjAtByteOffset_InStream_(int offset, std::fstream *fs)
{
        bool isExtracted = false;
        std::string extr;
        char c = 0;
        int i = offset;

        while (!isExtracted) {
                (*fs).get(c);
                (*fs).clear();
                if (c == UNIX_EOL) {
                        std::getline(*fs, extr, UNIX_EOL);
                        (*fs).clear();
                        isExtracted = true;
                }
                else {
                        i--;
                        (*fs).seekg(i);
                }
        }

        return jay_io::Inflection(extr);
}

Sense_Interface Acorn::returnSenseInterfaceObjAtByteOffset_InStream_(std::string word, int offset, std::fstream *fs)
{
        std::string extr;
        (*fs).seekg(offset);
        std::getline(*fs, extr, UNIX_EOL);
        (*fs).clear();
        return Sense_Interface(word, extr);
}

std::vector<Sense_Interface> Acorn::vectoriseSenseInterfaces(std::string query,std::vector<int> *voi, std::fstream *datapos)
{
        std::vector<Sense_Interface> ret;
        for (auto i: *voi)
                ret.push_back(returnSenseInterfaceObjAtByteOffset_InStream_(query, i, datapos));
        return ret;
}

}

#endif /* ACORN_H_ */
