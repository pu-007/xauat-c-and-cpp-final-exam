/* 36_prime_pipeline 综合压轴：素数筛选、函数、排序 | ISO C99 | 提高
 * 来源/关系：S1 p120–121 模拟三编程4（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入恰好10个-10^9..10^9整数；输出原数组与升序素数数组
 * 思想：分别实现findprime和冒泡sort；筛选返回有效长度，后续只处理有效元素。
 * 复杂度：n个数时O(n√M+k²)，C++排序O(k log k)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
static int prime(int n) {
    if (n < 2)
        return 0;
    for (int d = 2; d <= n / d; ++d)
        if (n % d == 0)
            return 0;
    return 1;
}
static int findprime(const int input[], int n, int output[]) {
    int count = 0;
    for (int i = 0; i < n; ++i)
        if (prime(input[i]))
            output[count++] = input[i];
    return count;
}
static void sort(int a[], int n) {
    for (int end = n - 1; end > 0; --end)
        for (int j = 0; j < end; ++j)
            if (a[j] > a[j + 1]) {
                int t = a[j];
                a[j] = a[j + 1];
                a[j + 1] = t;
            }
}
static void print(const int a[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%s%d", i ? " " : "", a[i]);
    putchar('\n');
}
int main(void) {
    int a[10], b[10];
    for (int i = 0; i < 10; ++i)
        if (scanf("%d", &a[i]) != 1 || a[i] < -1000000000 || a[i] > 1000000000)
            return 1;
    int count = findprime(a, 10, b);
    sort(b, count);
    print(a, 10);
    print(b, count);
    return 0;
}
