---
oj: "roj"
problem_id: "1005"
title: "地球人口承载力估计"
description: "两式相减消去初始资源，得年增长量即最大可持续人口 (y*b-x*a)/(b-a)；按标准程序用整型除法向零截断输出两位小数。"
difficulty: "入门"
date: 2026-09-29 13:11
updated: 2026-10-04 22:15
toc: true
tags: ["数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1005
---

[[TOC]]

## 题目描述

地球上的新生资源按恒定速度增长，现有资源加新生资源可供 $x$ 亿人生活 $a$ 年，或供 $y$ 亿人生活 $b$ 年，求资源永不枯竭时最多能养活多少亿人（保留两位小数）。输入一行四个正整数 $x,a,y,b$（$x>y,\ a<b$），输出实数 $z$；样例输入 `110 90 90 210`，样例输出 `75.00`。

## 思路

设初始资源为 $S$、每年新增 $r$，由 $S+ar=xa$ 与 $S+br=yb$ 相减消去 $S$，得 $r=(yb-xa)/(b-a)$；可持续发展要求每年消耗不超过新增，故最大人口就是 $r$，按标准程序的整型除法向零截断输出两位小数。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
