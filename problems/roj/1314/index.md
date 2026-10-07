---
oj: "roj"
problem_id: "1314"
title: "【例3.6】过河卒(Noip2002)"
description: "标记马的 9 个控制点后用网格路径计数 DP 统计从 A 到 B 的方案数。"
difficulty: "普及-"
date: 2026-09-30 04:41
updated: 2026-10-05 09:11
toc: true
tags: ["普及-", "动态规划", "网格", "递推", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre:
  - oj: "roj"
    problem_id: "1190"
    reason: "一维线性递引入重复子问题与计数 DP 的基本形态"
common: []
recommend: []
source: https://roj.ac.cn/problem/1314
---

[[TOC]]

## 题目描述

棋盘左上角 A(0,0) 有一只卒，只能向右或向下走到 B(n,m)（$n,m \leqslant 20$）。棋盘上另有一个马 C(x,y)，马所在的点和 8 个“日字”跳跃点共 9 个控制点不能经过。求从 A 到 B 的路径条数。

## 思路

按到达每个格子的最后一步分类：只能从上方或左方走来。设 $f[i][j]$ 为到达 $(i,j)$ 的方案数，非控制点则 $f[i][j]=f[i-1][j]+f[i][j-1]$，控制点则为 0。按行从左到右递推即可，答案需用 64 位整数。

## 参考代码

@include-code(./main.cpp, cpp)
