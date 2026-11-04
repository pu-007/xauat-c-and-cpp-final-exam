# 26_prefix_window 前缀和与固定窗口

层级：拓展。来源：S1 p33 编程21的线性数组变式；拓展。

## 任务

n=1..1000,k=1..n；n个绝对值<=10^6整数；输出最大连续k项和及最早起点

## 样例

输入（空白表示无输入）：

```text
5 2
-4 2 3 -1 5
```

输出：

```text
5 1
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：前缀和将区间和化成一次相减；全负数组也必须从合法窗口初始化。

复杂度参考：O(n)；前缀和O(n)空间，窗口状态O(1)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/26_prefix_window.c) / [C++11](../../src/cpp/26_prefix_window.cpp)。

```bash
./build/c/26_prefix_window < tests/cases/26_prefix_window.in
./build/cpp/26_prefix_window < tests/cases/26_prefix_window.in
```
