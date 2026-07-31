---
oj: "shumeng"
problem_id: "CSP201912A"
title: "报数"
description: "按自然数顺序模拟轮次，分别检查 7 的倍数和十进制数字 7。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "数位"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201912A
---

[[TOC]]

### 题意

四人从 1 开始轮流报数。7 的倍数或十进制表示含有数字 7 时跳过并记到当前玩家；累计报出 `n` 个有效数字后停止，输出各自跳过次数。

### 思路

逐个枚举自然数。编号 `number` 对应的玩家为 `(number-1)%4`；先判断它是否为 7 的倍数，再逐位判断是否含 7。跳过则增加当前玩家计数，否则增加有效报数个数，达到 `n` 后立即结束。

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设停止时枚举到的最大数字为 $T$，时间复杂度为 $O(T\log T)$，空间复杂度为 $O(1)$。本题数据很小，直接模拟即可。

### 总结

游戏结束条件只统计真正报出的数字，不统计跳过次数。轮次始终随自然数推进，不能因跳过而换回同一位玩家。
