/* 51_course_max：统计 20 名学生三门课的最高分（S1 PDF p115 模拟二编程2）。
 * 输入 20 行，每行三个 0..100 的整数成绩，逐项更新各课最高分。
 * 按课程顺序输出一行三个最高分，单空格分隔，行末换行。
 * 时间 O(20×3)，额外空间 O(3)。
 * 对照 51_course_max.c：C++ 用 cin/cout，C 用 scanf/printf；
 * 两者均用 int 一维数组保存最高分，用 long long 读入检查范围。
 */
#include <iostream> // 提供标准输入输出。

int main() { // 程序入口。
    int maximum[3] = {0, 0, 0}; // 成绩非负，因此零可作各课程的初始最高分。
    for (int student = 0; student < 20; ++student) { // 遍历二十名学生。
        for (int course = 0; course < 3; ++course) { // 按顺序读取三门课程。
            long long score; // 用较宽类型检查范围。
            if (!(std::cin >> score) || score < 0 || score > 100) return 1; // 检查成绩。
            if (score > maximum[course]) { // 当前成绩更高时更新。
                maximum[course] = static_cast<int>(score); // 保存该课程最高成绩。
            }
        }
    }
    std::cout << maximum[0] << ' ' << maximum[1] << ' ' << maximum[2] << '\n'; // 按课程顺序输出。
    return 0; // 正常结束。
}
