---
oj: "roj"
problem_id: "1122"
title: "计算鞍点"
description: "每行最大值唯一，因此逐行取一个候选位置，再用预处理的列最小值验证即可，无解输出 not found。"
difficulty: "入门"
date: 2026-09-29 19:50
updated: 2026-10-05 02:31
toc: true
tags: ["入门", "数组", "最值", "python"]
favorite: false
favorite_reason: ""
categories: []
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/1122
---

[[TOC]]

## 题目描述

输入格式：一个 $5 \times 5$ 的整数矩阵，共 5 行 5 列，且每行只有一个最大值、每列只有一个最小值。

输出格式：求鞍点——它既是所在行的最大值、又是所在列的最小值；存在则输出行号、列号和值，不存在则输出 `not found`。样例输入为 `11 3 5 6 9` / `12 4 7 8 10` / `10 5 6 9 11` / `8 6 4 7 2` / `15 10 11 20 25` 五行，样例输出为 `4 1 8`（第 4 行第 1 列的 8）。

## 思路

鞍点必然是所在行的最大值，而每行最大值唯一，所以每行只有一个候选位置，不必检查全部 25 个格子。先预处理出每列的最小值，再逐行找出最大值的列号，验证该值是否等于对应列最小值，复杂度 $O(5 \times 5)$。

## 参考代码

@include-code(./main.cpp, cpp)
