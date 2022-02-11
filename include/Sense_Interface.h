#ifndef SENSE_INTERFACE_H_
#define SENSE_INTERFACE_H_

// relative path to project root from this file
#define PATH_TO_ROOT "../"

#include <cstring>
#include <fstream>
#include <iostream>

#include "Sense.h"
#include "WN3_Path.h"
#include "Acorn_Utils.h"
#include "String_Utils.h"
#include "Synset_Pointers.h"

class Sense_Interface: public Sense
/* as an established standard for this repository, all interface class members are to be appended with 'Interface' */
{
        public:
                // from [char] synsetType
                std::string synsetTypeInterface;
                // from [std::vector<WordLexidGroup>] wordLexidGroupVector
                std::vector<std::string> synWordVectorInterface;

                // from [std::vector<Pointer>] pointers for "data.noun"
                jay_io::NounPointers /*.......*/ nounPointersInterface; 
                // from [std::vector<Pointer>] pointers for "data.verb"
                jay_io::VerbPointers /*.......*/ verbPointersInterface;
                // from [std::vector<Pointer>] pointers for "data.adj"
                jay_io::AdjectivePointers /*..*/ adjectivePointersInterface;
                // from [std::vector<Pointer>] pointers for "data.adv"
                jay_io::AdverbPointers /*.....*/ adverbPointersInterface;

                // from [std::vector<Frame>] frames for "data.verb"
                std::vector<std::string> frameInterface;

                /* 
                 *  Interface frames are rather difficult to implement and there will
                 *  be no support for this feature until there is volunteered effort.
                 *  Refer to: https://wordnet.princeton.edu/documentation/wninput5wn 
                 *  for documentation on verb frames and how to compile them.
                 */

                // constructor should call superclass constructor
                Sense_Interface(std::string, std::string);
                void previewInterface();

        private:
                // from [std::string] lemma 
                std::string wordInterface;
                // from [std::string] lemma
                int wordIndexInterface;

                std::string /*................*/ parseSynsetTypeInterface /*.........*/ (char*);
                std::vector<std::string> /*...*/ parseSynWordVectorInterface /*......*/ (std::vector<WordLexidGroup>*);
                jay_io::NounPointers /*.......*/ parseNounPointersInterface /*.......*/ (std::vector<Pointer>*);
                jay_io::VerbPointers /*.......*/ parseVerbPointersInterface /*.......*/ (std::vector<Pointer>*);
                jay_io::AdjectivePointers /*..*/ parseAdjectivePointersInterface /*..*/ (std::vector<Pointer>*);
                jay_io::AdverbPointers /*.....*/ parseAdverbPointersInterface /*.....*/ (std::vector<Pointer>*);
                std::vector<std::string> /*...*/ parseFrameInterface /*..............*/ (std::vector<Frame>*);
};

Sense_Interface::Sense_Interface(std::string word, std::string sense): Sense(sense)
{
        /* class Sense_Interface constructor */
        this -> wordInterface = word;
        this -> synsetTypeInterface = parseSynsetTypeInterface(&synsetType);
        this -> synWordVectorInterface = parseSynWordVectorInterface(&wordLexidGroupVector);
        
        if (synsetType == 'n')
                nounPointersInterface = parseNounPointersInterface(&pointers);
        else if (synsetType == 'v')
                verbPointersInterface = parseVerbPointersInterface(&pointers);
        else if (synsetType == 'a' || synsetType == 's')
                adjectivePointersInterface = parseAdjectivePointersInterface(&pointers);
        else if (synsetType == 'r')
                adverbPointersInterface = parseAdverbPointersInterface(&pointers);

        // unused
        this -> frameInterface = parseFrameInterface(&frames);
}

std::string Sense_Interface::parseSynsetTypeInterface(char *synsetType)
{
        /* returns disambiguated form of char parameter synsetType */
        return parseSynsetTypeExpanded(synsetType);
}

std::vector<std::string> Sense_Interface::parseSynWordVectorInterface(std::vector<WordLexidGroup> *l_wordLexidGroupVector)
{
        /* returns manipulated form of synonym vector excluding queried word */
        std::string t;
        std::vector<std::string> l_synWordVectorInterface;

        for (int i = 0; i < (*l_wordLexidGroupVector).size(); i++) {
                t = (*l_wordLexidGroupVector)[i].word;

                if (stringToLower(&t) == wordInterface) {
                        wordIndexInterface = i + 1;
                        continue;
                }

                replaceStringUscoreWithSpace(&t);
                l_synWordVectorInterface.push_back(t);
        }
        return l_synWordVectorInterface;
}

