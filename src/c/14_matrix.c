/* 14_matrix 二维数组、转置、对角线、行列极值 | ISO C99 | 提高
 * 来源/关系：S1 p32 编程8/10、p42 编程4；S5 p3/p4（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入3×3整数矩阵，元素绝对值<=10^6；输出转置矩阵、去重对角和、最大值及行列（从0起）
 * 思想：a+i跨一行，a[i]+j跨一个元素；对角线交点只加一次。
 * 复杂度：推广n×n时O(n²)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
static void transpose(const int a[3][3], int b[3][3]) {
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            b[j][i] = a[i][j];
}
int main(void) {
    int a[3][3], b[3][3];
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (scanf("%d", &a[i][j]) != 1 || a[i][j] < -1000000 || a[i][j] > 1000000)
                return 1;
    /* C99给多维数组添加const限定存在转换限制，用显式指向const行的转换。 */
    transpose((const int (*)[3])a, b);
    long long diagonal = 0;
    int r = 0, c = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            printf("%s%d", j ? " " : "", b[i][j]);
            if (i == j || i + j == 2)
                diagonal += a[i][j];
            if (a[i][j] > a[r][c]) {
                r = i;
                c = j;
            }
        }
        putchar('\n');
    }
    printf("%lld\n%d %d %d\n", diagonal, a[r][c], r, c);
    return 0;
}
