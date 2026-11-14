/* 28_queens N皇后回溯 | ISO C99 | 拓展
 * 来源/关系：S1 p93 附加74八皇后的推广（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..10；输出所有合法摆放方案数（对称方案分别计数）
 * 思想：逐行选择列；列及两条对角线记录占用；返回上一层时撤销选择。
 * 复杂度：保守上界O(n·n!)，空间O(n)
 * 对照 28_queens.cpp：C 使用静态数组和函数，C++ 用类封装状态。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* 声明 scanf 和 printf；C++ 对照使用 cin、cout。 */
static int column[10], diag1[19], diag2[19]; /* 静态数组自动清零，分别记录列及两种对角线。 */
static long long search(int row, int n) { /* 前 row 行已合法放置，返回后续方案数。 */
    if (row == n) /* 每行都已放置，得到一个完整方案。 */
        return 1; /* 此分支恰有一个完整方案。 */
    long long count = 0; /* 累加当前行各合法选择的方案数。 */
    for (int c = 0; c < n; ++c) { /* 枚举当前行的每一列。 */
        int d1 = row + c, d2 = row - c + n - 1; /* 两种对角线编号均在 0..2n-2。 */
        if (column[c] || diag1[d1] || diag2[d2]) /* 与已有皇后冲突时跳过。 */
            continue;
        column[c] = diag1[d1] = diag2[d2] = 1; /* 暂时占用列和两条对角线。 */
        count += search(row + 1, n); /* 递归放下一行，并累加方案。 */
        column[c] = diag1[d1] = diag2[d2] = 0; /* 撤销当前选择以尝试其他列。 */
    }
    return count; /* 当前前缀下的全部方案数。 */
}
int main(void) {
    int n; /* 棋盘边长。 */
    if (scanf("%d", &n) != 1 || n < 1 || n > 10) /* 检查读入及数组容量。 */
        return 1; /* 输入非法时以非零状态结束。 */
    printf("%lld\n", search(0, n)); /* 从第零行开始搜索并输出总数。 */
    return 0; /* 正常结束。 */
}
