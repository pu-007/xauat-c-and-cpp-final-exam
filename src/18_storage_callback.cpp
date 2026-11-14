/* 18_storage_callback static、作用域、函数指针、宏 | ISO C++11 | 提高
 * 来源/关系：S1 函数/指针选择；S2 选择28–29；S4 p1/p4（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：无输入；输出累计调用数、函数回调结果、平方与位运算
 * 思想：局部static只初始化一次；函数指针保留签名；宏加括号也不能避免重复求值。
 * 复杂度：O(1)
 * 对照 18_storage_callback.c：C 演示函数指针及宏，C++ 使用 lambda 和 constexpr。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // cout 输出结果，对应 C 的 printf。
// constexpr 函数按值接收实参，表达式只求值一次。
constexpr int square(int x) {
    return x * x; // 计算传入值的平方。
} // 传值一次，避免宏SQUARE(i++)的副作用问题。
int counter() {
    // 静态局部变量在调用间保持状态。
    static int n = 0; // 首次调用初始化，之后保留状态。
    return ++n; // 自增后返回。
}
int main() {
    // 分别保存调用结果，避免依赖表达式中的求值顺序。
    int first = counter(), second = counter(); // 分别取得 1 和 2。
    std::cout << first << ' ' << second << '\n'; // 输出两次结果。
    // 无捕获 lambda 表示二元加法操作。
    auto add = [](int a, int b) { return a + b; }; // 定义接受两个整数的 lambda。
    std::cout << add(2, 3) << ' ' << square(2 + 3) << '\n'; // 输出和与平方。
    // 无符号数的移位和按位运算结果以十进制输出。
    unsigned x = 6u; // 二进制 110。
    std::cout << (x << 2) << ' ' << (x & 3u) << ' ' << (x ^ 3u) << '\n'; // 结果为 24、2、5。
}
