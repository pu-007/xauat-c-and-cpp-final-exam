/* 25_merge_sort 归并排序与分治 | ISO C99 | 拓展
 * 来源/关系：由S1/S5排序题拓展；非原题答案（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..1000及n个int；输出升序数组
 * 思想：把问题分为左右两半，各自有序后用双指针合并；相等时先取左侧保证稳定。
 * 复杂度：O(n log n)，辅助数组O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：25_merge_sort.cpp用vector引用传数组；C传数组参数并用scanf/printf进行输入输出。
 */
#include <stdio.h> /* 输入输出。 */
static void sort(int a[], int buffer[], int left, int right) { /* 排序半开区间[left,right)。 */
    if (right - left <= 1)
        return; /* 空区间或单元素已有序。 */
    int mid = left + (right - left) / 2; /* 分界点。 */
    sort(a, buffer, left, mid); /* 排序左半。 */
    sort(a, buffer, mid, right); /* 排序右半。 */
    int i = left, j = mid, k = left; /* 两个读位置及缓冲写位置。 */
    while (i < mid && j < right) /* 两侧均有剩余时取较小值。 */
        buffer[k++] = a[i] <= a[j] ? a[i++] : a[j++]; /* 相等先取左侧，保证稳定。 */
    while (i < mid)
        buffer[k++] = a[i++]; /* 复制左侧剩余元素。 */
    while (j < right)
        buffer[k++] = a[j++]; /* 复制右侧剩余元素。 */
    for (i = left; i < right; ++i)
        a[i] = buffer[i]; /* 合并结果写回原数组。 */
}
int main(void) {
    int n, a[1000], buffer[1000]; /* 固定容量数组及共享缓冲。 */
    if (scanf("%d", &n) != 1 || n < 0 || n > 1000)
        return 1; /* 数量无效。 */
    for (int i = 0; i < n; ++i)
        if (scanf("%d", &a[i]) != 1)
            return 1; /* 元素不足或格式错误。 */
    sort(a, buffer, 0, n); /* 排序全部有效元素。 */
    for (int i = 0; i < n; ++i)
        printf("%s%d", i ? " " : "", a[i]); /* 首项前无空格。 */
    putchar('\n'); /* 空数组也输出空行。 */
    return 0; /* 正常结束。 */
}
