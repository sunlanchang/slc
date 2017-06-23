#include <iostream>
#include <string>
#include <vector>

using namespace std;

//token的节点类
class token
{
  public:
    string value;
    int type;
};

int get_token(string);
void init_tokens();
//每个token的类别和总类别
int CLASS_NUMBER = -1;
int CLASS_SUM = 7;
//保存token结果的vector, 1:关键字, 2:标识符(变量、函数的名字), 3:整数, 4:小数, 5:字符串, 6: 分隔符, 7:运算符
vector<vector<token>> RES_TOKENS;
//simple little C的关键字
string KEYWORDS[] = {"VOID", "INT", "DOUBLE", "STRING", "IF", "ELSE", "WHILE", "FOR", "BEGIN", "END"};

int main()
{
    init_tokens();
    vector<string> code_lines{"VOID print()\n", "{\n", "cout<<\"hello\"\n", "}\n"};
    // vector<token> tokens;

    for (auto line : code_lines)
    {
        get_token(line);
        break;
    }

    // for (auto e : code_lines)
    // {
    //     cout << e;
    // }
    return 0;
}

int get_token(string code_line)
{
    //i为一行中字符的位置index
    for (int i = 0; i < code_line.size(); i++)
    {
        //char转换string使用
        string tmp_token = "";
        char ch = code_line[i];
        token tk;
        if (ch == ' ' || ch == ';' ||
            ch == '{' || ch == '}' ||
            ch == '(' || ch == ')')
        {
            CLASS_NUMBER = 6;
            tmp_token += ch;
            tk.value = ch;
            tk.type = CLASS_NUMBER;
            RES_TOKENS[CLASS_NUMBER].push_back(tk);
        }
    }
}

void init_tokens()
{
    vector<token> tk_vec;
    for (int i = 0; i < CLASS_NUMBER; i++)
    {
        RES_TOKENS.push_back(tk_vec);
    }
}