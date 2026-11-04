/* 37_quadratic 二次方程及退化情况 | ISO C++11 | 基础
 * 来源/关系：S6实验1(2) p3–4；S1分支填空5（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入三个有限实系数a b
 * c，绝对值<=10000；输出REAL两根/COMPLEX实部和正虚部幅度/LINEAR一根/ALL/NONE
 * 思想：先处理a=0，再按判别式分类；复根的虚部幅度取非负。
 * 复杂度：O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <utility>
int main() {
    double a, b, c;
    if (!(std::cin >> a >> b >> c) || !std::isfinite(a) || !std::isfinite(b) || !std::isfinite(c) ||
        std::abs(a) > 10000 || std::abs(b) > 10000 || std::abs(c) > 10000)
        return 1;
    std::cout << std::fixed << std::setprecision(6);
    if (a == 0) {
        if (b != 0)
            std::cout << "LINEAR " << -c / b << '\n';
        else
            std::cout << (c == 0 ? "ALL" : "NONE") << '\n';
        return 0;
    }
    double discriminant = b * b - 4 * a * c;
    if (discriminant >= 0) {
        double left = (-b - std::sqrt(discriminant)) / (2 * a),
               right = (-b + std::sqrt(discriminant)) / (2 * a);
        if (left > right)
            std::swap(left, right);
        std::cout << "REAL " << left << ' ' << right << '\n';
    } else
        std::cout << "COMPLEX " << -b / (2 * a) << ' ' << std::sqrt(-discriminant) / std::abs(2 * a)
                  << '\n';
}
