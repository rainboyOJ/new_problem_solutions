---
oj: "kattis"
problem_id: "r2"
title: "R2"
description: "根据平均数公式 S=(R1+R2)/2，代入已知的 R1 和 S 计算 R2=2S-R1。"
difficulty: "入门"
date: 2026-07-09 21:46
toc: true
tags: ["haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://open.kattis.com/problems/r2
---

[[TOC]]

### 题意

输入两个整数 $R_1$ 和 $S$，输出 $R_2$。
其中 $S = (R_1 + R_2) / 2$。

### 思路

移项得 $R_2 = 2S - R_1$，直接计算。

重点是用 Haskell 读取多个整数：
`words` 按空格分割，`map (read :: String -> Int)` 转为整数，
类型注解是必须的，否则 GHC 无法推断 `read` 的目标类型。

### 代码

@include-code(./main.hs, haskell)

### 复杂度

时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

Haskell 中读取多个整数并做算术运算的标准模式：
`getLine` → `words` → `map read :: [Int]` → 计算 → `print`。
