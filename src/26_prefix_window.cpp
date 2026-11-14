/* 26_prefix_window 前缀和与固定窗口 | ISO C++11 | 拓展
 * 来源/关系：S1 p33 编程21的线性数组变式；拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..1000,k=1..n；n个绝对值<=10^6整数；输出最大连续k项和及最早起点
 * 思想：前缀和将区间和化成一次相减；全负数组也必须从合法窗口初始化。
 * 复杂度：O(n)；前缀和O(n)空间，窗口状态O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：26_prefix_window.c用定长前缀和数组，C++用vector保存输入并逐次更新滑窗。
 */
#include <iostream> /* 流输入输出。 */
#include <vector> /* 保存输入以移除窗口左端。 */
int main() {
    int n, k; /* 数量与窗口长度。 */
    if (!(std::cin >> n >> k) || n < 1 || n > 1000 || k < 1 || k > n)
        return 1; /* 校验范围。 */
    std::vector<int> a(n); /* 保存各输入值。 */
    for (int &x : a) /* 引用使输入直接写入vector元素。 */
        if (!(std::cin >> x) || x < -1000000 || x > 1000000)
            return 1; /* 输入或范围错误。 */
    long long window = 0; /* 当前窗口和。 */
    for (int i = 0; i < k; ++i) /* 累加前k项。 */
        window += a[i]; /* 构造第一个合法窗口。 */
    long long best = window; /* 全负输入时也有合法初值。 */
    int start = 0; /* 最佳窗口零基起点。 */
    for (int i = k; i < n; ++i) { /* i是新加入元素的位置。 */
        window += a[i]; /* 纳入右端新元素。 */
        window -= a[i - k]; /* 移除原左端。 */
        if (window > best) { /* 相等不更新，保留较早起点。 */
            best = window; /* 记录更大的窗口和。 */
            start = i - k + 1; /* 当前右端对应的左端下标。 */
        }
    }
    std::cout << best << ' ' << start << '\n'; /* 输出最大和及零基起点。 */
}
