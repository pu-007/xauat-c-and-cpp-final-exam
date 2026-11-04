/* 28_queens N皇后回溯 | ISO C99 | 拓展
 * 来源/关系：S1 p93 附加74八皇后的推广（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..10；输出所有合法摆放方案数（对称方案分别计数）
 * 思想：逐行选择列；列及两条对角线记录占用；返回上一层时撤销选择。
 * 复杂度：保守上界O(n·n!)，空间O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
static int column[10], diag1[19], diag2[19];
static long long search(int row, int n) {
    if (row == n)
        return 1;
    long long count = 0;
    for (int c = 0; c < n; ++c) {
        int d1 = row + c, d2 = row - c + n - 1;
        if (column[c] || diag1[d1] || diag2[d2])
            continue;
        column[c] = diag1[d1] = diag2[d2] = 1;
        count += search(row + 1, n);
        column[c] = diag1[d1] = diag2[d2] = 0; /* 回溯撤销，否则后续分支受到污染。 */
    }
    return count;
}
int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 1 || n > 10)
        return 1;
    printf("%lld\n", search(0, n));
    return 0;
}
