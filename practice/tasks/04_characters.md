# 04_characters 字符分类与大小写

层级：基础。来源：S1 p22 编程3；S2 填空1/5；S5 p1 例3.10。

## 任务

读到换行或EOF；输出字母、数字、空格、其他的个数；只针对单字节英语文本

## 样例

输入（空白表示无输入）：

```text
Ab9 !
```

输出：

```text
2 1 1 1
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：getchar用int接收EOF；字符分类函数接收unsigned char值。

复杂度参考：O(n)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/04_characters.c) / [C++11](../../src/cpp/04_characters.cpp)。

```bash
./build/c/04_characters < tests/cases/04_characters.in
./build/cpp/04_characters < tests/cases/04_characters.in
```
