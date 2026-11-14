/* 05_factorial_sum 阶乘递推与累加 | ISO C++11 | 基础
 * 来源/关系：S1 p22 编程1/5、p120 填空4；S2 编程7/9（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入n=0..20；输出n!和1!+...+n!，n=0时和为0
 * 思想：乘积初值1，和初值0；用上一次阶乘递推，避免重复计算。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：同目录 05_factorial_sum.c 用 scanf/printf 和 (unsigned) 转换。
 */
#include <iostream> // 声明cin和cout；C版使用scanf/printf。
int main() { // C++程序入口。
    int n; // 要计算阶乘的非负整数。
    if (!(std::cin >> n) || n < 0 || n > 20)
        return 1; // 读取失败或超出0至20时退出。
    unsigned long long factorial = 1, sum = 0; // 0!=1，空和为0。
    for (int i = 1; i <= n; ++i) { // 依次处理1到n。
        factorial *= static_cast<unsigned>(i); // 用(i-1)!乘i得到i!；显式转换为无符号数。
        sum += factorial; // 将当前阶乘加入总和。
    }
    std::cout << factorial << ' ' << sum << '\n'; // 按类型输出阶乘和累加和。
} // main自然结束时返回0。
