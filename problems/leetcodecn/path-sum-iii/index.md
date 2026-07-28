---
oj: "leetcodecn"
problem_id: "path-sum-iii"
title: "路径总和 III"
difficulty: "中等"
tags: [二叉树, 前缀和, 回溯, cpp, python]
description: "DFS 维护根到当前的前缀和，查 prefix - target 次数，回溯撤销。"
---
[[TOC]]
### 题意
路径必须向下，统计节点和为 targetSum 的路径数量（路径可从任意祖先开始到任意子孙）。
### 思路
DFS 维护根到当前节点的前缀和，查历史 prefix - target 的出现次数。回溯时撤销当前前缀和。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
时间 O(n)，空间 O(n)。
### 总结
树上前缀和 + 哈希表是"两数之和"的树上推广。
