---
oj: "roj"
problem_id: "1422"
title: "活动安排"
description: "按活动结束时间升序排序后贪心选取互不冲突的区间，求最大兼容活动数。"
difficulty: "入门"
date: 2026-09-30 09:26
updated: 2026-10-05 23:14
toc: true
tags:
  - "贪心"
  - "排序"
favorite: false
favorite_reason: ""
categories:
  - "一本通在线评测"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1422
---

[[TOC]]

## 题目描述

有 $n$ 个活动要独占同一资源，活动 $i$ 占用时间区间 $[s_i, f_i)$，两个活动区间不重叠即可同时安排，求最多能安排的活动数。输入第一行 $n\ (n \le 1000)$，接下来 $n$ 行每行两个整数 $s_i, f_i$；输出最多互相兼容的活动个数。

样例输入：$n=4$，活动为 $(1,3),(4,6),(2,5),(1,7)$；样例输出：`2`。

## 思路

按结束时间升序排序后依次扫描，若当前活动的开始时间不早于已选活动的结束时间，就选它并更新结束时间；结束越早留给后续的空间越大，因此该贪心最优。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
