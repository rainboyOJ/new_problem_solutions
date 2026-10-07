---
oj: "roj"
problem_id: "1090"
title: "含k个3的数"
description: "判定 m % 19 == 0 且十进制写法里数字 3 恰好出现 k 次：整除用取模，数位统计用逐位取个位再除以 10，两个条件逻辑与。"
difficulty: "入门"
date: 2026-09-29 18:17
updated: 2026-10-05 00:39
toc: true
tags: ["模拟", "数位", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1090
---

[[TOC]]

## 题目描述

输入 $m,k$（$1<m<100000$，$1<k<5$）：若 $m$ 能被 $19$ 整除，且十进制写法中数字 $3$ 恰好出现 $k$ 次，输出 `YES`，否则输出 `NO`。例如输入 `43833 3` 输出 `YES`。

## 思路

两个独立条件做逻辑与：`m % 19 == 0` 判整除，把 $m$ 反复取个位、除以 $10$ 统计数字 `3` 的个数。
注意是**恰好** $k$ 个（用 `==` 而不是 `>=`），且任一条件不满足都输出 `NO`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
