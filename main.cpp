#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//预处理函数声明
vector<string> get_code(const char *);
int have_sharp(vector<string>);
vector<string> extend_include(vector<string>);
vector<string> erase_space(vector<string>);

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
//七类token的名字
string typename_token[] = {"", "keyword", "var", "int", "double", "string", "operator", "separator"};
//保存token结果的vector, 1:关键字, 2:标识符(变量、函数的名字), 3:整数, 4:小数, 5:字符串, 6: 分隔符, 7:运算符
vector<token> RES_TOKENS;

//subset little C的关键字
string KEYWORDS[] = {"void", "int", "double", "string", "if", "else", "while", "for", "return"};

int main()
{
    //预处理部分
    vector<string> code_lines;
    code_lines = get_code("code.c");
    int index = -1;
    while (have_sharp(code_lines) != -1)
    {
        code_lines = extend_include(code_lines);
    }

    code_lines = erase_space(code_lines);

    //词法分析部分
    // vector<string> code_lines{"int 0123() 45 ()+-*/>1<1>=1<=1+1-1*1/1=1{}\n", "{\n", "cout{}\"hello\"\n", "}\n"};
    // for (auto e : code_lines)
    // {
    //     cout << e;
    // }

    for (auto line : code_lines)
    {
        get_token(line);
        // break;
    }

    // cout << "(";
    for (auto e : RES_TOKENS)
    {
        cout << e.value << " ," << typename_token[e.type] << endl;
    }
    // cout << ")" << endl;

    return 0;
}
//词法分析函数实现
//去除空格
vector<string> erase_space(vector<string> code_lines)
{
    for (auto &line : code_lines)
    {
        bool flag = false;
        string tmp_line = "";
        for (auto letter : line)
        {
            if (letter != ' ' && letter != '\t')
            {
                flag = true;
            }
            if (flag == true)
            {
                tmp_line += letter;
            }
        }
        line = tmp_line;
    }
    return code_lines;
}

//展开头文件内容
vector<string> extend_include(vector<string> code_lines)
{
    int index = have_sharp(code_lines);
    string filename = "", line_sharp = "";
    line_sharp = code_lines[index];
    bool flag = false;
    for (int i = 0; i < line_sharp.size(); i++)
    {
        if (line_sharp[i] == '<')
        {
            flag = true;
            i++;
        }
        else if (line_sharp[i] == '>')
        {
            flag = false;
        }
        if (flag == true)
        {
            filename += line_sharp[i];
        }
    }
    ifstream myfile;
    myfile.open(filename, ios_base::in);
    vector<string> head_file;
    string head_file_line = "";
    while (getline(myfile, head_file_line))
    {
        head_file.push_back(head_file_line);
    }
    // for (string e : head_file)
    // {
    //     cout << e << endl;
    // }
    // cout << str << endl;
    auto it = code_lines.begin();
    code_lines.erase(code_lines.begin() + index);
    code_lines.insert(it + index, head_file.begin(), head_file.end());
    return code_lines;
}

//判断源代码的某一行是否有#
int have_sharp(vector<string> code_lines)
{
    int index = 0;
    for (string &element : code_lines)
    {
        for (int i = 0; i < element.size(); i++)
        {
            if (element[i] != ' ' || element[i] != '\t')
            {
                if (element[i] == '#')
                {
                    return index;
                }
            }
        }
        index++;
    }
    return -1;
}

//读取源文件的代码
vector<string> get_code(const char *filename)
{
    vector<string> ERROR;
    vector<string> code_lines;
    string line = "";
    fstream myfile(filename, ios::in);

    if (myfile.fail())
    {
        cout << "failed open the file" << endl;
        myfile.close();
        return ERROR;
    }

    while (getline(myfile, line, '\n'))
    {
        code_lines.push_back(line);
    }

    for (int i = 0; i < code_lines.size(); i++)
    {
        string line_tmp = code_lines[i];
    }

    return code_lines;
}

//语法分析函数实现
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
            CLASS_NUMBER = SEPARATOR;
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
            for (auto e : KEYWORDS)
            {
                // cout << "word: " << word << " keyword: " << KEYWORDS[j] << endl;
                if (word == e)
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
                bool is_equal = false;
                operator_tmp += ch;
                i++;
                ch = code_line[i];
                if (ch == '=')
                {
                    operator_tmp += ch;
                    is_equal = true;
                }

                if (is_equal == false)
                {
                    i--;
                }

                tk.type = CLASS_NUMBER;
                tk.value = operator_tmp;
                RES_TOKENS.push_back(tk);
                break;
            }
            case '>':
            {
                bool is_equal = false;
                operator_tmp += ch;
                i++;
                ch = code_line[i];
                if (ch == '=')
                {
                    operator_tmp += ch;
                    is_equal = true;
                }

                if (is_equal == false)
                {
                    i--;
                }

                tk.type = CLASS_NUMBER;
                tk.value = operator_tmp;
                RES_TOKENS.push_back(tk);
                break;
            }
            case '+':
            {
                tk.type = OPERATOR;
                tk.value = ch;
                RES_TOKENS.push_back(tk);
                break;
            }
            case '-':
            {
                tk.type = OPERATOR;
                tk.value = ch;
                RES_TOKENS.push_back(tk);
                break;
            }
            case '*':
            {
                tk.type = OPERATOR;
                tk.value = ch;
                RES_TOKENS.push_back(tk);
                break;
            }
            case '/':
            {
                tk.type = OPERATOR;
                tk.value = ch;
                RES_TOKENS.push_back(tk);
                break;
            }
            case '=':
            {
                tk.type = OPERATOR;
                tk.value = ch;
                RES_TOKENS.push_back(tk);
                break;
            }
            }
        }
    }
}