#include"HLL.h"

using std::cout;
int main()
{
    string s(R"(3.1 ,2,3,"hello",'x' )");
    LL l(s);
    l.traverse(cout)<<"\n";
    l.remove();
    l.traverse(cout)<<"\n";
    return 0;
}