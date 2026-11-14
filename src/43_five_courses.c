/* 43_five_courses 10名学生5门课：行列统计 | ISO C99 | 基础
 * 来源/关系：S6实验1(3)/(5)，实验3清单中的额外统计（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入10×5个0..100分数；输出每人均分（10行）、每科均分（1行）、首个最高分及其行列下标
 * 思想：每人均分按行遍历，每科均分按列累加；所有成绩是一个二维表。
 * 复杂度：推广为r×c时O(rc)
 * 对照 43_five_courses.cpp：C 使用二维数组，C++ 使用嵌套 array 与格式化流。
 * scanf("%lf", &a[r][c]) 对应 cin >> 元素；printf 的 %.2f 对应 fixed/setprecision(2)。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* scanf 和 printf 读写成绩。 */
int main(void) {
    double a[10][5], course[5] = {0}; /* 成绩表与各科累计值。 */
    int best_r = 0, best_c = 0; /* 用首个位置初始化最高分位置。 */
    for (int r = 0; r < 10; ++r) /* 按学生读取。 */
        for (int c = 0; c < 5; ++c) /* 每人读取五门课。 */
            if (scanf("%lf", &a[r][c]) != 1 || !(a[r][c] >= 0 && a[r][c] <= 100))
                return 1; /* 拒绝缺失、越界或 NaN。 */
    for (int r = 0; r < 10; ++r) {
        double sum = 0; /* 每个学生重新开始累计。 */
        for (int c = 0; c < 5; ++c) {
            sum += a[r][c]; /* 加入当前学生总分。 */
            course[c] += a[r][c]; /* 同时加入该科总分。 */
            if (a[r][c] > a[best_r][best_c]) { /* 严格大于才更新，保留并列首项。 */
                best_r = r;
                best_c = c;
            }
        }
        printf("%.2f\n", sum / 5); /* 输出此学生均分。 */
    }
    for (int c = 0; c < 5; ++c)
        printf("%s%.2f", c ? " " : "", course[c] / 10); /* 科目间用空格分隔。 */
    printf("\n%.2f %d %d\n", a[best_r][best_c], best_r, best_c); /* 最高分及零起始坐标。 */
    return 0;
}
