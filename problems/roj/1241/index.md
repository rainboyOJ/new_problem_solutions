---
oj: "roj"
problem_id: "1241"
title: "二分法求函数的零点"
description: "五次多项式无求根公式，用题面给出的异号端点与区间内唯一根作前提，实数二分 40 轮后输出中点。"
difficulty: "普及-"
date: 2026-09-30 01:19
updated: 2026-10-05 06:30
toc: true
tags: ["数学", "二分", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1241
---

[[TOC]]

## 题目描述

有函数 $f(x)=x^5-15x^4+85x^3-225x^2+274x-121$。已知 $f(1.5)>0$、$f(2.4)<0$，且方程 $f(x)=0$ 在区间 $[1.5,2.4]$ 内有且只有一个根，请用二分法求出该根。

输入：无。输出：该根，四舍五入到小数点后 $6$ 位（精确值为 $1.8490158267\ldots$）。

## 思路

五次方程没有求根公式，但题面给出的"端点异号 + 区间内唯一根"正是二分法的全部前提：全程保持 $f(left)>0>f(right)$，每轮取中点只看 $f(mid)$ 的符号决定丢弃哪一半区间，根永远不会丢。停止条件直接写在区间宽度上（`right-left > 1e-12`），每轮减半，40 轮后区间宽约 $8\times10^{-13}$，取中点输出即可保证 $6$ 位小数正确；求值用秦九韶形式减少浮点误差。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
