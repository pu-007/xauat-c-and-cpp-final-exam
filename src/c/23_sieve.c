/* 23_sieve 埃氏筛：批量判断素数 | ISO C99 | 提高
 * 来源/关系：S1 p32 编程7；08的批量优化（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100000；输出不大于n的所有素数
 * 思想：从p²开始划去倍数，小于p²的倍数已被更小素数处理。
 * 复杂度：O(n log log n)，空间O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <stdlib.h>
int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0 || n > 100000)
        return 1;
    unsigned char *composite = calloc((size_t)n + 1, sizeof *composite);
    if (!composite)
        return 1;
    for (int p = 2; p <= n / p; ++p)
        if (!composite[p])
            for (int j = p * p; j <= n; j += p)
                composite[j] = 1;
    int first = 1;
    for (int p = 2; p <= n; ++p)
        if (!composite[p]) {
            printf("%s%d", first ? "" : " ", p);
            first = 0;
        }
    putchar('\n');
    free(composite);
    return 0;
}
