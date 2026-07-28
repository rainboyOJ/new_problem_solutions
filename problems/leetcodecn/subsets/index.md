---
oj: "leetcodecn"
problem_id: "subsets"
title: "子集"
difficulty: "中等"
tags: [回溯, DFS, 位运算, cpp, python]
description: "每个元素选/不选的 DFS，或枚举二进制 mask。"
---
[[TOC]]
### 题意
返回数组所有子集。
### 思路
DFS 选/不选分支，到叶子时收集结果。也可用枚举 mask。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(n·2^n)。
### 总结
选/不选 DFS 是子集枚举的标准递归写法。
