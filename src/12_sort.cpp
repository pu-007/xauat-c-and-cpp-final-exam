/* 12_sort 冒泡、选择、插入三种排序 | ISO C++11 | 提高
 * 来源/关系：S5 p2/p4/p6；S2 填空8；S1 p89 附加49（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100，再输入n个int；三行分别输出三种升序排序结果
 * 思想：冒泡固定后缀，选择固定前缀，插入维护已排序前缀。
 * 复杂度：最坏O(n²)，单个排序额外空间O(1)
 * 对照 12_sort.c：C 使用数组和指针交换，C++ 使用 vector 与迭代器。
 * 练习：比较相等元素是否交换，解释冒泡/插入的稳定性及选择排序的不稳定性。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream> // cin、cout 对应 C 的 scanf、printf。
#include <vector> // vector 可复制；C 数组逐项复制。
#include <algorithm> // swap、min_element、iter_swap 对应 C 手写过程。
void print(const std::vector<int> &a) {
    // 遍历容器；空容器也输出换行。
    for (std::size_t i = 0; i < a.size(); ++i) // size_t 表示下标。
        std::cout << (i ? " " : "") << a[i]; // 首项前不输出空格。
    std::cout << '\n'; // 空数组也占一行。
}
int main() {
    // 读取和验证长度，再逐项填入 vector。
    int n; // 保存长度。
    if (!(std::cin >> n) || n < 0 || n > 100) // 允许空数组。
        return 1; // 输入失败或长度越界。
    std::vector<int> a(n); // vector 自动管理空间。
    for (int &x : a) // 引用使输入直接写入元素。
        if (!(std::cin >> x))
            return 1; // 缺少元素。
    auto b = a, c = a; // vector复制的是内容；C数组不能直接用赋值运算符复制。
    // 冒泡每轮固定后缀末项，无交换时提前结束。
    for (int end = n - 1; end > 0; --end) { // 每轮末项就位。
        bool changed = false; // 尚未交换。
        for (int j = 0; j < end; ++j) // 比较相邻元素。
            if (a[j] > a[j + 1]) { // 相等不交换。
                std::swap(a[j], a[j + 1]); // 较大值右移。
                changed = true; // 记录本轮有交换。
            }
        if (!changed) // 全部相邻元素有序。
            break; // 提前结束。
    }
    // 选择后缀的首个最小值，与当前位置交换。
    for (int i = 0; i < n; ++i) // i 左侧已排好。
        std::iter_swap(b.begin() + i, std::min_element(b.begin() + i, b.end())); // 交换当前位和后缀首个最小值。
    // 将 key 插入已排序前缀：较大的数向右移动。
    for (int i = 1; i < n; ++i) { // 前 i 个数已有序。
        int key = c[i], j = i; // 保存待插入值和空位。
        while (j > 0 && c[j - 1] > key) { // 相等不右移。
            c[j] = c[j - 1]; // 大值右移一格。
            --j; // 空位左移。
        }
        c[j] = key; // 把值写入最终位置。
    }
    // 按冒泡、选择、插入顺序分别输出。
    print(a);
    print(b);
    print(c); // 工程中通常用std::sort；本题要求练习手写过程。
}
