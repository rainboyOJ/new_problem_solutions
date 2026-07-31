---
oj: "shumeng"
problem_id: "CSP201503B"
title: "数字排序"
description: "统计每个数的出现次数，再按频次降序、数值升序排序输出。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["排序", "计数"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201503B
---

[[TOC]]

### 题意

统计输入中每个出现过的非负整数的次数，按次数降序、数值升序输出。

### 思路

先看逐个统计不同数值、反复选择当前最优条目的小数据基准：

@include-code(./brute.cpp, cpp)

数值范围只有 `0..1000`，用计数数组统计频率。把所有频率非零的数保存为 `(value, count)`；排序时先让较大 `count` 在前，若相等则让较小 `value` 在前。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

设不同数值数为 $k$，时间复杂度为 $O(n+k\log k)$，空间复杂度为 $O(1001+k)$。

### 总结

有重复元素的排序题先压缩为“值和频次”的条目，再把题意的主、次关键字完整写进比较器即可。
