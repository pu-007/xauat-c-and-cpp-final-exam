/* 39_saddle 矩阵所有鞍点 | ISO C++11 | 提高
 * 来源/关系：S6实验2(3) p11–13（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：rows cols均1..10；输入整数矩阵；逐行输出每个行最大且列最小的鞍点：行 列
 * 值，下标0起；无解NONE 思想：一个行内可能有多个并列最大；所有候选都检查，避免漏解。
 * 复杂度：O(rc(r+c))；预处理行最大/列最小可优化到O(rc)
 * 对照 39_saddle.c：C 使用固定二维数组及整数标志；C++ 使用 vector 和 bool。
 * cin >> 元素对应 scanf("%d", &元素)；cout 的连续插入对应 printf 的格式串。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // cin、cout 处理输入输出。
#include <vector> // 根据行列数存储矩阵。
int main() {
    int rows, cols; // 矩阵尺寸。
    if (!(std::cin >> rows >> cols) || rows < 1 || rows > 10 || cols < 1 || cols > 10)
        return 1; // 读取失败或尺寸越界。
    std::vector<std::vector<int>> a(rows, std::vector<int>(cols)); // 按尺寸分配矩阵。
    for (auto &row : a) // 引用每行，避免复制。
        for (int &x : row) // 引用元素，以便直接写入。
            if (!(std::cin >> x))
                return 1;
    bool found = false; // 是否找到过鞍点。
    for (int r = 0; r < rows; ++r) // 行优先枚举每个候选。
        for (int c = 0; c < cols; ++c) {
            bool valid = true; // 没有发现反例之前视为有效。
            for (int j = 0; j < cols; ++j) // 检查整行。
                if (a[r][j] > a[r][c])
                    valid = false; // 行内有更大值。
            for (int i = 0; i < rows; ++i) // 检查整列。
                if (a[i][c] < a[r][c])
                    valid = false; // 列内有更小值。
            if (valid) { // 等值不排除候选。
                std::cout << r << ' ' << c << ' ' << a[r][c] << '\n'; // 输出坐标和值。
                found = true;
            }
        }
    if (!found) // 一个鞍点也没有。
        std::cout << "NONE\n";
}
