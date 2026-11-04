/* 04_characters 字符分类与大小写 | ISO C99 | 基础
 * 来源/关系：S1 p22 编程3；S2 填空1/5；S5 p1 例3.10（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：读到换行或EOF；输出字母、数字、空格、其他的个数；只针对单字节英语文本
 * 思想：getchar用int接收EOF；字符分类函数接收unsigned char值。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <ctype.h>
int main(void) {
    int c;
    int letters = 0, digits = 0, spaces = 0, other = 0;
    while ((c = getchar()) != EOF && c != '\n') {
        if (isalpha((unsigned char)c))
            ++letters;
        else if (isdigit((unsigned char)c))
            ++digits;
        else if (c == ' ')
            ++spaces; /* 原题统计空格；不能把制表符也算进去。 */
        else
            ++other;
    }
    printf("%d %d %d %d\n", letters, digits, spaces, other);
    return 0;
}
