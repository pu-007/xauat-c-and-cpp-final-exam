# 11_reverse_rotate 逆序、循环右移、最小最大交换

层级：提高。来源：S5 p5 例8.8、p8 习题3；S1 p61 编程2/3。

## 任务

n=1..100,k=0..10^9，再输入n个int；先右移k位输出，再将最小换到首、最大换到尾后输出

本题将资料中的操作组合改编。整数须在 int 范围内；输出两行，每行 n 个数，重复极值选择当前数组中第一次出现者。非法输入以非零状态退出。

## 样例

输入（空白表示无输入）：

```text
5 2
1 2 3 4 5
```

输出：

```text
4 5 1 2 3
1 3 4 2 5
```

推演：右移两位得到 `4 5 1 2 3`；将 1 与首元素交换得到 `1 5 4 2 3`，重新找最大值 5 并与末元素交换。

## 实践步骤

1. 将 k 对 n 取余；先整体反转，再分别反转前 k 项和剩余项。
2. 输出旋转结果；找首个最小值并与首项交换。
3. 在交换后的数组重新找首个最大值，与末项交换并输出。n=1 和 k=0 均适用。
4. C 使用指针交换及三次反转；C++ 使用 rotate、min_element 和 iter_swap。C++ vector 占 O(n) 空间。

时间 O(n)，数组存储 O(n)；C 版旋转操作额外空间 O(1)。

完成后对照：[C99](./11_reverse_rotate.c) / [C++11](./11_reverse_rotate.cpp)。

```bash
./build/c/11_reverse_rotate < tests/cases/11_reverse_rotate.in
./build/cpp/11_reverse_rotate < tests/cases/11_reverse_rotate.in
```
