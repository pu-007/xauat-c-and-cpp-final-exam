/* 27_knapsack 0/1背包动态规划 | ISO C++11 | 拓展
 * 来源/关系：自编算法拓展，未计入资料考频（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100,容量W=0..1000；n行正整数重量和0..10^6价值；输出最大价值
 * 思想：dp[c]是已处理物品在容量c内的最优值；容量倒序保证每物品至多用一次。
 * 复杂度：O(nW)，空间O(W)
 * 练习：把容量循环改成正序，找反例说明它变成完全背包。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：27_knapsack.c用定长数组与if比较；本文件用vector<long long>和std::max。
 */
#include <iostream> /* 流输入输出。 */
#include <vector> /* 动态规划表。 */
#include <algorithm> /* std::max。 */
int main() {
    int n, capacity; /* 物品数和容量。 */
    if (!(std::cin >> n >> capacity) || n < 0 || n > 100 || capacity < 0 || capacity > 1000)
        return 1; /* 检查读取及范围。 */
    std::vector<long long> dp(capacity + 1, 0); /* 各容量的初始最优值均为零。 */
    for (int i = 0; i < n; ++i) { /* 每次处理一件物品。 */
        int weight, value; /* 当前物品数据。 */
        if (!(std::cin >> weight >> value) || weight < 1 || weight > 1000000 || value < 0 ||
            value > 1000000)
            return 1; /* 验证物品数据。 */
        for (int c = capacity; c >= weight; --c) /* 从大到小更新，避免重复取同一物品。 */
            dp[c] = std::max(dp[c], dp[c - weight] + value); /* 不选与选取较大值。 */
    }
    std::cout << dp[capacity] << '\n'; /* 输出容量内的最优值。 */
}
