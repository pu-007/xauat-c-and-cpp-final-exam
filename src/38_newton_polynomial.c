/* 38_newton_polynomial 报告指定方程的牛顿迭代 | ISO C99 | 提高
 * 来源/关系：S6实验2(1) p9–10（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：无输入；从1.5求2x^3-4x^2+3x-6=0的根，输出六位小数
 * 思想：x下一步=x-f(x)/导数；同时检查步长、残差与迭代次数。
 * 复杂度：本程序最多100次迭代
 * 对照 38_newton_polynomial.cpp：C 用 fabs/printf，C++ 用 std::abs 和格式化流。
 * isfinite 与 std::isfinite 均拒绝非有限值；printf 的 %.6f 对应 fixed/setprecision(6)。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* printf 输出近似根。 */
#include <math.h> /* fabs 和 isfinite 检查迭代值。 */
static double f(double x) {
    return ((2 * x - 4) * x + 3) * x - 6; /* 按嵌套乘法计算多项式值。 */
} /* Horner形式减少乘法。 */
int main(void) {
    double x = 1.5; /* 从题设初值开始。 */
    for (int iteration = 0; iteration < 100; ++iteration) { /* 限制不收敛时的计算次数。 */
        double derivative = (6 * x - 8) * x + 3; /* 计算 f'(x)。 */
        if (fabs(derivative) < 1e-14) /* 导数过小时避免不稳定的除法。 */
            return 1;
        double next = x - f(x) / derivative; /* 切线与横轴交点作为下一个近似。 */
        if (!isfinite(next)) /* 溢出或无效计算不能用于迭代。 */
            return 1;
        if (fabs(next - x) < 1e-10 && fabs(f(next)) < 1e-9) { /* 步长和残差同时达标。 */
            printf("%.6f\n", next); /* 按题目精度输出。 */
            return 0;
        }
        x = next; /* 把本次结果作为下一次的起点。 */
    }
    return 1; /* 超过迭代次数仍未收敛。 */
}
