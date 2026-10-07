---
oj: "roj"
problem_id: "1087"
title: "级数求和"
description: "逐项累加调和级数，首次超过 k 的 n 就是最小答案，单调性保证正确。"
difficulty: "入门"
date: 2026-09-29 18:04
updated: 2026-10-05 00:39
toc: true
tags: ["入门", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1087
---

[[TOC]]

## 题目描述

已知 $S_n = 1 + \frac{1}{2} + \frac{1}{3} + \cdots + \frac{1}{n}$。对于任意整数 $k$，当 $n$ 足够大时 $S_n > k$。给定整数 $k\ (1 \leqslant k \leqslant 15)$，求最小的 $n$ 使得 $S_n > k$。

**输入**：一个整数 $k$。**输出**：一个整数 $n$。

**样例输入**：$k=1$，此时 $S_1=1 \leqslant 1$、$S_2=1.5>1$，故输出 $2$。

```text
1
```

**样例输出**：

```text
2
```

## 思路

$S_n$ 每步加上正数，严格递增且发散，所以从 $n=1$ 起逐项累加，和首次大于 $k$ 时的 $n$ 就是最小答案。由 $S_n \approx \ln n + \gamma$ 知 $k \leqslant 15$ 时答案不超过约 $1.8 \times 10^6$，直接用 double 循环即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
