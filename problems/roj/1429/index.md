---
oj: "roj"
problem_id: "1429"
title: "「一本通 1.1 练习 3」线段"
description: "按右端点排序后贪心选取互不重合的线段，O(n log n) 求解区间调度。"
difficulty: "普及-"
date: 2026-09-30 09:54
updated: 2026-10-05 23:32
toc: true
tags:
  - 贪心
  - 排序
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1429
---

[[TOC]]

## 题目描述
数轴上有 $n$ 条线段，第 $i$ 条由整数端点 $a_i, b_i$ 表示。要求选出尽量大的子集，使得任意两条线段没有重合部分（端点相接不算重合），输出最大条数。输入第一行为 $n$，接下来 $n$ 行每行两个整数 $a_i, b_i$。样例输入 `3 / 0 2 / 2 4 / 1 3`，输出 `2`。

## 思路
把所有线段按右端点从小到大排序；维护已选最后一条线段的右端点 `last_right`，若当前线段左端点 $\geqslant$ `last_right` 就选中并更新，否则跳过。

## 参考代码
@include-code(./main.cpp, cpp)
