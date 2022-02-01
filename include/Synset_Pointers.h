#ifndef SYNSET_POINTERS_H_
#define SYNSET_POINTERS_H_

#include <vector>
#include <string>

namespace jay_io
/* refer docs: https://wordnet.princeton.edu/documentation/wninput5wn */
{
typedef std::vector<std::string> StringVector_CXX11;

struct NounPointers {
        // lexical & semantic relations
        StringVector_CXX11 antonyms;
        StringVector_CXX11 hypernyms;
        StringVector_CXX11 instanceHypernyms;
        StringVector_CXX11 hyponyms;
        StringVector_CXX11 instanceHyponyms;
        StringVector_CXX11 memberHolonym;
        StringVector_CXX11 substanceHolonym;
        StringVector_CXX11 partHolonym;
        StringVector_CXX11 memberMeronym;
        StringVector_CXX11 substanceMeronym;
        StringVector_CXX11 partMeronym;
        StringVector_CXX11 attribute;
        StringVector_CXX11 derivationallyRelatedForm;
        // lemma topics
        StringVector_CXX11 domainOfSynsetTOPIC;
        StringVector_CXX11 memberOfThisDomainTOPIC;
        // lemma regions
        StringVector_CXX11 domainOfSynsetREGION;
        StringVector_CXX11 memberOfThisDomainREGION;
        // lemma usage
        StringVector_CXX11 domainOfSynsetUSAGE;
        StringVector_CXX11 memberOfThisDomainUSAGE; 
};

struct VerbPointers {
        // lexical and semantic relations
        StringVector_CXX11 antonym;
        StringVector_CXX11 hypernym;
        StringVector_CXX11 hyponym;
        StringVector_CXX11 entailment;
        StringVector_CXX11 cause;
        StringVector_CXX11 alsoSee;
        StringVector_CXX11 verbGroup;
        StringVector_CXX11 derivationallyRelatedForm;
        // lemma topics
        StringVector_CXX11 domainOfSynsetTOPIC;
        // lemma regions
        StringVector_CXX11 domainOfSynsetREGION;
        // lemma usage
        StringVector_CXX11 domainOfSynsetUSAGE;
};

struct AdjectivePointers {
        // lexical and semantic relations
        StringVector_CXX11 antonym;
        StringVector_CXX11 similarTo;
        StringVector_CXX11 participleOfVerb;
        StringVector_CXX11 pertainym; // (pertains to noun)
        StringVector_CXX11 attribute;
        StringVector_CXX11 alsoSee;
        // lemma topics
        StringVector_CXX11 domainOfSynsetTOPIC;
        // lemma regions
        StringVector_CXX11 domainOfSynsetREGION;
        // lemma usage
        StringVector_CXX11 domainOfSynsetUSAGE;
};

struct AdverbPointers {
        // lexical and semantic relations
        StringVector_CXX11 antonym;
        StringVector_CXX11 derivedFromAdjective;
        // lemma topics
        StringVector_CXX11 domainOfSynsetTOPIC;
        // lemma regions
        StringVector_CXX11 domainOfSynsetREGION;
        // lemma usage
        StringVector_CXX11 domainOfSynsetUSAGE;
};
}

#endif /* SYNSET_POINTERS_H_ */