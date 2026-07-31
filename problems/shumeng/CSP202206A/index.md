---
oj: "shumeng"
problem_id: "CSP202206A"
title: "归一化处理"
description: "先计算平均值和方差，再按标准差对每个数据做平移缩放。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "数学", "浮点数"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP202206A
---

[[TOC]]

### 题意

将整数序列处理为均值为 0、方差为 1 的标准化浮点数序列。

### 思路

先累加求平均值，再按定义累加平方偏差求方差。标准差是方差平方根，每项输出 `(a[i]-average)/deviation`。

@include-code(./brute.cpp, cpp)

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

两次扫描数据，时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

归一化的分子负责消去均值，分母负责把方差缩放为 1；题目保证方差非零。
