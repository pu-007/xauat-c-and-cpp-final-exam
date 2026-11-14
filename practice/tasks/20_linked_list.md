# 20 单链表删除与反转

本题综合改编自 S1 PDF 第 77～78 页链表相关题，并非某一道原题的直接答案。

输入 n 和目标整数 target（0≤n≤100），再输入 n 个 int 范围内整数。按输入顺序构造链表，删除所有等于 target 的节点，然后反转剩余链表，输出一行整数，元素之间一个空格。没有剩余节点时输出空行。

输入：
```text
5 2
1 2 3 2 4
```
输出：
```text
4 3 1
```
推演：原链表为 1→2→3→2→4，删除两个 2 得 1→3→4，再反转得 4→3→1。

1. C 头插得到逆序链表，先反转恢复输入顺序；C++ 在尾部追加。
2. C 用指向当前链接的二级指针遍历，删除时先接上后继再释放；C++ 使用 remove。
3. 反转并输出，最后释放 C 节点；检查空表、全删和连续命中。时间 O(n)，节点占 O(n) 空间。

边界练习：`0 2` 输出空行；`3 7` 后接 `7 7 7` 也输出空行；`3 2` 后接 `2 2 1` 输出 `1`，检验连续删除头节点。

C 手动 malloc/free 和调整 next；C++ forward_list 的 insert_after、remove、reverse 管理节点和释放。对照 [C99](../../src/20_linked_list.c) / [C++11](../../src/20_linked_list.cpp)：
```bash
./build/c/20_linked_list < tests/cases/20_linked_list.in
./build/cpp/20_linked_list < tests/cases/20_linked_list.in
```

