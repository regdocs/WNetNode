#include <iostream>
#include <fstream>

using namespace std;

int main() {
        string a;
        fstream f("touchwood");
        getline(f, a, '\n');
        cout << '>' << a << '<' << endl;
}
