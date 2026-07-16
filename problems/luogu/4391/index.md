---
oj: "luogu"
problem_id: "P4391"
title: "[BalticOI 2009] Radio Transmission 无线传输"
description: "用整个字符串的最长 border 求能够生成接收片段的最短信号周期。"
difficulty: "普及/提高-"
date: 2026-07-16 19:57
toc: true
tags: ["KMP", "周期", "border", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4391
---

[[TOC]]

### 题意

给出一段可能从周期信号中截取的字符串，求原信号最短可能长度。

### 思路

若整个长度 `n` 的字符串有长度为 `border` 的最长前后缀相同，那么前后两份相同部分错开了 `n-border` 个字符，这个错位量就是一个可行周期。

最长 border 产生最短错位，所以答案是：

```text
n - prefix[n - 1]
```

这里不要求周期整除 `n`，因为接收到的只可能是无限周期信号的一段。

### Python 知识

- `n, word = buffer.read().split()` 可直接解包两项输入。
- `array("i", [0]) * n` 紧凑建立定长前缀数组。
- Python 的 `bytes` 和普通字符串一样支持 KMP 所需的下标比较。

### 代码

@include-code(./main.py, python)

### 复杂度

时间和空间均为 $O(n)$。

### 总结

周期与 border 是同一件事的两种描述：`周期长度 = 前缀长度 - border 长度`。
