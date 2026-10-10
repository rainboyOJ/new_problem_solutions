---
oj: "roj"
problem_id: "2024"
title: "usaco-2.1.4 健康的好斯坦奶牛"
description: "G≤15 时枚举饲料子集，按份数递增扫描，首个满足每种维生素总量均不低于需求的方案即最小解；子集总含量用最低位增量递推避免重复求和。"
difficulty: "普及-"
date: 2026-10-01 03:32
updated: 2026-10-06 09:46
toc: true
tags: ["枚举", "位运算", "记忆化", "USACO"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/2024
---

[[TOC]]

## 题目描述

给定 V 种维生素的需求量，以及 G 种饲料各自的维生素含量。选出若干种饲料，使每种维生素的摄入总量都不低于需求，且所选饲料种数最少。输出最小种数 P 与按升序排列的饲料编号。

## 思路

G≤15，共有 2^G 个饲料子集。按子集内饲料种数 k 从 1 递增枚举，第一个满足条件的子集即为最优解。用最低位拆分递推计算每个子集对每种维生素的总含量，避免重复求和。

## 参考代码

Python 版：

@include-code(./main.py, python)

C++ 版（同一算法）：

@include-code(./main.cpp, cpp)
