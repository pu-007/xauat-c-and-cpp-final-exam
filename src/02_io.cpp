/* 02_io 格式化输入输出与类型 | ISO C++11 | 基础
 * 来源/关系：S2 编程1–2；S4 p2（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入整数a与实数r，|a|<=10000、0<=r<=10000；输出a平方、圆面积和周长（PI=3.14）
 * 思想：cin按变量类型读取；fixed和setprecision控制浮点输出。
 * 复杂度：O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：同目录 02_io.c 用 scanf 传地址，用 printf 的 %.2f 输出两位小数。
 */
#include <iostream> // 声明cin和cout；C版使用scanf/printf。
#include <iomanip> // 声明fixed和setprecision格式控制符。
int main() { // C++程序入口。
    int a; // 保存要计算平方的整数。
    double r; // 保存圆的半径。
    if (!(std::cin >> a >> r) || a < -10000 || a > 10000 || !(r >= 0 && r <= 10000))
        return 1; // 读取失败或范围不合法时退出。
    constexpr double pi = 3.14; // 按题目指定的圆周率计算。
    std::cout << a * a << ' ' << std::fixed << std::setprecision(2) << pi * r * r << ' '
              << 2 * pi * r << '\n'; // 输出平方、面积和周长，浮点数保留两位小数。
} // main自然结束时返回0。
