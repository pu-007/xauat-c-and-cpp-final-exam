# 37_quadratic 二次方程及退化情况

层级：基础。来源：S6实验1(2) p3–4；S1分支填空5。

## 任务

输入三个有限实系数a b c，绝对值<=10000；输出REAL两根/COMPLEX实部和正虚部幅度/LINEAR一根/ALL/NONE

## 样例

输入（空白表示无输入）：

```text
1 -3 2
```

输出：

```text
REAL 1.000000 2.000000
```

## 实践步骤

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：先处理a=0，再按判别式分类；复根的虚部幅度取非负。

复杂度参考：O(1)。

挑战：换一组边界数据，先手算再运行。

完成后对照：[C99](../../src/c/37_quadratic.c) / [C++11](../../src/cpp/37_quadratic.cpp)。

```bash
./build/c/37_quadratic < tests/cases/37_quadratic.in
./build/cpp/37_quadratic < tests/cases/37_quadratic.in
```
