---
oj: "luogu"
problem_id: "P3435"
title: "[POI 2006] OKR-Periods of Words"
description: "把每个前缀的最长 period 转成最短非空 border，再沿 KMP 的前缀函数链递推这个最短 border。"
difficulty: "提高+/省选-"
date: 2026-06-21 13:00
toc: true
tags: ["字符串", "KMP", "递推"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3435
---

[[TOC]]

### 题意

给一个字符串 `S`。

对 `S` 的每个前缀，都定义它的 `maximum period`：

- 这个 `period` 本身必须是这个前缀的一个真前缀
- 同时整个前缀要是这个 `period` 无限循环后的前缀
- 如果不存在，就认为长度为 `0`

现在要求所有前缀的 `maximum period` 长度之和。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

暴力做法是对每个前缀从大到小枚举 period 长度，再直接判断这个前缀能不能由前 `p` 个字符循环得到。

瓶颈在于判断太慢，所以要先把定义改写一下。

设当前前缀长度为 `i`，若存在一个合法 period，长度为 `p`，那么后面所有字符都满足：

- `s[k] = s[k-p]`

这就说明前缀 `s[1..i-p]` 同时是 `s[1..i]` 的前缀和后缀，也就是一个非空 border。

反过来，如果 `b` 是一个非空 border，那么令 `p = i-b`，这个 `p` 也一定是一个合法 period。

所以：

- period 长度 `p`
- 与 border 长度 `b`

满足关系：

- `p = i - b`

要让 period 最长，就等价于让 border 最短。

于是题目变成：

- 对每个前缀，求最短的非空 border 长度
- 这一项贡献就是 `前缀长度 - 最短非空 border`

接下来用 KMP 前缀函数。

设 `pi[i]` 表示前缀 `s[1..i]` 的最长真前后缀长度，那么这个前缀的所有 border 正好是一条链：

- `pi[i]`
- `pi[pi[i]]`
- `pi[pi[pi[i]]]`
- ...

因此最短的非空 border，就是这条链上的最后一个非零值。

设 `min_border[i]` 表示前缀 `s[1..i]` 的最短非空 border：

- 若 `pi[i] = 0`，则不存在
- 若 `pi[i]` 还能继续跳到更短的非空 border，就直接继承
- 否则 `pi[i]` 本身就是最短非空 border

这样在求前缀函数的同时就能顺手线性递推出来。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

前缀函数是 $O(n)$。

递推 `min_border` 也是 $O(n)$。

总时间复杂度 $O(n)$，空间复杂度 $O(n)$。

### 总结

这题最关键的转换是：

1. 最长 period 等价于最短非空 border
2. 所有 border 正好在 KMP 的失配链上
3. 所以用前缀函数加一个简单递推就能线性求解

本质上是一个“把循环定义改写成前后缀关系”的字符串题。
