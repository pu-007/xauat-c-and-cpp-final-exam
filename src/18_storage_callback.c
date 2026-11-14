/* 18_storage_callback static、作用域、函数指针、宏 | ISO C99 | 提高
 * 来源/关系：S1 函数/指针选择；S2 选择28–29；S4 p1/p4（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：无输入；输出累计调用数、函数回调结果、平方与位运算
 * 思想：局部static只初始化一次；函数指针保留签名；宏加括号也不能避免重复求值。
 * 复杂度：O(1)
 * 对照 18_storage_callback.cpp：C 使用函数指针和宏，C++ 使用 lambda 与 constexpr 函数。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* printf 输出结果；C++ 对应 cout。 */
/* 括号保护表达式优先级，但实参在宏中出现两次。 */
#define SQUARE(x) ((x) * (x))
static int counter(void) {
    /* 静态局部变量只初始化一次，后续调用保留上次值。 */
    static int n = 0; /* 生命周期贯穿整个程序。 */
    return ++n; /* 先递增，再返回新值。 */
}
static int add(int a, int b) {
    /* 符合回调签名的二元加法。 */
    return a + b; /* 返回两个实参的和。 */
}
static int apply(int (*operation)(int, int), int a, int b) {
    /* 通过函数指针调用指定的操作。 */
    return operation(a, b); /* 按传入签名调用并返回结果。 */
}
int main(void) {
    /* 按声明顺序先后调用，避免依赖函数参数求值顺序。 */
    int first = counter(), second = counter(); /* 两个初始化按声明顺序进行。 */
    printf("%d %d\n", first, second); /* 输出 1 2。 */
    /* 回调求和；宏将 2+3 整体相乘。 */
    printf("%d %d\n", apply(add, 2, 3), SQUARE(2 + 3)); /* 分别输出 5 和 25。 */
    /* 无符号数适合演示移位、与和异或。 */
    unsigned x = 6u; /* 二进制为 110。 */
    printf("%u %u %u\n", x << 2, x & 3u, x ^ 3u); /* 输出 24、2、5。 */
    return 0; /* 正常结束。 */
}
