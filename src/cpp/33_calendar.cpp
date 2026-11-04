/* 33_calendar 闰年、日期结构体与年内序号 | ISO C++11 | 基础
 * 来源/关系：S5 p1 闰年；S1 p84 附加15、结构体日期题（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入年1..9999、月、日；输出是否闰年、年内第几天；非法日期退出码1
 * 思想：先验证月份再用月份作下标；二月天数由闰年决定。
 * 复杂度：O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <array>
struct Date {
    int year, month, day;
};
bool leap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0;
}
int main() {
    Date d{};
    std::array<int, 12> days{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (!(std::cin >> d.year >> d.month >> d.day) || d.year < 1 || d.year > 9999 || d.month < 1 ||
        d.month > 12)
        return 1;
    days[1] += leap(d.year);
    if (d.day < 1 || d.day > days[d.month - 1])
        return 1;
    int total = d.day;
    for (int m = 0; m < d.month - 1; ++m)
        total += days[m];
    std::cout << leap(d.year) << ' ' << total << '\n';
}
