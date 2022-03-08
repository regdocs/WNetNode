#ifndef ACORN_UTILS_H_
#define ACORN_UTILS_H_

#include <string>
#include <map>

#include "synset-pointers.hpp"

// parse lexicographer file index and return equivalent file name
auto parseLexFilename = [] (int *lexFilenum) -> std::string {
        switch (*lexFilenum) {
                case 0:  return "adj.all";            case 1:  return "adj.pert";         case 2:  return "adv.all";            case 3:  return "noun.Tops";
                case 4:  return "noun.act";           case 5:  return "noun.animal";      case 6:  return "noun.artifact";      case 7:  return "noun.attribute";
                case 8:  return "noun.body";          case 9:  return "noun.cognition";   case 10: return "noun.communication"; case 11: return "noun.event";
                case 12: return "noun.feeling";       case 13: return "noun.food";        case 14: return "noun.group";         case 15: return "noun.location";
                case 16: return "noun.motive";        case 17: return "noun.object";      case 18: return "noun.person";        case 19: return "noun.phenomenon";
                case 20: return "noun.plant";         case 21: return "noun.possession";  case 22: return "noun.process";       case 23: return "noun.quantity";
                case 24: return "noun.relation";      case 25: return "noun.shape";       case 26: return "noun.state";         case 27: return "noun.substance";
                case 28: return "noun.time";          case 29: return "verb.body";        case 30: return "verb.change";        case 31: return "verb.cognition";
                case 32: return "verb.communication"; case 33: return "verb.competition"; case 34: return "verb.consumption";   case 35: return "verb.contact";
                case 36: return "verb.creation";      case 37: return "verb.emotion";     case 38: return "verb.motion";        case 39: return "verb.perception";
                case 40: return "verb.possession";    case 41: return "verb.social";      case 42: return "verb.stative";       case 43: return "verb.weather";
                                                                                                                                case 44: return "adj.ppl";
        }
};

// parse synset type character and return complete string equivalent
auto parseSynsetTypeExpanded = [] (char *synsetType) {
        switch (*synsetType) {
                case 'n': return "noun";
                case 'v': return "verb";
                case 'a': return "adjective";
                case 'r': return "adverb";
                case 's': return "adjective satellite";
        }
};

// exception file character and complete file name equivalent
std::map<char, std::string> excPosFileNameFromChar = {
        {'n', "noun.exc"},
        {'v', "noun.exc"},
        {'a', "adj.exc"},
        {'r', "adv.exc"}
}; 

// pointer pos and data.pos file name map
std::map<char, std::string> dataPosFileNameFromChar = {
        {'n', "data.noun"},
        {'v', "data.verb"},
        {'a',  "data.adj"},
        {'r',  "data.adv"},
        {'s',  "data.adj"}
};

// noun pointer disambiguation map
std::map<std::string, std::string> nounPointerDisambiguation = {
        {"!",  "Antonym"},
        {"@",  "Hypernym"},
        {"@i", "Instance Hypernym"},
        {"~",  "Hyponym"},
        {"~i", "Instance Hyponym"},
        {"#m", "Member holonym"},
        {"#s", "Substance holonym"},
        {"#p", "Part holonym"},
        {"%m", "Member meronym"},
        {"%s", "Substance meronym"},
        {"%p", "Part meronym"},
        {"=",  "Attribute"},
        {"+",  "Derivationally related form"},
        {";c", "Domain of synset - TOPIC"},
        {"-c", "Member of this domain - TOPIC"},
        {";r", "Domain of synset - REGION"},
        {"-r", "Member of this domain - REGION"},
        {";u", "Domain of synset - USAGE"},
        {"-u", "Member of this domain - USAGE"}
};

