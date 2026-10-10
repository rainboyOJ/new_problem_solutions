---
oj: "roj"
problem_id: "3529"
title: "[NOIP2004-普及] 花生采摘"
description: "按花生数从大到小模拟采摘顺序，每次检查采摘后能否按时跳回路边，贪心即可；复杂度 O(MN log MN)。"
difficulty: "普及-"
date: 2026-10-02 05:39
updated: 2026-10-07 13:50
toc: true
tags: ["贪心", "模拟", "排序"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "luogu"
    problem_id: "P2676"
    reason: "B 把 A 教的降序排序优先取最大复用为按花生数从大到小排序，再叠加时间模拟与返程判定"
common: []
recommend: []
source: https://roj.ac.cn/problem/3529
---

[[TOC]]

## 题目描述

$M \times N$ 花生田（$M,N \le 20$，花生数互不相同），多多每次跳到第一行某植株、四邻移动、采摘或跳回路边，各占 1 时间，总时间 $K$。采摘顺序固定为花生数从大到小，求限时内最多采多少花生。

## 思路

按花生数降序模拟：进田到首棵花 $r$ 步、植株间转移花曼哈顿距离、采摘花 1 步、返回花 $r$ 步；每采一株后检查剩余时间是否够返回，不够即停（后面花生更少，采了来不及返回不优）。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
