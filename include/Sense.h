#include <vector>
#include <string>
#include <locale>
#include "String_Utils.h"

const auto SYNSET_OFFSET_IDX = 0;
const auto LEX_FILENUM_IDX = 1;


struct WordLexid {
        std::string word;
        int lexid;
};

struct Ptr {
        std::string pointerSymbol;
        int synsetOffset;
        std::string pos;
        std::string source;
        std::string target;
};

struct Frame {
        int frameNumber;
        int wordNumber;
};

class Sense
{
        private:
                // from [std::string] synset_offset
                int synsetOffset;
                // from [std::string] lex_filenum
                std::string lexFile;
                // from [std::string] synset_type
                std::string synsetType;
                // from [std::string] syn_count
                int synCount;
                // from [std::string] word and [std::string] lex_id
                std::vector<WordLexid> wordLexidSet;
                // from [std::string] p_cnt
                int pointerCount;
                // from [std::string] pointer_symbol, [std::string] synset_offset, [std::string] pos and [std::string] source/target
                std::vector<Ptr> pointers;
                // from [std::string] f_cnt
                int frameCount;
                // from [std::string] f_num and [std::string] w_num
                std::vector<Frame> frames;
                // from [std::string] gloss
                std::string def;
                // from [std::string] gloss
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
                this -> lexFile = parseLexFilenum(&fragments);
                this -> synCount = parseSynCount(&fragments);
                this -> wordLexidSet = parseWordLexidSet(&fragments);
                
                this -> pointerCount = parsePointerCount(&fragments);
                this -> pointers = parsePointers(&fragments);
                
                if (isFileDataVerb) {
                        this -> frameCount = parseFrameCount(&fragments);
                        this -> frames = parseFrames(&fragments);
                }
                
                this -> def = parseGloss(&fragments);
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

int Sense::parseSynsetOffset(std::vector<std::string> *fragments)
{
        /* parse string synset offset to integer */
        auto l_synsetOffset = (*fragments)[SYNSET_OFFSET_IDX];
        return parseStringToInteger(&l_synsetOffset);
}

std::string Sense::parseLexFilenum(std::vector<std::string> *fragments)
{
        /* parse and read lex_filenum and spit corresponding lexicographer file name */
        auto parsedLexFilenum = parseStringToInteger(&(*fragments)[LEX_FILENUM_IDX]);
        switch (parsedLexFilenum)
        {
        case 0:  return "adj.all";
        case 1:  return "adj.pert";
        case 2:  return "adv.all";
        case 3:  return "noun.Tops";
        case 4:  return "noun.act";
        case 5:  return "noun.animal";
        case 6:  return "noun.artifact";
        case 7:  return "noun.attribute";
        case 8:  return "noun.body";
        case 9:  return "noun.cognition";
        case 10: return "noun.communication";
        case 11: return "noun.event";
        case 12: return "noun.feeling";
        case 13: return "noun.food";
        case 14: return "noun.group";
        case 15: return "noun.location";
        case 16: return "noun.motive";
        case 17: return "noun.object";
        case 18: return "noun.person";
        case 19: return "noun.phenomenon";
        case 20: return "noun.plant";
        case 21: return "noun.possession";
        case 22: return "noun.process";
        case 23: return "noun.quantity";
        case 24: return "noun.relation";
        case 25: return "noun.shape";
        case 26: return "noun.state";
        case 27: return "noun.substance";
        case 28: return "noun.time";
        case 29: return "verb.body";
        case 30: return "verb.change";
        case 31: return "verb.cognition";
        case 32: return "verb.communication";
        case 33: return "verb.competition";
        case 34: return "verb.consumption";
        case 35: return "verb.contact";
        case 36: return "verb.creation";
        case 37: return "verb.emotion";
        case 38: return "verb.motion";
        case 39: return "verb.perception";
        case 40: return "verb.possession";
        case 41: return "verb.social";
        case 42: return "verb.stative";
        case 43: return "verb.weather";
        case 44: return "adj.ppl";
        }
}