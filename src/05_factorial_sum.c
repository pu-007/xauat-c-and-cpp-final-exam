/* 05_factorial_sum 阶乘递推与累加 | ISO C99 | 基础
 * 来源/关系：S1 p22 编程1/5、p120 填空4；S2 编程7/9（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入n=0..20；输出n!和1!+...+n!，n=0时和为0
 * 思想：乘积初值1，和初值0；用上一次阶乘递推，避免重复计算。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：同目录 05_factorial_sum.cpp 用 cin/cout，static_cast 对应 C 的强制转换。
 */
#include <stdio.h> /* 声明scanf和printf；C++版使用输入输出流。 */
int main(void) { /* C程序入口。 */
    int n; /* 要计算阶乘的非负整数。 */
    if (scanf("%d", &n) != 1 || n < 0 || n > 20)
        return 1; /* 读取失败或超出0至20时退出。 */
    unsigned long long factorial = 1, sum = 0; /* 0!=1，空和为0。 */
    for (int i = 1; i <= n; ++i) { /* 依次处理1到n。 */
        factorial *= (unsigned)i; /* 用(i-1)!乘i得到i!；题目范围内不会溢出。 */
        sum += factorial; /* 将当前阶乘加入总和。 */
    }
    printf("%llu %llu\n", factorial, sum); /* %llu与unsigned long long匹配。 */
    return 0; /* 表示程序正常结束。 */
}
