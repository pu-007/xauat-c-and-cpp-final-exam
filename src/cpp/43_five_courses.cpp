/* 43_five_courses 10名学生5门课：行列统计 | ISO C++11 | 基础
 * 来源/关系：S6实验1(3)/(5)，实验3清单中的额外统计（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入10×5个0..100分数；输出每人均分（10行）、每科均分（1行）、首个最高分及其行列下标
 * 思想：每人均分按行遍历，每科均分按列累加；所有成绩是一个二维表。
 * 复杂度：推广为r×c时O(rc)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <array>
#include <iomanip>
int main() {
    std::array<std::array<double, 5>, 10> a{};
    std::array<double, 5> course{};
    int best_r = 0, best_c = 0;
    for (auto &row : a)
        for (double &x : row)
            if (!(std::cin >> x) || !(x >= 0 && x <= 100))
                return 1;
    std::cout << std::fixed << std::setprecision(2);
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
        std::cout << sum / 5 << '\n';
    }
    for (int c = 0; c < 5; ++c)
        std::cout << (c ? " " : "") << course[c] / 10;
    std::cout << '\n' << a[best_r][best_c] << ' ' << best_r << ' ' << best_c << '\n';
}
