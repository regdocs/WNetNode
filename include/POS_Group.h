#include <string>
#include <vector>
#include "Sense.h"

using namespace std;

class POSGroup
{
	private:
		string prettyLemma;
		string prettyPos;
		vector<string> inflections;
		vector<Sense> senses;
	
	public:
		POSGroup(string lemma, string pos, vector<string> inflections, vector<Sense> senses)
		{
			this -> prettyLemma = lemma;
			this -> prettyPos = pos;
			this -> inflections = inflections;
			this -> senses = senses;
		}
};
