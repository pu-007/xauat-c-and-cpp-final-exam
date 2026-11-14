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

1. 读取三个无空白的字符串，每个 1 至 9 字节；按字节字典序而非长度比较。
2. 先取前两个较大者，再与第三个比较；相等时输出相同内容即可。
3. 样例首字符依次为 a、z、p，z 最大，所以输出 `zoo`；例如 `ab` 小于 `abc`，因为前者是后者前缀。

总比较时间 O(n)，C 固定缓冲区空间 O(1)，C++ 字符串空间 O(n)。C 用 `strcmp` 比较内容、`strcpy` 复制，C++ 使用 `std::string` 与 `std::max`。输入长度限制是教学改编。

完成后对照：[C99](../../src/45_string_max.c) / [C++11](../../src/45_string_max.cpp)。

```bash
./build/c/45_string_max < tests/cases/45_string_max.in
./build/cpp/45_string_max < tests/cases/45_string_max.in
```
