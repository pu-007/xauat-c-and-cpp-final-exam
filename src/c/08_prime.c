/* 08_prime 素数判定与区间筛选 | ISO C99 | 基础
 * 来源/关系：S2 编程12；S5 p2/7；S1 模拟二编程1（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入-10^9..10^9的整数；输出0或1（是否素数）
 * 思想：非素数至少有一个因子<=平方根；d<=n/d避免d*d溢出。
 * 复杂度：O(sqrt(n))，空间O(1)
 * 练习：用函数筛选数组素数，再用12排序；对应S1模拟三最后一题。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <stdbool.h>
static bool is_prime(long long n) {
    if (n < 2)
        return false; /* 0、1和负数不是素数；原资料有遗漏。 */
    for (long long d = 2; d <= n / d; ++d)
        if (n % d == 0)
            return false;
    return true;
}
int main(void) {
    long long n;
    if (scanf("%lld", &n) != 1 || n < -1000000000 || n > 1000000000)
        return 1;
    printf("%d\n", is_prime(n));
    return 0;
}
