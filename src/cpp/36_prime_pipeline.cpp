/* 36_prime_pipeline 综合压轴：素数筛选、函数、排序 | ISO C++11 | 提高
 * 来源/关系：S1 p120–121 模拟三编程4（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入恰好10个-10^9..10^9整数；输出原数组与升序素数数组
 * 思想：分别实现findprime和冒泡sort；筛选返回有效长度，后续只处理有效元素。
 * 复杂度：n个数时O(n√M+k²)，C++排序O(k log k)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
bool prime(int n) {
    if (n < 2)
        return false;
    for (int d = 2; d <= n / d; ++d)
        if (n % d == 0)
            return false;
    return true;
}
void print(const std::vector<int> &a) {
    for (std::size_t i = 0; i < a.size(); ++i)
        std::cout << (i ? " " : "") << a[i];
    std::cout << '\n';
}
int main() {
    std::vector<int> a(10), b;
    for (int &x : a)
        if (!(std::cin >> x) || x < -1000000000 || x > 1000000000)
            return 1;
    std::copy_if(a.begin(), a.end(), std::back_inserter(b), prime);
    std::sort(b.begin(), b.end());
    print(a);
    print(b);
    // C++工程写法；若考试指定冒泡和函数签名，必须按C版要求实现。
}
