/* 17_pointers 值传递、指针、数组指针 | ISO C++11 | 提高
 * 来源/关系：S1 p43–61；S2 函数/指针读程序；S4 p4（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：无输入；输出值传递后原值、指针交换后值、指针步进及二维访问
 * 思想：C所有参数均按值传递；传地址让函数能间接修改调用者对象。
 * 复杂度：O(1)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
void wrong_swap(int a, int b) {
    int t = a;
    a = b;
    b = t;
    (void)a;
    (void)b;
}
void swap_ref(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
} // 引用是已有对象的别名。
int main() {
    int x = 3, y = 7;
    wrong_swap(x, y);
    std::cout << x << ' ' << y << '\n';
    swap_ref(x, y);
    std::cout << x << ' ' << y << '\n';
    int a[] = {10, 20, 30};
    int *p = a;
    int old = *p++;
    (*p)++;
    std::cout << old << ' ' << *p << ' ' << a[1] << '\n';
    int m[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int (*row)[3] = m;
    std::cout << *(*(row + 1) + 2) << ' ' << m[1][2] << '\n';
}
