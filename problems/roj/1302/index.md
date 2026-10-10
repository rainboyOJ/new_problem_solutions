---
oj: "roj"
problem_id: "1302"
title: "股票买卖"
description: "把两笔交易用拆分点 i 解耦成前缀单笔最优 f(i) + 后缀单笔最优 g(i)，正反两遍扫描维护窗口最值，O(N) 取最大值。"
difficulty: "普及-"
date: 2026-09-30 03:55
updated: 2026-10-05 08:33
toc: true
tags: ["动态规划", "贪心", "线性扫描", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1302
---

[[TOC]]

## 题目描述

阿福已知股票未来 N 天的价格，希望买卖两次使利润最大，利润 = 卖出价 - 买入价；同一天可买卖多次，但第二次买入必须不早于第一次卖出。输入第一行是 T（数据组数），接下来每组一个 N 和 N 个价格（|p_i| ≤ 1e6，N ≤ 1e5）。每组输出一行表示最大利润。样例：第 1 组 `5 14 -2 4 9 3 17` 答案 28；第 2 组 `6 8 7 4 1 -2` 答案 2；第 3 组 `18 9 5 2` 答案 0。

## 思路

枚举拆分点 i，把两笔交易解耦成"前 i 天一笔最优" + "i 之后一笔最优"。前缀最优从左往右扫，维护最低买入价 low 与最大单笔利润 gain；后缀最优从右往左扫，对称维护最高卖出价 high。答案为 max(gain + g(i))，每组 O(N)。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)