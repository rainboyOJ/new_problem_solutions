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
---

[[TOC]]

## 形式化题目

在边长为 $2a$ 的正方形中随机生成 $n$ 个点。统计落在以原点为圆心、半径为 $a$ 的圆内（含边界）的点数 $m$，输出 $\dfrac{4m}{n}$。

## 思路

点 $(x,y)$ 在圆内当且仅当 $x^2 + y^2 \le a^2$，逐点判断并计数即可。

### 边界处理

圆内"含边界"，判断用 $\le$。由于浮点计算可能有微小误差，比较时在 $a^2$ 上加上一个小量（如 `1e-12`），确保恰好落在圆上的点被计入。

### 输出格式

题目按绝对误差小于 $0.0001$ 评分，保留 6 位小数输出最稳妥。

## 代码

@include-code(./main.cpp, cpp)

## 复杂度

需要扫描全部 $n$ 个点，时间复杂度 $O(n)$，空间复杂度 $O(1)$。

## 总结

本题是蒙特卡洛模拟的简化版，核心就是圆的判定式 $x^2+y^2 \le a^2$。注意边界点计入圆内，以及用 `double` 计算时的小量容差。