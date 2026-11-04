/* 41_global_scores 全局数组与输出参数 | ISO C99 | 提高
 * 来源/关系：S6实验3(4) p18、p23–24；题意重写（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入10个0..100成绩；输出均分、最低、最高；再输出两次静态计数器结果
 * 思想：全局数组体现实验要求；再通过指针/引用返回多个结果；static保存跨调用状态。
 * 复杂度：固定10项；推广n项时O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
static double scores[10]; /* 文件作用域数组；static限制链接范围，不是局部数组。 */
static double statistics(double *low, double *high) {
    *low = *high = scores[0];
    double sum = 0;
    for (int i = 0; i < 10; ++i) {
        sum += scores[i];
        if (scores[i] < *low)
            *low = scores[i];
        if (scores[i] > *high)
            *high = scores[i];
    }
    return sum / 10;
}
static int counter(void) {
    static int calls = 0;
    return ++calls;
}
int main(void) {
    for (int i = 0; i < 10; ++i)
        if (scanf("%lf", &scores[i]) != 1 || !(scores[i] >= 0 && scores[i] <= 100))
            return 1;
    double low, high, average = statistics(&low, &high);
    printf("%.2f %.2f %.2f\n", average, low, high);
    int a = counter(), b = counter();
    printf("%d %d\n", a, b);
    return 0;
}
