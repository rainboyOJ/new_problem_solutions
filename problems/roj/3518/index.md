---
oj: "roj"
problem_id: "3518"
title: "[NOIP2002-提高] 自由落体"
description: "把接球判定化为滑动区间取并：球在车顶到地面的时间窗内，车身扫过的连续区间取并，数出其中的整数球位。"
difficulty: "普及"
date: 2026-10-02 04:59
updated: 2026-10-06 12:41
toc: true
tags: ["数学", "浮点数", "模拟", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3518
---
[[TOC]]
## 题目描述
天花板高 $H$，其下 $n$ 个体积不计的小球位于 $0,1,\dots,n-1$；地面上有长 $L$、高 $K$ 的小车，车头距原点 $S_1$，以速度 $V$ 朝原点前进。球与车同时运动，球做自由落体 $d=5t^2$（$g=10$），与车距离 $\le 0.0001$ 即算被接住，落到地面后不再能被接住，求能接住多少球。
输入 $H,S_1,V,L,K,n$（$1 \le H,S_1,V,L,K,n \le 100000$，除 $n$ 外均可为小数）。样例：输入 `5.0 9.0 5.0 2.5 1.8 5`，输出 `1`。
## 思路
球只在高度落在车顶到地面这段时间内可能被接住，即 $t \in [t_{roof}, t_g]$，其中 $t_g=\sqrt{H/5}$、$t_{roof}=\sqrt{\max(H-K,0)/5}$。这段时间里车头 $e(t)=S_1-Vt$ 连续左移，车身区间扫过的并集仍是连续一段 $[S_1-Vt_g-\varepsilon,\ S_1-Vt_{roof}+L+\varepsilon]$，故只需数落在这段内、编号 $0 \sim n-1$ 的整数个数。注意 $K \ge H$ 时 $t_{roof}=0$，取整前留一点浮点护栏。
## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
