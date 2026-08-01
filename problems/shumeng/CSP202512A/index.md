---
oj: "shumeng"
problem_id: "CSP202512A"
title: 集合
description: "同时比较集合本身与异或值是否相等，判断异或判等方法是否正确。"
date: 2026-07-31 16:22
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202512A
difficulty: "未知"
---

[[TOC]]

### 题意

对每个询问给出两个升序排列的不可重复集合 `S`、`T`。小 C 用集合元素对应的 `a_i` 异或值判断集合是否相等，要求判断这个判断结果是否与真实集合相等结果一致。

### 思路

输入保证集合内部已经严格递增，因此两个集合直接用 `vector` 比较即可。读入每个集合时同时计算所有 `a_x` 的异或和。

真实结论是 `S == T`，小 C 的结论是 `xor(S) == xor(T)`。两个布尔值相同就输出 `correct`，否则输出 `wrong`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设所有集合元素总数为 `L`，时间复杂度为 `O(L)`，空间复杂度为 `O(L)`。

### 总结

异或相等只是小 C 的判定条件，不能直接当作集合相等；必须比较两个判定的真假是否一致。
