---
oj: "roj"
problem_id: "1227"
title: "Ride to Office"
description: "Charley 0 时刻从起点出发，途中遇到更快的人就跟上去；答案就是 t>=0 的同行人中 t + ceil(16200/v) 的最小值。"
difficulty: "入门"
date: 2026-09-30 00:42
updated: 2026-10-05 05:57
toc: true
tags: ["思维", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1227
---
[[TOC]]

## 题目描述

起点到终点相距 4500 米。Charley 在时刻 0 从起点出发，必须与同行人同速骑行；遇到速度更快的人就跟上去。给出 n 个同行人的速度 v（km/h）与出发时间 t（t<0 表示提早出发），多组数据直到 n=0。求 Charley 到达终点的时间，结果向上取整。样例：第一组输入 `4\n20 0\n25 -155\n27 190\n30 240` 输出 `780`；第二组输入 `2\n21 0\n22 34` 输出 `771`。

## 思路

观察一：Charley 的到达时刻恰等于某个 t≥0 的同行人独自骑到的时刻，所以问题坍缩成"挑出最小 t+ceil(16200/v)"；其中 16200=4500×3.6 是把 km/h 换算成 m/s 后的乘子。观察二：t<0 的同行人 Charley 出发时已在前方，永远追不上，直接跳过。

## 参考代码

@include-code(./main.cpp, cpp)