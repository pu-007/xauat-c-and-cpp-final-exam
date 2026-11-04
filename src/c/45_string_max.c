/* 45_string_max 三个字符串中字典序最大者 | ISO C99 | 基础
 * 来源/关系：S6实验2(4) p13–14（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入3个无空格字符串，每个1..9字节；输出字典序最大者
 * 思想：strcmp比较内容；最大不是最长，比较规则基于字符编码。
 * 复杂度：O(字符串总长度)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <string.h>
int main(void) {
    char a[10], b[10], c[10], best[10];
    if (scanf("%9s%9s%9s", a, b, c) != 3)
        return 1;
    strcpy(best, strcmp(a, b) > 0 ? a : b);
    if (strcmp(c, best) > 0)
        strcpy(best, c);
    puts(best);
    return 0;
}
