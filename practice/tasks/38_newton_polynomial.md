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

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：x下一步=x-f(x)/导数；同时检查步长、残差与迭代次数。

复杂度参考：本程序最多100次迭代。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/38_newton_polynomial.c) / [C++11](../../src/cpp/38_newton_polynomial.cpp)。

```bash
./build/c/38_newton_polynomial < tests/cases/38_newton_polynomial.in
./build/cpp/38_newton_polynomial < tests/cases/38_newton_polynomial.in
```
