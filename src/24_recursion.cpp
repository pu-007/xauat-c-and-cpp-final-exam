/* 24_recursion 递归与快速幂（取模） | ISO C++11 | 拓展
 * 来源/关系：S1 p42 编程12；递归算法拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：a=0..10^9,b=0..10^9；输出a^b mod 1000000007；约定a^0=1
 * 思想：指数减半；先算一次半幂再复用，避免重复递归。
 * 复杂度：O(log(b+1))，递归栈O(log(b+1))，含b=0时的常数开销。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：24_recursion.c用#define定义模数和scanf/printf，本文件用constexpr、auto及cin/cout。
 */
#include <iostream> /* 流输入输出。 */
constexpr long long mod = 1000000007; /* 编译期有类型常量。 */
long long power(long long a, long long b) { /* 返回模幂。 */
    if (b == 0)
        return 1; /* 终止条件，包括约定的0^0。 */
    auto half = power(a, b / 2); /* auto推导long long，递归一次。 */
    auto result = half * half % mod; /* 先平方再取模，乘积在long long内。 */
    return b % 2 ? result * a % mod : result; /* 奇数指数还需乘a。 */
}
int main() {
    long long a, b; /* 非负底数和指数。 */
    if (!(std::cin >> a >> b) || a < 0 || b < 0 || a > 1000000000 || b > 1000000000)
        return 1; /* 输入或范围有误。 */
    std::cout << power(a, b) << '\n'; /* 输出结果。 */
}
