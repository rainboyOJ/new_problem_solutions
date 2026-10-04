---
oj: "roj"
problem_id: "1246"
title: "膨胀的木棍"
description: "弧长与弦长固定时圆心角唯一，二分求角后代弓形高公式输出偏移。"
difficulty: "普及-"
date: 2026-09-30 01:32
updated: 2026-10-05 06:54
toc: true
tags: ["数学", "二分", "计算几何", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1246
---

[[TOC]]

## 题目描述

木棍原长 $L$，温度变化 $n$，热膨胀系数 $C$。受热后长度变为 $L'=(1+nC)L$（保证 $L'\le 1.5L$），木棍弯成圆弧，弦仍为原位置线段（长 $L$）。输出弧中点到弦的垂直距离，保留三位小数。

输入：三个非负实数 $L,n,C$。输出：木棍中心偏移距离。

样例输入：`1000 100 0.0001`，样例输出：`61.329`。

## 思路

由 $r=L'/\theta$ 与弦长公式 $L=2r\sin(\theta/2)$ 消去半径，得方程 $2L'\sin(\theta/2)/\theta=L$。左端在 $(0,\pi]$ 严格递减，实数二分求圆心角 $\theta$，再代回 $h=r(1-\cos(\theta/2))$ 输出弓形高。

## 参考代码

@include-code(./main.cpp, cpp)
