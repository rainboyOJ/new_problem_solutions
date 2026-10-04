---
oj: "roj"
problem_id: "1062"
title: "最高的分数"
description: "用打擂台变量记录当前最高分，初值取 0 以兼顾成绩非负和 n=0 的空序列。"
difficulty: "入门"
date: 2026-09-29 16:46
updated: 2026-10-04 23:49
toc: true
tags: ["入门", "输入输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1062
---

[[TOC]]

## 题目描述

孙老师想知道《计算概论》期中考试的最高分。输入第一行是人数 $n$（$0 \leqslant n < 100$），第二行是 $n$ 个 $0$ 到 $100$ 之间的整数成绩，相邻两数用单个空格隔开；输出一个整数，即最高的成绩，$n=0$ 时输出 `0`。
样例输入：`5` / `85 78 90 99 60`；样例输出：`99`。

## 思路

用一个变量打擂台记录当前最高分，初值取 $0$，从左到右读入每个成绩，比擂台值大就更新它，扫完输出擂台值。成绩非负，所以初值 $0$ 不会被任何真实成绩超过，$n=0$ 的空序列也自然得到 $0$。时间复杂度 $O(n)$，额外空间 $O(1)$。

## 参考代码

@include-code(./main.cpp, cpp)
