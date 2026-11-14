/* 38_newton_polynomial 报告指定方程的牛顿迭代 | ISO C++11 | 提高
 * 来源/关系：S6实验2(1) p9–10（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：无输入；从1.5求2x^3-4x^2+3x-6=0的根，输出六位小数
 * 思想：x下一步=x-f(x)/导数；同时检查步长、残差与迭代次数。
 * 复杂度：本程序最多100次迭代
 * 对照 38_newton_polynomial.c：C 用 fabs/printf，C++ 用 std::abs 和格式化流。
 * std::isfinite 对应 C 的 isfinite；fixed/setprecision(6) 对应 printf 的 %.6f。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // cout 输出近似根。
#include <iomanip> // fixed 和 setprecision 控制小数位。
#include <cmath> // abs 和 isfinite 检查迭代值。
double f(double x) {
    return ((2 * x - 4) * x + 3) * x - 6; // 嵌套乘法计算 f(x)。
}
int main() {
    double x = 1.5; // 题设初值。
    for (int iteration = 0; iteration < 100; ++iteration) { // 至多迭代 100 次。
        double derivative = (6 * x - 8) * x + 3; // 计算当前导数。
        if (std::abs(derivative) < 1e-14) // 防止除以接近零的值。
            return 1;
        double next = x - f(x) / derivative; // 切线法求新近似。
        if (!std::isfinite(next)) // 不接受无穷或 NaN。
            return 1;
        if (std::abs(next - x) < 1e-10 && std::abs(f(next)) < 1e-9) { // 同时检查步长与残差。
            std::cout << std::fixed << std::setprecision(6) << next << '\n'; // 保留六位。
            return 0;
        }
        x = next; // 下一轮从新近似继续。
    }
    return 1; // 迭代上限内未满足收敛条件。
}
