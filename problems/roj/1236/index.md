---
oj: "roj"
problem_id: "1236"
title: "区间合并"
description: "按左端点排序后维护已并入区间的最大右端点 reach，一旦某个左端点越过 reach 就出现断口、输出 no，否则答案为最小左端点与最终 reach。"
difficulty: "普及-"
date: 2026-09-30 01:08
updated: 2026-10-05 06:11
toc: true
tags: ["贪心", "排序", "区间合并", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1236
---

[[TOC]]

## 题目描述

给定 $n$ 个闭区间 $[a_i; b_i]$（$3 \le n \le 50000$，$1 \le a_i \le b_i \le 10000$），任意两个相交或相邻的闭区间可以合并。判断能否最终合并成一个闭区间：能则输出该区间的左右端点，否则输出 `no`。

输入第一行 $n$，之后 $n$ 行每行两个整数 $a_i, b_i$。样例输入 `5`、`5 6`、`1 5`、`10 10`、`6 9`、`8 10`，输出 `1 10`。

## 思路

按左端点升序排序，只维护已并入区间的最大右端点 `reach`。逐行比较：若当前左端点大于 `reach`，中间出现谁都跨不过的断口，立即输出 `no`，否则 `reach` 取自身与当前右端点的较大值。全程无断口时并集就是 `[最小左端点, reach]`；闭区间相邻也算合并，所以断口判定用严格大于 `>`。

## 参考代码

@include-code(./main.cpp, cpp)
