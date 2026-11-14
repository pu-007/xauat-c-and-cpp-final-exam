/* 24_recursion 递归与快速幂（取模） | ISO C99 | 拓展
 * 来源/关系：S1 p42 编程12；递归算法拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：a=0..10^9,b=0..10^9；输出a^b mod 1000000007；约定a^0=1
 * 思想：指数减半；先算一次半幂再复用，避免重复递归。
 * 复杂度：O(log(b+1))，递归栈O(log(b+1))，含b=0时的常数开销。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：24_recursion.cpp用constexpr代替#define模数，并用cin/cout代替scanf/printf。
 */
#include <stdio.h> /* 输入输出。 */
#define MOD 1000000007LL /* LL后缀使模数为long long。 */
static long long power(long long a, long long b) { /* 返回a的b次幂的余数。 */
    if (b == 0)
        return 1; /* 递归基；包括本题约定的0^0。 */
    long long half = power(a, b / 2); /* 只计算一次半指数结果。 */
    long long result = half * half % MOD; /* 两个余数之积能放入long long。 */
    return b % 2 ? result * a % MOD : result; /* 奇数指数再乘一次底数。 */
}
int main(void) {
    long long a, b; /* 底数与非负指数。 */
    if (scanf("%lld%lld", &a, &b) != 2 || a < 0 || b < 0 || a > 1000000000 || b > 1000000000)
        return 1; /* 范围或输入错误。 */
    printf("%lld\n", power(a, b)); /* 输出模幂。 */
    return 0; /* 正常结束。 */
}
