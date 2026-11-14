/* 10_array_stats 数组、平均数、极值与下标 | ISO C++11 | 基础
 * 来源/关系：S2 改错2/编程8/13；S5 p3–5（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..100，再输入n个绝对值<=10^6的整数；输出最小值及首个下标、最大值及首个下标、平均数
 * 思想：极值初始化为首元素；sum用宽类型，平均数先转double。
 * 复杂度：O(n)
 * 对照 10_array_stats.c：C 手写扫描；C++ 使用 vector 和标准算法。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // cin、cout 对应 C 的 scanf、printf。
#include <vector> // 动态数组，对应 C 定长数组。
#include <algorithm> // min_element、max_element 对应 C 手写扫描。
#include <numeric> // accumulate 对应 C 的累加循环。
#include <iomanip> // fixed 和 setprecision 对应 printf 的 %.2f。
int main() {
    int n; // 元素个数。
    if (!(std::cin >> n) || n < 1 || n > 100) // 保障范围非空。
        return 1;
    std::vector<int> a(n); // vector 管理长度和生命周期。
    for (int &x : a) // 引用允许直接写入容器元素。
        if (!(std::cin >> x) || x < -1000000 || x > 1000000)
            return 1;
    auto lo = std::min_element(a.begin(), a.end()), hi = std::max_element(a.begin(), a.end()); // 均取第一个极值。
    auto sum = std::accumulate(a.begin(), a.end(), 0LL); // 0LL 决定累加类型。
    std::cout << *lo << ' ' << lo - a.begin() << ' ' << *hi << ' ' << hi - a.begin() << ' ' // 解引用取值，迭代器相减得到下标。
              << std::fixed << std::setprecision(2) << static_cast<double>(sum) / n << '\n'; // 浮点平均数。
}
