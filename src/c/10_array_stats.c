/* 10_array_stats 数组、平均数、极值与下标 | ISO C99 | 基础
 * 来源/关系：S2 改错2/编程8/13；S5 p3–5（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..100，再输入n个绝对值<=10^6的整数；输出最小值及首个下标、最大值及首个下标、平均数
 * 思想：极值初始化为首元素；sum用宽类型，平均数先转double。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
int main(void) {
    int n, a[100];
    if (scanf("%d", &n) != 1 || n < 1 || n > 100)
        return 1;
    for (int i = 0; i < n; ++i)
        if (scanf("%d", &a[i]) != 1 || a[i] < -1000000 || a[i] > 1000000)
            return 1;
    int lo = 0, hi = 0;
    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += a[i];
        if (a[i] < a[lo])
            lo = i;
        if (a[i] > a[hi])
            hi = i;
    }
    printf("%d %d %d %d %.2f\n", a[lo], lo, a[hi], hi, (double)sum / n);
    return 0;
}
