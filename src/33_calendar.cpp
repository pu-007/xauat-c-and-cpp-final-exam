/* 33_calendar 闰年、日期结构体与年内序号 | ISO C++11 | 基础
 * 来源/关系：S5 p1 闰年；S1 p84 附加15、结构体日期题（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入年1..9999、月、日；输出是否闰年、年内第几天；非法日期退出码1
 * 思想：先验证月份再用月份作下标；二月天数由闰年决定。
 * 复杂度：O(1)
 * 对照 33_calendar.c：C 用 struct Date 和普通数组，C++ 用 Date 和 array。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 提供 cin、cout；C 用 scanf、printf。
#include <array> // 提供 std::array 月天数表；C 用普通数组。
struct Date { // 保存同一日期的三个分量。
    int year, month, day; // 月、日均从 1 开始。
};
bool leap(int y) { // 返回年份是否符合公历闰年规则。
    return (y % 4 == 0 && y % 100 != 0) || y % 400 == 0; // 整百年须被 400 整除。
}
int main() {
    Date d{}; // 值初始化，随后由输入填充。
    std::array<int, 12> days{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // 平年各月天数。
    if (!(std::cin >> d.year >> d.month >> d.day) || d.year < 1 || d.year > 9999 || d.month < 1 ||
        d.month > 12) // 先检查月份，后续才能安全索引数组。
        return 1; // 年月无效时退出。
    days[1] += leap(d.year); // bool 转成 0 或 1，调整二月。
    if (d.day < 1 || d.day > days[d.month - 1]) // 日期必须在本月范围内。
        return 1; // 日期无效时退出。
    int total = d.day; // 先算当月的天数。
    for (int m = 0; m < d.month - 1; ++m) // 再加之前的整月。
        total += days[m]; // 加入当前完整月份的天数。
    std::cout << leap(d.year) << ' ' << total << '\n'; // 默认以 0/1 输出 bool。
}
