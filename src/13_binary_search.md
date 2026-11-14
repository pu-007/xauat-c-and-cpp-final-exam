# 13_binary_search 二分查找第一个匹配

层级：拓展。来源：S2 填空6的线性查找拓展。

## 任务

n=0..100及目标x，再输入非降序数组；输出首个匹配下标或-1

本题是资料线性查找的拓展。x 和元素须在 int 范围；下标从 0 开始，重复元素返回最左位置。数组不满足非降序或输入无效时以非零状态退出。

## 样例

输入（空白表示无输入）：

```text
5 2
1 2 2 4 9
```

输出：

```text
1
```

推演：区间 `[0,5)` 的中点 2 对应 2，保留左侧 `[0,2)`；中点 1 仍为 2，接着检查位置 0 的 1，最终定位 1。

## 实践步骤

1. 读入并检查数组非降序，令 left=0、right=n，维护半开候选区间。
2. 中点值小于 x 时令 left=mid+1，否则令 right=mid，直到区间为空。
3. 若 left 未越界且对应值等于 x，输出下标，否则输出 -1；空数组直接得到 -1。
4. C 手写循环；C++ 用 lower_bound 并检查 end。数组存储 O(n)，查找辅助空间 O(1)。

复杂度参考：查找O(log n)，含输入及验证的整个程序O(n)。

完成后对照：[C99](../../src/13_binary_search.c) / [C++11](../../src/13_binary_search.cpp)。

```bash
./build/c/13_binary_search < tests/cases/13_binary_search.in
./build/cpp/13_binary_search < tests/cases/13_binary_search.in
```
