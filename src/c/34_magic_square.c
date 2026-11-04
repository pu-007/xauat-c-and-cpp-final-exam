/* 34_magic_square 奇数阶魔方阵 | ISO C99 | 提高
 * 来源/关系：S1 p33–34 编程23；p99–102另有更多阶数拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入奇数n=1..15；输出n×n魔方阵
 * 思想：从首行中间开始向右上走；遇占用则从原位置向下；用模运算处理边界。
 * 复杂度：O(n²)，空间O(n²)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
int main(void) {
    int n, a[15][15] = {0};
    if (scanf("%d", &n) != 1 || n < 1 || n > 15 || n % 2 == 0)
        return 1;
    int r = 0, c = n / 2;
    for (int value = 1; value <= n * n; ++value) {
        a[r][c] = value;
        int nr = (r + n - 1) % n, nc = (c + 1) % n;
        if (a[nr][nc])
            r = (r + 1) % n;
        else {
            r = nr;
            c = nc;
        }
    }
    for (r = 0; r < n; ++r) {
        for (c = 0; c < n; ++c)
            printf("%s%d", c ? " " : "", a[r][c]);
        putchar('\n');
    }
    return 0;
}
