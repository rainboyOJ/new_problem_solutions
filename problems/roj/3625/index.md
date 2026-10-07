---
oj: "roj"
problem_id: "3625"
title: "[noip2015-普及] 扫雷游戏"
description: "读入雷区后，对每个非地雷格枚举 8 个方向统计相邻地雷数，地雷格原样输出 `*`。"
difficulty: "普及-"
date: 2026-10-02 11:07
updated: 2026-10-06 15:26
toc: true
tags: ["网格", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3625
---

[[TOC]]

## 题目描述

$n$ 行 $m$ 列雷区中，`*` 表示地雷格，`?` 表示非地雷格。对每个非地雷格输出其周围 8 个方向上的地雷格数量，地雷格仍输出 `*`。$1 \le n, m \le 100$。

## 思路

对每个非地雷格枚举 8 个方向，先判越界再判是否地雷，累加即得该格数字。时间复杂度 $O(nm)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
