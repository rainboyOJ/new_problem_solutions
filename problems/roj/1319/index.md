---
oj: "roj"
problem_id: "1319"
title: "【例6.1】排队接水"
description: "接水时间短的人排前面即最优：交换论证排除相邻逆序对，按时间升序排序后总等待为 Σ(n-1-pos)·t，除以 n 输出两位小数。"
difficulty: "入门"
date: 2026-09-30 04:53
updated: 2026-10-05 09:18
toc: true
tags: ["入门", "贪心", "排序", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1319
---

[[TOC]]

## 题目描述

$n$ 个人在一个水龙头前排队接水，第 $i$ 个人的接水时间为 $T_i$，求使 $n$ 人平均等待时间最小的排队顺序。

输入第一行 $n$（$1 \le n \le 1000$），第二行 $T_1 \dots T_n$（空格分隔）。输出两行：第一行为 $1..n$ 的一种排队顺序，第二行为对应的平均等待时间（保留两位小数）。样例：输入 `10 / 56 12 1 99 1000 234 33 55 99 812`，输出 `3 2 7 8 1 4 9 6 10 5` 与 `291.90`。

## 思路

按接水时间升序排序即可得最优；交换论证说明任何相邻逆序对交换都让总等待严格减少，所以最优解就是升序。排好后第 pos 位（从 0 起）的权为 n-1-pos，总等待=Σ (n-1-pos)·t[pos]，除以 n 即平均等待。

## 参考代码

@include-code(./main.cpp, cpp)
