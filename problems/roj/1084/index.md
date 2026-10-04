---
oj: "roj"
problem_id: "1084"
title: "幂的末尾"
description: "利用乘法取模同余，每次只保留末三位，迭代 b 次后格式化输出。"
difficulty: "入门"
date: 2026-09-29 17:53
updated: 2026-09-29 17:53
toc: true
tags: ["模拟", "取模"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1084
---

[[TOC]]

## 形式化题目

给定两个正整数 $a, b$，求 $a^b$ 的末三位十进制数字，不足三位时前补 `0`。

数据范围：$1 \leqslant a \leqslant 100$，$1 \leqslant b \leqslant 10000$。

## 正解

### 思路

直接计算 $a^b$ 会得到一个巨大的数，但题目只要末三位。利用同余性质：

$$(x \cdot y) \bmod m = ((x \bmod m) \cdot (y \bmod m)) \bmod m$$

令 $m = 1000$，则每次乘法后取模即可只保留末三位。设 $r_0 = 1$，递推：

$$r_i = r_{i-1} \cdot a \bmod 1000$$

则 $r_b \equiv a^b \pmod{1000}$，即为答案。

以样例 $a = 7, b = 2011$ 为例：

| 步数 $i$ | $r_i = r_{i-1} \cdot 7 \bmod 1000$ |
| ---: | ---: |
| 1 | 7 |
| 2 | 49 |
| 3 | 343 |
| 4 | 401 |
| ... | ... |
| 2011 | 743 |

最终输出 `743`。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(b)$，每次循环一次乘法和取模。
- 空间复杂度：$O(1)$，只保存当前余数。

## 总结

本题是模运算同余性质的最直接应用：只需要末几位，就在乘法过程中反复对 $10^k$ 取模，避免大数运算。实现时把结果格式化为固定宽度即可补齐前导零。
