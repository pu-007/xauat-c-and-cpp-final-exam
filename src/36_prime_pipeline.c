/* 36_prime_pipeline 综合压轴：素数筛选、函数、排序 | ISO C99 | 提高
 * 来源/关系：S1 p120–121 模拟三编程4（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入恰好10个-10^9..10^9整数；输出原数组与升序素数数组
 * 思想：分别实现findprime和冒泡sort；筛选返回有效长度，后续只处理有效元素。
 * 复杂度：n个数时O(n√M+k²)，C++排序O(k log k)
 * 对照 36_prime_pipeline.cpp：C 手写筛选和冒泡排序，C++ 用 copy_if 和 sort。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* 提供 scanf、printf 和 putchar；C++ 对照使用输入输出流。 */
static int prime(int n) { /* 判断一个整数是否为素数。 */
    if (n < 2) /* 负数、零和一均不是素数。 */
        return 0; /* 不是素数。 */
    for (int d = 2; d <= n / d; ++d) /* 试除至平方根，用除法避免乘法溢出。 */
        if (n % d == 0) /* 找到因子即为合数。 */
            return 0; /* 找到因子，立即报告合数。 */
    return 1; /* 没有找到因子。 */
}
static int findprime(const int input[], int n, int output[]) { /* 筛选并返回结果数量。 */
    int count = 0; /* 当前已写入的元素个数。 */
    for (int i = 0; i < n; ++i) /* 逐个检查输入。 */
        if (prime(input[i])) /* 素数才进入结果。 */
            output[count++] = input[i]; /* 保留重复值并增加长度。 */
    return count; /* 调用者只应访问有效部分。 */
}
static void sort(int a[], int n) { /* 对有效部分冒泡升序排序。 */
    for (int end = n - 1; end > 0; --end) /* 每轮将最大值移到 end。 */
        for (int j = 0; j < end; ++j) /* 比较相邻元素。 */
            if (a[j] > a[j + 1]) { /* 逆序时交换。 */
                int t = a[j]; /* 暂存左值。 */
                a[j] = a[j + 1]; /* 较小值移到左边。 */
                a[j + 1] = t; /* 原左值移到右边。 */
            }
}
static void print(const int a[], int n) { /* 输出指定长度，不修改数组。 */
    for (int i = 0; i < n; ++i) /* 逐个输出有效元素。 */
        printf("%s%d", i ? " " : "", a[i]); /* 首项无前导空格。 */
    putchar('\n'); /* 即使无元素也输出空行。 */
}
int main(void) {
    int a[10], b[10]; /* 原数组及筛选结果。 */
    for (int i = 0; i < 10; ++i) /* 恰好读取十个数。 */
        if (scanf("%d", &a[i]) != 1 || a[i] < -1000000000 || a[i] > 1000000000) /* 检查范围。 */
            return 1; /* 输入非法时退出。 */
    int count = findprime(a, 10, b); /* 筛选并记录有效长度。 */
    sort(b, count); /* 原数组保持输入顺序。 */
    print(a, 10); /* 输出原数组。 */
    print(b, count); /* 输出已排序的素数。 */
    return 0; /* 正常结束。 */
}
