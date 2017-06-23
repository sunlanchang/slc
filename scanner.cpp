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

//每个token的类别和总类别
int CLASS_NUMBER = -1;
int CLASS_SUM = 7;
//枚举类型来存储类型
enum TYPES
{
    KEYWORD = 1,
    ID = 2,
    INT = 3,
    DOUBLE = 4,
    STRING = 5,
    OPERATOR = 6,
    SEPARATOR = 7
};

//保存token结果的vector, 1:关键字, 2:标识符(变量、函数的名字), 3:整数, 4:小数, 5:字符串, 6: 分隔符, 7:运算符
vector<token> RES_TOKENS;

//simple little C的关键字
string KEYWORDS[] = {"INT", "DOUBLE", "STRING", "IF", "ELSE", "WHILE", "FOR", "BEGIN", "END"};

int main()
{
    vector<string> code_lines{"INT 0123() 45 ()+-*/=><{}\n", "{\n", "cout{}\"hello\"\n", "}\n"};
    for (auto e : code_lines)
    {
        cout << e;
    }

    for (auto line : code_lines)
    {
        get_token(line);
        // break;
    }

    // cout << "(";
    for (auto e : RES_TOKENS)
    {
        cout << e.value << " ," << e.type << endl;
    }
    // cout << ")" << endl;

    return 0;
}

int get_token(string code_line)
{
    //i为一行中字符的位置index
    for (int i = 0; i < code_line.size(); i++)
    {
        char ch = code_line[i];
        token tk;

        //一共有七个条件判断，每一个对应着一个类

        //第六类 分隔符类
        if (ch == ' ' || ch == ';' ||
            ch == '{' || ch == '}' ||
            ch == '(' || ch == ')')
        {
            CLASS_NUMBER = OPERATOR;
            tk.value = ch;
            tk.type = CLASS_NUMBER;
            RES_TOKENS.push_back(tk);
        }

        //第二类 标识符类 第一类 关键字类
        else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '_'))
        {
            string word = "";
            while ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_')
            {
                word += ch;

                //字符位置移动
                i++;
                ch = code_line[i];
            }

            //判断是不是关键字
            bool is_keyword = false;
            for (int j = 0; j < CLASS_SUM; j++)
            {
                // cout << "word: " << word << " keyword: " << KEYWORDS[j] << endl;
                if (word == KEYWORDS[j])
                {
                    is_keyword = true;
                    break;
                }
            }

            if (is_keyword == true)
            {
                CLASS_NUMBER = KEYWORD;
            }
            else
            {
                CLASS_NUMBER = ID;
            }
            i--;
            tk.value = word;
            tk.type = CLASS_NUMBER;
            RES_TOKENS.push_back(tk);
        }

        //第三类 整数类 第四类 小数类
        else if (ch >= '0' && ch <= '9')
        {
            //判断是否是小数
            bool is_decimal = false;
            CLASS_NUMBER = INT;
            string number_str = "";

            while (ch >= '0' && ch <= '9')
            {
                number_str += ch;
                i++;
                ch = code_line[i];
            }

            if (ch == '.')
            {
                is_decimal = true;
                CLASS_NUMBER = DOUBLE;
                number_str += ch;
                i++;
                ch = code_line[i];
                while (ch >= '0' && ch <= '9')
                {
                    number_str += ch;
                    i++;
                    ch = code_line[i];
                }
            }
            i--;
            tk.type = CLASS_NUMBER;
            tk.value = number_str;
            RES_TOKENS.push_back(tk);
        }

        //第五类 字符串类
        else if (ch == '\"')
        {
            //字符串中间变量
            string str = "";

            CLASS_NUMBER = STRING;

            i++;
            ch = code_line[i];
            while (ch != '\"')
            {
                str += ch;
                i++;
                ch = code_line[i];
            }

            tk.type = CLASS_NUMBER;
            tk.value = str;
            RES_TOKENS.push_back(tk);
        }

        //第七类 运算符类
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=')
        {
            CLASS_NUMBER = SEPARATOR;
            string operator_tmp = "";
            switch (ch)
            {
            case '<':
            {
                operator_tmp += ch;
                i++;
                ch = code_line[i];
                if (ch == '=')
                {
                    operator_tmp += ch;
                }

                tk.type = CLASS_NUMBER;
                tk.value = operator_tmp;
                RES_TOKENS.push_back(tk);
                break;
            }
            }
        }
    }
}