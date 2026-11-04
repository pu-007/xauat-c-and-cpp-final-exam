# 36_prime_pipeline 综合压轴：素数筛选、函数、排序

层级：提高。来源：S1 p120–121 模拟三编程4。

## 任务

输入恰好10个-10^9..10^9整数；输出原数组与升序素数数组

## 样例

输入（空白表示无输入）：

```text
7 4 2 1 11 9 3 3 0 -5
```

输出：

```text
7 4 2 1 11 9 3 3 0 -5
2 3 3 7 11
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：分别实现findprime和冒泡sort；筛选返回有效长度，后续只处理有效元素。

复杂度参考：n个数时O(n√M+k²)，C++排序O(k log k)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/36_prime_pipeline.c) / [C++11](../../src/cpp/36_prime_pipeline.cpp)。

```bash
./build/c/36_prime_pipeline < tests/cases/36_prime_pipeline.in
./build/cpp/36_prime_pipeline < tests/cases/36_prime_pipeline.in
```
