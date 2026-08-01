---
oj: "shumeng"
problem_id: "CSP202509A"
title: "蒙特卡洛"
description: "统计给定坐标中满足 x^2+y^2<=a^2 的点数，再按 4m/n 计算圆周率估计值。"
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
source: https://oj.shumeng.tech/p/CSP202509A
difficulty: "未知"
---

[[TOC]]

### 题意

在边长为 `2a` 的正方形中给出 `n` 个点，统计落在半径为 `a` 的圆内的点数 `m`，输出 `4m/n`。

### 思路

点 `(x,y)` 在圆内当且仅当 `x*x+y*y<=a*a`。逐点统计后输出 `4.0*m/n`，保留若干位小数即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度 `O(n)`，空间复杂度 `O(1)`。

### 总结

直接使用圆的判定式模拟即可，边界点要计入圆内。
