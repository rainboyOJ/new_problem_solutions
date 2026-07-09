---
oj: "kattis"
problem_id: "hello"
title: "Hello World!"
description: "直接使用 putStrLn 输出固定字符串 Hello World!。"
difficulty: "入门"
date: 2026-07-09 21:31
toc: true
tags: ["haskell"]
categories: []
pre: []
common: []
recommend: []
source: https://open.kattis.com/problems/hello
---

[[TOC]]

### 题意

没有输入。输出一行 `Hello World!`。

### 思路

本题不涉及算法，目标是学习 Haskell 的基础输出。

Haskell 中使用 `putStrLn` 输出一行字符串。

### 代码

@include-code(./main.hs, haskell)

### 复杂度

时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

`putStrLn` 是 Haskell 中最基本的输出函数，等价于其他语言的 `println`。
