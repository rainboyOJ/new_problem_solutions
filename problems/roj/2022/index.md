---
oj: "roj"
problem_id: "2022"
title: "usaco-2.1.2 顺序的分数"
description: "枚举全部分数，用 gcd 约成最简后去重，再按分数值升序排序输出，即法里序列的构造。"
difficulty: "入门"
date: 2026-10-01 03:19
updated: 2026-10-06 09:40
toc: true
tags: ["入门", "数学", "排序", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2022
---

[[TOC]]

## 题目描述

输入自然数 $N$（$1 \le N \le 160$），按从小到大输出所有分母不超过 $N$ 的既约真分数，每行一个。

样例输入 `5`，输出 `0/1`、`1/5`、`1/4`、`1/3`、`2/5`、`1/2`、`3/5`、`2/3`、`3/4`、`4/5`、`1/1` 各占一行。

## 思路

枚举分母 $b$ 和分子 $a$，用 $\gcd$ 约分后丢进有序集合去重，就得到全部最简分数。排序必须按分数值比较（交叉相乘 $ad$ 与 $cb$），不能对分子分母元组做字典序比较。分子从 $0$ 开始枚举才能让 `0/1` 排在开头。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
