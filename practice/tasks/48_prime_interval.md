# 48_prime_interval 区间素数

来源：S1 PDF 第115页模拟二编程1；本题为限定输入输出后的改编。

## 题意与输入输出

无输入。使用独立素数判断函数，输出闭区间 200 至 300 内的全部素数，按升序放在一行，相邻数字以一个空格分隔，行末换行。素数是大于 1 且只有 1 和自身两个正因子的整数。

## 样例

输入为空。输出：

```text
211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293
```

推演：200 能被 2 整除，故不输出；211 试除从 2 到 14 均无因子，因此输出 211。

## 方法

依次枚举区间内的整数，独立函数从 2 试除到平方根；若存在因子便不是素数。时间复杂度 O(101×sqrt(300))，空间复杂度 O(1)。C99 以整数表示真伪并用 `printf` 输出；C++11 以 `bool` 表示真伪并用 `std::cout` 输出。

常见错误：将 1 视为素数；发现一个数不能整除就过早判定为素数；漏掉平方根处的因子；多输出空格。

## 编译与运行

源码：[C99](../../src/48_prime_interval.c) / [C++11](../../src/48_prime_interval.cpp)。

```bash
cc -std=c99 -Wall -Wextra -pedantic src/48_prime_interval.c -o /tmp/48_c
c++ -std=c++11 -Wall -Wextra -pedantic src/48_prime_interval.cpp -o /tmp/48_cpp
/tmp/48_c < tests/cases/48_prime_interval.in
/tmp/48_cpp < tests/cases/48_prime_interval.in
```
