/* 37_quadratic 二次方程及退化情况 | ISO C99 | 基础
 * 来源/关系：S6实验1(2) p3–4；S1分支填空5（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入三个有限实系数a b
 * c，绝对值<=10000；输出REAL两根/COMPLEX实部和正虚部幅度/LINEAR一根/ALL/NONE
 * 思想：先处理a=0，再按判别式分类；复根的虚部幅度取非负。
 * 复杂度：O(1)
 * 对照 37_quadratic.cpp：C 使用 scanf/printf 和数学库；C++ 使用流、std::abs 与 std::swap。
 * scanf 的 %lf 读入 double 对应 cin >>；printf 的 %.6f 对应 fixed/setprecision(6)。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* scanf、printf 和 puts 的声明。 */
#include <math.h> /* sqrt、fabs 和 isfinite 的声明。 */
int main(void) {
    double a, b, c; /* 方程 ax²+bx+c=0 的系数。 */
    if (scanf("%lf%lf%lf", &a, &b, &c) != 3 || !isfinite(a) || !isfinite(b) || !isfinite(c) ||
        fabs(a) > 10000 || fabs(b) > 10000 || fabs(c) > 10000)
        return 1; /* 缺失、非有限或超出约定范围。 */
    if (a == 0) { /* 先处理退化方程，避免除以零。 */
        if (b != 0)
            printf("LINEAR %.6f\n", -c / b); /* 一次方程唯一解。 */
        else
            puts(c == 0 ? "ALL" : "NONE"); /* 恒等式或矛盾式。 */
        return 0;
    }
    double discriminant = b * b - 4 * a * c; /* 判别式决定根的类型。 */
    if (discriminant >= 0) { /* 零也在此分支，得到相同的两根。 */
        double left = (-b - sqrt(discriminant)) / (2 * a),
               right = (-b + sqrt(discriminant)) / (2 * a); /* 求根公式。 */
        if (left > right) { /* a 为负时公式中的顺序可能反转。 */
            double t = left;
            left = right;
            right = t;
        }
        printf("REAL %.6f %.6f\n", left, right); /* 按数值升序输出。 */
    } else {
        printf("COMPLEX %.6f %.6f\n", -b / (2 * a), sqrt(-discriminant) / fabs(2 * a)); /* 输出实部与非负虚部幅度。 */
    }
    /* 教材直接公式可能发生相消；工程数值优化见实验手册，不把固定epsilon视为万能判据。 */
    return 0;
}
