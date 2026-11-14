/* 53_bracket_stack：用栈检查括号是否匹配 | ISO C99 | 算法拓展
 * 题目：输入一行最多100个括号字符，仅允许 ()[]{}；输出1表示匹配，0表示不匹配。
 * 空行视为匹配；出现其他字符、超过100个字符或无法读取时以状态码1退出。
 * 思想：左括号依次压栈；右括号必须与栈顶相配并弹栈；结束时栈必须为空。
 * 复杂度：时间O(n)，栈空间O(n)，n为输入字符数。
 * C++对照：53_bracket_stack.cpp使用string和标准stack；本版使用字符数组和下标模拟栈，
 *          getchar/printf分别对应C++的getline/cout。此题是数据结构拓展，不计入原卷题量。
 */
#include <stdio.h> /* 提供getchar和printf。 */

static int matches(char left, char right) { /* 判断左右括号的种类是否相同。 */
    return (left == '(' && right == ')') || (left == '[' && right == ']') ||
           (left == '{' && right == '}'); /* 三种合法配对之一即返回1。 */
}

int main(void) { /* 程序入口。 */
    char line[100]; /* 只存储有效的括号字符。 */
    char stack[100]; /* 每个左括号最多压栈一次。 */
    size_t length = 0; /* 输入行中已保存的括号数。 */
    int depth = 0; /* 当前栈内元素数量，也是下一次压栈的位置。 */
    int c = getchar(); /* 使用int保存字符或文件结束标记EOF。 */
    if (c == EOF) /* 没有读到任何输入。 */
        return 1; /* 不把缺失的输入行当作空行。 */
    while (c != EOF && c != '\n') { /* 逐字节读取本行，不包含换行。 */
        if (c == '\r') { /* 回车只允许出现在CRLF或文件末尾。 */
            c = getchar(); /* 检查回车后是否为换行或文件结束。 */
            if (c != '\n' && c != EOF) /* 行中间的回车不是合法括号。 */
                return 1; /* 非法输入时不输出判断结果。 */
            break; /* 已读完本行。 */
        }
        if (length == sizeof line) /* 已有100个字符，不能再继续保存。 */
            return 1; /* 超长时退出。 */
        if (c != '(' && c != ')' && c != '[' && c != ']' && c != '{' && c != '}')
            return 1; /* 任何非括号字节都无效，包括零字节。 */
        line[length++] = (char)c; /* 保存当前括号，推进有效长度。 */
        c = getchar(); /* 读取下一个字符或EOF。 */
    }
    for (size_t i = 0; i < length; ++i) { /* 再按从左到右的顺序处理括号。 */
        char c = line[i]; /* 当前已通过校验的括号。 */
        if (c == '(' || c == '[' || c == '{') { /* 遇到左括号。 */
            stack[depth] = c; /* 放到栈顶后面的空位。 */
            ++depth; /* 更新栈的有效长度。 */
        } else { /* 遇到右括号。 */
            if (depth == 0 || !matches(stack[depth - 1], c)) { /* 没有左括号或种类不匹配。 */
                printf("0\n"); /* 输出不匹配。 */
                return 0; /* 判定完成，无需继续。 */
            }
            --depth; /* 已配对的栈顶左括号弹出。 */
        }
    }
    printf("%d\n", depth == 0); /* 若还有左括号则不匹配；空栈表示全部配对。 */
    return 0; /* 正常结束。 */
}
