---
oj: "atcoder"
problem_id: "abc143_c"
title: "C - Slimes"
description: "使用 group 将连续相同字符分组，组数即为合并后剩余的史莱姆个数。"
difficulty: "入门"
date: 2026-07-10 21:22
toc: true
tags: ["haskell", "字符串"]
categories: []
pre: []
common: []
recommend: []
source: https://atcoder.jp/contests/abc143/tasks/abc143_c
---

[[TOC]]

### 题意

相邻相同字符合并，求合并后字符串长度。

### 思路

`group` 将连续相同字符分成一组，`length` 统计组数。

### 代码

@include-code(./main.hs, haskell)

### 复杂度

时间复杂度 $O(N)$，空间复杂度 $O(N)$。

### 总结

`group` 天然适合这种"相邻相同合并"的问题。
