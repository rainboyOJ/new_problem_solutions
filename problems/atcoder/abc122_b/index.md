---
oj: "atcoder"
problem_id: "abc122_b"
title: "B - ATCoder"
description: "扫描字符串，维护当前连续 ACGT 字符的长度，遇非法字符归零，取过程中最大值。"
difficulty: "入门"
date: 2026-07-10 15:33
toc: true
tags: ["haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://atcoder.jp/contests/abc122/tasks/abc122_b
---

[[TOC]]

### 题意

求字符串中最长的、仅由 `A` `C` `G` `T` 构成的连续子串的长度。

### 思路

扫描字符串，维护当前连续 ACGT 长度，遇非 ACGT 归零，过程中取最大值。

### 代码

@include-code(./main.hs, haskell)

另一种写法，更接近 DP / C++ 思维：

@include-code(./main-1.hs, haskell)

### 复杂度

时间复杂度 $O(|S|)$，空间复杂度 $O(1)$。

### 总结

scanl 版本简洁，递归版本直观。核心都是"遇 ACGT 累加，否则归零"。
