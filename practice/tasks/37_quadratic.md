# 37_quadratic 二次方程及退化情况

层级：基础。来源：S6实验1(2) p3–4；S1分支填空5。

## 任务

输入三个有限实数 a、b、c，绝对值均不超过 10000。求 ax²+bx+c=0：a 非零且判别式非负时输出 `REAL` 和升序两根；判别式为负输出 `COMPLEX`、实部和非负虚部幅值。a 为零时输出 `LINEAR` 和唯一根，或 `ALL`（恒等式）、`NONE`（无解）。数值保留六位小数。本题是原实验的退化及复数情况扩展。

## 样例

输入（空白表示无输入）：

```text
1 -3 2
```

输出：

```text
REAL 1.000000 2.000000
```

## 推演与步骤

样例中 Δ=(-3)²-4×1×2=1，两根为 (3±1)/2，即 1、2。

1. 先判断 a=0，避免以 2a 为除数；再判断 b、c。
2. 否则计算判别式，非负时计算两根并排序；负数时输出共轭根的实部和虚部幅值。
3. 例如 `0 0 0` 输出 `ALL`，`1 0 1` 输出 `COMPLEX -0.000000 1.000000`；浮点计算可能产生带符号零和舍入误差。

时间、空间均 O(1)。C 用 scanf/printf 和 sqrt，C++ 用流、std::sqrt 与 std::swap；直接求根公式可能有相消误差。

[C99](../../src/37_quadratic.c) / [C++11](../../src/37_quadratic.cpp)

```bash
./build/c/37_quadratic < tests/cases/37_quadratic.in
./build/cpp/37_quadratic < tests/cases/37_quadratic.in
```

