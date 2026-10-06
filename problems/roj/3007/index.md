---
oj: "roj"
problem_id: "3007"
title: "递归实现组合型枚举"
description: "从 start..n 中递归选数，强制后选数大于先选数，行内升序即天然字典序。"
difficulty: "普及-"
date: 2026-10-01 09:32
updated: 2026-10-06 10:54
toc: true
tags:
  - "递归"
  - "搜索"
  - "组合枚举"
favorite: false
favorite_reason: ""
categories:
  - "算法竞赛进阶指南"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3007
---

[[TOC]]

## 题目描述

从 $1 \sim n$ 中选出 $m$ 个数，输出所有选择方案。每个方案内部 $m$ 个数升序、用一个空格隔开，方案之间按字典序从小到大，每行一个方案。输入一行 $n, m$（$0 \le m \le n$，$n+(n-m) \le 25$），$m=0$ 时输出一个空行。样例输入 `5 3`，样例输出为 `1 2 3 / 1 2 4 / 1 2 5 / 1 3 4 / 1 3 5 / 1 4 5 / 2 3 4 / 2 3 5 / 2 4 5 / 3 4 5`（斜杠分隔，实际每项占一行）。

## 思路

强制后选的数严格大于先选的数，每个组合就只有唯一一种升序写法，天然去掉重复。递归记录下一层可选的最小值 `start`，本层选的数最多取到 `n-remaining+1`，否则后面凑不够剩余个数。这样深搜的先序输出恰好就是题目要求的字典序。

## 参考代码

@include-code(./main.cpp, cpp)
