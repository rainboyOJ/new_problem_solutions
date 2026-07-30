---
oj: "noi_openjudge"
problem_id: "ch0108-16"
title: "矩阵剪刀石头布"
description: "每天基于旧矩阵检查四邻格是否存在克制者，再同步更新剪刀石头布领地。"
difficulty: "普及-"
date: 2026-07-30 23:01
toc: true
tags: ["矩阵", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0108/16/
---

[[TOC]]

### 题意

在二维剪刀石头布中，若四邻格存在能战胜当前生命的种类，当前格在当天结束后被占领。

### 思路

字典记录每种生命的克制者。每一天复制旧网格，判断每个格的四邻格是否存在克制者，所有判断结束后同步换成新网格。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

<!-- 原解析未提供复杂度说明时，后续人工补充。 -->

### 总结

<!-- 保留原解析内容，不额外编造结论。 -->
## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设天数为 $d$，时间复杂度为 $O(drc)$，额外空间复杂度为 $O(rc)$。

### 总结

同一时刻发生的格子变化必须同步更新。
