---
oj: "noi_openjudge"
problem_id: "ch0107-30"
title: "字符环"
description: "将两个字符环各自复制一遍，在双串上用最长公共子串 DP 求答案。"
difficulty: "普及/提高-"
date: 2026-07-30 23:01
toc: true
tags: ["动态规划", "字符串", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: http://noi.openjudge.cn/ch0107/30/
---

[[TOC]]

### 题意

两个字符串首尾相连形成字符环，求两环的最长连续公共字符串长度。

### 思路

把每个环复制为两倍长度，任意跨越原串末尾的连续片段都会变成双串中的普通子串。设 `dp[i][j]` 为两个双串分别以第 $i,j$ 个字符结尾的最长公共后缀，字符相等时从左上角状态加一，否则为零。

公共片段不能绕环超过一整圈，因此每个状态取不超过两原串较短长度的值。代码用两行数组滚动保存 DP。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

设两串长度为 $n,m$，双串 DP 时间复杂度为 $O(nm)$，滚动数组空间复杂度为 $O(m)$。

### 总结

环上的连续子串问题常先把环展开成双倍字符串，再套线性字符串算法。
