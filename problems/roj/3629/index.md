---
oj: "roj"
problem_id: "3629"
title: "[noip2015-提高] 信息传递"
description: "把信息传递对象看成出度为 1 的有向图，答案即最短环长度，用三色标记线性遍历。"
difficulty: "普及-"
date: 2026-10-02 11:31
updated: 2026-10-06 15:32
toc: true
tags: ["图论", "基环树", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3629
---

[[TOC]]

## 题目描述

$n$ 个同学每人有一个固定信息传递对象 $T_i$（$T_i \leq n$，$T_i \neq i$）。每轮所有人同时把已知的生日告诉自己的 $T_i$。当有人从别人口中听到自己的生日时游戏结束，求进行了多少轮。

## 思路

每人只有一条出边，图由若干链指向环组成。不在环上的点的生日永远不会回到自己，环上的点会在环长轮后第一次听到自己的生日。因此答案就是所有环长度的最小值。用三色标记（未访问/当前路径/已归档）沿出边走，每个点只走一次，遇到当前路径上的点即得到一个环。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
