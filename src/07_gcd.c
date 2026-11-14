/* 07_gcd 欧几里得算法与最小公倍数 | ISO C99 | 基础
 * 来源/关系：S1 p22 编程11；算法优化（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入0..10^9的两个整数；输出gcd和lcm；约定gcd(0,0)=0
 * 思想：gcd(a,b)=gcd(b,a%b)；lcm先除后乘以降低溢出风险。
 * 复杂度：O(log(min(a,b)+1))
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * C++对照：同目录07_gcd.cpp用cin/cout；C++11没有std::gcd，因此两版都手写递推。
 */
#include <stdio.h> /* 声明scanf和printf。 */
static long long gcd(long long a, long long b) { /* 返回两个非负整数的最大公约数。 */
    while (b != 0) { /* 除数为0时结束，避免取余除以0。 */
        long long remainder = a % b; /* 保存余数，公约数集合不变。 */
        a = b; /* 原除数成为下一轮被除数。 */
        b = remainder; /* 余数成为下一轮除数。 */
    }
    return a; /* 最后一个非零除数是最大公约数；两数为0时返回0。 */
}
int main(void) { /* C程序入口。 */
    long long a, b; /* 两个非负输入。 */
    if (scanf("%lld%lld", &a, &b) != 2 || a < 0 || b < 0 || a > 1000000000 || b > 1000000000)
        return 1; /* 读取失败或超出范围时退出。 */
    long long g = gcd(a, b); /* 调用辗转相除函数。 */
    printf("%lld %lld\n", g, g == 0 ? 0 : a / g * b); /* 两数均为0时避开除零，否则先除后乘。 */
    return 0; /* 表示程序正常结束。 */
}
