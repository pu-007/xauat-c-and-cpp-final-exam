/* 11_reverse_rotate 逆序、循环右移、最小最大交换 | ISO C99 | 提高
 * 来源/关系：S5 p5 例8.8、p8 习题3；S1 p61 编程2/3（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=1..100,k=0..10^9，再输入n个int；先右移k位输出，再将最小换到首、最大换到尾后输出
 * 思想：三次反转实现旋转；交换后旧的极值位置可能失效，重新查找最大值。
 * 复杂度：O(n)，C版额外空间O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <stdio.h>
static void swap(int *x, int *y) {
    int t = *x;
    *x = *y;
    *y = t;
}
static void reverse(int a[], int left, int right) {
    while (left < right)
        swap(&a[left++], &a[right--]);
}
static void print(const int a[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%s%d", i ? " " : "", a[i]);
    putchar('\n');
}
int main(void) {
    int n, k, a[100];
    if (scanf("%d%d", &n, &k) != 2 || n < 1 || n > 100 || k < 0 || k > 1000000000)
        return 1;
    for (int i = 0; i < n; ++i)
        if (scanf("%d", &a[i]) != 1)
            return 1;
    k %= n;
    reverse(a, 0, n - 1);
    reverse(a, 0, k - 1);
    reverse(a, k, n - 1);
    print(a, n);
    int lo = 0;
    for (int i = 1; i < n; ++i)
        if (a[i] < a[lo])
            lo = i;
    swap(&a[0], &a[lo]);
    int hi = 0;
    for (int i = 1; i < n; ++i)
        if (a[i] > a[hi])
            hi = i;
    swap(&a[n - 1], &a[hi]);
    print(a, n);
    return 0;
}
