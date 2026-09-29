---
oj: "roj"
problem_id: "1101"
title: "不定方程求解"
description: "枚举 x 的非负上界 c//a，逐个判定 (c-ax) 能否被 b 整除，整除即唯一确定一组非负解，计数即为答案。"
difficulty: "入门"
date: 2026-09-29 18:51
updated: 2026-09-29 18:53
toc: true
tags:
  - 枚举
  - 数论
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1101
---

[[TOC]]

## 形式化题目

给定正整数 $a, b, c$，统计不定方程

$$a x + b y = c$$

的非负整数解 $(x, y)$（即 $x \geqslant 0$ 且 $y \geqslant 0$）的组数。

## 正解

### 思路

要求的是"解的个数"，而不是某组具体的解，这提示我们去**计数**。方程里有两个未知数，但"非负"这个限制给了每个未知数独立的上界：

- 由 $by \geqslant 0$ 得 $ax \leqslant c$，即 $x \leqslant \lfloor c/a \rfloor$；
- 同理 $y \leqslant \lfloor c/b \rfloor$。

最朴素的想法是双重循环枚举 $x, y$ 验证等式，复杂度 $O\bigl((c/a)\cdot(c/b)\bigr)$，最坏约 $10^6$。但这个做法浪费在"每个 $x$ 配对所有 $y$"上——仔细看方程：**固定 $x$ 之后，$y$ 就被唯一确定了**：

$$by = c - ax \implies y = \frac{c - ax}{b}$$

它是一组合法解，当且仅当：

1. $c - ax \geqslant 0$：保证 $y \geqslant 0$（这就是枚举上界 $x \leqslant \lfloor c/a \rfloor$ 的来源）；
2. $(c - ax) \bmod b = 0$：保证 $y$ 是整数。

满足这两个条件时，$y = (c-ax)/b$ 是**唯一**确定的，所以每个合法的 $x$ 恰好贡献一组解；又因为不同的解 $x$ 必不同，按 $x$ 分类计数不重不漏。于是：

$$\text{答案} = \#\{\, x \mid 0 \leqslant x \leqslant \lfloor c/a \rfloor,\ (c - ax) \bmod b = 0 \,\}$$

用样例 $a=2, b=3, c=18$ 走一遍这个过程（$x$ 上界为 $\lfloor 18/2 \rfloor = 9$）：

| $x$ | $c - ax$ | $\bmod\ b$ | 是否成解 $(y)$ |
| :-: | :-: | :-: | :-: |
| 0 | 18 | 0 | ✔ $(6)$ |
| 1 | 16 | 1 | ✘ |
| 2 | 14 | 2 | ✘ |
| 3 | 12 | 0 | ✔ $(4)$ |
| 4 | 10 | 1 | ✘ |
| 5 | 8 | 2 | ✘ |
| 6 | 6 | 0 | ✔ $(2)$ |
| 7 | 4 | 1 | ✘ |
| 8 | 2 | 2 | ✘ |
| 9 | 0 | 0 | ✔ $(0)$ |

表中每一行是固定 $x$ 后对 $y$ 的唯一判定：余数为 $0$ 的行各给出一组解，共 4 组，与样例输出一致。注意最后一行 $x=9$ 时余数为 $0$，此时 $y=0$——$y=0$ 是合法的非负解，说明枚举区间的右端点必须取到 $\lfloor c/a \rfloor$。

数据范围 $a, b, c \leqslant 1000$ 保证枚举量至多 $1001$，单循环即可通过；无需扩展欧几里得求通解，直接计数更简单也更不易错。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(c/a) \leqslant O(c)$，即至多约 $1000$ 次整除判定；空间复杂度 $O(1)$（生成器逐个产出，不建表）。

## 总结

- "非负"限制天然给出每个未知数的上界，使枚举成为可能；
- 固定一个未知数后，另一个被一元方程唯一确定——第二维根本不需要枚举，"整除判定"就是它存在的全部条件；
- 计数不重不漏：按 $x$ 分类，不同的解 $x$ 必不同，每个合法 $x$ 恰给一组解；
- $y = 0$ 也是合法解，枚举右端点要闭合（`range(c // a + 1)` 中的 `+1`）。
