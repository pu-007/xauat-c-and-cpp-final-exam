/* 06_digits 数位拆分、水仙花数 | ISO C99 | 基础
 * 来源/关系：S1 p22 编程12、p120 编程1；S5 p6–7 水仙花数（页码均为 PDF
 * 页码；此文件为重写的教学实现）
 * 输入输出约定：输入0..999999999；输出位数、数字和、倒序数字；再输出所有三位水仙花数
 * 思想：模10取末位，除10删末位；do-while正确处理0。
 * 复杂度：O(log n)，枚举三位数为常数工作
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
int main(void) {
    long long n;
    if (scanf("%lld", &n) != 1 || n < 0 || n > 999999999)
        return 1;
    int count = 0, sum = 0;
    long long reversed = 0;
    do {
        int digit = (int)(n % 10);
        sum += digit;
        reversed = reversed * 10 + digit;
        ++count;
        n /= 10;
    } while (n);
    printf("%d %d %lld\n", count, sum, reversed);
    int first = 1;
    for (int x = 100; x <= 999; ++x) {
        int a = x / 100, b = x / 10 % 10, c = x % 10;
        if (a * a * a + b * b * b + c * c * c == x) {
            printf("%s%d", first ? "" : " ", x);
            first = 0;
        }
    }
    putchar('\n');
    return 0;
}
