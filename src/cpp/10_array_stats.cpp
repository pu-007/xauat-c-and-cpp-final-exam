/* 10_array_stats 数组、平均数、极值与下标 | ISO C++11 | 基础
 * 来源/关系：S2 改错2/编程8/13；S5 p3–5（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..100，再输入n个绝对值<=10^6的整数；输出最小值及首个下标、最大值及首个下标、平均数
 * 思想：极值初始化为首元素；sum用宽类型，平均数先转double。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
int main() {
    int n;
    if (!(std::cin >> n) || n < 1 || n > 100)
        return 1;
    std::vector<int> a(n); // vector管理长度与生命周期；下标仍需要自己保证合法。
    for (int &x : a)
        if (!(std::cin >> x) || x < -1000000 || x > 1000000)
            return 1;
    auto lo = std::min_element(a.begin(), a.end()), hi = std::max_element(a.begin(), a.end());
    auto sum = std::accumulate(a.begin(), a.end(), 0LL); // 0LL决定累加器类型，0会使用int。
    std::cout << *lo << ' ' << lo - a.begin() << ' ' << *hi << ' ' << hi - a.begin() << ' '
              << std::fixed << std::setprecision(2) << static_cast<double>(sum) / n << '\n';
}
