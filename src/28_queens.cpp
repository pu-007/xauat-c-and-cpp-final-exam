/* 28_queens N皇后回溯 | ISO C++11 | 拓展
 * 来源/关系：S1 p93 附加74八皇后的推广（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..10；输出所有合法摆放方案数（对称方案分别计数）
 * 思想：逐行选择列；列及两条对角线记录占用；返回上一层时撤销选择。
 * 复杂度：保守上界O(n·n!)，空间O(n)
 * 对照 28_queens.c：C 用静态数组，C++ 用类及值初始化的 std::array。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 提供 cin、cout；C 对照用 scanf、printf。
#include <array> // 提供固定大小的 std::array；C 对照用静态数组。
class Queens { // 用类把搜索状态封装，避免全局状态影响多次求解。
    std::array<bool, 10> column{}; // 值初始化为 false，记录各列占用。
    std::array<bool, 19> d1{}, d2{}; // 两类对角线最多各 19 条。

  public:
    long long solve(int row, int n) { // 前 row 行已合法摆放，返回后续方案数。
        if (row == n) // 到达第 n 行表示所有皇后均已放置。
            return 1; // 此分支贡献一个方案。
        long long count = 0; // 汇总当前前缀下所有分支。
        for (int c = 0; c < n; ++c) { // 枚举当前行的列。
            int a = row + c, b = row - c + n - 1; // 对角线下标偏移到非负范围。
            if (column[c] || d1[a] || d2[b]) // 冲突时跳过该列。
                continue;
            column[c] = d1[a] = d2[b] = true; // 标记本次占用。
            count += solve(row + 1, n); // 搜索下一行并累计方案数。
            column[c] = d1[a] = d2[b] = false; // 撤销占用，保证其他分支独立。
        }
        return count; // 返回本层得到的总方案数。
    }
};
int main() {
    int n; // 棋盘边长。
    if (!(std::cin >> n) || n < 1 || n > 10) // 读入失败或超过数组容量时退出。
        return 1; // 非法输入以非零状态结束。
    Queens solver; // 对象内的布尔数组均初始化为 false。
    std::cout << solver.solve(0, n) << '\n'; // 从第 0 行开始，输出合法方案数。
}
