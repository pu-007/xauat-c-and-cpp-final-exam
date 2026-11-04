/* 24_recursion 递归与快速幂（取模） | ISO C++11 | 拓展
 * 来源/关系：S1 p42 编程12；递归算法拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：a=0..10^9,b=0..10^9；输出a^b mod 1000000007；约定a^0=1
 * 思想：指数减半；先算一次半幂再复用，避免重复递归。
 * 复杂度：O(log b)，递归栈O(log b)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
constexpr long long mod = 1000000007;
long long power(long long a, long long b) {
    if (b == 0)
        return 1;
    auto half = power(a, b / 2);
    auto result = half * half % mod;
    return b % 2 ? result * a % mod : result;
}
int main() {
    long long a, b;
    if (!(std::cin >> a >> b) || a < 0 || b < 0 || a > 1000000000 || b > 1000000000)
        return 1;
    std::cout << power(a, b) << '\n';
}
