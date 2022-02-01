#ifndef SENSE_INTERFACE_H_
#define SENSE_INTERFACE_H_

#include "Sense.h"
#include "String_Utils.h"
#include "Synset_Pointers.h"

class Sense_Interface: public Sense
/* as an established standard for this repository, all interface class members are to be appended with 'Interface' */
{
        public:
                // from [std::string] lemma 
                std::string wordInterface;
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

        private:
                Sense_Interface(std::string, std::string);
};

Sense_Interface::Sense_Interface(std::string word, std::string sense): Sense(sense)
        {
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
                
                // returns null, do not use
                this -> frameInterface = parseFrameInterface(&frames);
        }


#endif /* SENSE_INTERFACE_H_ */