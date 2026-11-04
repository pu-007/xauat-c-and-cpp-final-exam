/* 20_linked_list 动态内存、头插、删除、反转 | ISO C++11 | 提高
 * 来源/关系：S1 p77–78 链表题、模拟三编程3；同类综合（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100、删除目标；再输入n个int；按输入顺序建表，删除所有目标后反转输出
 * 思想：用二级指针统一删除头结点与普通结点；先保存next再释放。
 * 复杂度：O(n)，空间O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 */
#include <iostream>
#include <forward_list>
int main() {
    int n, target;
    if (!(std::cin >> n >> target) || n < 0 || n > 100)
        return 1;
    std::forward_list<int> a; // RAII：离开作用域自动释放所有结点。
    auto tail = a.before_begin();
    for (int i = 0; i < n; ++i) {
        int x;
        if (!(std::cin >> x))
            return 1;
        tail = a.insert_after(tail, x);
    }
    a.remove(target);
    a.reverse();
    bool first = true;
    for (int x : a) {
        if (!first)
            std::cout << ' ';
        std::cout << x;
        first = false;
    }
    std::cout << '\n';
}
