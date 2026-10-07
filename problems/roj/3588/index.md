---
oj: "roj"
problem_id: "3588"
title: "铺地毯"
description: "从最后铺的地毯往前枚举，第一个覆盖查询点的矩形就是答案。"
difficulty: "普及-"
date: 2026-10-02 09:27
updated: 2026-10-06 14:42
toc: true
tags: ["模拟"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3588
---

[[TOC]]

## 题目描述

平面上按 $1\sim n$ 顺序铺上 $n$ 张与坐标轴平行的矩形地毯，后铺的覆盖在先铺的上面。第 $i$ 张地毯左下角为 $(a_i,b_i)$，$x$ 方向长 $g_i$、$y$ 方向长 $k_i$（含边界）。给定查询点 $(x,y)$，输出覆盖该点的最上面那张地毯编号；若没有则输出 $-1$。

## 思路

查询点只有一个，倒序检查每张地毯，第一个满足 $a_i\le x\le a_i+g_i$ 且 $b_i\le y\le b_i+k_i$ 的即为答案；全不满足则输出 $-1$。

## 参考代码

@include-code(./main.cpp, cpp)
