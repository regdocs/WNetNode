#include <vector>
#include <string>
#include <locale>
#include "String_Utils.h"

struct WordLexid {
        std::string word;
        int lexid;
};

struct Ptr {
        std::string pointerSymbol;
        int synsetOffset;
        std::string pos;
        std::string sourceTarget;
};

struct Frame {
        int frameNumber;
        int wordNumber;
};

class Sense
{
        private:
                int synsetOffset;
                
                std::string lexFilenum;
                std::string synsetType;
                int synCount;
                std::vector<WordLexid> wordLexidSet;
                
                int pointerCount;
                std::vector<Ptr> pointers;
                
                int frameCount;
                std::vector<Frame> frames;
                
                std::string gloss;
                std::vector<std::string> exampleSentences;
                
        public:
                /* constructor: */       Sense                 (std::string, bool);
                std::vector<std::string> fragmentDataRow       (std::string*);
                int                      parseSynsetOffset     (std::vector<std::string>*);
                std::string              parseLexFilenum       (std::vector<std::string>*);
                std::string              parseSynsetType       (std::vector<std::string>*);
                int                      parseSynCount         (std::vector<std::string>*);
                std::vector<WordLexid>   parseWordLexidSet     (std::vector<std::string>*);
                int                      parsePointerCount     (std::vector<std::string>*);
                std::vector<Ptr>         parsePointers         (std::vector<std::string>*);
                int                      parseFrameCount       (std::vector<std::string>*);
                std::vector<Frame>       parseFrames           (std::vector<std::string>*);
                std::string              parseGloss            (std::vector<std::string>*);
                std::vector<std::string> parseExampleSentences (std::vector<std::string>*);
};

Sense::Sense(std::string dataRow, bool isFileDataVerb)
        {
                std::vector<std::string> fragments = fragmentDataRow(&dataRow);
                
                this -> synsetOffset = parseSynsetOffset(&fragments);
                this -> lexFilenum = parseLexFilenum(&fragments);
                this -> synCount = parseSynCount(&fragments);
                this -> wordLexidSet = parseWordLexidSet(&fragments);
                
                this -> pointerCount = parsePointerCount(&fragments);
                this -> pointers = parsePointers(&fragments);
                
                if (isFileDataVerb) {
                        this -> frameCount = parseFrameCount(&fragments);
                        this -> frames = parseFrames(&fragments);
                }
                
                this -> gloss = parseGloss(&fragments);
                this -> exampleSentences = parseExampleSentences(&fragments);
        }

std::vector<std::string> Sense::fragmentDataRow(std::string *dataRow)
{
        /* parse data row into constituent data fragments */
        bool barPositionCrossed = false;
        std::string dataRowPrefix = "", dataRowPostfix = "";
        std::vector<std::string> fragments;

        // break data row into prefix and postfix sections w.r.t. the index of '|'
        for (int i = 0; i < (*dataRow).length(); i++) {
                if ((*dataRow)[i] == '|') {
                        barPositionCrossed = true;
                        continue;
                }
                if (!barPositionCrossed)
                        dataRowPrefix.push_back((*dataRow)[i]);
                else
                        dataRowPostfix.push_back((*dataRow)[i]);
        }

        // trim leading and trailing spaces
        trim(&dataRowPrefix);
        trim(&dataRowPostfix);

        // parse data row into constituent data fragments
        std::string fragment = "";
        for (int i = 0; i < dataRowPrefix.length(); i++) {
                if (dataRowPrefix[i] == ' ') {
                        trim(&fragment);
                        fragments.push_back(fragment);
                        fragment = "";
                        continue;
                }
                fragment.push_back(dataRowPrefix[i]);
        }

        trim(&fragment);
        fragments.push_back(fragment);
        fragment = "";

        for (int i = 0; i < dataRowPostfix.length(); i++) {
                if (dataRowPostfix[i] == ';') {
                        trim(&fragment);
                        fragments.push_back(fragment);
                        fragment = "";
                        continue;
                }
                fragment.push_back(dataRowPostfix[i]);
        }
}

std::vector 