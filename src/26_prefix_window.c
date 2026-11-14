/* 26_prefix_window 前缀和与固定窗口 | ISO C99 | 拓展
 * 来源/关系：S1 p33 编程21的线性数组变式；拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..1000,k=1..n；n个绝对值<=10^6整数；输出最大连续k项和及最早起点
 * 思想：前缀和将区间和化成一次相减；全负数组也必须从合法窗口初始化。
 * 复杂度：O(n)；前缀和O(n)空间，窗口状态O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：26_prefix_window.cpp用vector保存输入并滑窗加减；C以定长long long数组存前缀和。
 */
#include <stdio.h> /* 输入输出。 */
int main(void) {
    int n, k; /* 元素数及窗口长度。 */
    long long prefix[1001] = {0}; /* prefix[i]为前i项之和。 */
    if (scanf("%d%d", &n, &k) != 2 || n < 1 || n > 1000 || k < 1 || k > n)
        return 1; /* 保证至少一个合法窗口。 */
    for (int i = 0; i < n; ++i) { /* 逐项读取并构造前缀和。 */
        int x; /* 当前元素。 */
        if (scanf("%d", &x) != 1 || x < -1000000 || x > 1000000)
            return 1; /* 拒绝缺失或越界的数。 */
        prefix[i + 1] = prefix[i] + x; /* 扩展前缀和。 */
    }
    long long best = prefix[k]; /* 用第一个合法窗口初始化，兼容全负值。 */
    int start = 0; /* 最佳窗口的零基起点。 */
    for (int i = 1; i + k <= n; ++i) { /* 从第二个窗口开始枚举。 */
        long long sum = prefix[i + k] - prefix[i]; /* [i,i+k)的区间和。 */
        if (sum > best) { /* 仅严格变大才更新，保留最早起点。 */
            best = sum; /* 保存更大的窗口和。 */
            start = i; /* 同时记录它的起点。 */
        }
    }
    printf("%lld %d\n", best, start); /* 输出最大和与零基起点。 */
    return 0; /* 正常结束。 */
}
