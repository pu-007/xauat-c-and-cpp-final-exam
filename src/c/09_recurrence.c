/* 09_recurrence 斐波那契与分数序列 | ISO C99 | 基础
 * 来源/关系：S5 p2 例5.8；S2 编程10（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入n=1..90；输出F(n)，F(1)=F(2)=1；再输出前20项分数和（六位小数）
 * 思想：先保存下一项再移动状态；分数递推用double避免整数除法。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 1 || n > 90)
        return 1;
    unsigned long long a = 0, b = 1;
    for (int i = 1; i < n; ++i) {
        unsigned long long next = a + b;
        a = b;
        b = next;
    }
    double x = 2, y = 1, sum = 0;
    for (int i = 0; i < 20; ++i) {
        sum += x / y;
        double next = x + y;
        y = x;
        x = next;
    }
    printf("%llu %.6f\n", b, sum);
    return 0;
}
