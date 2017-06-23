#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<string> code_lines{"void print()\n", "{\n", "cout<<\"hello\"\n", "}\n"};
    for (auto e : code_lines)
    {
        cout << e;
    }
    return 0;
}