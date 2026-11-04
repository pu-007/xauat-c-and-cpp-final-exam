# 01_expressions 表达式、短路与确定的求值顺序

层级：基础。来源：S3 选择4/12、简答1；S2 选择10–16。

## 任务

无输入；逐行输出表达式结果

## 样例

输入（空白表示无输入）：

```text

```

输出：

```text
2 2.5
24 10 60 0 0
0 0 2
3 4
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：先确定类型，再确定结合关系；优先级不等于执行顺序。

复杂度参考：O(1)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/01_expressions.c) / [C++11](../../src/cpp/01_expressions.cpp)。

```bash
./build/c/01_expressions < tests/cases/01_expressions.in
./build/cpp/01_expressions < tests/cases/01_expressions.in
```
