#include <vector>
#include <string>
#include <locale>
#include "String_Utils.h"

#define SYNSET_OFFSET_IDX 0
#define LEX_FILENUM_IDX 1
#define SYNSET_TYPE_IDX 2
#define SYNSET_COUNT_IDX 3
#define WORD_LEXID_SET_START_IDX 4
#define SRC_SRCTARGET_IDX 0
#define SRC_SRCTARGET_LEN 2
#define TARGET_SRCTARGET_IDX 2
#define TARGET_SRCTARGET_LEN 2

struct WordLexidGroup {
        std::string word;
        int lexid;
};

struct Pointer {
        std::string pointerSymbol;
        int synsetOffset;
        std::string pos;
        int source;
        int target;
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
                // from [std::string] ss_type
                std::string synsetType;
                // from [std::string] syn_count
                int synCount;
                // from [std::string] word and [std::string] lex_id
                std::vector<WordLexidGroup> wordLexidGroupVector;
                // from [std::string] p_cnt
                int pointerCount;
                // from [std::string] pointer_symbol, [std::string] synset_offset, [std::string] pos and [std::string] source/target
                std::vector<Pointer> pointers;
                // from [std::string] f_cnt
                int frameCount;
                // from [std::string] f_num and [std::string] w_num
                std::vector<Frame> frames;
                // from [std::string] gloss
                std::string def;
                // from [std::string] gloss
                std::vector<std::string> exampleSentences;
                
        public:
                /* constructor: */          Sense                 (std::string);
                std::vector<std::string>    fragmentDataRow       (std::string*);
                int                         parseSynsetOffset     (std::vector<std::string>*);
                std::string                 parseLexFilenum       (std::vector<std::string>*);
                std::string                 parseSynsetType       (std::vector<std::string>*);
                int                         parseSynCount         (std::vector<std::string>*);
                std::vector<WordLexidGroup> parseWordLexidGroup   (std::vector<std::string>*);
                int                         parsePointerCount     (std::vector<std::string>*);
                std::vector<Pointer>        parsePointers         (std::vector<std::string>*);
                int                         parseFrameCount       (std::vector<std::string>*);
                std::vector<Frame>          parseFrames           (std::vector<std::string>*);
                std::string                 parseDefinition       (std::vector<std::string>*);
                std::vector<std::string>    parseExampleSentences (std::vector<std::string>*);
};

