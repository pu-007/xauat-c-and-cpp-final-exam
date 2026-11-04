/* 11_reverse_rotate 逆序、循环右移、最小最大交换 | ISO C++11 | 提高
 * 来源/关系：S5 p5 例8.8、p8 习题3；S1 p61 编程2/3（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..100,k=0..10^9，再输入n个int；先右移k位输出，再将最小换到首、最大换到尾后输出
 * 思想：三次反转实现旋转；交换后旧的极值位置可能失效，重新查找最大值。
 * 复杂度：O(n)，C版额外空间O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <vector>
#include <algorithm>
void print(const std::vector<int> &a) {
    for (std::size_t i = 0; i < a.size(); ++i)
        std::cout << (i ? " " : "") << a[i];
    std::cout << '\n';
}
int main() {
    int n, k;
    if (!(std::cin >> n >> k) || n < 1 || n > 100 || k < 0 || k > 1000000000)
        return 1;
    std::vector<int> a(n);
    for (int &x : a)
        if (!(std::cin >> x))
            return 1;
    k %= n;
    std::rotate(a.begin(), a.end() - k, a.end());
    print(a);
    std::iter_swap(a.begin(), std::min_element(a.begin(), a.end()));
    std::iter_swap(a.end() - 1, std::max_element(a.begin(), a.end()));
    print(a);
}
