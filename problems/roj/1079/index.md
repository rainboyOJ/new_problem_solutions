---
oj: "roj"
problem_id: "1079"
title: "计算分数加减表达式的值"
description: "按奇偶符号直接逐项累加交错调和级数前 n 项，输出保留 4 位小数。"
difficulty: "入门"
date: 2026-09-29 17:42
updated: 2026-10-04 14:12
toc: true
tags: ["模拟", "数学", "入门"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1079
---

[[TOC]]

## 形式化题目

给定正整数 $n$，求

$$
S_n = \sum_{i=1}^{n} (-1)^{i-1}\frac1i
$$

即

$$
\frac11 - \frac12 + \frac13 - \frac14 + \cdots + (-1)^{n-1}\frac1n
$$

输出 $S_n$，保留小数点后 $4$ 位。

## 正解

### 思路

观察数列规律：第 $i$ 项的绝对值是 $1/i$，符号在奇数项为 $+$、偶数项为 $-$。因此可以直接从 $1$ 到 $n$ 枚举 $i$，用 `+1 / i` 或 `-1 / i` 加入答案。

把符号判断写成 `(1 if i & 1 else -1)`，整个求和用 `sum` 配合生成器表达式即可一行完成。$n \le 1000$，$O(n)$ 时间完全够用。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(n)$，只遍历一次 $1\sim n$。
- 空间复杂度：$O(1)$，仅用一个累加器。

## 总结

本题本质是带交替符号的调和级数求和。抓住“奇数项加、偶数项减”的规律，直接逐项累加即可。实现上用生成器求和能让代码更紧凑，输出时保留 4 位小数。
