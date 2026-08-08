---
oj: "luogu"
problem_id: "P5660"
title: "[CSP-J 2019] 数字游戏"
description: "顺序扫描长度为 8 的 01 串，遇到字符 '1' 就把计数加一。"
difficulty: "入门"
date: 2026-06-19 09:37
toc: true
tags: ["模拟", "字符串"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5660
---

[[TOC]]

### 题意

给出一个长度固定为 `8` 的 01 字符串。

要求统计其中一共有多少个字符 `'1'`。

### 思路

这题就是最直接的遍历统计。

从左到右扫一遍字符串，遇到 `'1'` 就把答案加一。

最直观的写法如下：

@include-code(./brute.cpp, cpp)

因为字符串长度只有 `8`，甚至不需要考虑任何优化。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(n)$
- 空间复杂度：$O(1)$

这里 `n = 8`，所以本质上就是常数时间。

### 总结

题目本身没有隐藏条件，就是简单数一数字符串中 `'1'` 的个数。
