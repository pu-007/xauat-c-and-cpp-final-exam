/* 13_binary_search 二分查找第一个匹配 | ISO C99 | 拓展
 * 来源/关系：S2 填空6的线性查找拓展（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100及目标x，再输入非降序数组；输出首个匹配下标或-1
 * 思想：半开区间[left,right)；小于目标的在左侧，候选答案始终在未排除范围。
 * 复杂度：查找O(log n)，含输入及验证的整个程序O(n)
 * 对照 13_binary_search.cpp：C 手写半开区间，C++ 使用 lower_bound。
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h> /* scanf 和 printf 对应 C++ 的 cin 和 cout。 */
int main(void) {
    int n, x, a[100]; /* 个数、目标与输入数组。 */
    if (scanf("%d%d", &n, &x) != 2 || n < 0 || n > 100)
        return 1; /* 个数不合法或输入缺失。 */
    for (int i = 0; i < n; ++i) /* 输入时检查相邻元素是否非降序。 */
        if (scanf("%d", &a[i]) != 1 || (i && a[i] < a[i - 1]))
            return 1;
    int left = 0, right = n; /* 待查找区间为 [left,right)。 */
    while (left < right) {
        int mid = left + (right - left) / 2; /* 中点不会越过右边界。 */
        if (a[mid] < x)
            left = mid + 1; /* mid 及左侧都不可能是答案。 */
        else
            right = mid; /* mid 可能是首个候选，保留它。 */
    }
    printf("%d\n", left < n && a[left] == x ? left : -1); /* 防止越界后再判等。 */
    return 0;
}
