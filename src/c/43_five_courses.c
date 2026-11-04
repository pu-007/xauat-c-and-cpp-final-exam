/* 43_five_courses 10名学生5门课：行列统计 | ISO C99 | 基础
 * 来源/关系：S6实验1(3)/(5)，实验3清单中的额外统计（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入10×5个0..100分数；输出每人均分（10行）、每科均分（1行）、首个最高分及其行列下标
 * 思想：每人均分按行遍历，每科均分按列累加；所有成绩是一个二维表。
 * 复杂度：推广为r×c时O(rc)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
int main(void) {
    double a[10][5], course[5] = {0};
    int best_r = 0, best_c = 0;
    for (int r = 0; r < 10; ++r)
        for (int c = 0; c < 5; ++c)
            if (scanf("%lf", &a[r][c]) != 1 || !(a[r][c] >= 0 && a[r][c] <= 100))
                return 1;
    for (int r = 0; r < 10; ++r) {
        double sum = 0;
        for (int c = 0; c < 5; ++c) {
            sum += a[r][c];
            course[c] += a[r][c];
            if (a[r][c] > a[best_r][best_c]) {
                best_r = r;
                best_c = c;
            }
        }
        printf("%.2f\n", sum / 5);
    }
    for (int c = 0; c < 5; ++c)
        printf("%s%.2f", c ? " " : "", course[c] / 10);
    printf("\n%.2f %d %d\n", a[best_r][best_c], best_r, best_c);
    return 0;
}
