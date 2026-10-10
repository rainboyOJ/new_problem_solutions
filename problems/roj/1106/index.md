---
oj: "roj"
problem_id: "1106"
title: "年龄与疾病"
description: "三个右端点 18/35/60 把年龄切成四段，年龄严格越过几个端点就属于第几段，再按段统计百分比。"
difficulty: "入门"
date: 2026-09-29 19:05
updated: 2026-10-05 01:15
toc: true
tags: ["入门", "计数", "格式化输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1106
---

[[TOC]]

## 题目描述

某医院要整理诊断记录，按 0-18、19-35、36-60、61 以上（含 61）四个年龄段，统计各段患病人数占总患病人数的百分比。
输入两行：第一行为病人数 $n$（$0 < n \leqslant 100$），第二行为 $n$ 个病人的年龄。
输出四行，依次为四个年龄段的人数占比，写成百分比形式并保留两位小数。
样例输入第一行 `10`、第二行 `1 11 21 31 41 51 61 71 81 91`，输出 `20.00%`、`20.00%`、`20.00%`、`40.00%`。

## 思路

三个右端点 $18/35/60$ 把年龄切成四段：年龄严格大于几个右端点，就属于第几段，据此累加四个计数器。
统计完后逐段输出 `该段人数 * 100 / n`，保留两位小数并加 `%`，复杂度 $O(n)$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
