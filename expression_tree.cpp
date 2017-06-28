#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>

using namespace std;

const char str[] = "3*4+5-2/1";

struct Node
{
    char c;
    struct Node *left;
    struct Node *right;
};
stack<struct Node *> subTreeStack;
stack<char> operatorStack;

struct Node *BuildTree()
{

    struct Node *node;
    for (unsigned int pos = 0; pos < strlen(str); pos++)
    {
        //若是数字则作为叶子节点
        if (str[pos] - '0' >= 0 && str[pos] - '0' <= 9)
        {

            node = (struct Node *)malloc(sizeof(struct Node));
            node->c = str[pos];
            node->left = NULL;
            node->right = NULL;

            subTreeStack.push(node);
        }
        else if (str[pos] == '*' || str[pos] == '/' || str[pos] == '+' || str[pos] == '-')
        {
            //若优先级比栈顶元素低
            if (!operatorStack.empty() && (str[pos] == '+' || str[pos] == '-'))
            {
                node = (struct Node *)malloc(sizeof(struct Node));
                node->c = operatorStack.top();
                node->right = subTreeStack.top();
                subTreeStack.pop();
                node->left = subTreeStack.top();
                subTreeStack.pop();

                subTreeStack.push(node);

                operatorStack.pop();
                operatorStack.push(str[pos]);
            }
            else
                operatorStack.push(str[pos]);
        }
    }

    while (!operatorStack.empty())
    {

        node = (struct Node *)malloc(sizeof(struct Node));
        node->c = operatorStack.top();
        operatorStack.pop();
        node->right = subTreeStack.top();
        subTreeStack.pop();
        node->left = subTreeStack.top();
        subTreeStack.pop();

        subTreeStack.push(node);
    }
    return subTreeStack.top();
}
void PrintTree(struct Node *node)
{
    if (node == NULL)
        return;
    PrintTree(node->left);

    printf("%c", node->c);
    PrintTree(node->right);
}

int main()
{
    struct Node *root = BuildTree();
    PrintTree(root);
    return 0;
}