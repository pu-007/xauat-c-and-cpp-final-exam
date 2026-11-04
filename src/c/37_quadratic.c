/* 37_quadratic 二次方程及退化情况 | ISO C99 | 基础
 * 来源/关系：S6实验1(2) p3–4；S1分支填空5（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入三个有限实系数a b
 * c，绝对值<=10000；输出REAL两根/COMPLEX实部和正虚部幅度/LINEAR一根/ALL/NONE
 * 思想：先处理a=0，再按判别式分类；复根的虚部幅度取非负。
 * 复杂度：O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <math.h>
int main(void) {
    double a, b, c;
    if (scanf("%lf%lf%lf", &a, &b, &c) != 3 || !isfinite(a) || !isfinite(b) || !isfinite(c) ||
        fabs(a) > 10000 || fabs(b) > 10000 || fabs(c) > 10000)
        return 1;
    if (a == 0) {
        if (b != 0)
            printf("LINEAR %.6f\n", -c / b);
        else
            puts(c == 0 ? "ALL" : "NONE");
        return 0;
    }
    double discriminant = b * b - 4 * a * c;
    if (discriminant >= 0) {
        double left = (-b - sqrt(discriminant)) / (2 * a),
               right = (-b + sqrt(discriminant)) / (2 * a);
        if (left > right) {
            double t = left;
            left = right;
            right = t;
        }
        printf("REAL %.6f %.6f\n", left, right);
    } else {
        printf("COMPLEX %.6f %.6f\n", -b / (2 * a), sqrt(-discriminant) / fabs(2 * a));
    }
    /* 教材直接公式可能发生相消；工程数值优化见实验手册，不把固定epsilon视为万能判据。 */
    return 0;
}
