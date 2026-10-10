---
oj: "roj"
problem_id: "1395"
title: "烦人的幻灯片(slides)"
description: "用位掩码记录每个数字点可能落入的幻灯片，反复确定候选唯一的数字并删去该字母，若最终不能唯一对应则输出 None。"
difficulty: "普及-"
date: 2026-09-30 08:21
updated: 2026-10-07 13:50
toc: true
tags: ["拓扑排序", "二分图匹配", "位运算", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRink: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1351"
    reason: "A 教的 Kahn「把入度为 0（已无未处理前驱）的点入队作起点」正是 B 的拓扑消元起点「把 |cand(i)|=1 的数字放进队列」；B 的 main.py 复用同一队列删点骨架，只把「入度归零」判据换成「候选由位掩码删到只剩一个」，再叠加二分图唯一完美匹配判定与位运算实现。"
common: []
recommend: []
source: https://roj.ac.cn/problem/1395
---

[[TOC]]

## 题目描述

给定 $n$ 个按顺序编号为 $A,B,\dots$ 的矩形幻灯片，以及 $n$ 个按顺序编号为 $1,2,\dots$ 的数字点。点不会落在所有矩形之外。求数字与字母之间是否存在**唯一**的双射；若存在，按字母升序输出每对 `字母 数字`，否则输出 `None`。

输入第一行为 $n$，接下来 $n$ 行每行四个整数 `xmin xmax ymin ymax` 表示幻灯片坐标，再接下来 $n$ 行每行两个整数 $x,y$ 表示数字点坐标。

## 思路

对每个数字点枚举所有矩形，得到它可能落入的幻灯片集合（含边界）。用位掩码存储候选集合， repeatedly 将候选集合只剩一个字母的数字确定下来，并把该字母从其它数字的候选中删去；若出现同一字母被两个数字抢占、或消元后仍有字母未确定，则输出 `None`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
