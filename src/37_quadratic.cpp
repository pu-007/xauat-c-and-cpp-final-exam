/* 37_quadratic 二次方程及退化情况 | ISO C++11 | 基础
 * 来源/关系：S6实验1(2) p3–4；S1分支填空5（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入三个有限实系数a b
 * c，绝对值<=10000；输出REAL两根/COMPLEX实部和正虚部幅度/LINEAR一根/ALL/NONE
 * 思想：先处理a=0，再按判别式分类；复根的虚部幅度取非负。
 * 复杂度：O(1)
 * 对照 37_quadratic.c：C 使用 scanf/printf 和临时变量交换；C++ 使用流与 std::swap。
 * cin >> 对应 scanf 的 %lf；fixed/setprecision(6) 对应 printf 的 %.6f。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 输入输出流 cin、cout。
#include <iomanip> // fixed 输出精度设置。
#include <cmath> // sqrt、abs 和 isfinite。
#include <utility> // swap 交换两根。
int main() {
    double a, b, c; // 方程的三个系数。
    if (!(std::cin >> a >> b >> c) || !std::isfinite(a) || !std::isfinite(b) || !std::isfinite(c) ||
        std::abs(a) > 10000 || std::abs(b) > 10000 || std::abs(c) > 10000)
        return 1; // 输入失败、非有限或超出范围。
    std::cout << std::fixed << std::setprecision(6); // 实数统一输出六位小数。
    if (a == 0) { // 退化时不使用二次公式。
        if (b != 0)
            std::cout << "LINEAR " << -c / b << '\n'; // 一次方程。
        else
            std::cout << (c == 0 ? "ALL" : "NONE") << '\n'; // 恒等或无解。
        return 0;
    }
    double discriminant = b * b - 4 * a * c; // 判别式。
    if (discriminant >= 0) { // 实根分支包括重根。
        double left = (-b - std::sqrt(discriminant)) / (2 * a),
               right = (-b + std::sqrt(discriminant)) / (2 * a); // 求出两根。
        if (left > right) // 负的 a 可能使两根逆序。
            std::swap(left, right);
        std::cout << "REAL " << left << ' ' << right << '\n'; // 升序输出。
    } else
        std::cout << "COMPLEX " << -b / (2 * a) << ' ' << std::sqrt(-discriminant) / std::abs(2 * a)
                  << '\n'; // 共轭根的实部与非负虚部幅度。
}