// noun pointer element index map
std::map<int, std::string> nounPointerElemDisambiguationIndex = {
        { 0,  "Antonym"},
        { 1,  "Hypernym"},
        { 2, "Instance Hypernym"},
        { 3,  "Hyponym"},
        { 4, "Instance Hyponym"},
        { 5, "Member holonym"},
        { 6, "Substance holonym"},
        { 7, "Part holonym"},
        { 8, "Member meronym"},
        { 9, "Substance meronym"},
        {10, "Part meronym"},
        {11, "Attribute"},
        {12, "Derivationally related form"},
        {13, "Domain of synset - TOPIC"},
        {14, "Member of this domain - TOPIC"},
        {15, "Domain of synset - REGION"},
        {16, "Member of this domain - REGION"},
        {17, "Domain of synset - USAGE"},
        {18, "Member of this domain - USAGE"}
};

// verb pointer disambiguation map
std::map<std::string, std::string> verbPointerDisambiguation = {
        {"!",  "Antonym"},
        {"@",  "Hypernym"},
        {"~",  "Hyponym"},
        {"*",  "Entailment"},
        {">",  "Cause"},
        {"^",  "Also see"},
        {"$",  "Verb Group"},
        {"+",  "Derivationally related form"},
        {";c", "Domain of synset - TOPIC"},
        {";r", "Domain of synset - REGION"},
        {";u", "Domain of synset - USAGE"}
};

// verb pointer element index map
std::map<int, std::string> verbPointerElemDisambiguationIndex = {
        { 0, "Antonym"},
        { 1, "Hypernym"},
        { 2, "Hyponym"},
        { 3, "Entailment"},
        { 4, "Cause"},
        { 5, "Also see"},
        { 6, "Verb Group"},
        { 7, "Derivationally related form"},
        { 8, "Domain of synset - TOPIC"},
        { 9, "Domain of synset - REGION"},
        {10, "Domain of synset - USAGE"}
};

// adjective pointer disambiguation map
std::map<std::string, std::string> adjectivePointerDisambiguation = {
        {"!",  "Antonym"},
        {"&",  "Similar to"},
        {"<",  "Participle of verb"},
        {"\\", "Pertainym (pertains to noun)"},
        {"=",  "Attribute"},
        {"^",  "Also see"},
        {";c", "Domain of synset - TOPIC"},
        {";r", "Domain of synset - REGION"},
        {";u", "Domain of synset - USAGE"}
};

// adjective pointer element index map
std::map<int, std::string> adjectivePointerElemDisambiguationIndex = {
        {0, "Antonym"},
        {1, "Similar to"},
        {2, "Participle of verb"},
        {3, "Pertainym (pertains to noun)"},
        {4, "Attribute"},
        {5, "Also see"},
        {6, "Domain of synset - TOPIC"},
        {7, "Domain of synset - REGION"},
        {8, "Domain of synset - USAGE"}
};

// adverb pointer disambiguation map
std::map<std::string, std::string> adverbPointerDisambiguation = {
        {"!",  "Antonym"},
        {"\\", "Derived from adjective"},
        {";c", "Domain of synset - TOPIC"},
        {";r", "Domain of synset - REGION"},
        {";u", "Domain of synset - USAGE"},
};

// adverb pointer element index map
std::map<int, std::string> adverbPointerElemDisambiguationIndex = {
        {0, "Antonym"},
        {1, "Derived from adjective"},
        {2, "Domain of synset - TOPIC"},
        {3, "Domain of synset - REGION"},
        {4, "Domain of synset - USAGE"},
};

// parse pointer_symbols and return disambiguated pointer type
auto parsePointerSymbol = [] (std::string pointerSymbol, std::string pos) {
        switch (pos[0]) {
                case 'n': return nounPointerDisambiguation[pointerSymbol];
                case 'v': return verbPointerDisambiguation[pointerSymbol];
                case 'a': return adjectivePointerDisambiguation[pointerSymbol];
                case 'r': return adverbPointerDisambiguation[pointerSymbol];
                case 's': return adjectivePointerDisambiguation[pointerSymbol];
        }
};

#endif /* ACORN_UTILS_H_ */
