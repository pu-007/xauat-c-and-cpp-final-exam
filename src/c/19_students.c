/* 19_students 结构体数组与成绩统计 | ISO C99 | 提高
 * 来源/关系：S5 p6 例9.4、p9 习题5；S1 p77 编程6（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..100；每行学号、无空格姓名(<=19字节)、三科0..100成绩；输出三科均分、最高均分学生、按均分降序的学号
 * 思想：记录把相关字段绑定；交换整个结构体；并列最高取输入中第一人。
 * 复杂度：C排序O(n²)，C++有额外缓冲时O(n log n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
struct Student {
    int id;
    char name[20];
    double score[3], average;
};
int main(void) {
    int n;
    struct Student a[100];
    double sums[3] = {0};
    if (scanf("%d", &n) != 1 || n < 1 || n > 100)
        return 1;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d%19s%lf%lf%lf", &a[i].id, a[i].name, &a[i].score[0], &a[i].score[1],
                  &a[i].score[2]) != 5)
            return 1;
        double total = 0;
        for (int j = 0; j < 3; ++j) {
            if (!(a[i].score[j] >= 0 && a[i].score[j] <= 100))
                return 1;
            sums[j] += a[i].score[j];
            total += a[i].score[j];
        }
        a[i].average = total / 3;
    }
    for (int end = n - 1; end > 0; --end)
        for (int j = 0; j < end; ++j)
            if (a[j].average < a[j + 1].average) {
                struct Student temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp; /* 结构体可赋值，内部字符数组也一并复制。 */
            }
    printf("%.2f %.2f %.2f\n", sums[0] / n, sums[1] / n, sums[2] / n);
    printf("%d %s %.2f\n", a[0].id, a[0].name, a[0].average);
    for (int i = 0; i < n; ++i)
        printf("%s%d", i ? " " : "", a[i].id);
    putchar('\n');
    return 0;
}
