# 49_min_to_end 最小元素移至末尾

来源：S1 PDF 第 115 页模拟二编程 3；本题为限定输入输出和数据范围后的改编。

读入整数 n（1..100）及 n 个整数（均为 -10^9..10^9）。编写自定义函数，将第一次出现的最小元素与最后一项交换。输出交换后的 n 个整数，占一行，相邻整数以一个空格分隔。读取失败或数值越界时返回 1，不输出结果。

输入：先给出 n，随后给出 n 个整数，空白分隔。

样例输入：

```text
5
4 1 3 1 2
```

样例输出：

```text
4 2 3 1 1
```

最小值 1 首次出现在第二项，与末项 2 交换，得到上述结果。n 为 1 或最小值已在末尾时，交换自身即可。

从下标 0 开始记录最小位置，扫描后续元素，仅在发现严格更小的值时更新，从而保留首次位置；然后交换该位置和末尾。时间 O(n)，数组空间 O(n)。C 使用定长数组，C++ 使用 vector 和引用。

源码：[C99](../../src/49_min_to_end.c) / [C++11](../../src/49_min_to_end.cpp)。

```bash
cc -std=c99 -Wall -Wextra -pedantic src/49_min_to_end.c -o /tmp/49_min_to_end_c
c++ -std=c++11 -Wall -Wextra -pedantic src/49_min_to_end.cpp -o /tmp/49_min_to_end_cpp
/tmp/49_min_to_end_c < tests/cases/49_min_to_end.in
/tmp/49_min_to_end_cpp < tests/cases/49_min_to_end.in
```

常见错误：比较时使用 `<=` 会选择最后一次出现的最小值；把最小值覆盖后才尝试交换会丢失原值。
