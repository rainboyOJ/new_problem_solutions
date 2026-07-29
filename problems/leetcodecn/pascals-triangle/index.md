---
oj: "leetcodecn"
problem_id: "pascals-triangle"
title: "杨辉三角"
description: "边界恒为 1，内部由上一行相邻两数相加，逐行递推生成。"
difficulty: "入门"
date: 2026-07-29 12:35
toc: true
tags: ["动态规划", "递推"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/pascals-triangle/
---

[[TOC]]

### 题意
生成杨辉三角的前 n 行。

### 思路
每行边界为 1，内部 `ans[i][j] = ans[i-1][j-1] + ans[i-1][j]`。逐行从上到下填充。

### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)

### 复杂度
- 时间复杂度：$O(n^2)$。
- 空间复杂度：$O(n^2)$，存储结果。

### 总结
杨辉三角是二维递推的基础：每行依赖上一行，边界初始化为 1，内部由相邻两个值相加。
