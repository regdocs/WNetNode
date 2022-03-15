/**
*
*   Author: 	jay.dnb@outlook.in
*   Created: 	
*
*   UNIX CPP scipt >> 
*   Synopsis: ~$
*
**/

#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	
	// 0 1 2 3 4 5 6, to erase [2] through [5], str.erase(2, 5 - 2 + 1)
        string x = "                 a house in the middle of nowhere ";
	string *s = &x;
	cout << x << "|" << endl;
	int leftTrimStartIdx = 0, leftTrimEndIdx = 0;
        for (int i = 0; (*s)[i] == ' '; i++)
                leftTrimEndIdx = i;
        (*s).erase(leftTrimStartIdx, leftTrimEndIdx - leftTrimStartIdx + (leftTrimEndIdx==0?0:1));
        cout << x << "|" << endl;
        
        int rightTrimEndIdx = (*s).length() - 1, rightTrimStartIdx = (*s).length() - 1;
        for (int i = (*s).length() - 1; (*s)[i] == ' '; i--)
                rightTrimStartIdx = i;
        (*s).erase(rightTrimStartIdx, rightTrimEndIdx - rightTrimStartIdx + (rightTrimStartIdx == ((*s).length() - 1)? 0 : 1));
        cout << x << "|" << endl;
	return 0;
	
}
