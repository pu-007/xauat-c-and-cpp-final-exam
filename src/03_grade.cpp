/* 03_grade switch百分制成绩 | ISO C++11 | 基础
 * 来源/关系：S3 编程1；S2 编程4；S1 p14 编程6（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入0..100整数；输出A/B/C/D/E；范围外退出码1
 * 思想：按十位数分组，100单独并入A，break防贯穿。
 * 复杂度：O(1)
 * 练习：测试59/60/69/70/79/80/89/90/100；再改为if版本。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：同目录 03_grade.c 用 scanf/printf；switch 和 break 语义相同。
 */
#include <iostream> // 声明cin和cout；C版使用scanf/printf。
int main() { // C++程序入口。
    int score; // 保存百分制成绩。
    char grade; // 保存对应等级字符。
    if (!(std::cin >> score) || score < 0 || score > 100)
        return 1; // 读入失败或不在0到100之间时退出。
    switch (score / 10) { // 整数除以10，按十位分组。
    case 10: // 100分与90至99分共用A分支。
    case 9:
        grade = 'A'; // 保存A等级。
        break; // 退出switch，避免继续进入下一分支。
    case 8: // 80至89分。
        grade = 'B'; // 保存B等级。
        break; // 当前分支结束。
    case 7: // 70至79分。
        grade = 'C'; // 保存C等级。
        break; // 当前分支结束。
    case 6: // 60至69分。
        grade = 'D'; // 保存D等级。
        break; // 当前分支结束。
    default: // 已检查范围，所以其余情况是0至59分。
        grade = 'E'; // 保存E等级。
    }
    std::cout << grade << '\n'; // 输出等级字符和换行。
} // main自然结束时返回0。
