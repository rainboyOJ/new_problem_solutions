---
oj: "roj"
problem_id: "1240"
title: "查找最接近的元素"
description: "在非降序列上二分定位插入位置，比较夹住询问值的左右相邻元素，距离相等时取较小值，单次询问 O(log n)。"
difficulty: "普及-"
date: 2026-09-30 01:19
updated: 2026-10-05 06:25
toc: true
tags: ["二分", "数组", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1240
---

[[TOC]]

## 题目描述

在一个非降序列中查找与给定值 $x$ 最接近的元素，若有多个值满足条件则输出最小的一个。输入第一行 $n$（$1\le n\le 10^5$），第二行 $n$ 个非降序整数，第三行 $m$（$1\le m\le 10^4$）为询问个数，随后 $m$ 行每行一个询问值（所有元素与询问值均在 $0$ 到 $10^9$ 之间）；输出 $m$ 行，依次为每个询问的答案。样例输入第一行 `3`、第二行 `2 5 8`、第三行 `2`、随后两行 `10` 与 `5`，输出两行 `8` 与 `5`。

## 思路

序列非降，对询问 $x$ 二分出第一个 $\ge x$ 的位置 $r$ 后，最近元素一定落在 $a_{r-1}$ 与 $a_r$ 之间。只需比较这两个候选到 $x$ 的距离，距离相等时取较小的 $a_{r-1}$，正好满足题面「有多个值输出最小的一个」。单次询问 $O(\log n)$，总计 $O(n + m\log n)$。

## 参考代码

@include-code(./main.cpp, cpp)
