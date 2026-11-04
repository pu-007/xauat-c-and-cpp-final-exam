/* 26_prefix_window 前缀和与固定窗口 | ISO C99 | 拓展
 * 来源/关系：S1 p33 编程21的线性数组变式；拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..1000,k=1..n；n个绝对值<=10^6整数；输出最大连续k项和及最早起点
 * 思想：前缀和将区间和化成一次相减；全负数组也必须从合法窗口初始化。
 * 复杂度：O(n)；前缀和O(n)空间，窗口状态O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
int main(void) {
    int n, k;
    long long prefix[1001] = {0};
    if (scanf("%d%d", &n, &k) != 2 || n < 1 || n > 1000 || k < 1 || k > n)
        return 1;
    for (int i = 0; i < n; ++i) {
        int x;
        if (scanf("%d", &x) != 1 || x < -1000000 || x > 1000000)
            return 1;
        prefix[i + 1] = prefix[i] + x;
    }
    long long best = prefix[k];
    int start = 0;
    for (int i = 1; i + k <= n; ++i) {
        long long sum = prefix[i + k] - prefix[i];
        if (sum > best) {
            best = sum;
            start = i;
        }
    }
    printf("%lld %d\n", best, start);
    return 0;
}
