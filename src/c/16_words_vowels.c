/* 16_words_vowels 单词状态机、元音筛选、字符排序 | ISO C99 | 提高
 * 来源/关系：S5 p3 单词数、p7–8 元音/字符排序；S1 p32 编程14（页码均为 PDF
 * 页码；此文件为重写的教学实现）
 * 输入输出约定：输入一行<=100字节；单词按空白分隔；输出单词数、原顺序元音、升序字符（含空格）
 * 思想：状态从单词外进入单词内时才计数；筛选维护写位置，排序不包含结束符。
 * 复杂度：C字符排序O(n²)，C++排序O(n log n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main(void) {
    char s[102], vowels[102];
    if (!fgets(s, sizeof s, stdin))
        return 1;
    size_t n = strcspn(s, "\n");
    if (n > 100)
        return 1;
    s[n] = '\0';
    int inside = 0, count = 0;
    size_t used = 0;
    for (size_t i = 0; i < n; ++i) {
        unsigned char c = (unsigned char)s[i];
        if (isspace(c))
            inside = 0;
        else if (!inside) {
            ++count;
            inside = 1;
        }
        if (strchr("aeiouAEIOU", c))
            vowels[used++] = s[i];
    }
    vowels[used] = '\0';
    for (size_t i = 1; i < n; ++i)
        for (size_t j = 0; j < n - i; ++j)
            if ((unsigned char)s[j] > (unsigned char)s[j + 1]) {
                char t = s[j];
                s[j] = s[j + 1];
                s[j + 1] = t;
            }
    printf("%d\n%s\n%s\n", count, vowels, s);
    return 0;
}
