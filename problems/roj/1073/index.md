---
oj: "roj"
problem_id: "1073"
title: "救援"
description: "每个屋顶独立往返一次，累加航行时间与上下船时间，最后向上取整。"
difficulty: "入门"
date: 2026-01-12 11:20
updated: 2026-10-05 00:11
toc: true
tags: ["数学", "模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: "https://roj.ac.cn/problem/1073"
---

[[TOC]]

## 题目描述

救生船从原点（大本营）出发，营救若干屋顶上的人回到大本营。屋顶数 n 及每个屋顶的坐标 (x, y)、人数 c 由输入给出。船每次从原点出发，速度 50 米/分钟；到达屋顶救下所有人，每人上船 1 分钟，船原路返回，每人下船 0.5 分钟。假设原点与任意屋顶的连线不穿过其它屋顶。求完成所有救援并返回大本营的总时间，向上取整到分钟。

输入：第一行一个整数 n；接下来 n 行，每行两个实数 x、y 和一个整数 c。输出：救援总时间（向上取整到分钟）。

样例输入：`1\n30 40 3`；样例输出：`7`。

## 思路

每个屋顶必须独立往返一次，对第 i 个屋顶贡献 $2\cdot\frac{\sqrt{x_i^2+y_i^2}}{50}+1.5c_i$ 分钟，把所有屋顶累加后向上取整即可。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)