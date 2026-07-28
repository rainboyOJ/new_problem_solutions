---
oj: "leetcodecn"
problem_id: "permutations"
title: "全排列"
difficulty: "中等"
tags: [回溯, DFS, 递归, cpp, python]
description: "每层选择未使用元素，swap 写法不重不漏。"
---
[[TOC]]
### 题意
返回数组所有全排列。
### 思路
DFS 回溯，swap 写法将当前数与后面每个数交换，递归后恢复。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(n·n!)，空间 O(n)。
### 总结
swap 写法省去 visited 数组，是排列生成的标准实现。
