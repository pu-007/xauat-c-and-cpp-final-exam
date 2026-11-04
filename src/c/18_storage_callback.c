/* 18_storage_callback static、作用域、函数指针、宏 | ISO C99 | 提高
 * 来源/关系：S1 函数/指针选择；S2 选择28–29；S4 p1/p4（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：无输入；输出累计调用数、函数回调结果、平方与位运算
 * 思想：局部static只初始化一次；函数指针保留签名；宏加括号也不能避免重复求值。
 * 复杂度：O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#define SQUARE(x) ((x) * (x))
static int counter(void) {
    static int n = 0;
    return ++n;
}
static int add(int a, int b) {
    return a + b;
}
static int apply(int (*operation)(int, int), int a, int b) {
    return operation(a, b);
}
int main(void) {
    int first = counter(), second = counter(); /* 不在printf参数里依赖调用先后。 */
    printf("%d %d\n", first, second);
    printf("%d %d\n", apply(add, 2, 3), SQUARE(2 + 3));
    unsigned x = 6u;
    printf("%u %u %u\n", x << 2, x & 3u, x ^ 3u); /* 位运算优先用无符号数。 */
    return 0;
}
