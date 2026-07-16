---
oj: "luogu"
problem_id: "P3435"
title: "[POI 2006] OKR-Periods of Words"
description: "沿前缀函数链递推每个前缀的最短非空 border，从而得到最长 period。"
difficulty: "提高+/省选-"
date: 2026-07-16 19:57
toc: true
tags: ["KMP", "周期", "递推", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3435
---

[[TOC]]

### 题意

对字符串的每个前缀求最长 period 的长度，并把这些长度求和。

### 思路

长度为 `length` 的前缀若有 border `b`，对应 period 长度就是 `length-b`。要让 period 最长，就要找最短的非空 border。

KMP 的 `prefix[length]` 给出最长 border，而所有更短 border 都沿 `prefix` 链出现。令 `shortest_border[length]` 表示链尾的最短非零长度，则：

```text
shortest_border[length] = shortest_border[j] or j
```

其中 `j = prefix[length]`。每个位置只做常数次递推。

### Python 知识

- `x or fallback` 会在 `x == 0` 时取后者，正好表达“已有最短 border，否则当前 border”。
- 使用 1-based 长度数组能让 `prefix[j]` 与数学定义直接对应。
- 两个 `array("i")` 在百万长度下仍只占约 8 MB。

### 代码

@include-code(./main.py, python)

### 复杂度

时间 $O(n)$，空间 $O(n)$。

### 总结

前缀函数只直接给最长 border，但它的链包含全部 border；在链上递推所需统计量是常见技巧。
