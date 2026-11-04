# 09_recurrence 斐波那契与分数序列

层级：基础。来源：S5 p2 例5.8；S2 编程10。

## 任务

输入n=1..90；输出F(n)，F(1)=F(2)=1；再输出前20项分数和（六位小数）

## 样例

输入（空白表示无输入）：

```text
10
```

输出：

```text
55 32.660261
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：先保存下一项再移动状态；分数递推用double避免整数除法。

复杂度参考：O(n)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/09_recurrence.c) / [C++11](../../src/cpp/09_recurrence.cpp)。

```bash
./build/c/09_recurrence < tests/cases/09_recurrence.in
./build/cpp/09_recurrence < tests/cases/09_recurrence.in
```
