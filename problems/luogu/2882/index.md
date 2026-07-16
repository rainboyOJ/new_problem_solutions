---
oj: "luogu"
problem_id: "P2882"
title: "[USACO07MAR] Face The Right Way G"
description: "枚举翻转长度 K，用异或差分在线维护当前翻转奇偶并贪心确定每个起点是否必须操作。"
difficulty: "普及/提高-"
date: 2026-07-16 17:48
toc: true
tags: ["枚举", "差分", "贪心", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2882
---

[[TOC]]

### 题意

选择一个固定长度 $K$，每次翻转连续 $K$ 头牛，求能让所有牛朝前的最少操作数；先最小化操作数，再最小化 $K$。

### 思路

枚举 $K$。从左到右处理时，若当前位置在已有翻转作用后仍朝后，那么以后从更右边开始的区间已无法覆盖它，所以必须立刻从这里翻转。

`ends[i]` 记录在位置 `i` 结束的翻转奇偶性，扫描时用异或维护当前位置受多少次翻转。若必须翻转但剩余长度不足 $K$，当前 $K$ 不可行。

### Python 知识

- `bytearray` 是紧凑的 0/1 数组，适合保存异或差分。
- `^` 同时用于布尔异或和整数异或，直接表达“原方向与翻转奇偶不同”。
- `min(..., key=lambda result: result[1])` 按操作数取最优；生成器顺序保证并列时先得到更小的 $K$。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(N^2)$，空间复杂度 $O(N)$。

### 总结

固定窗口后的左端决策是被迫的，差分异或让一次窗口翻转只需常数时间维护。
