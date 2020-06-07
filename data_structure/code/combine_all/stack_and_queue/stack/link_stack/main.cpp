/*
 * function:实现编译器中的符号成对检测
 * 算法思路：从第一个字符开始扫描，当遇见普通字符时忽略，
 *          当遇见左符号时压入栈中，当遇见右符号时弹出栈顶符号，并进行匹配
 * 结束：   
 *      成功：所有字符扫描完毕，且栈为空
 *      失败：匹配失败或所有字符扫描完毕但栈非空
 */

#include <iostream>
#include "static_stack.h"
#include "link_stack.h"

using namespace std;
using namespace DTLib;

bool is_left(char c)
{
    return (c == '(') || (c == '{') || (c == '[') || (c == '<');
}

bool is_right(char c)
{
    return (c == ')') || (c == '}') || (c == ']') || (c == '>');
}

bool is_quot(char c)
{
    return (c == '\'') || (c == '\"');
}

bool is_match(char l, char r)
{
    return  ((l == '(') && (r == ')')) ||
            ((l == '{') && (r == '}')) ||
            ((l == '[') && (r == ']')) ||
            ((l == '<') && (r == '>')) ||
            ((l == '\'') && (r == '\'')) ||
            ((l == '\"') && (r == '\"'));
}

bool scan(const char *code)
{
    LinkStack<char> stack;
    int i = 0;
    bool ret = true;

    code = (code == NULL) ? "" : code;

    while(ret && (code[i] != '\0')) {
        if (is_left(code[i])) {
            stack.push(code[i]);
        } else if(is_right(code[i])){
            if (stack.size() > 0 && is_match(stack.top(), code[i])) {
                stack.pop();
            } else {
                ret = false;
            }
        } else if(is_quot(code[i])) {
            if (stack.size() == 0 || !is_match(stack.top(), code[i])) {
                stack.push(code[i]);
            } else if (is_match(stack.top(), code[i])) {
                stack.pop();
            }
        }
        i++;
    }

    return ret && (stack.size() == 0);
}

int main(int argc, char **argv)
{

    cout << scan("\"<a{s[d(yjur)t]a}s>\"") << endl;

    return 0;
}
