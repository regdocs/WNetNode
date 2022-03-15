#ifndef INFLECTION_H_
#define INFLECTION_H_

#include <vector>
#include <string>

#include "acorn-utils.hpp"
#include "string-utils.hpp"

namespace jay_io
{

class Inflection
{
        public:
                bool isEmpty;
                std::string inflection;
                std::vector<std::string> rootWords;
                
                Inflection();
                Inflection(std::string, bool);
                Inflection(const Inflection&);
        
        private:
                std::vector<std::string> fragments;
                std::vector<std::string> fragmentDataRow(std::string&);
};

Inflection::Inflection() : isEmpty(true) {}

Inflection::Inflection(std::string dataRow, bool isEmpty = false)
{
        if (!isEmpty) {
                this -> fragments = fragmentDataRow(dataRow);
                this -> inflection = fragments[0];
                for (int i = 1; i < fragments.size(); i++)
                        rootWords.push_back(fragments[i]);
        }
        else
                this -> isEmpty = true;
}

Inflection::Inflection(const Inflection& i)
{
        this -> isEmpty = i.isEmpty;
        this -> fragments = i.fragments;
        this -> inflection = i.inflection;
        this -> rootWords = i.rootWords;
}

std::vector<std::string> Inflection::fragmentDataRow(std::string &dataRow)
{
        /* parse data row into constituent data fragments */
        std::string fragment = "";
        std::vector<std::string> fragments;

        for (int i = 0; i < dataRow.length(); i++) {
                if (dataRow[i] == ' ') {
                        trim(&fragment);
                        fragments.push_back(fragment);
                        fragment.clear();
                        continue;
                }
                fragment.push_back(dataRow[i]);
        }
        trim(&fragment);
        fragments.push_back(fragment);
        return fragments;
}

}

#endif /* INFLECTION_H_ */