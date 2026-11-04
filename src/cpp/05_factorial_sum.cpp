/* 05_factorial_sum 阶乘递推与累加 | ISO C++11 | 基础
 * 来源/关系：S1 p22 编程1/5、p120 填空4；S2 编程7/9（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入n=0..20；输出n!和1!+...+n!，n=0时和为0
 * 思想：乘积初值1，和初值0；用上一次阶乘递推，避免重复计算。
 * 复杂度：O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
int main() {
    int n;
    if (!(std::cin >> n) || n < 0 || n > 20)
        return 1;
    unsigned long long factorial = 1, sum = 0;
    for (int i = 1; i <= n; ++i) {
        factorial *= static_cast<unsigned>(i);
        sum += factorial;
    }
    std::cout << factorial << ' ' << sum << '\n';
}
