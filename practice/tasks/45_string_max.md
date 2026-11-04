# 45_string_max 三个字符串中字典序最大者

层级：基础。来源：S6实验2(4) p13–14。

## 任务

输入3个无空格字符串，每个1..9字节；输出字典序最大者

## 样例

输入（空白表示无输入）：

```text
apple zoo pear
```

输出：

```text
zoo
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：strcmp比较内容；最大不是最长，比较规则基于字符编码。

复杂度参考：O(字符串总长度)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/45_string_max.c) / [C++11](../../src/cpp/45_string_max.cpp)。

```bash
./build/c/45_string_max < tests/cases/45_string_max.in
./build/cpp/45_string_max < tests/cases/45_string_max.in
```
