/* 19_students 结构体数组与成绩统计 | ISO C++11 | 提高
 * 来源/关系：S5 p6 例9.4、p9 习题5；S1 p77 编程6（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..100；每行学号、无空格姓名(<=19字节)、三科0..100成绩；输出三科均分、最高均分学生、按均分降序的学号
 * 思想：记录把相关字段绑定；交换整个结构体；并列最高取输入中第一人。
 * 复杂度：C排序O(n²)，C++有额外缓冲时O(n log n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <string>
#include <algorithm>
struct Student {
    int id;
    std::string name;
    std::array<double, 3> score;
    double average;
};
int main() {
    int n;
    if (!(std::cin >> n) || n < 1 || n > 100)
        return 1;
    std::vector<Student> a(n);
    std::array<double, 3> sums{};
    for (auto &s : a) {
        if (!(std::cin >> s.id >> s.name) || s.name.size() > 19)
            return 1;
        double total = 0;
        for (int j = 0; j < 3; ++j) {
            if (!(std::cin >> s.score[j]) || !(s.score[j] >= 0 && s.score[j] <= 100))
                return 1;
            sums[j] += s.score[j];
            total += s.score[j];
        }
        s.average = total / 3;
    }
    std::stable_sort(a.begin(), a.end(),
                     [](const Student &x, const Student &y) { return x.average > y.average; });
    std::cout << std::fixed << std::setprecision(2) << sums[0] / n << ' ' << sums[1] / n << ' '
              << sums[2] / n << '\n';
    std::cout << a[0].id << ' ' << a[0].name << ' ' << a[0].average << '\n';
    for (int i = 0; i < n; ++i)
        std::cout << (i ? " " : "") << a[i].id;
    std::cout << '\n';
}
