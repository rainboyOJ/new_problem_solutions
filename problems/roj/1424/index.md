---
oj: "roj"
problem_id: "1424"
title: "「一本通 1.1 例 3」喷水装置"
description: "圆覆盖转中心线有效区间后，按左端点排序并反复选左端不超过当前覆盖点、右端最远的区间贪心覆盖。"
difficulty: "普及-"
date: 2026-09-30 09:29
updated: 2026-10-05 23:23
toc: true
tags:
  - 贪心
  - 排序
  - 区间覆盖
favorite: false
favorite_reason: ""
categories:
  - 贪心
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1424
---

[[TOC]]

## 题目描述

长 $L$、宽 $W$ 的草坪中心线上装 $n$ 个喷头，给出每个喷头离左端的位置和浇灌半径。求同时浇灌整块草坪最少需打开几个喷头；无法浇灌输出 $-1$。$n \leqslant 15000$，多组数据。

## 思路

把能覆盖到草坪上下两边的喷头按勾股定理转成中心线上的有效区间 $[pos-reach,\ pos+reach]$，半径不足半宽的喷头直接丢弃。区间按左端点排序后，从 $0$ 出发反复在所有左端不超过当前覆盖点的区间里选右端最远者，直到覆盖 $L$ 或无法推进，贪心选中的区间数即答案。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
