/* 12_sort 冒泡、选择、插入三种排序 | ISO C99 | 提高
 * 来源/关系：S5 p2/p4/p6；S2 填空8；S1 p89 附加49（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100，再输入n个int；三行分别输出三种升序排序结果
 * 思想：冒泡固定后缀，选择固定前缀，插入维护已排序前缀。
 * 复杂度：最坏O(n²)，单个排序额外空间O(1)
 * 练习：比较相等元素是否交换，解释冒泡/插入的稳定性及选择排序的不稳定性。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
static void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
static void bubble(int a[], int n) {
    for (int end = n - 1; end > 0; --end) {
        int changed = 0;
        for (int j = 0; j < end; ++j)
            if (a[j] > a[j + 1]) {
                swap(&a[j], &a[j + 1]);
                changed = 1;
            }
        if (!changed)
            break; /* 一轮未交换说明已经有序。 */
    }
}
static void selection(int a[], int n) {
    for (int i = 0; i < n; ++i) {
        int best = i;
        for (int j = i + 1; j < n; ++j)
            if (a[j] < a[best])
                best = j;
        swap(&a[i], &a[best]);
    }
}
static void insertion(int a[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = a[i], j = i;
        while (j > 0 && a[j - 1] > key) {
            a[j] = a[j - 1];
            --j;
        }
        a[j] = key;
    }
}
static void print(const int a[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%s%d", i ? " " : "", a[i]);
    putchar('\n');
}
int main(void) {
    int n, a[100], b[100], c[100];
    if (scanf("%d", &n) != 1 || n < 0 || n > 100)
        return 1;
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &a[i]) != 1)
            return 1;
        b[i] = c[i] = a[i];
    }
    bubble(a, n);
    selection(b, n);
    insertion(c, n);
    print(a, n);
    print(b, n);
    print(c, n);
    return 0;
}
