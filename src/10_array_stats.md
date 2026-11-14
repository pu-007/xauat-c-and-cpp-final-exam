# 10_array_stats 数组、平均数、极值与下标

层级：基础。来源：S2 改错2/编程8/13；S5 p3–5。

## 任务

n=1..100，再输入n个绝对值<=10^6的整数；输出最小值及首个下标、最大值及首个下标、平均数

本题综合改编资料中的数组统计。下标从 0 开始，重复极值取第一次出现的位置；平均数保留两位小数。输入不合法时程序以非零状态退出。

## 样例

输入（空白表示无输入）：

```text
4
-5 3 3 1
```

输出：

```text
-5 0 3 1 0.50
```

推演：和为 -5+3+3+1=2；最小值 -5 在 0，最大值 3 首次在 1，平均数为 2/4=0.50。

## 实践步骤

1. 读入并检查 n 与每个数；用首元素的下标初始化两个极值位置。
2. 扫描数组，累加到 long long；只在严格更小或更大时更新位置。
3. 将和转为 double 再除以 n，按要求输出。单元素及全相等时两个位置均为 0。
4. C 使用定长数组与 scanf；C++ 使用 vector、min_element、max_element 和以 0LL 开始的 accumulate。

时间 O(n)，数组存储 O(n)。

完成后对照：[C99](./10_array_stats.c) / [C++11](./10_array_stats.cpp)。

```bash
./build/c/10_array_stats < tests/cases/10_array_stats.in
./build/cpp/10_array_stats < tests/cases/10_array_stats.in
```
