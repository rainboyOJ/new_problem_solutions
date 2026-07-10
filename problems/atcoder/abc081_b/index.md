---
oj: "atcoder"
problem_id: "abc081_b"
title: "ABC081B - Shift only"
description: "计算每个数二进制末尾 0 的个数（ν₂），取最小值即为所有数能同时除以 2 的最大次数。"
difficulty: "入门"
date: 2026-07-10 09:19
toc: true
tags: ["haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://atcoder.jp/contests/abs/tasks/abc081_b
---

[[TOC]]

### 题意

$N$ 个正整数，每次操作将所有偶数除以 2。求最大操作次数。

### 思路

对每个数计算能除以 2 的次数（即二进制末尾 0 的个数，$\nu_2$），
取最小值即为答案。

### 代码

@include-code(./main.hs, haskell)

另一种写法，使用 `getContents` 一次读完输入：

@include-code(./main2.hs, haskell)

### 复杂度

时间复杂度 $O(N \log A_{\max})$，空间复杂度 $O(1)$。

### 总结

$\nu_2$ 递归计算 + `minimum` 取最小值。
两种输入方式：`getLine` 逐行读或 `getContents` 一次读完。
