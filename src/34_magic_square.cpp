/* 34_magic_square 奇数阶魔方阵 | ISO C++11 | 提高
 * 来源/关系：S1 p33–34 编程23；p99–102另有更多阶数拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入奇数n=1..15；输出n×n魔方阵
 * 思想：从首行中间开始向右上走；遇占用则从原位置向下；用模运算处理边界。
 * 复杂度：O(n²)，空间O(n²)
 * 对照 34_magic_square.c：C 使用定长二维数组，C++ 使用嵌套 vector。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 提供 cin、cout；C 使用 scanf、printf 和 putchar。
#include <vector> // 提供二维动态数组；C 使用定长二维数组。
int main() {
    int n; // 方阵阶数。
    if (!(std::cin >> n) || n < 1 || n > 15 || n % 2 == 0) // 只接受范围内奇数。
        return 1; // 输入无效时退出。
    std::vector<std::vector<int>> a(n, std::vector<int>(n, 0)); // 零表示空格。
    int r = 0, c = n / 2; // 第一行中间是起点。
    for (int value = 1; value <= n * n; ++value) { // 放入 1 至 n²。
        a[r][c] = value; // 填当前格。
        int nr = (r + n - 1) % n, nc = (c + 1) % n; // 求绕回后的右上格。
        if (a[nr][nc]) // 右上格已占用时。
            r = (r + 1) % n; // 从当前格向下，保持原列。
        else {
            r = nr; // 否则转到候选行。
            c = nc; // 同时转到候选列。
        }
    }
    for (const auto &row : a) { // 只读引用，逐行输出。
        for (int j = 0; j < n; ++j) // 逐列输出。
            std::cout << (j ? " " : "") << row[j]; // 首项不加前导空格。
        std::cout << '\n'; // 行结束。
    }
}
