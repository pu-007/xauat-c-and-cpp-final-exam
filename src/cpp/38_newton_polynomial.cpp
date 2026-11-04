/* 38_newton_polynomial 报告指定方程的牛顿迭代 | ISO C++11 | 提高
 * 来源/关系：S6实验2(1) p9–10（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：无输入；从1.5求2x^3-4x^2+3x-6=0的根，输出六位小数
 * 思想：x下一步=x-f(x)/导数；同时检查步长、残差与迭代次数。
 * 复杂度：本程序最多100次迭代
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <iomanip>
#include <cmath>
double f(double x) {
    return ((2 * x - 4) * x + 3) * x - 6;
}
int main() {
    double x = 1.5;
    for (int iteration = 0; iteration < 100; ++iteration) {
        double derivative = (6 * x - 8) * x + 3;
        if (std::abs(derivative) < 1e-14)
            return 1;
        double next = x - f(x) / derivative;
        if (!std::isfinite(next))
            return 1;
        if (std::abs(next - x) < 1e-10 && std::abs(f(next)) < 1e-9) {
            std::cout << std::fixed << std::setprecision(6) << next << '\n';
            return 0;
        }
        x = next;
    }
    return 1;
}
