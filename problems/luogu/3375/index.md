---
oj: "luogu"
problem_id: "P3375"
title: "【模板】KMP"
description: "先为模式串求前缀函数 next，再在线性扫描文本串时失配回退，实现模式匹配与 border 长度统计。"
difficulty: "普及/提高-"
date: 2026-06-21 12:48
toc: true
tags: ["字符串", "KMP"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3375
---

[[TOC]]

### 题意

给两个字符串 `s1` 和 `s2`：

1. 输出 `s2` 在 `s1` 中所有出现的位置
2. 输出 `s2` 每个前缀的最长 border 长度

这里 border 指“既是前缀又是后缀，但不能是整个串本身”的最长长度。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

朴素匹配的问题在于：

- 文本串失配以后，模式串通常会退回到开头重新匹配

这样会做很多重复比较。

KMP 的核心就是：

- 先预处理模式串自身的信息

设 `nxt[i]` 表示：

- 模式串前缀 `pat[0..i]` 的最长 border 长度

那么在求 `nxt` 时，如果当前字符失配，就可以把 `j` 回退到：

- `nxt[j-1]`

因为更长的 border 已经不可能了，只能尝试次长 border。

匹配文本串时也完全同理：

- 若 `text[i]` 和 `pat[j]` 失配
- 就让 `j = nxt[j-1]`

这样每个字符至多进退若干次，总复杂度是线性的。

而题目要求输出的“每个前缀最长 border 长度”，其实就是整个 `nxt` 数组本身。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

构造 `nxt` 数组是 $O(m)$。

匹配文本串是 $O(n)$。

总复杂度 $O(n + m)$。

### 总结

KMP 最重要的不是背板子，而是理解：

- 失配后为什么可以跳到 `nxt[j-1]`

因为这代表“当前还能保留的最长相等前后缀长度”。

一旦理解这点，构造 `nxt` 和文本匹配就是同一套回退逻辑。
