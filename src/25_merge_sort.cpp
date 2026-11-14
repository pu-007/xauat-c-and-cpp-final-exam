/* 25_merge_sort 归并排序与分治 | ISO C++11 | 拓展
 * 来源/关系：由S1/S5排序题拓展；非原题答案（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..1000及n个int；输出升序数组
 * 思想：把问题分为左右两半，各自有序后用双指针合并；相等时先取左侧保证稳定。
 * 复杂度：O(n log n)，辅助数组O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：25_merge_sort.c传递固定数组；本文件以vector引用共享原数据与缓冲区，使用cin/cout。
 */
#include <iostream> /* 流输入输出。 */
#include <vector> /* 动态数组。 */
void merge_sort(std::vector<int> &a, std::vector<int> &buffer, int left, int right) { /* 半开区间。 */
    if (right - left <= 1)
        return; /* 空区间及单元素自然有序。 */
    int mid = left + (right - left) / 2; /* 左右分界。 */
    merge_sort(a, buffer, left, mid); /* 排序左半。 */
    merge_sort(a, buffer, mid, right); /* 排序右半。 */
    int i = left, j = mid, k = left; /* 左右读位置及输出位置。 */
    while (i < mid && j < right) /* 两侧均未耗尽时逐项比较。 */
        buffer[k++] = a[i] <= a[j] ? a[i++] : a[j++]; /* 同值先取左边以保持稳定。 */
    while (i < mid) /* 左半尚有剩余时复制。 */
        buffer[k++] = a[i++]; /* 复制左半余项。 */
    while (j < right) /* 右半尚有剩余时复制。 */
        buffer[k++] = a[j++]; /* 复制右半余项。 */
    for (i = left; i < right; ++i) /* 遍历刚合并的区间。 */
        a[i] = buffer[i]; /* 将合并区间写回。 */
}
int main() {
    int n; /* 元素数量。 */
    if (!(std::cin >> n) || n < 0 || n > 1000)
        return 1; /* 校验数量。 */
    std::vector<int> a(n), buffer(n); /* 输入和共用的合并缓冲。 */
    for (int &x : a) /* 引用允许直接写入每个元素。 */
        if (!(std::cin >> x))
            return 1; /* 元素输入失败。 */
    merge_sort(a, buffer, 0, n); /* 排序整个数组。 */
    for (int i = 0; i < n; ++i) /* 依次输出已排序元素。 */
        std::cout << (i ? " " : "") << a[i]; /* 输出升序结果。 */
    std::cout << '\n'; /* 空数组也换行。 */
}
