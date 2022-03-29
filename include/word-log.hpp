#ifndef WORD_LOG_H_
#define WORD_LOG_H_

#include <vector>
#include <string>

#include "sense-interface.hpp"
#include "string-utils.hpp"
#include "pos-group.hpp"
#include "wn3-path.hpp"

namespace jay_io
{

struct Word_Log
{
        bool containsCargo;
        std::string word;

        // if contains cargo, use:
        std::vector<POS_Group> posGroups;

        // if does not contain cargo (no match found), use:
        // also write Suggestion(), Suggestion::suggestor()
        std::vector<std::string> suggestions;

        void previewWordLog()
        {
                using namespace std;

                auto prettyPrintVectorOfStrings = [&] (std::vector<std::string> &vos) -> std::string {
                        std::string a, t;
                        if (vos.size() == 0)
                                return "-";

                        for (int i = 0; i < vos.size(); i++)
                        {
                                if (vos.size() - 1 != i) {
                                        t = vos[i];
                                        t.append(", ");
                                        a.append(t);
                                } else
                                        a.append(vos[i]);
                        }
                        return a;
                };

                cout << "Word: " << word << endl << endl;
                for (auto i: posGroups) {
                        for (auto itr: i.prettySenses)
                                itr.consoleDump();
                }
        }
};

}

#endif /* WORD_LOG_H_ */