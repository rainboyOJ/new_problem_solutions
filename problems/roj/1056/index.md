---
oj: "roj"
problem_id: "1056"
title: "点和正方形的关系"
description: "判断一点是否在以原点为中心、边与坐标轴平行的单位正方形内：检查 x 与 y 是否同时落在 [-1,1] 区间。"
difficulty: "入门"
date: 2026-09-29 16:34
updated: 2026-10-04 23:43
toc: true
tags:
  - 入门
  - 几何
  - 判断
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1056
---

[[TOC]]

## 题目描述

给定平面上一点 $(x,y)$，判断它是否在四个顶点为 $(-1,-1),(-1,1),(1,-1),(1,1)$ 的正方形内部或边界上。输入一行两个整数 $x,y$，输出 `yes` 或 `no`。

## 思路

正方形边与坐标轴平行，点在其内部或边界上的充要条件是 $-1 \le x \le 1$ 且 $-1 \le y \le 1$，直接做两次区间判断即可。

## 参考代码

@include-code(./main.cpp, cpp)
