/* 18_storage_callback static、作用域、函数指针、宏 | ISO C++11 | 提高
 * 来源/关系：S1 函数/指针选择；S2 选择28–29；S4 p1/p4（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：无输入；输出累计调用数、函数回调结果、平方与位运算
 * 思想：局部static只初始化一次；函数指针保留签名；宏加括号也不能避免重复求值。
 * 复杂度：O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
constexpr int square(int x) {
    return x * x;
} // 传值一次，避免宏SQUARE(i++)的副作用问题。
int counter() {
    static int n = 0;
    return ++n;
}
int main() {
    int first = counter(), second = counter();
    std::cout << first << ' ' << second << '\n';
    auto add = [](int a, int b) { return a + b; }; // lambda可作为算法的回调。
    std::cout << add(2, 3) << ' ' << square(2 + 3) << '\n';
    unsigned x = 6u;
    std::cout << (x << 2) << ' ' << (x & 3u) << ' ' << (x ^ 3u) << '\n';
}
