#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<string> get_code(const char *);
int have_sharp(vector<string>);
vector<string> extend_include(vector<string>);
vector<string> erase_space(vector<string>);

int main()
{
    vector<string> code_lines;
    code_lines = get_code("code.c");
    int index = -1;
    while (have_sharp(code_lines) != -1)
    {
        code_lines = extend_include(code_lines);
    }

    code_lines = erase_space(code_lines);

    for (string e : code_lines)
    {
        cout << e << endl;
    }

    return 0;
}

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