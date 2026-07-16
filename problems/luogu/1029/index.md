---
oj: "luogu"
problem_id: "P1029"
title: "[NOIP 2001 普及组] 最大公约数和最小公倍数问题"
description: "设 P=x0*a、Q=x0*b 后可化成 a*b=y0/x0 且 gcd(a,b)=1，答案就是 y0/x0 的不同质因子个数对应的 2^k。"
difficulty: "普及-"
date: 2026-06-18 22:24
toc: true
tags: ["数论", "最大公约数", "质因数分解", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1029
---

[[TOC]]

### 题意

给出两个正整数 $x_0, y_0$。  
要求统计有多少组正整数有序对 `(P,Q)` 满足：

- $\gcd(P,Q) = x_0$
- $\operatorname{lcm}(P,Q) = y_0$

### 思路

先看一个可以直接验证想法的朴素解：

把题目改写成：

- $P = x_0 \cdot a$
- $Q = x_0 \cdot b$

那么只要枚举 $n = y_0 / x_0$ 的所有因子对 `(a,b)`，检查它们是否互质，就能数出答案。

@include-code(./brute.cpp, cpp)

这个想法已经很接近正解了，关键只差最后一步：

既然要求 $\gcd(a,b)=1$，那 $n = y_0 / x_0$ 的每个质因子幂次块就不能同时分给 `a` 和 `b`。

例如若：

$n = 2^2 \times 5$

那么方案只会是下面四种：

| `2^2` 去向 | `5` 去向 | `a` | `b` |
| --- | --- | --- | --- |
| 左边 | 左边 | `20` | `1` |
| 左边 | 右边 | `4` | `5` |
| 右边 | 左边 | `5` | `4` |
| 右边 | 右边 | `1` | `20` |

表格里每个“质因子块”都只有两种去向：给左边或给右边。  
所以如果 `n` 有 `k` 个不同质因子，总方案数就是：

`2^k`

于是正式做法就很简单：

1. 先判断 `y0` 是否能被 `x0` 整除；
2. 令 $n = y_0 / x_0$；
3. 对 `n` 做试除分解；
4. 每发现一个新的不同质因子，就让答案乘 `2`。

### Python 知识

- Python 整数不会溢出，可以直接计算质因子块数量对应的 `1 << k`。
- `while quotient % prime == 0` 一次除尽同一质因子，只统计不同质因子个数。
- 位移 `1 << distinct_primes` 就是 $2^k$，准确表达每个质因子块的二选一。
- 先检查整除关系，避免对不可能的输入继续分解。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：Python 任意精度整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：把独立选择归约成乘积的思路。

### 代码

@include-code(./main.py, python)

### 复杂度

设 $n = y_0 / x_0$，时间复杂度是 $O(\sqrt{n})$，空间复杂度是 $O(1)$。

### 总结

这题表面在数 `(P,Q)`，本质在数 `y0/x0` 的不同质因子块如何分给左右两边。

把 gcd 和 lcm 先拆开之后，问题会一下子变成很标准的数论计数题。
