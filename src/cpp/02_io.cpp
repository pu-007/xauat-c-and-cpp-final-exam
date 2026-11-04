/* 02_io 格式化输入输出与类型 | ISO C++11 | 基础
 * 来源/关系：S2 编程1–2；S4 p2（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入整数a与实数r，|a|<=10000、0<=r<=10000；输出a平方、圆面积和周长（PI=3.14）
 * 思想：scanf需要对象地址，printf需要值；double输入用%lf。
 * 复杂度：O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <iomanip>
int main() {
    int a;
    double r;
    if (!(std::cin >> a >> r) || a < -10000 || a > 10000 || !(r >= 0 && r <= 10000))
        return 1;
    constexpr double pi = 3.14; // constexpr适合编译期常量。
    std::cout << a * a << ' ' << std::fixed << std::setprecision(2) << pi * r * r << ' '
              << 2 * pi * r << '\n';
}
