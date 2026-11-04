/* 32_numerical 数值迭代：莱布尼茨级数与牛顿法 | ISO C99 | 提高
 * 来源/关系：S5 p1–2 求π；S1 p23 编程22的求根变式（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入x，0<=x<=10^12；输出牛顿法sqrt(x)及以原资料1e-6项阈值求得的π（六位小数）
 * 思想：递推避免重复运算；迭代要有容差和次数上限；项误差不等于最终π误差。
 * 复杂度：平方根有200次上限；π约500000项
 * 练习：把sqrt结果与库函数比较；解释为何不能声称π精确到小数点后8位。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
#include <math.h>
int main(void) {
    double x;
    if (scanf("%lf", &x) != 1 || !(x >= 0 && x <= 1e12))
        return 1;
    double root = x > 1 ? x : 1;
    if (x == 0)
        root = 0;
    else
        for (int i = 0; i < 200; ++i) {
            double next = (root + x / root) / 2;
            if (fabs(next - root) <= 1e-12 * fmax(1.0, fabs(next))) {
                root = next;
                break;
            }
            root = next;
        }
    double sum = 0;
    for (int k = 0; k < 1000000; ++k) {
        double term = (k % 2 ? -1.0 : 1.0) / (2 * k + 1);
        if (fabs(term) < 1e-6)
            break;
        sum += term;
    }
    printf("%.6f %.6f\n", root, 4 * sum);
    return 0;
}
