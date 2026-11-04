/* 26_prefix_window 前缀和与固定窗口 | ISO C++11 | 拓展
 * 来源/关系：S1 p33 编程21的线性数组变式；拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..1000,k=1..n；n个绝对值<=10^6整数；输出最大连续k项和及最早起点
 * 思想：前缀和将区间和化成一次相减；全负数组也必须从合法窗口初始化。
 * 复杂度：O(n)；前缀和O(n)空间，窗口状态O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <vector>
int main() {
    int n, k;
    if (!(std::cin >> n >> k) || n < 1 || n > 1000 || k < 1 || k > n)
        return 1;
    std::vector<int> a(n);
    for (int &x : a)
        if (!(std::cin >> x) || x < -1000000 || x > 1000000)
            return 1;
    long long window = 0;
    for (int i = 0; i < k; ++i)
        window += a[i];
    long long best = window;
    int start = 0;
    for (int i = k; i < n; ++i) {
        window += a[i];
        window -= a[i - k];
        if (window > best) {
            best = window;
            start = i - k + 1;
        }
    }
    std::cout << best << ' ' << start << '\n'; // 与C的前缀和方案对照，滑窗额外状态O(1)。
}
