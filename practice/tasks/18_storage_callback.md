# 18_storage_callback static、作用域、函数指针、宏

层级：提高。来源：S1 函数/指针选择；S2 选择28–29；S4 p1/p4。

## 任务

无输入；输出累计调用数、函数回调结果、平方与位运算

## 样例

输入（空白表示无输入）：

```text

```

输出：

```text
1 2
5 25
24 2 5
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：局部static只初始化一次；函数指针保留签名；宏加括号也不能避免重复求值。

复杂度参考：O(1)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/18_storage_callback.c) / [C++11](../../src/cpp/18_storage_callback.cpp)。

```bash
./build/c/18_storage_callback < tests/cases/18_storage_callback.in
./build/cpp/18_storage_callback < tests/cases/18_storage_callback.in
```
