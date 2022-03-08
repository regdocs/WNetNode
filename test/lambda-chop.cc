#include <string>
#include <vector>
#include <iostream>

class Claus
{
        public:
                std::vector<std::string> vos;
                
                Claus() { this -> vos.push_back("foo"); }
                
                void foobar()
                {
                        std::string str, str2;
                        
                        str.assign(vos[0]);
                        
                        auto foobar2 = [&]() {
                        
                                str2.assign(vos[1]);
                                
                        };
                }
};

int main()
{
    std::string x;
    x.append("a" + "b");
    std::cout << x;
}