#ifndef INDEX_H_
#define INDEX_H_

#include <string>
#include <vector>
#include <iostream>

#include "wn3_path.h"
#include "acorn_utils.h"
#include "string_utils.h"

namespace jay_io
{

class Index
{
        private:
                std::vector<std::string> fragmentDataRow(std::string*);
                std::string parseLemma(std::vector<std::string>*);
                std::string parsePos(std::vector<std::string>*);
                int parseSynsetCount(std::vector<std::string>*);
                int parsePointerCount(std::vector<std::string>*);
                std::vector<std::string> parsePointerSymbols(std::vector<std::string>*);
                int parseTagsenseCount(std::vector<std::string>*);
                std::vector<int> parseSynsetOffsets(std::vector<std::string>*);

        public:
                // standard container for the space separated dataRow components
                std::vector<std::string> fragments;
                // from [std::string] lemma
                std::string lemma;
                // from [std::string] pos
                std::string posFilename;
                // from [std::string] synset_cnt
                int synsetCount;
                // from [std::string] p_cnt
                int pointerCount;
                // from [std:string] [ptr_symbols...]
                std::vector<std::string> pointerSymbols;
                // from [std::string] sense_cnt (= synset_cnt above)
                int senseCount;
                // from [std::string] tagsense_count
                int tagsenseCount;
                // from [std::string] [synset_offset...]
                std::vector<int> synsetOffsets;

                Index(std::string);
                void previewIndex(void);
};

Index::Index(std::string dataRow)
{
        this -> fragments = fragmentDataRow(&dataRow);
        this -> lemma = parseLemma(&fragments);
        this -> posFilename = parsePos(&fragments);
        this -> synsetCount = parseSynsetCount(&fragments);
        this -> pointerCount = parsePointerCount(&fragments);
        this -> pointerSymbols = parsePointerSymbols(&fragments);
        this -> senseCount = synsetCount;
        this -> tagsenseCount = parseTagsenseCount(&fragments);
        this -> synsetOffsets = parseSynsetOffsets(&fragments);
}

std::vector<std::string> Index::fragmentDataRow(std::string *dataRow)
{
        /* parse data row into constituent data fragments */
        std::string fragment = "";
        std::vector<std::string> fragments;

        for (int i = 0; i < (*dataRow).length(); i++) {
                if ((*dataRow)[i] == ' ') {
                        trim(&fragment);
                        fragments.push_back(fragment);
                        fragment = "";
                        continue;
                }
                fragment.push_back((*dataRow)[i]);
        }
        trim(&fragment);
        fragments.push_back(fragment);
        return fragments;
}

std::string Index::parseLemma(std::vector<std::string> *fragments)
{
        return (*fragments)[0];
}

std::string Index::parsePos(std::vector<std::string> *fragments)
{
        std::string addr = WN3DB_IDX_POS_PATH;
        return addr + posFile[(*fragments)[1][0]];
}

int Index::parseSynsetCount(std::vector<std::string> *fragments)
{
        return parseStringToInteger(&(*fragments)[2]);
}

int Index::parsePointerCount(std::vector<std::string> *fragments)
{
        return parseStringToInteger(&(*fragments)[3]);
}

std::vector<std::string> Index::parsePointerSymbols(std::vector<std::string> *fragments)
{
        std::vector<std::string> p;
        for (int i = 0; i < this -> pointerCount; i++) {
                p.push_back((*fragments)[4 + i]);
        }
        return p;
}

int Index::parseTagsenseCount(std::vector<std::string> *fragments)
{
        return parseStringToInteger(&(*fragments)[5 + pointerCount]);
}

std::vector<int> Index::parseSynsetOffsets(std::vector<std::string> *fragments)
{
        std::vector<int> soff;
        for (int i = 0; i < this -> synsetCount; i++) {
                soff.push_back(parseStringToInteger(&(*fragments)[6 + pointerCount + i]));
        }
        return soff;
}

void Index::previewIndex()
{
        using namespace std;
        for (auto i: this -> fragments) {
                cout << i << " ";
        }
        cout << endl;
        cout << this -> lemma << endl;
        cout << this -> posFilename << endl;
        cout << this -> synsetCount << endl;
        cout << this -> pointerCount << endl;
        for (auto i: this -> pointerSymbols) {
                cout << i << " ";
        }
        cout << endl;
        cout << this -> senseCount << endl;
        cout << this -> tagsenseCount << endl;
        for (auto i: this -> synsetOffsets) {
                cout << i << " ";
        }
        cout << endl;
}

}

#endif /* INDEX_H_ */