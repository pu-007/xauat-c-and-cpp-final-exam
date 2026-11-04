# 15_strings 手写strlen/strcat/strcmp、回文

层级：提高。来源：S1 p42 编程5–7、p120 编程2；S5 p7 My_strcat。

## 任务

输入两行英语字符串，每行<=100字节；输出拼接、长度、字典序比较符号、第一行是否回文

## 样例

输入（空白表示无输入）：

```text
abba
xy
```

输出：

```text
abbaxy
6 -1 1
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：字符串内容之后必须放零字符；容量包含该零字符；双指针从两端比较。

复杂度参考：O(n+m)。

挑战：补写有容量参数的copy；不要把字符数组等同于字符串。

完成后对照：[C99](../../src/c/15_strings.c) / [C++11](../../src/cpp/15_strings.cpp)。

```bash
./build/c/15_strings < tests/cases/15_strings.in
./build/cpp/15_strings < tests/cases/15_strings.in
```
