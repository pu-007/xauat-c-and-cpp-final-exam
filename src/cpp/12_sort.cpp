/* 12_sort 冒泡、选择、插入三种排序 | ISO C++11 | 提高
 * 来源/关系：S5 p2/p4/p6；S2 填空8；S1 p89 附加49（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100，再输入n个int；三行分别输出三种升序排序结果
 * 思想：冒泡固定后缀，选择固定前缀，插入维护已排序前缀。
 * 复杂度：最坏O(n²)，单个排序额外空间O(1)
 * 练习：比较相等元素是否交换，解释冒泡/插入的稳定性及选择排序的不稳定性。
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
    int n;
    if (!(std::cin >> n) || n < 0 || n > 100)
        return 1;
    std::vector<int> a(n);
    for (int &x : a)
        if (!(std::cin >> x))
            return 1;
    auto b = a, c = a; // vector复制的是内容；C数组不能直接用赋值运算符复制。
    for (int end = n - 1; end > 0; --end) {
        bool changed = false;
        for (int j = 0; j < end; ++j)
            if (a[j] > a[j + 1]) {
                std::swap(a[j], a[j + 1]);
                changed = true;
            }
        if (!changed)
            break;
    }
    for (int i = 0; i < n; ++i)
        std::iter_swap(b.begin() + i, std::min_element(b.begin() + i, b.end()));
    for (int i = 1; i < n; ++i) {
        int key = c[i], j = i;
        while (j > 0 && c[j - 1] > key) {
            c[j] = c[j - 1];
            --j;
        }
        c[j] = key;
    }
    print(a);
    print(b);
    print(c); // 工程中通常用std::sort；本题要求练习手写过程。
}
