#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
整体的思想：
比如匹配一个赋值语句 int sum = 0;
先用一个特定的自动机跑一遍这个赋值语句，返回结果如果是接受状态
则进行构建语法树的操作。
*/
enum TYPES
{
    KEYWORD = 1,
    VAR = 2,
    INT = 3,
    DOUBLE = 4,
    STRING = 5,
    OPERATOR = 6,
    SEPARATOR = 7
};
string typename_token[] = {"", "keyword", "var", "int", "double", "string", "operator", "separator"};
class token
{
  public:
    string value;
    int type;
};

int main()
{
    vector<token> RES_TOKENS;
    token t1, t_blank, t2, t3, t4, t5;
    t_blank.value = " ";
    t_blank.type = SEPARATOR;
    t1.value = "int";
    t1.type = INT;
    t2.value = "sum";
    t2.type = VAR;
    t3.value = "=";
    t3.type = OPERATOR;
    t4.value = "a";
    t4.type = VAR;
    t5.value = ";";
    t5.type = SEPARATOR;
    RES_TOKENS.push_back(t1);
    RES_TOKENS.push_back(t_blank);
    RES_TOKENS.push_back(t2);
    RES_TOKENS.push_back(t_blank);
    RES_TOKENS.push_back(t3);
    RES_TOKENS.push_back(t_blank);
    RES_TOKENS.push_back(t4);
    RES_TOKENS.push_back(t5);
    for (auto e : RES_TOKENS)
    {
        cout << e.value << "," << typename_token[e.type] << endl;
    }

    //自动机初始状态为1
    int state = 1;
    for (auto e : RES_TOKENS)
    {
        if (e.value == " ")
        {
            continue;
        }
        switch (e.type)
        {
        case INT:
        {
            if (state == 1)
            {
                state = 2;
            }
            else if (state == 4)
            {
                state = 5;
            }
            break;
        }
        case VAR:
        {
            if (state == 2)
            {
                state = 3;
            }
            else if (state == 4)
            {
                state = 7;
            }
            break;
        }
        case OPERATOR:
        {
            if (state == 3)
            {
                state = 4;
            }
        }
        case SEPARATOR:
        {
            if (state == 5)
            {
                state = 6;
            }
            else if (state == 7)
            {
                state = 8;
            }
            break;
        }
        }
    }
    if (state == 6)
    {
        cout << "type: int sum = 0;" << endl;
    }
    else if (state == 8)
    {
        cout << "type: int sum = a;" << endl;
    }
    else
    {
        cout << "type: a+b+c*d" << endl;
    }
    return 0;
}