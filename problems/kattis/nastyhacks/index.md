---
oj: "kattis"
problem_id: "nastyhacks"
title: "Nasty Hacks"
description: "对每组数据比较 e-c 与 r 的大小，输出 advertise / do not advertise / does not matter。"
difficulty: "入门"
date: 2026-07-10 14:27
toc: true
tags: ["haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://open.kattis.com/problems/nastyhacks
---

[[TOC]]

### 题意

$n$ 组数据，每组 $r, e, c$。如果 $e - c > r$ → `advertise`，$e - c < r$ → `do not advertise`，否则 → `does not matter`。

### 思路

纯条件判断。重点是用 Haskell 处理多组数据：`getContents` 一次读完，
递归分组每 3 个数一组处理。

### 代码

@include-code(./main.hs, haskell)

### 复杂度

时间复杂度 $O(n)$，空间复杂度 $O(1)$。

### 总结

guard 三分支 + 模式匹配 `(r:e:c:xs)` 分组 + `mapM_ putStrLn` 输出。
