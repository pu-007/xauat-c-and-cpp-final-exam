# 34_magic_square 奇数阶魔方阵

层级：提高。来源：S1 p33–34 编程23；p99–102另有更多阶数拓展。

## 任务

输入奇数n=1..15；输出n×n魔方阵

## 样例

输入（空白表示无输入）：

```text
3
```

输出：

```text
8 1 6
3 5 7
4 9 2
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：从首行中间开始向右上走；遇占用则从原位置向下；用模运算处理边界。

复杂度参考：O(n²)，空间O(n²)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/34_magic_square.c) / [C++11](../../src/cpp/34_magic_square.cpp)。

```bash
./build/c/34_magic_square < tests/cases/34_magic_square.in
./build/cpp/34_magic_square < tests/cases/34_magic_square.in
```
