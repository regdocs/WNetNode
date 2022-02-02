#include <iostream>
#include <string>
#include <vector>
#include "String_Utils.h"

int main()
{
        std::string dataRow = "01716563 36 v 03 perform 0 execute 1 do 1 023 + 09786620 n 0302 + 00098324 n 0202 + 10089103 n 0201 + 00098324 n 0101 ~ 00492487 v 0000 ~ 01051478 v 0000 ~ 01052437 v 0000 ~ 01053236 v 0000 ~ 01707716 v 0000 ~ 01716413 v 0000 ~ 01717207 v 0000 ~ 01717350 v 0000 ~ 01717446 v 0000 ~ 01717842 v 0000 ~ 01717954 v 0000 ~ 01722044 v 0000 ~ 01724857 v 0000 ~ 01725046 v 0000 ~ 01727101 v 0000 ~ 01732719 v 0000 ~ 01736053 v 0000 ~ 01736802 v 0000 ~ 01759660 v 0000 01 + 08 00 | carry out or perform an action; \"John did the painting, the weeding, and he cleaned out the gutters\"; \"the skater executed a triple pirouette\"; \"she did a little dance\"  ";
        /* parse data row into constituent data fragments */
        bool barPositionCrossed = false;
        std::string dataRowPrefix = "", dataRowPostfix = "";
        std::vector<std::string> fragments;

        // break data row into prefix and postfix sections w.r.t. the index of '|'
        for (int i = 0; i < dataRow.length(); i++) {
                if (dataRow[i] == '|') {
                        barPositionCrossed = true;
                        continue;
                }
                if (!barPositionCrossed)
                        dataRowPrefix.push_back(dataRow[i]);
                else
                        dataRowPostfix.push_back(dataRow[i]);
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
        
        for (int i = 0; i < fragments.size(); i++)
                std::cout << fragments[i] << std::endl;
        return 0;
}
