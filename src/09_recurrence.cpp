/* 09_recurrence 斐波那契与分数序列 | ISO C++11 | 基础
 * 来源/关系：S5 p2 例5.8；S2 编程10（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入n=1..90；输出F(n)，F(1)=F(2)=1；再输出前20项分数和（六位小数）
 * 思想：先保存下一项再移动状态；分数递推用double避免整数除法。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * C对照：同目录09_recurrence.c显式声明临时变量并用printf；本版用auto和流格式。
 */
#include <iostream> // 声明cin和cout；C版使用stdio.h。
#include <iomanip> // 声明fixed和setprecision以控制小数位数。
int main() { // C++程序入口。
    int n; // 希望求出的斐波那契数列项号。
    if (!(std::cin >> n) || n < 1 || n > 90)
        return 1; // 读取失败或不在1至90之间时退出。
    unsigned long long a = 0, b = 1; // 初始保存F(0)=0和F(1)=1。
    for (int i = 1; i < n; ++i) { // 每轮从相邻两项计算下一项。
        auto next = a + b; // 推导为unsigned long long，先保存F(i+1)。
        a = b; // 原F(i)成为前一项。
        b = next; // 新项成为当前项。
    }
    double x = 2, y = 1, sum = 0; // 分数序列首项2/1，累加和从0开始。
    for (int i = 0; i < 20; ++i) { // 恰好累加前20项。
        sum += x / y; // 两个变量是double，执行浮点除法。
        auto next = x + y; // 推导为double，保存下一项分子。
        y = x; // 下一项分母等于原分子。
        x = next; // 更新为下一项分子。
    }
    std::cout << b << ' ' << std::fixed << std::setprecision(6) << sum << '\n'; // 输出F(n)和六位小数的和。
} // main自然结束时返回0。
