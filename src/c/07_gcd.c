/* 07_gcd 欧几里得算法与最小公倍数 | ISO C99 | 基础
 * 来源/关系：S1 p22 编程11；算法优化（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入0..10^9的两个整数；输出gcd和lcm；约定gcd(0,0)=0
 * 思想：gcd(a,b)=gcd(b,a%b)；lcm先除后乘以降低溢出风险。
 * 复杂度：O(log(min(a,b)+1))
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
static long long gcd(long long a, long long b) {
    while (b != 0) {
        long long remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}
int main(void) {
    long long a, b;
    if (scanf("%lld%lld", &a, &b) != 2 || a < 0 || b < 0 || a > 1000000000 || b > 1000000000)
        return 1;
    long long g = gcd(a, b);
    printf("%lld %lld\n", g, g == 0 ? 0 : a / g * b);
    return 0;
}
