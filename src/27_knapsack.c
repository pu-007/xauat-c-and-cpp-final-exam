/* 27_knapsack 0/1背包动态规划 | ISO C99 | 拓展
 * 来源/关系：自编算法拓展，未计入资料考频（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100,容量W=0..1000；n行正整数重量和0..10^6价值；输出最大价值
 * 思想：dp[c]是已处理物品在容量c内的最优值；容量倒序保证每物品至多用一次。
 * 复杂度：O(nW)，空间O(W)
 * 练习：把容量循环改成正序，找反例说明它变成完全背包。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：27_knapsack.cpp用vector<long long>与std::max；C用定长数组和if比较两个方案。
 */
#include <stdio.h> /* 输入输出。 */
int main(void) {
    int n, capacity; /* 物品数量及背包容量。 */
    long long dp[1001] = {0}; /* dp[c]是已处理物品在容量c内的最优价值。 */
    if (scanf("%d%d", &n, &capacity) != 2 || n < 0 || n > 100 || capacity < 0 || capacity > 1000)
        return 1; /* 约束容量和数量。 */
    for (int i = 0; i < n; ++i) { /* 每次处理一件物品。 */
        int weight, value; /* 当前物品重量及价值。 */
        if (scanf("%d%d", &weight, &value) != 2 || weight < 1 || weight > 1000000 || value < 0 ||
            value > 1000000)
            return 1; /* 拒绝缺失或越界的物品。 */
        for (int c = capacity; c >= weight; --c) { /* 倒序保持本轮所需旧状态。 */
            long long take = dp[c - weight] + value; /* 选择该物品的价值。 */
            if (take > dp[c]) /* 只有选择更优时才替换旧状态。 */
                dp[c] = take; /* 比较不选和选，保留较大者。 */
        }
    }
    printf("%lld\n", dp[capacity]); /* 没有可选物品时输出零。 */
    return 0; /* 正常结束。 */
}
