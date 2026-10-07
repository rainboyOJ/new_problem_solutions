---
oj: "roj"
problem_id: "1059"
title: "求平均年龄"
description: "读入 n 后一遍循环累加年龄求和，用实数除法求平均值并按 %.2f 输出两位小数。"
difficulty: "入门"
date: 2026-09-29 16:45
updated: 2026-10-04 23:49
toc: true
tags: ["入门", "循环", "格式化输出", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1059
---

[[TOC]]

## 题目描述

班上有学生若干名，给出每名学生的年龄（整数），求班上所有学生的平均年龄，保留到小数点后两位。

输入：第一行一个整数 $n$（$1 \le n \le 100$）表示学生人数；其后 $n$ 行每行一个整数，表示每个学生的年龄（$15 \sim 25$）。

输出：一行一个浮点数，为平均年龄，保留到小数点后两位。样例：输入 `2 / 18 / 17`（第一行是人数），输出 `17.50`——末尾的 `0` 也要输出。

## 思路

把 $n$ 个年龄读进来一遍循环累加求和，再除以 $n$ 就是答案。除法要用实数除法（累加和用 `double` 存），否则会退化成整除得到 `17` 而不是 `17.50`；输出用 `%.2f` 固定两位小数，会自动补齐末尾的 `0`。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
