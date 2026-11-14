/* 13_binary_search 二分查找第一个匹配 | ISO C++11 | 拓展
 * 来源/关系：S2 填空6的线性查找拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100及目标x，再输入非降序数组；输出首个匹配下标或-1
 * 思想：半开区间[left,right)；小于目标的在左侧，候选答案始终在未排除范围。
 * 复杂度：查找O(log n)，含输入及验证的整个程序O(n)
 * 对照 13_binary_search.c：C 手写二分，C++ 使用 lower_bound 和 is_sorted。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // cin、cout 对应 C 标准输入输出。
#include <vector> // 保存输入，对应 C 数组。
#include <algorithm> // is_sorted 和 lower_bound 对应 C 的检查及二分循环。
int main() {
    int n, x; // 个数和目标。
    if (!(std::cin >> n >> x) || n < 0 || n > 100)
        return 1; // 拒绝无效个数或输入。
    std::vector<int> a(n); // n=0 时容器为空。
    for (int &v : a) // 逐项写入。
        if (!(std::cin >> v))
            return 1;
    if (!std::is_sorted(a.begin(), a.end())) // 二分要求非降序。
        return 1;
    auto it = std::lower_bound(a.begin(), a.end(), x); // 首个不小于 x 的位置，可能为 end。
    std::cout << (it != a.end() && *it == x ? it - a.begin() : -1) << '\n'; // 先判越界，再判相等。
}
