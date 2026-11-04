# 11_reverse_rotate 逆序、循环右移、最小最大交换

层级：提高。来源：S5 p5 例8.8、p8 习题3；S1 p61 编程2/3。

## 任务

n=1..100,k=0..10^9，再输入n个int；先右移k位输出，再将最小换到首、最大换到尾后输出

## 样例

输入（空白表示无输入）：

```text
5 2
1 2 3 4 5
```

输出：

```text
4 5 1 2 3
1 3 4 2 5
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：三次反转实现旋转；交换后旧的极值位置可能失效，重新查找最大值。

复杂度参考：O(n)，C版额外空间O(1)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/11_reverse_rotate.c) / [C++11](../../src/cpp/11_reverse_rotate.cpp)。

```bash
./build/c/11_reverse_rotate < tests/cases/11_reverse_rotate.in
./build/cpp/11_reverse_rotate < tests/cases/11_reverse_rotate.in
```
