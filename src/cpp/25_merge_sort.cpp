/* 25_merge_sort 归并排序与分治 | ISO C++11 | 拓展
 * 来源/关系：由S1/S5排序题拓展；非原题答案（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..1000及n个int；输出升序数组
 * 思想：把问题分为左右两半，各自有序后用双指针合并；相等时先取左侧保证稳定。
 * 复杂度：O(n log n)，辅助数组O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <vector>
void merge_sort(std::vector<int> &a, std::vector<int> &buffer, int left, int right) {
    if (right - left <= 1)
        return;
    int mid = left + (right - left) / 2;
    merge_sort(a, buffer, left, mid);
    merge_sort(a, buffer, mid, right);
    int i = left, j = mid, k = left;
    while (i < mid && j < right)
        buffer[k++] = a[i] <= a[j] ? a[i++] : a[j++];
    while (i < mid)
        buffer[k++] = a[i++];
    while (j < right)
        buffer[k++] = a[j++];
    for (i = left; i < right; ++i)
        a[i] = buffer[i];
}
int main() {
    int n;
    if (!(std::cin >> n) || n < 0 || n > 1000)
        return 1;
    std::vector<int> a(n), buffer(n);
    for (int &x : a)
        if (!(std::cin >> x))
            return 1;
    merge_sort(a, buffer, 0, n);
    for (int i = 0; i < n; ++i)
        std::cout << (i ? " " : "") << a[i];
    std::cout << '\n';
}
