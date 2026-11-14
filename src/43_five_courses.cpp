/* 43_five_courses 10名学生5门课：行列统计 | ISO C++11 | 基础
 * 来源/关系：S6实验1(3)/(5)，实验3清单中的额外统计（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入10×5个0..100分数；输出每人均分（10行）、每科均分（1行）、首个最高分及其行列下标
 * 思想：每人均分按行遍历，每科均分按列累加；所有成绩是一个二维表。
 * 复杂度：推广为r×c时O(rc)
 * 对照 43_five_courses.c：C 使用二维数组，C++ 使用嵌套 array 与格式化流。
 * cin >> 元素对应 scanf("%lf", &元素)；fixed/setprecision(2) 对应 printf 的 %.2f。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 标准输入输出流。
#include <array> // 固定尺寸成绩表。
#include <iomanip> // 设置两位小数。
int main() {
    std::array<std::array<double, 5>, 10> a{}; // 10 人各 5 门成绩。
    std::array<double, 5> course{}; // 各科累计总分从零开始。
    int best_r = 0, best_c = 0; // 最高分暂定为第一项。
    for (auto &row : a) // 用引用读取每一行。
        for (double &x : row) // 直接写入每个元素。
            if (!(std::cin >> x) || !(x >= 0 && x <= 100))
                return 1; // 输入缺失或成绩非法。
    std::cout << std::fixed << std::setprecision(2); // 后续实数均保留两位小数。
    for (int r = 0; r < 10; ++r) {
        double sum = 0; // 当前学生的总分。
        for (int c = 0; c < 5; ++c) {
            sum += a[r][c]; // 更新行总分。
            course[c] += a[r][c]; // 更新列总分。
            if (a[r][c] > a[best_r][best_c]) { // 相等时不覆盖首次位置。
                best_r = r;
                best_c = c;
            }
        }
        std::cout << sum / 5 << '\n'; // 输出当前学生均分。
    }
    for (int c = 0; c < 5; ++c)
        std::cout << (c ? " " : "") << course[c] / 10; // 依次输出科目均分。
    std::cout << '\n' << a[best_r][best_c] << ' ' << best_r << ' ' << best_c << '\n'; // 输出最高分和坐标。
}
