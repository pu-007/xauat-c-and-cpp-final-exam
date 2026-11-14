/* 41_global_scores 全局数组与输出参数 | ISO C99 | 提高
 * 来源/关系：S6实验3(4) p18、p23–24；题意重写（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入10个0..100成绩；输出均分、最低、最高；再输出两次静态计数器结果
 * 思想：全局数组体现实验要求；再通过指针/引用返回多个结果；static保存跨调用状态。
 * 复杂度：固定10项；推广n项时O(n)
 * 对照 41_global_scores.cpp：C 指针返回极值；C++ 引用返回极值，array 保存成绩。
 * statistics(&low,&high) 对应 C++ statistics(low,high)；%.2f 对应 fixed/setprecision(2)。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* scanf 和 printf 读写成绩。 */
static double scores[10]; /* 文件作用域数组；static限制链接范围，不是局部数组。 */
static double statistics(double *low, double *high) {
    *low = *high = scores[0]; /* 首项同时作为初始极值。 */
    double sum = 0; /* 总分初始为零。 */
    for (int i = 0; i < 10; ++i) {
        sum += scores[i]; /* 累加当前成绩。 */
        if (scores[i] < *low)
            *low = scores[i]; /* 通过指针更新调用者的最低分。 */
        if (scores[i] > *high)
            *high = scores[i]; /* 通过指针更新最高分。 */
    }
    return sum / 10; /* 均分通过返回值传出。 */
}
static int counter(void) {
    static int calls = 0; /* 只初始化一次，跨调用保留。 */
    return ++calls; /* 先递增，再返回本次调用数。 */
}
int main(void) {
    for (int i = 0; i < 10; ++i) /* 依次填入全局数组。 */
        if (scanf("%lf", &scores[i]) != 1 || !(scores[i] >= 0 && scores[i] <= 100))
            return 1; /* 输入缺失或不在允许范围。 */
    double low, high, average = statistics(&low, &high); /* 传地址接收两个极值。 */
    printf("%.2f %.2f %.2f\n", average, low, high); /* 固定两位小数。 */
    int a = counter(), b = counter(); /* 依次保存两次调用结果。 */
    printf("%d %d\n", a, b);
    return 0;
}
