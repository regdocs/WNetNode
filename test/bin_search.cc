#include <iostream>
#include "../include/index.h"

using namespace std;

jay_io::Index returnIndexObjAtByte_InStream_(int offset, std::fstream *fs)
{
        bool isExtracted = false;
        std::string extr;
        char c = 0;
        int i = offset;

        while (!isExtracted) {
                (*fs).get(c);
                (*fs).clear();
                if (c == '\n') {
                        std::getline(*fs, extr, '\n');
                        (*fs).clear();
                        isExtracted = true;
                }
                else {
                        i--;
                        (*fs).seekg(i);
                }
        }

        return jay_io::Index(extr);
}

jay_io::Index binarySearchDataPOS(std::string query, std::string filepath)
{
        std::fstream file(filepath, std::ios::in);
        
        auto returnFinalByteOffset = [] (std::fstream* f) -> std::streamoff {
                (*f).seekg(0, std::ios::end);
                std::streamoff pos = (*f).tellg();
                (*f).seekg(0);
                return pos;
        };

        auto findStartByteOfIndexPOS = [] (std::fstream* f) -> std::streamoff {
                std::string s;
                std::streamoff tempOffset, startOffset;
                bool isStartByteFound = false;

                (*f).seekg(0);
                while (!isStartByteFound) {
                        std::streamoff tempOffset = (*f).tellg(); 
                        std::getline(*f, s, '\n');
                        (*f).clear();

                        if (s[0] == ' ' && s[1] == ' ')
                                continue;
                        else {
                                isStartByteFound = true;
                                startOffset = tempOffset;
                        }
                }

                (*f).seekg(0);
                cout << startOffset;
                return startOffset;
        };

        bool isEntryFound = false;
        jay_io::Index t, i;
        std::streamoff mean, start = findStartByteOfIndexPOS(&file), stop = returnFinalByteOffset(&file);

        while (!isEntryFound) {
                mean = (start + stop)/2;
                i = returnIndexObjAtByte_InStream_(mean, &file);
                i.previewIndex();
                int diff = strcmp(i.lemma.c_str(), query.c_str());

                if (diff < 0)
                        start = mean;
                
                else if (diff > 0)
                        stop = mean;
                
                else /* if (diff == 0) */ {
                        t = i;
                        isEntryFound = true;
                }
        }
        return t;
}

int main() {
        jay_io::Index x = binarySearchDataPOS("act", "../wndb3/index/index.noun");
        x.previewIndex();
}