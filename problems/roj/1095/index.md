---
oj: "roj"
problem_id: "1095"
title: "数1的个数"
description: "从 1 到 n 枚举每个整数，逐位统计数字 \"1\" 出现的次数并求和。"
difficulty: "入门"
date: 2026-09-29 18:29
updated: 2026-10-05 00:59
toc: true
tags: ["枚举", "字符串", "一本通"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1095
---

[[TOC]]

## 题目描述

给定一个十进制正整数 $n$（$1 \leqslant n \leqslant 10000$），写下从 $1$ 到 $n$ 的所有整数，数一数其中出现的数字 "1" 的个数。例如 $n=12$ 时，写下 $1,2,\dots,12$，共出现了 $5$ 个 "1"。

输入：正整数 $n$。输出：一个正整数，即 "1" 的个数。

样例输入：

```text
12
```

样例输出：

```text
5
```

## 思路

$n$ 不超过 $10^4$，直接从 $1$ 到 $n$ 枚举每个整数，对每个数不断除以 $10$ 取余数，统计个位为 $1$ 的次数后累加即可。总时间约 $O(n \cdot d)$（$d \leqslant 5$ 为位数），空间 $O(1)$。

## 参考代码

@include-code(./main.cpp, cpp)
