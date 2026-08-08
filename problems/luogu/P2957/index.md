---
oj: "luogu"
problem_id: "P2957"
title: "[USACO09OCT] Barn Echoes G"
description: "枚举所有可能的重合长度，分别检查两个方向的“后缀等于前缀”，取最大合法长度。"
difficulty: "入门"
date: 2026-06-19 10:28
toc: true
tags: ["字符串", "枚举"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2957
---

[[TOC]]

### 题意

给出两个字符串。

要求找出最长的重复部分长度。这里的重复部分指的是：

- 是一个字符串的前缀；
- 同时是另一个字符串的后缀。

两个方向都要考虑。

### 思路

因为字符串长度最大只有 `80`，直接枚举长度最简单。

最直接的教学版写法如下：

@include-code(./brute.cpp, cpp)

我们枚举一个长度 `len`，然后检查两件事：

1. `s` 的后 `len` 位是否等于 `t` 的前 `len` 位；
2. `t` 的后 `len` 位是否等于 `s` 的前 `len` 位。

只要某个方向成立，就可以用这个 `len` 更新答案。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(n^2)$
- 空间复杂度：$O(1)$

这里 `n` 是字符串长度上限，最多只有 `80`。

### 总结

这题不需要复杂字符串算法。

数据很小，直接枚举重合长度并比较前后缀，就是最稳的做法。
