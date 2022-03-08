#ifndef WORD_LOG_H_
#define WORD_LOG_H_

#include <vector>
#include <string>

#include "sense_interface.h"
#include "string_utils.h"
#include "pos_group.h"
#include "wn3_path.h"

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
                        cout << "Part of Speech: " << i.prettyPos << endl;
                        cout << "Inflections: " << prettyPrintVectorOfStrings(i.inflections) << endl;
                        cout << "Pronunciation: " << prettyPrintVectorOfStrings(i.pronunciations) << endl;
                        cout << "Definitions: " << endl;
                        for (auto i: i.prettySenses)
                                i.previewSenseInterface();
                        cout << endl << endl;
                }
        }
};

}

#endif /* WORD_LOG_H_ */