jay_io::NounPointers Sense_Interface::parseNounPointersInterface(std::vector<Pointer> *pointers)
{
        /* parse noun pointers and create a decorated interface struct */
        std::string filepath, t;
        filepath.append(PATH_TO_ROOT);
        filepath.append(WN3DB_DAT_POS_PATH);
        std::basic_ifstream<char> datapos;
        jay_io::NounPointers p;

        for (int i = 0; i < (*pointers).size(); i++) {
                // do, if source index of the pointer refers to wordInterface (word looked up)
                if ((*pointers)[i].source == wordIndexInterface || (*pointers)[i].source == 0) {
                        
                        // getlining the target sense
                        datapos.open(filepath.append(posFile[(*pointers)[i].pos[0]]).c_str());
                        datapos.seekg((*pointers)[i].synsetOffset);
                        std::getline(datapos, t, '\n');

                        // parsing the getlined data row
                        Sense sense(t);

                        // push back on pointer's element with the word from the synset
                        auto pushbackOnPointerElement_With_ = [](std::vector<std::string> *element, std::string *elementOfElement) {
                                std::string w = *elementOfElement;
                                replaceStringUscoreWithSpace(&w);
                                (*element).push_back(w);
                        };

                        // placeholder variable for the returned string
                        std::string disambiguatedPointerSymbol = parsePointerSymbol((*pointers)[i].pointerSymbol, (*pointers)[i].pos);
                        
                        // read through all synonyms in target pointer if target index is zero
                        if ((*pointers)[i].target == 0) {
                                for (int j = 0; j < sense.wordLexidGroupVector.size(); j++) {

                                        if (disambiguatedPointerSymbol == "Antonym")
                                                pushbackOnPointerElement_With_(&(p.antonym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Hypernym")
                                                pushbackOnPointerElement_With_(&(p.hypernym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Instance Hypernym")
                                                pushbackOnPointerElement_With_(&(p.instanceHypernym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Hyponym")
                                                pushbackOnPointerElement_With_(&(p.hyponym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Instance Hyponym")
                                                pushbackOnPointerElement_With_(&(p.instanceHyponym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Member holonym")
                                                pushbackOnPointerElement_With_(&(p.memberHolonym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Substance holonym")
                                                pushbackOnPointerElement_With_(&(p.substanceHolonym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Part holonym")
                                                pushbackOnPointerElement_With_(&(p.partHolonym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Member meronym")
                                                pushbackOnPointerElement_With_(&(p.memberMeronym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Substance meronym")
                                                pushbackOnPointerElement_With_(&(p.substanceMeronym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Part meronym")
                                                pushbackOnPointerElement_With_(&(p.partMeronym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Attribute")
                                                pushbackOnPointerElement_With_(&(p.attribute), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Derivationally related form")
                                                pushbackOnPointerElement_With_(&(p.derivationallyRelatedForm), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Domain of synset - TOPIC")
                                                pushbackOnPointerElement_With_(&(p.domainOfSynsetTOPIC), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Member of this domain - TOPIC")
                                                pushbackOnPointerElement_With_(&(p.memberOfThisDomainTOPIC), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Domain of synset - REGION")
                                                pushbackOnPointerElement_With_(&(p.domainOfSynsetREGION), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Member of this domain - REGION")
                                                pushbackOnPointerElement_With_(&(p.memberOfThisDomainTOPIC), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Domain of synset - USAGE")
                                                pushbackOnPointerElement_With_(&(p.domainOfSynsetUSAGE), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Member of this domain - USAGE")
                                                pushbackOnPointerElement_With_(&(p.memberOfThisDomainUSAGE), &(sense.wordLexidGroupVector[j].word));
                                }
                        }

                        // read only the select synonym in target pointer if target index is non-zero
                        else {
                                for (int j = 0; j < sense.wordLexidGroupVector.size(); j++) {
                                        if (j + 1 == (*pointers)[i].target) {

                                                if (disambiguatedPointerSymbol == "Antonym")
                                                        pushbackOnPointerElement_With_(&(p.antonym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Hypernym")
                                                        pushbackOnPointerElement_With_(&(p.hypernym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Instance Hypernym")
                                                        pushbackOnPointerElement_With_(&(p.instanceHypernym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Hyponym")
                                                        pushbackOnPointerElement_With_(&(p.hyponym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Instance Hyponym")
                                                        pushbackOnPointerElement_With_(&(p.instanceHyponym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Member holonym")
                                                        pushbackOnPointerElement_With_(&(p.memberHolonym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Substance holonym")
                                                        pushbackOnPointerElement_With_(&(p.substanceHolonym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Part holonym")
                                                        pushbackOnPointerElement_With_(&(p.partHolonym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Member meronym")
                                                        pushbackOnPointerElement_With_(&(p.memberMeronym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Substance meronym")
                                                        pushbackOnPointerElement_With_(&(p.substanceMeronym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Part meronym")
                                                        pushbackOnPointerElement_With_(&(p.partMeronym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Attribute")
                                                        pushbackOnPointerElement_With_(&(p.attribute), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Derivationally related form")
                                                        pushbackOnPointerElement_With_(&(p.derivationallyRelatedForm), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Domain of synset - TOPIC")
                                                        pushbackOnPointerElement_With_(&(p.domainOfSynsetTOPIC), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Member of this domain - TOPIC")
                                                        pushbackOnPointerElement_With_(&(p.memberOfThisDomainTOPIC), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Domain of synset - REGION")
                                                        pushbackOnPointerElement_With_(&(p.domainOfSynsetREGION), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Member of this domain - REGION")
                                                        pushbackOnPointerElement_With_(&(p.memberOfThisDomainTOPIC), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Domain of synset - USAGE")
                                                        pushbackOnPointerElement_With_(&(p.domainOfSynsetUSAGE), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Member of this domain - USAGE")
                                                        pushbackOnPointerElement_With_(&(p.memberOfThisDomainUSAGE), &(sense.wordLexidGroupVector[j].word));
                                        }
                                }
                        }
                }        
        }
        
        return p;
}

jay_io::VerbPointers Sense_Interface::parseVerbPointersInterface(std::vector<Pointer> *pointers)
{
        std::string filepath, t;
        filepath.append(PATH_TO_ROOT);
        filepath.append(WN3DB_DAT_POS_PATH);
        std::basic_ifstream<char> datapos;
        jay_io::VerbPointers p;

        for (int i = 0; i < (*pointers).size(); i++) {
                // do, if source index of the pointer refers to wordInterface (word looked up)
                if ((*pointers)[i].source == wordIndexInterface || (*pointers)[i].source == 0) {
                        
                        // getlining the target sense
                        datapos.open(filepath.append(posFile[(*pointers)[i].pos[0]]).c_str());
                        datapos.seekg((*pointers)[i].synsetOffset);
                        std::getline(datapos, t, '\n');

                        // parsing the getlined data row
                        Sense sense(t);

                        // push back on pointer's element with the word from the synset
                        auto pushbackOnPointerElement_With_ = [](std::vector<std::string> *element, std::string *elementOfElement) {
                                std::string w = *elementOfElement;
                                replaceStringUscoreWithSpace(&w);
                                (*element).push_back(w);
                        };

                        // placeholder variable for the returned string
                        std::string disambiguatedPointerSymbol = parsePointerSymbol((*pointers)[i].pointerSymbol, (*pointers)[i].pos);
                        
                        // read through all synonyms in target pointer if target index is zero
                        if ((*pointers)[i].target == 0) {
                                for (int j = 0; j < sense.wordLexidGroupVector.size(); j++) {

                                        if (disambiguatedPointerSymbol == "Antonym")
                                                pushbackOnPointerElement_With_(&(p.antonym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Hypernym")
                                                pushbackOnPointerElement_With_(&(p.hypernym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Hyponym")
                                                pushbackOnPointerElement_With_(&(p.hyponym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Entailment")
                                                pushbackOnPointerElement_With_(&(p.entailment), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Cause")
                                                pushbackOnPointerElement_With_(&(p.cause), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Also see")
                                                pushbackOnPointerElement_With_(&(p.alsoSee), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Verb Group")
                                                pushbackOnPointerElement_With_(&(p.verbGroup), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Derivationally related form")
                                                pushbackOnPointerElement_With_(&(p.derivationallyRelatedForm), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Domain of synset - TOPIC")
                                                pushbackOnPointerElement_With_(&(p.domainOfSynsetTOPIC), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Domain of synset - REGION")
                                                pushbackOnPointerElement_With_(&(p.domainOfSynsetREGION), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Domain of synset - USAGE")
                                                pushbackOnPointerElement_With_(&(p.domainOfSynsetUSAGE), &(sense.wordLexidGroupVector[j].word));
                                        }
                        }

                        // read only the select synonym in target pointer if target index is non-zero
                        else {
                                for (int j = 0; j < sense.wordLexidGroupVector.size(); j++) {
                                        if (j + 1 == (*pointers)[i].target) {

                                                if (disambiguatedPointerSymbol == "Antonym")
                                                        pushbackOnPointerElement_With_(&(p.antonym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Hypernym")
                                                        pushbackOnPointerElement_With_(&(p.hypernym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Hyponym")
                                                        pushbackOnPointerElement_With_(&(p.hyponym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Entailment")
                                                        pushbackOnPointerElement_With_(&(p.entailment), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Cause")
                                                        pushbackOnPointerElement_With_(&(p.cause), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Also see")
                                                        pushbackOnPointerElement_With_(&(p.alsoSee), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Verb Group")
                                                        pushbackOnPointerElement_With_(&(p.verbGroup), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Derivationally related form")
                                                        pushbackOnPointerElement_With_(&(p.derivationallyRelatedForm), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Domain of synset - TOPIC")
                                                        pushbackOnPointerElement_With_(&(p.domainOfSynsetTOPIC), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Domain of synset - REGION")
                                                        pushbackOnPointerElement_With_(&(p.domainOfSynsetREGION), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Domain of synset - USAGE")
                                                        pushbackOnPointerElement_With_(&(p.domainOfSynsetUSAGE), &(sense.wordLexidGroupVector[j].word));
                                        }
                                }
                        }
                }        
        }

        return p;
}

jay_io::AdjectivePointers Sense_Interface::parseAdjectivePointersInterface(std::vector<Pointer> *pointers)
{
        std::string filepath, t;
        filepath.append(PATH_TO_ROOT);
        filepath.append(WN3DB_DAT_POS_PATH);
        std::basic_ifstream<char> datapos;
        jay_io::AdjectivePointers p;

        for (int i = 0; i < (*pointers).size(); i++) {
                // do, if source index of the pointer refers to wordInterface (word looked up)
                if ((*pointers)[i].source == wordIndexInterface || (*pointers)[i].source == 0) {
                        
                        // getlining the target sense
                        datapos.open(filepath.append(posFile[(*pointers)[i].pos[0]]).c_str());
                        datapos.seekg((*pointers)[i].synsetOffset);
                        std::getline(datapos, t, '\n');

                        // parsing the getlined data row
                        Sense sense(t);

                        // push back on pointer's element with the word from the synset
                        auto pushbackOnPointerElement_With_ = [](std::vector<std::string> *element, std::string *elementOfElement) {
                                std::string w = *elementOfElement;
                                replaceStringUscoreWithSpace(&w);
                                (*element).push_back(w);
                        };

                        // placeholder variable for the returned string
                        std::string disambiguatedPointerSymbol = parsePointerSymbol((*pointers)[i].pointerSymbol, (*pointers)[i].pos);
                        
                        // read through all synonyms in target pointer if target index is zero
                        if ((*pointers)[i].target == 0) {
                                for (int j = 0; j < sense.wordLexidGroupVector.size(); j++) {

                                        if (disambiguatedPointerSymbol == "Antonym")
                                                pushbackOnPointerElement_With_(&(p.antonym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Similar to")
                                                pushbackOnPointerElement_With_(&(p.similarTo), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Participle of verb")
                                                pushbackOnPointerElement_With_(&(p.participleOfVerb), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Pertainym (pertains to noun)")
                                                pushbackOnPointerElement_With_(&(p.pertainym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Attribute")
                                                pushbackOnPointerElement_With_(&(p.attribute), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Also see")
                                                pushbackOnPointerElement_With_(&(p.alsoSee), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Domain of synset - TOPIC")
                                                pushbackOnPointerElement_With_(&(p.domainOfSynsetTOPIC), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Domain of synset - REGION")
                                                pushbackOnPointerElement_With_(&(p.domainOfSynsetREGION), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Domain of synset - USAGE")
                                                pushbackOnPointerElement_With_(&(p.domainOfSynsetUSAGE), &(sense.wordLexidGroupVector[j].word));
                                }
                        }

                        // read only the select synonym in target pointer if target index is non-zero
                        else {
                                for (int j = 0; j < sense.wordLexidGroupVector.size(); j++) {
                                        if (j + 1 == (*pointers)[i].target) {

                                                if (disambiguatedPointerSymbol == "Antonym")
                                                        pushbackOnPointerElement_With_(&(p.antonym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Similar to")
                                                        pushbackOnPointerElement_With_(&(p.similarTo), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Participle of verb")
                                                        pushbackOnPointerElement_With_(&(p.participleOfVerb), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Pertainym (pertains to noun)")
                                                        pushbackOnPointerElement_With_(&(p.pertainym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Attribute")
                                                        pushbackOnPointerElement_With_(&(p.attribute), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Also see")
                                                        pushbackOnPointerElement_With_(&(p.alsoSee), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Domain of synset - TOPIC")
                                                        pushbackOnPointerElement_With_(&(p.domainOfSynsetTOPIC), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Domain of synset - REGION")
                                                        pushbackOnPointerElement_With_(&(p.domainOfSynsetREGION), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Domain of synset - USAGE")
                                                        pushbackOnPointerElement_With_(&(p.domainOfSynsetUSAGE), &(sense.wordLexidGroupVector[j].word));
                                        }
                                }
                        }
                }        
        }

        return p;
}

jay_io::AdverbPointers Sense_Interface::parseAdverbPointersInterface(std::vector<Pointer> *pointers)
{
        std::string filepath, t;
        filepath.append(PATH_TO_ROOT);
        filepath.append(WN3DB_DAT_POS_PATH);
        std::basic_ifstream<char> datapos;
        jay_io::AdverbPointers p;

        for (int i = 0; i < (*pointers).size(); i++) {
                // do, if source index of the pointer refers to wordInterface (word looked up)
                if ((*pointers)[i].source == wordIndexInterface || (*pointers)[i].source == 0) {
                        
                        // getlining the target sense
                        datapos.open(filepath.append(posFile[(*pointers)[i].pos[0]]).c_str());
                        datapos.seekg((*pointers)[i].synsetOffset);
                        std::getline(datapos, t, '\n');

                        // parsing the getlined data row
                        Sense sense(t);

                        // push back on pointer's element with the word from the synset
                        auto pushbackOnPointerElement_With_ = [](std::vector<std::string> *element, std::string *elementOfElement) {
                                std::string w = *elementOfElement;
                                replaceStringUscoreWithSpace(&w);
                                (*element).push_back(w);
                        };

                        // placeholder variable for the returned string
                        std::string disambiguatedPointerSymbol = parsePointerSymbol((*pointers)[i].pointerSymbol, (*pointers)[i].pos);
                        
                        // read through all synonyms in target pointer if target index is zero
                        if ((*pointers)[i].target == 0) {
                                for (int j = 0; j < sense.wordLexidGroupVector.size(); j++) {

                                        if (disambiguatedPointerSymbol == "Antonym")
                                                pushbackOnPointerElement_With_(&(p.antonym), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Derived from adjective")
                                                pushbackOnPointerElement_With_(&(p.derivedFromAdjective), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Domain of synset - TOPIC")
                                                pushbackOnPointerElement_With_(&(p.domainOfSynsetTOPIC), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Domain of synset - REGION")
                                                pushbackOnPointerElement_With_(&(p.domainOfSynsetREGION), &(sense.wordLexidGroupVector[j].word));

                                        else if (disambiguatedPointerSymbol == "Domain of synset - USAGE")
                                                pushbackOnPointerElement_With_(&(p.domainOfSynsetUSAGE), &(sense.wordLexidGroupVector[j].word));
                                }
                        }

                        // read only the select synonym in target pointer if target index is non-zero
                        else {
                                for (int j = 0; j < sense.wordLexidGroupVector.size(); j++) {
                                        if (j + 1 == (*pointers)[i].target) {

                                                if (disambiguatedPointerSymbol == "Antonym")
                                                        pushbackOnPointerElement_With_(&(p.antonym), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Derived from adjective")
                                                        pushbackOnPointerElement_With_(&(p.derivedFromAdjective), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Domain of synset - TOPIC")
                                                        pushbackOnPointerElement_With_(&(p.domainOfSynsetTOPIC), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Domain of synset - REGION")
                                                        pushbackOnPointerElement_With_(&(p.domainOfSynsetREGION), &(sense.wordLexidGroupVector[j].word));

                                                else if (disambiguatedPointerSymbol == "Domain of synset - USAGE")
                                                        pushbackOnPointerElement_With_(&(p.domainOfSynsetUSAGE), &(sense.wordLexidGroupVector[j].word));
                                        }
                                }
                        }
                }        
        }

        return p;
}

std::vector<std::string> Sense_Interface::parseFrameInterface(std::vector<Frame>* l_frames)
{
        return {""};
}

void Sense_Interface::previewInterface()
{
        std::string out, t, tab = "\t", colonSpace = ": ", newline = "\n";

        auto prettyPrintVectorOfStrings = [&] (std::vector<std::string> *vos) -> std::string {
                out.clear();
                for (int i = 0; i < (*vos).size(); i++)
                {
                        if ((*vos).size() - 1 != i) {
                                t = (*vos)[i];
                                t.append(", ");
                                out.append(t);
                        } else
                                out.append((*vos)[i]);
                }
                return out;
        };

        auto printNounPointers = [&] () -> std::string {
                out.clear();
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.antonym) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.hypernym) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.instanceHypernym) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.hyponym) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.instanceHyponym) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.memberHolonym) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.substanceHolonym) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.partHolonym) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.memberMeronym) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.substanceMeronym) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.partMeronym) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.attribute) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.derivationallyRelatedForm) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.domainOfSynsetTOPIC) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.memberOfThisDomainTOPIC) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.domainOfSynsetREGION) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.memberOfThisDomainREGION) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.domainOfSynsetUSAGE) + newline);
                out.append(tab + nounPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&nounPointersInterface.memberOfThisDomainUSAGE) + newline);
                return out;
        };

        auto printVerbPointers = [&] () -> std::string {
                out.clear();
                out.append(tab + verbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&verbPointersInterface.antonym) + newline);
                out.append(tab + verbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&verbPointersInterface.hypernym) + newline);
                out.append(tab + verbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&verbPointersInterface.hyponym) + newline);
                out.append(tab + verbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&verbPointersInterface.entailment) + newline);
                out.append(tab + verbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&verbPointersInterface.cause) + newline);
                out.append(tab + verbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&verbPointersInterface.alsoSee) + newline);
                out.append(tab + verbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&verbPointersInterface.verbGroup) + newline);
                out.append(tab + verbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&verbPointersInterface.derivationallyRelatedForm) + newline);
                out.append(tab + verbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&verbPointersInterface.domainOfSynsetTOPIC) + newline);
                out.append(tab + verbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&verbPointersInterface.domainOfSynsetREGION) + newline);
                out.append(tab + verbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&verbPointersInterface.domainOfSynsetUSAGE) + newline);
                return out;
        };

        auto printAdjectivePointers = [&] () -> std::string {
                out.clear();
                out.append(tab + adjectivePointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adjectivePointersInterface.antonym) + newline);
                out.append(tab + adjectivePointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adjectivePointersInterface.similarTo) + newline);
                out.append(tab + adjectivePointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adjectivePointersInterface.participleOfVerb) + newline);
                out.append(tab + adjectivePointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adjectivePointersInterface.pertainym) + newline);
                out.append(tab + adjectivePointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adjectivePointersInterface.attribute) + newline);
                out.append(tab + adjectivePointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adjectivePointersInterface.alsoSee) + newline);
                out.append(tab + adjectivePointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adjectivePointersInterface.domainOfSynsetTOPIC) + newline);
                out.append(tab + adjectivePointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adjectivePointersInterface.domainOfSynsetREGION) + newline);
                out.append(tab + adjectivePointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adjectivePointersInterface.domainOfSynsetUSAGE) + newline);
                return out;
        };

        auto printAdverbPointers = [&] () -> std::string {
                out.clear();
                out.append(tab + adverbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adverbPointersInterface.antonym) + newline);
                out.append(tab + adverbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adverbPointersInterface.derivedFromAdjective) + newline);
                out.append(tab + adverbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adverbPointersInterface.domainOfSynsetTOPIC) + newline);
                out.append(tab + adverbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adverbPointersInterface.domainOfSynsetREGION) + newline);
                out.append(tab + adverbPointerElemDisambiguationIndex[0] + colonSpace + prettyPrintVectorOfStrings(&adverbPointersInterface.domainOfSynsetUSAGE) + newline);
                return out;
        };

        std::cout << "Part of speech:     " << synsetTypeInterface << std::endl;
        std::cout << "Synonym set:        " << prettyPrintVectorOfStrings(&synWordVectorInterface) << std::endl;
        std::cout << "Noun pointers:      " << printNounPointers() << std::endl;
        std::cout << "Verb pointers:      " << printVerbPointers() << std::endl;
        std::cout << "Adjective pointers: " << printAdjectivePointers() << std::endl;
        std::cout << "Adverb pointers:    " << printAdverbPointers() << std::endl;
}

#endif /* SENSE_INTERFACE_H_ */