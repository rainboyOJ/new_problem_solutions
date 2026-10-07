---
oj: "roj"
problem_id: "1169"
title: "大整数减法"
description: "高精度竖式减法：从末位逐位相减，维护单个借位 0/1，越界位按 0 处理。"
difficulty: "普及-"
date: 2026-09-29 22:14
updated: 2026-10-05 04:11
toc: true
tags: ["高精度", "模拟", "字符串"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1169
---

[[TOC]]

## 题目描述

求两个大的正整数相减的差。

输入共 2 行，第 1 行是被减数 $a$，第 2 行是减数 $b$。每个大整数不超过 200 位，没有多余前导零。输出一行，即所求的差。

## 思路

从最低位开始逐位相减，用单个变量保存借位（只可能是 0 或 1）。
两数长度不同，较短的一侧越界位按 0 参与运算，避免补零对齐；本位不够减时向高位借 1，再输出当前位。时间复杂度 $O(L)$，$L \leq 200$。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
