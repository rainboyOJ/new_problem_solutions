---
oj: "roj"
problem_id: "1172"
title: "求10000以内n的阶乘"
description: "n! 有 35660 位，必须高精度；Python 的 int 天生任意精度，用分治相乘的 math.factorial 直接算，唯一要处理的是 Python 3.11 起 int→str 的 4300 位转换上限。"
difficulty: "入门"
date: 2026-09-29 22:01
updated: 2026-09-29 22:12
toc: true
tags: ["高精度", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1172
---

[[TOC]]

## 形式化题目

给定整数 $n$（$0 \leqslant n \leqslant 10000$），求

$$n! = \prod_{i=1}^{n} i$$

的**精确十进制表示**（约定 $0! = 1$），输出为一行不含前导零的数字串。要求结果一位不差，不接受浮点近似或科学计数法。

## 正解

### 思路

这道题的算法部分没有可优化的余地：$n!$ 就是 $n-1$ 次乘法，减不掉。真正决定成败的是**结果有多大**，以及**用什么类型装它**。

先算一笔账。$n!$ 的十进制位数是

$$d(n) = \lfloor \log_{10}(n!) \rfloor + 1 \approx n\log_{10}\frac{n}{e}$$

代入几个值：

| $n$ | 4 | 20 | 100 | 1000 | 8628（真实数据最大） | 10000（题面上界） |
| --- | --- | --- | --- | --- | --- | --- |
| $n!$ 位数 | 2 | 19 | 158 | 2568 | 30215 | 35660 |

64 位整数只能存下约 19 位十进制，所以 $n$ 稍大一点就溢出。这正是 C++ 解法必须手写高精度的原因：开一个 `int a[100000]` 数组，`a[0]` 记位数，每一位只存 0--9，每次乘 $i$ 之后统一进位。本题目录下的 `std.cpp` 走的就是这条路，代价是 $O(n \cdot D)$（$D$ 为结果位数）。

Python 不需要做这件事，因为 `int` 本身就是任意精度整数：它内部同样是一个"数组 + 进位"的实现，只不过每个数组元素打包了 30 个二进制位而不是 1 个十进制位，而且进位、扩容全部由解释器完成。于是 C++ 里那一整个手写循环，在 Python 里就是一次乘法。

有了任意精度整数，直接乘也能过，但标准库已经给了更快的实现：

| 表达式 | 含义 |
| --- | --- |
| `factorial(n)` | $n!$，来自 `math`，内部用**分治**相乘而非逐个累乘 |
| `str(x)` | 把大整数转成十进制字符串，即题目要的输出 |
| `sys.set_int_max_str_digits(5 * MAX_N)` | 放宽 `int` → `str` 的位数上限，见下 |

关于 `factorial` 的分治：逐个累乘是 $1 \times 2 \times 3 \times \cdots$，越到后面越是大数乘小数，大数的位长几乎参与每一次乘法。`math.factorial` 改用 **binary splitting**：把待乘的奇数区间不断对半切开递归相乘（CPython 源码 `Modules/mathmodule.c` 中这段的标题就是 *Divide-and-conquer factorial algorithm*，核心函数 `factorial_partial_product` 每次都按 `midpoint` 一分为二），同时把 $n!$ 写成 $2^k \cdot m$，偶数部分只贡献指数 $k$、用一次左移补回，奇数部分 $m$ 才真正参与大数相乘。这样相乘的两个操作数规模相近，大数×大数只发生在高层，参与的乘法次数大幅减少。

最后是本题在 Python 上唯一真正会踩的坑。Python 3.11 起给 `int` 转 `str` 加了一个 4300 位的默认上限（`int` 与 `str` 的进制转换是 $O(d^2)$ 的，限制是为了防止有人拿它做 DoS）。$10000!$ 有 35660 位，直接 `print(str(factorial(10000)))` 会抛出：

```
ValueError: Exceeds the limit (4300 digits) for integer string conversion;
use sys.set_int_max_str_digits() to increase the limit
```

所以要先放宽到题面上界之上。位数满足 $d(n) \leqslant n\log_{10} n$，取 `5 * MAX_N = 50000` 位足以覆盖 $10000!$ 的 35660 位：

```python
MAX_N = 10000
sys.set_int_max_str_digits(5 * MAX_N)
```

还有一处细节：$0! = 1$ 是数学约定，而 `factorial(0)` 恰好返回 `1`，与"循环一次都不执行、初值为 1"的写法一致，所以不需要为 $n=0$ 单独特判。

### 代码

@include-code(./main.py, python)

### 复杂度

记 $D = O(n\log n)$ 为 $n!$ 的十进制位数，$M$ 为 $D$ 位乘法的代价。

- 时间复杂度：$O(M(D)\log n)$。C++ 的逐位高精乘是 $O(nD)$，两者同阶或前者更优。
- 空间复杂度：$O(D)$，恰好是结果本身所需的位数。

实测：$n = 10000$ 约 $0.03$ s，峰值内存约 $15$ MB，均远低于题面的 1000 ms / 128 MB。

## 总结

- 本题的关键不在算法而在**数据类型**：$10000!$ 有 35660 位，只有高精度能装下它。
- Python 的 `int` 是任意精度的，C++ 里"数组存位 + 统一进位"的整套手写高精在 Python 中退化成一个类型本身，不需要自己实现。
- `math.factorial` 用 binary splitting（分治相乘），比逐个累乘更快，且与高精解法同阶 —— 这是"用标准库的正确算法"，不是"用取巧手段绕过算法"。
- **Python 3.11 起 `int` → `str` 默认只允许 4300 位**，大数题必须用 `sys.set_int_max_str_digits()` 放宽，否则拿到正确的大整数也会在输出时崩溃。这是本题最容易漏的一步。
- 边界 $n = 0$ 由 `factorial(0) == 1` 自然覆盖，无需特判。
