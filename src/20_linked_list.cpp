/* 20_linked_list 动态内存、头插、删除、反转 | ISO C++11 | 提高
 * 来源/关系：S1 p77–78 链表题、模拟三编程3；同类综合（页码均为 PDF 页码；此文件为重写的教学实现）
 * 输入输出约定：n=0..100、删除目标；再输入n个int；按输入顺序建表，删除所有目标后反转输出
 * 思想：尾插保持输入顺序，remove删除所有匹配值，reverse反转；容器自动释放结点。
 * 复杂度：O(n)，空间O(n)
 * 练习：换一组边界数据，先手算再运行。
 * 学习顺序：先看题目→手算样例→遮住代码独立写→运行测试→比较另一语言。
 * 对照：20_linked_list.c用malloc/free及二级指针；本文件用forward_list插入、删除、反转并自动释放。
 */
#include <iostream> /* 流式输入输出。 */
#include <forward_list> /* 单向链表容器。 */
int main() {
    int n, target; /* 结点数及删除目标。 */
    if (!(std::cin >> n >> target) || n < 0 || n > 100)
        return 1; /* 输入失败或数量越界。 */
    std::forward_list<int> a; /* 离开作用域时自动释放结点。 */
    auto tail = a.before_begin(); /* 空表的头前位置，用于尾插。 */
    for (int i = 0; i < n; ++i) { /* 依次读入并尾插。 */
        int x; /* 当前输入值。 */
        if (!(std::cin >> x))
            return 1; /* 已建结点由容器析构释放。 */
        tail = a.insert_after(tail, x); /* 插到尾后并更新尾迭代器。 */
    }
    a.remove(target); /* 删除全部等于目标的结点。 */
    a.reverse(); /* 原地反转剩余结点。 */
    bool first = true; /* 标记是否输出首项。 */
    for (int x : a) { /* 从头至尾遍历反转结果。 */
        if (!first) /* 非首项需要分隔符。 */
            std::cout << ' '; /* 只在相邻元素间输出空格。 */
        std::cout << x; /* 输出当前结点。 */
        first = false; /* 后续元素前需要空格。 */
    }
    std::cout << '\n'; /* 空链也输出换行。 */
}
