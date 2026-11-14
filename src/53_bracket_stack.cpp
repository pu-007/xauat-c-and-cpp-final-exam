/* 53_bracket_stack：用栈检查括号是否匹配 | ISO C++11 | 算法拓展
 * 题目：输入一行最多100个括号字符，仅允许 ()[]{}；输出1表示匹配，0表示不匹配。
 * 空行视为匹配；出现其他字符、超过100个字符或无法读取时以状态码1退出。
 * 思想：左括号依次压栈；右括号必须与栈顶相配并弹栈；结束时栈必须为空。
 * 复杂度：时间O(n)，栈空间O(n)，n为输入字符数。
 * C对照：53_bracket_stack.c用字符数组与下标模拟栈；本版使用string和标准stack，
 *        getline/cout分别对应C的getchar/printf。此题是数据结构拓展，不计入原卷题量。
 */
#include <iostream> /* 提供cin和cout。 */
#include <stack> /* 提供后进先出的std::stack。 */
#include <string> /* 提供std::string与getline。 */

static bool matches(char left, char right) { /* 判断左右括号的种类是否相同。 */
    return (left == '(' && right == ')') || (left == '[' && right == ']') ||
           (left == '{' && right == '}'); /* 三种合法配对之一即返回true。 */
}

int main() { /* 程序入口。 */
    std::string line; /* 保存输入的一整行。 */
    if (!std::getline(std::cin, line)) /* 读取一行，检查是否有输入。 */
        return 1; /* 没有读到行时退出。 */
    if (!line.empty() && line.back() == '\r') /* getline移除换行，但CRLF中的回车仍可能保留。 */
        line.pop_back(); /* 排除回车符。 */
    if (line.size() > 100) /* 允许空行，最多100个括号。 */
        return 1; /* 超长时不输出判断结果。 */
    for (char c : line) { /* 先检查整行，避免无效字符被当作括号。 */
        if (c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}')
            return 1; /* 非题目允许的字符，退出且不输出。 */
    }
    std::stack<char> brackets; /* 标准栈保存尚未配对的左括号。 */
    for (char c : line) { /* 按从左到右的顺序处理括号。 */
        if (c == '(' || c == '[' || c == '{') { /* 遇到左括号。 */
            brackets.push(c); /* 把当前左括号压到栈顶。 */
        } else { /* 遇到右括号。 */
            if (brackets.empty() || !matches(brackets.top(), c)) { /* 空栈或种类不匹配。 */
                std::cout << "0\n"; /* 输出不匹配。 */
                return 0; /* 判定完成，无需继续。 */
            }
            brackets.pop(); /* 已配对的栈顶左括号弹出。 */
        }
    }
    std::cout << brackets.empty() << '\n'; /* 空栈输出1，否则有未匹配的左括号，输出0。 */
    return 0; /* 正常结束。 */
}
