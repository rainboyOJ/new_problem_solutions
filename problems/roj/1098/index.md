---
oj: "roj"
problem_id: "1098"
title: "质因数分解"
description: "n 是两个不同质数之积，从小到大试除到 sqrt(n) 找最小质因子 p，输出 n/p 即较大质数，O(sqrt(n))。"
difficulty: "入门"
date: 2026-09-29 18:39
updated: 2026-10-04 14:29
toc: true
tags: ["入门", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1098
---

[[TOC]]

## 形式化题目

给定正整数 $n = p \cdot q$，其中 $p$、$q$ 是两个**不同**的质数，求出较大的那个质数。

样例：$n = 21 = 3 \times 7$，输出 $7$。

## 正解

### 思路

按定义做的话，枚举 $2 \sim n-1$ 找 $n$ 的因子是 $O(n)$ 的，$n$ 最大 $2 \times 10^9$，1 秒内跑不完。

关键观察是**因子成对出现**：设 $n = pq$ 且 $p < q$，那么必有 $p \leqslant \sqrt{n}$——否则 $p > \sqrt{n}$ 且 $q > \sqrt{n}$，乘起来就超过 $n$ 了，矛盾。又因为两个质数不同，所以严格地有 $p < \sqrt{n} < q$。$\sqrt{2 \times 10^9} \approx 44722$，枚举量一下子从二十亿降到四万多。

于是从小到大枚举 $d = 2, 3, \dots, \lfloor\sqrt{n}\rfloor$，**第一个**整除 $n$ 的 $d$ 就是较小的质数 $p$：如果这个 $d$ 是合数，它一定有更小的因子也整除 $n$，与"第一个"矛盾；而 $n$ 只有两个非平凡因子 $p$、$q$，其中只有 $p$ 落在枚举范围内。答案即 $n / p$，直接整除输出。

以样例演示：$n = 21$，依次试除 $2$（不整除）、$3$（整除），得 $p = 3$，输出 $21 / 3 = 7$。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间：$O(\sqrt{n})$，最坏约 $4.5 \times 10^4$ 次取模，找到即停。
- 空间：$O(1)$。

## 总结

本题的核心是"因子成对、最小因子不超过 $\sqrt{n}$"这一条性质，它把找因子的枚举范围从 $O(n)$ 压缩到 $O(\sqrt{n})$。由于题目额外保证 $n$ 恰好是两个不同质数之积，从小到大找到的第一个因子必然是较小的质数，无需任何素性判断。这也是一般质因数分解试除法的同款上界，是数论题的基本功。
