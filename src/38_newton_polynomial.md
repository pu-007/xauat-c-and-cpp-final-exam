# 38_newton_polynomial 报告指定方程的牛顿迭代

层级：提高。来源：S6实验2(1) p9–10。

## 任务

无输入；从1.5求2x^3-4x^2+3x-6=0的根，输出六位小数

## 样例

输入（空白表示无输入）：

```text

```

输出：

```text
2.000000
```

## 实践步骤

1. 写出导数 f'(x)=6x²−8x+3；计算 f(1.5)=-3.75、f'(1.5)=4.5，第一次迭代得到 x=7/3，约 2.333333。
2. 每次计算 x−f(x)/f'(x)，导数过小或结果非有限时退出；同时满足步长小于 1e-10、残差小于 1e-9 才输出。
3. 后续迭代逐渐接近 2，最多迭代 100 次，满足条件后输出 2.000000。失败时返回非零状态，无正常输出。

时间 O(k)，k≤100；空间 O(1)。C 使用 `fabs` 和 `printf`，C++ 使用 `std::abs`、流与 `setprecision`。本题固定初值，无输入边界；更换初值属于拓展。

完成后对照：[C99](./38_newton_polynomial.c) / [C++11](./38_newton_polynomial.cpp)。

```bash
./build/c/38_newton_polynomial < tests/cases/38_newton_polynomial.in
./build/cpp/38_newton_polynomial < tests/cases/38_newton_polynomial.in
```
