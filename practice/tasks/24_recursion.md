# 24_recursion 递归与快速幂（取模）

层级：拓展。来源：S1 p42 编程12；递归算法拓展。

## 任务

a=0..10^9,b=0..10^9；输出a^b mod 1000000007；约定a^0=1

## 样例

输入（空白表示无输入）：

```text
2 10
```

输出：

```text
1024
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：指数减半；先算一次半幂再复用，避免重复递归。

复杂度参考：O(log b)，递归栈O(log b)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/24_recursion.c) / [C++11](../../src/cpp/24_recursion.cpp)。

```bash
./build/c/24_recursion < tests/cases/24_recursion.in
./build/cpp/24_recursion < tests/cases/24_recursion.in
```
