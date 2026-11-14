/* 04_characters 字母、数字、空格和其他字符统计 | ISO C99 | 基础
 * 来源/关系：S1 p22 编程3；S2 填空1/5；S5 p1 例3.10（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：读到换行或EOF；输出字母、数字、空格、其他的个数；只针对单字节英语文本
 * 思想：getchar用int接收EOF；字符分类函数接收unsigned char值。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：同目录 04_characters.cpp 用 getline 保存整行并用范围for遍历。
 */
#include <stdio.h> /* 声明getchar和printf。 */
#include <ctype.h> /* 声明isalpha和isdigit字符分类函数。 */
int main(void) { /* C程序入口。 */
    int c; /* 用int接收字符，才能区分所有字节值和EOF。 */
    int letters = 0, digits = 0, spaces = 0, other = 0; /* 四类计数器从0开始。 */
    while ((c = getchar()) != EOF && c != '\n') { /* 读至换行或EOF；换行本身不计入。 */
        if (isalpha((unsigned char)c)) /* 字母包括大写和小写。 */
            ++letters; /* 字母数增加1。 */
        else if (isdigit((unsigned char)c)) /* 否则检查是否为数字。 */
            ++digits; /* 数字数增加1。 */
        else if (c == ' ') /* 只把普通空格归入空格类。 */
            ++spaces; /* 空格数增加1；制表符不属于此类。 */
        else
            ++other; /* 其余字符归入其他类。 */
    }
    printf("%d %d %d %d\n", letters, digits, spaces, other); /* 按题目顺序输出四个计数。 */
    return 0; /* 表示程序正常结束。 */
}
