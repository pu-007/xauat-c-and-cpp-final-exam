/* 23_sieve 埃氏筛：批量判断素数 | ISO C++11 | 提高
 * 来源/关系：S1 p32 编程7；08的批量优化（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100000；输出不大于n的所有素数
 * 思想：从p²开始划去倍数，小于p²的倍数已被更小素数处理。
 * 复杂度：O(n log log n)，空间O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：23_sieve.c用calloc分配并free；本文件用vector<unsigned char>自动管理内存。
 */
#include <iostream> /* 流输入输出。 */
#include <vector> /* 动态标记数组。 */
int main() {
    int n; /* 筛选上界。 */
    if (!(std::cin >> n) || n < 0 || n > 100000)
        return 1; /* 范围或输入错误。 */
    std::vector<unsigned char> composite(n + 1, 0); /* 包括下标n，初始均未标记。 */
    for (int p = 2; p <= n / p; ++p) /* 只需处理平方不超过n的p。 */
        if (!composite[p]) /* p未被筛去，即为素数。 */
            for (int j = p * p; j <= n; j += p) /* 从平方起划去倍数。 */
                composite[j] = 1; /* 标记这个倍数为合数。 */
    bool first = true; /* 控制首项之前没有空格。 */
    for (int p = 2; p <= n; ++p) /* 从2开始枚举输出候选。 */
        if (!composite[p]) {
            if (!first)
                std::cout << ' '; /* 只在数字之间加空格。 */
            std::cout << p; /* 输出素数。 */
            first = false; /* 后续素数前加分隔空格。 */
        }
    std::cout << '\n'; /* n小于2也输出空行。 */
}
