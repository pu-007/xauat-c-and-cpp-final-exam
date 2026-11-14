/* 33_calendar 闰年、日期结构体与年内序号 | ISO C99 | 基础
 * 来源/关系：S5 p1 闰年；S1 p84 附加15、结构体日期题（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入年1..9999、月、日；输出是否闰年、年内第几天；非法日期退出码1
 * 思想：先验证月份再用月份作下标；二月天数由闰年决定。
 * 复杂度：O(1)
 * 对照 33_calendar.cpp：C 用 struct Date 和普通数组，C++ 用 Date 和 array。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* 提供 scanf 和 printf；C++ 用 cin、cout。 */
struct Date { /* 将同一个日期的年月日放在一起。 */
    int year, month, day; /* 年份、从 1 开始的月份和日期。 */
};
static int leap(int y) { /* 返回公历年份是否为闰年。 */
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0; /* 整百年须被 400 整除。 */
}
int main(void) {
    struct Date d; /* 保存输入的日期。 */
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; /* 平年各月天数。 */
    if (scanf("%d%d%d", &d.year, &d.month, &d.day) != 3 || d.year < 1 || d.year > 9999 ||
        d.month < 1 || d.month > 12) /* 先检查月份，才能安全用作下标。 */
        return 1; /* 年月无效时退出。 */
    days[1] += leap(d.year); /* 闰年为二月增加一天。 */
    if (d.day < 1 || d.day > days[d.month - 1]) /* 按对应月份验证日。 */
        return 1; /* 日期超过本月范围时退出。 */
    int total = d.day; /* 当月已经过去的天数。 */
    for (int m = 0; m < d.month - 1; ++m) /* 累加本月之前完整的月份。 */
        total += days[m]; /* 把一个完整月份加到序号。 */
    printf("%d %d\n", leap(d.year), total); /* 输出闰年标志和年内序号。 */
    return 0; /* 正常结束。 */
}
