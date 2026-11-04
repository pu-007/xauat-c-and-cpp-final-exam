# 13_binary_search 二分查找第一个匹配

层级：拓展。来源：S2 填空6的线性查找拓展。

## 任务

n=0..100及目标x，再输入非降序数组；输出首个匹配下标或-1

## 样例

输入（空白表示无输入）：

```text
5 2
1 2 2 4 9
```

输出：

```text
1
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：半开区间[left,right)；小于目标的在左侧，候选答案始终在未排除范围。

复杂度参考：查找O(log n)，含输入及验证的整个程序O(n)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/13_binary_search.c) / [C++11](../../src/cpp/13_binary_search.cpp)。

```bash
./build/c/13_binary_search < tests/cases/13_binary_search.in
./build/cpp/13_binary_search < tests/cases/13_binary_search.in
```
