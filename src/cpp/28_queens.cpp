/* 28_queens N皇后回溯 | ISO C++11 | 拓展
 * 来源/关系：S1 p93 附加74八皇后的推广（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..10；输出所有合法摆放方案数（对称方案分别计数）
 * 思想：逐行选择列；列及两条对角线记录占用；返回上一层时撤销选择。
 * 复杂度：保守上界O(n·n!)，空间O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <array>
class Queens { // 用类把搜索状态封装，避免全局状态影响多次求解。
    std::array<bool, 10> column{};
    std::array<bool, 19> d1{}, d2{};

  public:
    long long solve(int row, int n) {
        if (row == n)
            return 1;
        long long count = 0;
        for (int c = 0; c < n; ++c) {
            int a = row + c, b = row - c + n - 1;
            if (column[c] || d1[a] || d2[b])
                continue;
            column[c] = d1[a] = d2[b] = true;
            count += solve(row + 1, n);
            column[c] = d1[a] = d2[b] = false;
        }
        return count;
    }
};
int main() {
    int n;
    if (!(std::cin >> n) || n < 1 || n > 10)
        return 1;
    Queens solver;
    std::cout << solver.solve(0, n) << '\n';
}
