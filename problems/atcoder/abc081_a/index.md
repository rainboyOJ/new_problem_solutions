---
oj: "atcoder"
problem_id: "abc081_a"
title: "ABC081A - Placing Marbles"
description: "统计三位字符串中字符 1 的个数，作为需要放置弹珠的格子数。"
difficulty: "入门"
date: 2026-07-09 20:33
toc: true
tags: ["字符串", "haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://atcoder.jp/contests/abs/tasks/abc081_a
---

[[TOC]]

### 题意

输入一个长度为 3 的字符串，每个字符为 `0` 或 `1`。
统计其中 `1` 的个数并输出。

例如 `101` 中有 2 个 `1`，输出 `2`。

### 思路

本题不涉及算法优化，重点是练习 Haskell 的基础 IO 和字符串操作。

核心流程：

1. 用 `getLine` 读入一行字符串
2. 用 `filter (== '1')` 过滤出所有 `'1'` 字符
3. 用 `length` 统计个数
4. 用 `print` 输出结果

### 代码

@include-code(./main.hs, haskell)

### 复杂度

时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

Haskell 中处理简单输入输出和字符串过滤的基本模式：
`getLine` 读入，`filter` 筛选，`length` 计数，`print` 输出。
