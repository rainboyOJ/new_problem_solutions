---
oj: "roj"
problem_id: "2095"
title: "矩形牛棚"
description: "逐行维护悬垂高度直方图，用单调栈在每行 O(C) 求最大矩形。"
difficulty: "普及"
date: 2026-10-01 08:45
updated: 2026-10-06 10:44
toc: true
tags: ["悬线法", "单调栈", "直方图"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2095
---

[[TOC]]

## 题目描述

给定 $R \times C$ 的网格（$R, C \leqslant 3000$），其中有 $P$（$P \leqslant 30000$）个损坏格子。求不含损坏格子的最大子矩形面积。

## 思路

逐行维护每列向上连续完好的高度 $h[c]$，每行用单调栈在 $O(C)$ 内求直方图最大矩形。总复杂度 $O(RC)$。注意官方数据因历史缺陷只登记第 1 个损坏点，实现需复刻该行为。

## 参考代码

@include-code(./main.cpp, cpp)
