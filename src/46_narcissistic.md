# 46_narcissistic 三位水仙花数

来源：S1 PDF 第108页模拟一编程1；本题为限定输入输出后的改编。

## 题意与输入输出

枚举所有三位水仙花数：一个三位数等于其百位、十位、个位的立方和。无输入，按从小到大在一行输出所有结果，相邻数字以一个空格分隔，行末换行。范围为 100 至 999。

## 样例

输入为空。输出：

```text
153 370 371 407
```

推演：153 的三位分别是 1、5、3，立方和为 1 + 125 + 27 = 153，故输出；逐一检查其他三位数得到其余结果。

## 方法

遍历 100 到 999，用整除和取余拆位，计算立方和并比较。首次输出不加前导空格。时间复杂度 O(900)，空间复杂度 O(1)。C99 用 `printf` 和整数标志，C++11 用 `std::cout` 和 `bool`。

常见错误：遗漏区间端点；取十位时忘记再对 10 取余；输出多余空格。

## 编译与运行

源码：[C99](./46_narcissistic.c) / [C++11](./46_narcissistic.cpp)。

```bash
cc -std=c99 -Wall -Wextra -pedantic src/46_narcissistic.c -o /tmp/46_c
c++ -std=c++11 -Wall -Wextra -pedantic src/46_narcissistic.cpp -o /tmp/46_cpp
/tmp/46_c < tests/cases/46_narcissistic.in
/tmp/46_cpp < tests/cases/46_narcissistic.in
```
