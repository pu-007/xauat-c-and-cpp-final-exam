# 05_factorial_sum 阶乘递推与累加

层级：基础。来源：S1 p22 编程1/5、p120 填空4；S2 编程7/9。

## 任务

输入n=0..20；输出n!和1!+...+n!，n=0时和为0

## 样例

输入（空白表示无输入）：

```text
5
```

输出：

```text
120 153
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：乘积初值1，和初值0；用上一次阶乘递推，避免重复计算。

复杂度参考：O(n)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/05_factorial_sum.c) / [C++11](../../src/cpp/05_factorial_sum.cpp)。

```bash
./build/c/05_factorial_sum < tests/cases/05_factorial_sum.in
./build/cpp/05_factorial_sum < tests/cases/05_factorial_sum.in
```
