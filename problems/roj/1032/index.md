---
oj: "roj"
problem_id: "1032"
title: "大象喝水查"
description: "20 升水先换算成 20000 cm³，用圆柱体积 πr²h 一次除法向上取整即得最少桶数。"
difficulty: "入门"
date: 2026-09-29 15:03
updated: 2026-10-04 23:00
toc: true
tags: ["数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1032
---

[[TOC]]

## 题目描述

大象要喝 $20$ 升水解渴，只有一个深 $h$ 厘米、底面半径 $r$ 厘米的小圆桶。每桶装满，问至少要喝多少桶。

输入一行两个整数 $h, r$，输出一个整数表示最少桶数。

样例输入：`23 11`，样例输出：`3`。

## 思路

$20$ 升 = $20000\ \text{cm}^3$，每桶容积 $V = \pi r^2 h$，答案即 $\lceil 20000 / V \rceil$。注意必须向上取整，向下取整会不够喝。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
