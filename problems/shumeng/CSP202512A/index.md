---
oj: "shumeng"
problem_id: "CSP202512A"
title: "集合"
description: "同时比较集合本身与异或值是否相等，判断异或判等方法是否正确。"
difficulty: "未知"
date: 2026-07-31 16:22
toc: true
tags: ["集合", "位运算", "模拟", "哈希"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202512A
---

[[TOC]]

## 形式化题目

给定 $n$ 个非负整数 $a_1,\dots,a_n$。对每个询问给出两个集合 $S_i,T_i$（元素在 $[1,n]$ 内、内部严格递增），真实结论是 $S_i$ 与 $T_i$ 是否相等。小 C 用 $\bigoplus_{x \in S} a_x = \bigoplus_{x \in T} a_x$ 来判定。判断小 C 的判定结果是否与真实结论一致。

## 思路

读入集合时顺手计算异或值，最后把两个布尔值比较即可。

### 集合相等

输入保证集合内元素严格递增，因此两个集合用 `vector` 直接比较就能判断是否相等。

### 判定一致性

设 `same_set` 为真实相等结论，`same_xor` 为小 C 用异或得到的结论。只有当两者一致时小 C 的做法才正确：

$$
\text{correct} \iff same\_set = same\_xor
$$

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

设所有集合的元素总数为 $L$，时间复杂度 $O(L)$，空间复杂度 $O(L)$。

## 总结

异或相等只是小 C 的判定条件，不能替代集合相等的定义。本题的关键是分别得到两个结论再比较它们是否一致，而不是判断集合本身是否相等。