Sense::Sense(std::string dataRow)
        {
                std::vector<std::string> fragments = fragmentDataRow(&dataRow);

                this -> synsetOffset = parseSynsetOffset(&fragments);
                this -> lexFile = parseLexFilenum(&fragments);

                this -> synsetType = parseSynsetType(&fragments);
                this -> synCount = parseSynCount(&fragments);
                this -> wordLexidGroupVector = parseWordLexidGroup(&fragments);
                
                this -> pointerCount = parsePointerCount(&fragments);
                this -> pointers = parsePointers(&fragments);
                
                if (lexFile == "data.verb") {
                        this -> frameCount = parseFrameCount(&fragments);
                        this -> frames = parseFrames(&fragments);
                }
                
                this -> def = parseDefinition(&fragments);
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
        return fragments;
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
        switch (parsedLexFilenum) {
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

std::string Sense::parseSynsetType(std::vector<std::string> *fragments)
{
        /* parse string synset_type and spit expanded form */
        char l_synsetType = (*fragments)[SYNSET_TYPE_IDX][0];
        switch (l_synsetType) {
                case 'n': return "noun";
                case 'v': return "verb";
                case 'a': return "adjective";
                case 'r': return "adverb";
                case 's': return "adjective satellite";
        }
}

int Sense::parseSynCount(std::vector<std::string> *fragments)
{
        /* parse string ss_count and spit its integer form */
        return parseStringToInteger(&(*fragments)[SYNSET_COUNT_IDX]);
}

std::vector<WordLexidGroup> Sense::parseWordLexidGroup(std::vector<std::string> *fragments)
{
        /* parse word and lex_id value groups into structures and spit their vector */
        std::vector<WordLexidGroup> l_wordLexidGroupVector;
        for (int i = 0; i < synCount; i++) {
                WordLexidGroup set = {
                        (*fragments)[WORD_LEXID_SET_START_IDX + 2*i],
                        parseStringToInteger(&(*fragments)[WORD_LEXID_SET_START_IDX + 2*i + 1])
                };
                l_wordLexidGroupVector.push_back(set);
        }
        return l_wordLexidGroupVector;
}

int Sense::parsePointerCount(std::vector<std::string> *fragments)
{
        /* parse string ptr_cnt and spit integer equivalent */ 
        int preceedingFragmentsCount = 4 + 2*synCount;
        return parseStringToInteger(&(*fragments)[preceedingFragmentsCount]);
}

std::vector<Pointer> Sense::parsePointers(std::vector<std::string> *fragments)
{
        /* parse pointer_symbol, synset_offset, pos and source/target into a Pointer struct equivalent */
        std::vector<Pointer> l_pointers;
        int preceedingFragmentsCount = 4 + 2*synCount + 1;

        auto getSourceFromSourceTarget = [](std::string srcTarget) -> int {
                std::string src = srcTarget.substr(SRC_SRCTARGET_IDX, SRC_SRCTARGET_LEN);
                return parseHexStringToDecInteger(&src);
        };

        auto getTargetFromSourceTarget = [](std::string srcTarget) -> int {
                std::string target = srcTarget.substr(TARGET_SRCTARGET_IDX, TARGET_SRCTARGET_LEN);
                return parseHexStringToDecInteger(&target);
        };

        for (int i = 0; i < pointerCount; i++) {
                Pointer set = {
                        (*fragments)[preceedingFragmentsCount + 4*i],
                        parseStringToInteger(&(*fragments)[preceedingFragmentsCount + 4*i + 1]),
                        (*fragments)[preceedingFragmentsCount + 4*i + 2],
                        getSourceFromSourceTarget((*fragments)[preceedingFragmentsCount + 4*i + 3]),
                        getTargetFromSourceTarget((*fragments)[preceedingFragmentsCount + 4*i + 3])
                };
                l_pointers.push_back(set);
        }
        return l_pointers;
}

int Sense::parseFrameCount(std::vector<std::string> *fragments)
{
        /* parse string f_cnt and spit integer equivalent */
        int preceedingFragmentsCount = 4 + 2*synCount + 1 + 4*pointerCount;
        return parseStringToInteger(&(*fragments)[preceedingFragmentsCount]);
}

std::vector<Frame> Sense::parseFrames(std::vector<std::string> *fragments)
{
        /* parse f_num and w_num and spit a structure frame equivalent */
        std::vector<Frame> l_frames;
        int preceedingFragmentsCount = 4 + 2*synCount + 1 + 4*pointerCount + 1;
        for (int i = 0; i < frameCount; i++) {
                Frame set = {
                        parseStringToInteger(&(*fragments)[preceedingFragmentsCount + 3*i + 1]),
                        parseHexStringToDecInteger(&(*fragments)[preceedingFragmentsCount + 3*i + 2])
                };
                l_frames.push_back(set);
        }
        return l_frames;
}

std::string Sense::parseDefinition(std::vector<std::string> *fragments)
{
        /* detect and return synset definition */
        int preceedingFragmentsCount = 4 + 2*synCount + 1 + 4*pointerCount
                                + (lexFile == "data.verb" ? (1 + 3*frameCount) : 0);
        return (*fragments)[preceedingFragmentsCount];
}

std::vector<std::string> Sense::parseExampleSentences(std::vector<std::string> *fragments)
{
        /* detect and return parsed example sentences */
        std::vector<std::string> l_exampleSentences;
        int preceedingFragmentsCount = 4 + 2*synCount + 1 + 4*pointerCount
                                + (lexFile == "data.verb" ? (1 + 3*frameCount) : 0) + 1;
        
        for (int i = preceedingFragmentsCount; i < (*fragments).size(); i++) {
                l_exampleSentences.push_back(
                        // returning substring excluding leading and trailing quotes
                        (*fragments)[i].substr(1, (*fragments)[i].length() - 2)
                );
        }
        return l_exampleSentences;
}