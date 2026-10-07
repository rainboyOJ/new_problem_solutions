---
oj: "roj"
problem_id: "1072"
title: "鸡尾酒疗法"
description: "算出基准有效率 x，每组改进疗法有效率 y 与之作差，按 y-x 与 5% 的严格大小三分类输出 better/worse/same，注意分子分母顺序与严格不等号。"
difficulty: "入门"
date: 2026-09-29 17:19
updated: 2026-10-05 00:13
toc: true
tags: ["入门", "数学", "浮点数", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1072
---

[[TOC]]

## 题目描述

给定 $n$ 组临床实验数据，第一组是鸡尾酒疗法的总病例数与有效病例数，其余为改进疗法。若改进疗法有效率 $y$ 与基准有效率 $x$ 的差 $y-x > 5\%$ 输出 `better`；$x-y > 5\%$ 输出 `worse`；否则输出 `same`。

数据范围：$1 < n \leqslant 20$，总病例数不超过 $10000$。

## 思路

先读入基准组的总病例数与有效病例数，算出 $x$；然后对每组改进疗法计算 $y=$ 有效 / 总，按 $y-x$ 与 $\pm 0.05$ 的严格大小关系三分类输出即可。注意严格大于才输出 `better` / `worse`，恰好等于 $5\%$ 时归为 `same`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
