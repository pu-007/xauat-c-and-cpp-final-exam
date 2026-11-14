# 50_sign_count 正负零计数

来源：S2 PDF 第 52 页编程 6；本题为限定输入输出和数据范围后的改编。

输入恰好 10 个整数，以空白分隔，每个整数在 -10^9..10^9 范围内。统计正数、负数和零各有多少个，按此顺序在一行输出三个整数，相邻数字用一个空格分隔。读取失败或数值越界时返回 1，不输出结果。

样例输入：

```text
2 -1 0 -5 0 3 7 -2 4 0
```

样例输出：

```text
4 3 3
```

推演：正数为 2、3、7、4，共 4 个；负数为 -1、-5、-2，共 3 个；剩余 3 个是零。

用三个计数器分别记录三种情况，逐项比较并且只增加对应计数器。时间 O(10)，额外空间 O(1)。C 使用 `scanf` 和 `printf`，C++ 使用输入输出流。

源码：[C99](./50_sign_count.c) / [C++11](./50_sign_count.cpp)。

```bash
cc -std=c99 -Wall -Wextra -pedantic src/50_sign_count.c -o /tmp/50_sign_count_c
c++ -std=c++11 -Wall -Wextra -pedantic src/50_sign_count.cpp -o /tmp/50_sign_count_cpp
/tmp/50_sign_count_c < tests/cases/50_sign_count.in
/tmp/50_sign_count_cpp < tests/cases/50_sign_count.in
```

常见错误：把零算入正数或负数；计数器没有初始化；输出顺序与题意不一致。
