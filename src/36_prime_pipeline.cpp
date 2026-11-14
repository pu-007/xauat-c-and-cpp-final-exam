/* 36_prime_pipeline 综合压轴：素数筛选、函数、排序 | ISO C++11 | 提高
 * 来源/关系：S1 p120–121 模拟三编程4（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：输入恰好10个-10^9..10^9整数；输出原数组与升序素数数组
 * 思想：用素数判断函数配合 copy_if 筛选，再用 sort 排序结果；原卷要求冒泡时应手写。
 * 复杂度：n个数、最大值M、k个素数时O(n√M+k log k)，空间O(n)。
 * 对照 36_prime_pipeline.c：C 手写筛选和冒泡排序，C++ 用 copy_if 和 sort。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // 提供 cin、cout；C 使用 scanf、printf。
#include <vector> // 保存原数组和筛选结果；C 用定长数组。
#include <algorithm> // 提供 copy_if 和 sort；C 手写筛选和冒泡排序。
#include <iterator> // 提供 back_inserter，使 copy_if 能追加到结果 vector。
bool prime(int n) { // 判断一个数是否为素数。
    if (n < 2) // 负数、零和一都不是素数。
        return false; // 不满足素数定义。
    for (int d = 2; d <= n / d; ++d) // 检查到平方根，避免 d*d 溢出。
        if (n % d == 0) // 存在因子即为合数。
            return false; // 找到因子，立即报告合数。
    return true; // 无因子则为素数。
}
void print(const std::vector<int> &a) { // 只读引用避免复制容器。
    for (std::size_t i = 0; i < a.size(); ++i) // 遍历全部元素。
        std::cout << (i ? " " : "") << a[i]; // 第一项无前导空格。
    std::cout << '\n'; // 即使为空也输出一行。
}
int main() {
    std::vector<int> a(10), b; // 原数组固定十项，结果初始为空。
    for (int &x : a) // 按引用填充原数组。
        if (!(std::cin >> x) || x < -1000000000 || x > 1000000000) // 检查输入范围。
            return 1; // 输入非法时退出。
    std::copy_if(a.begin(), a.end(), std::back_inserter(b), prime); // 追加所有满足素数判断的元素。
    std::sort(b.begin(), b.end()); // 仅排序结果，保留重复值。
    print(a); // 输出原始顺序。
    print(b); // 输出升序素数，空结果仍输出空行。
    // C++工程写法；若考试指定冒泡和函数签名，必须按C版要求实现。
}
