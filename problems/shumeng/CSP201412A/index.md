---
oj: "shumeng"
problem_id: "CSP201412A"
title: "门禁系统"
description: "按记录顺序维护每个读者编号的出现次数，并输出当前记录的累计次数。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["计数", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201412A
---

[[TOC]]

### 题意

给定读者编号记录，输出每条记录中的读者是此前第几次出现。

### 思路

先看直接扫描此前记录的暴力：

@include-code(./brute.cpp, cpp)

按记录从左到右处理，`count[x]` 表示读者 `x` 已经出现的次数。读到 `x` 时先执行 `count[x]++`，再输出它；这样输出值恰好是当前记录的出现次序。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每条记录只做一次数组自增，时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

顺序统计题的状态只需要保留“之前发生过什么”。把编号映射到计数数组，当前记录先更新再输出即可。
