---
oj: "roj"
problem_id: "3515"
title: "[NOIP2002-普及] 过河卒"
description: "棋盘路径计数：标记马的 9 个控制点，滚动数组递推 f[j]=f[j]+f[j-1]，控制点清零。"
difficulty: "普及"
date: 2026-10-02 04:52
updated: 2026-10-06 12:40
toc: true
tags: []
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3515
---

[[TOC]]

## 题目描述

棋盘上 $A(0,0)$ 有一个卒，要走到 $B(n,m)$（$0 \leqslant n,m \leqslant 20$），每步只能向下或向右。棋盘上有对方的马 $C(h_x,h_y)$，马所在点及它按“马走日”跳一步能到的点都是控制点。求卒从 $A$ 到 $B$ 不经过任何控制点的路径条数。结果可能很大。

## 思路

标记马和马脚共 9 个控制点。设 $f(i,j)$ 为到 $(i,j)$ 的路径数，若 $(i,j)$ 是控制点则 $f(i,j)=0$，否则 $f(i,j)=f(i-1,j)+f(i,j-1)$。用一维滚动数组自上而下、自左而右递推，答案为 $f(n,m)$。

## 参考代码

@include-code(./main.cpp, cpp)
