---
oj: "shumeng"
problem_id: "CSP202403A"
title: "词频统计"
description: "逐篇文章累加单词总次数，并用文章编号标记同一单词在当前文章中是否已经出现。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "计数"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202403A
---

[[TOC]]

### 题意

给出 $n$ 篇文章中的单词编号，统计每个单词出现在多少篇文章中，以及在所有文章中出现的总次数。

### 思路

先看用集合记录单篇文章不同单词的朴素做法：

@include-code(./brute.cpp, cpp)

扫描每篇文章时，单词每读到一次就将总次数加一；如果它在当前文章中第一次出现，再将文章数加一。用 `last_article[word]` 记录该单词上次计数的文章编号，就不必为每篇文章重新清空整张布尔表。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设所有文章的单词总数为 $S$，算法时间复杂度为 $O(S)$，空间复杂度为 $O(m)$。

### 总结

“出现总次数”和“出现文章数”是两个不同统计量：前者每次出现都累加，后者同一篇文章内只能累加一次。
