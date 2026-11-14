/* 23_sieve 埃氏筛：批量判断素数 | ISO C99 | 提高
 * 来源/关系：S1 p32 编程7；08的批量优化（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100000；输出不大于n的所有素数
 * 思想：从p²开始划去倍数，小于p²的倍数已被更小素数处理。
 * 复杂度：O(n log log n)，空间O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：23_sieve.cpp用vector<unsigned char>自动清零和释放；C用calloc/free管理标记。
 */
#include <stdio.h> /* 输入输出。 */
#include <stdlib.h> /* calloc和free。 */
int main(void) {
    int n; /* 筛选上界。 */
    if (scanf("%d", &n) != 1 || n < 0 || n > 100000)
        return 1; /* 验证上界。 */
    unsigned char *composite = calloc((size_t)n + 1, sizeof *composite); /* 标记初始全为零。 */
    if (!composite)
        return 1; /* 分配失败。 */
    for (int p = 2; p <= n / p; ++p) /* 用除法避免平方比较溢出。 */
        if (!composite[p]) /* 只用尚未划去的素数筛倍数。 */
            for (int j = p * p; j <= n; j += p) /* 更小倍数已被小素数划去。 */
                composite[j] = 1; /* 标记合数。 */
    int first = 1; /* 控制输出分隔符。 */
    for (int p = 2; p <= n; ++p) /* 从2开始，排除0和1。 */
        if (!composite[p]) {
            printf("%s%d", first ? "" : " ", p); /* 输出未标记数。 */
            first = 0; /* 后续输出项之前要加空格。 */
        }
    putchar('\n'); /* 无素数时输出空行。 */
    free(composite); /* 释放标记数组。 */
    return 0; /* 返回成功状态。 */
}
