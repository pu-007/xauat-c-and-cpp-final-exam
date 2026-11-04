# 16_words_vowels 单词状态机、元音筛选、字符排序

层级：提高。来源：S5 p3 单词数、p7–8 元音/字符排序；S1 p32 编程14。

## 任务

输入一行<=100字节；单词按空白分隔；输出单词数、原顺序元音、升序字符（含空格）

## 样例

输入（空白表示无输入）：

```text
hi a
```

输出：

```text
2
ia
 ahi
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：状态从单词外进入单词内时才计数；筛选维护写位置，排序不包含结束符。

复杂度参考：C字符排序O(n²)，C++排序O(n log n)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/16_words_vowels.c) / [C++11](../../src/cpp/16_words_vowels.cpp)。

```bash
./build/c/16_words_vowels < tests/cases/16_words_vowels.in
./build/cpp/16_words_vowels < tests/cases/16_words_vowels.in
```
