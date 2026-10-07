---
oj: "roj"
problem_id: "3009"
title: "「Strange Towers of Hanoi 4」 奇怪的汉诺塔"
description: "枚举拆分点 k，先用四塔搬走 k 个最小盘，再用三塔搬剩下 n-k 个大盘，递推 f(n)=min(2f(k)+2^{n-k}-1)。"
difficulty: "普及"
date: 2026-10-01 09:57
updated: 2026-10-06 11:13
toc: true
tags: ["递归", "递推", "数学", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3009
---

[[TOC]]

## 题目描述

有 4 根柱子 A、B、C、D 和 $n$ 个尺寸互不相同的圆盘，初始全部按"上小下大"叠在柱子 A 上。
每次只能移动柱顶的一个圆盘，且只能放到空柱上或更大的圆盘上。
对于 $1 \leqslant n \leqslant 12$，输出把全部圆盘从 A 搬到 D 所需的最小移动次数，每个 $n$ 占一行。

**没有输入。**

## 思路

四塔没有唯一中转柱，需要枚举"最大盘移动前已经搬走多少个最小盘" $k$：
先用四塔把 $k$ 个最小盘搬到中转柱（$f(k)$ 步），再用三塔把剩下 $n-k$ 个大盘搬到 D（$2^{n-k}-1$ 步），
最后用四塔把 $k$ 个最小盘接到 D（又是 $f(k)$ 步），取最小值：
$f(n)=\min_{0\leqslant k<n}(2f(k)+2^{n-k}-1)$，$f(0)=0$。

## 参考代码

@include-code(./main.cpp, cpp)

