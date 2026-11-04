/* 39_saddle 矩阵所有鞍点 | ISO C++11 | 提高
 * 来源/关系：S6实验2(3) p11–13（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：rows cols均1..10；输入整数矩阵；逐行输出每个行最大且列最小的鞍点：行 列
 * 值，下标0起；无解NONE 思想：一个行内可能有多个并列最大；所有候选都检查，避免漏解。
 * 复杂度：O(rc(r+c))；预处理行最大/列最小可优化到O(rc)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <vector>
int main() {
    int rows, cols;
    if (!(std::cin >> rows >> cols) || rows < 1 || rows > 10 || cols < 1 || cols > 10)
        return 1;
    std::vector<std::vector<int>> a(rows, std::vector<int>(cols));
    for (auto &row : a)
        for (int &x : row)
            if (!(std::cin >> x))
                return 1;
    bool found = false;
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c) {
            bool valid = true;
            for (int j = 0; j < cols; ++j)
                if (a[r][j] > a[r][c])
                    valid = false;
            for (int i = 0; i < rows; ++i)
                if (a[i][c] < a[r][c])
                    valid = false;
            if (valid) {
                std::cout << r << ' ' << c << ' ' << a[r][c] << '\n';
                found = true;
            }
        }
    if (!found)
        std::cout << "NONE\n";
}
