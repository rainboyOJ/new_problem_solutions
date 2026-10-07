---
oj: "roj"
problem_id: "3616"
title: "[NOIP2014]螺旋矩阵"
description: "按圈层分解螺旋矩阵：先算目标格所在圈之前所有完整圈的格子数，再按上右下左四段累加圈内偏移，O(n) 无需建表即可定位任意格子的值。"
difficulty: "普及"
date: 2026-10-02 10:41
updated: 2026-10-06 15:14
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3616
---

[[TOC]]

## 题目描述

给定 $n$，按“前进/右转”规则生成 $n \times n$ 螺旋矩阵（从左上角开始，依次填入 $1\dots n^2$）。输入 $n,i,j$，输出第 $i$ 行第 $j$ 列的数。

数据范围：$1 \le n \le 30000$。

## 思路

螺旋路线由外到内是一圈圈同心方环，每圈按“上→右→下→左”走完。先由 $\min(i-1,j-1,n-i,n-j)$ 定位目标格所在圈层 $k$，再求和前 $k$ 层完整圈的格子数，最后按四条边判断段内偏移，直接算出答案，$O(n)$ 时间、$O(1)$ 空间。

## 参考代码

@include-code(./main.cpp, cpp)
