---
oj: "leetcodecn"
problem_id: "letter-combinations-of-a-phone-number"
title: "电话号码的字母组合"
description: "回溯枚举每个数字对应的字母选择，递归层数对应数字位置，每层分支数由按键映射决定。"
difficulty: "普及/提高-"
date: 2026-07-29 11:15
toc: true
tags: ["回溯", "枚举", "递归"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
---

[[TOC]]

### 题意

给定仅含数字 `2-9` 的字符串 `digits`，每个数字对应一组字母（如 `2→abc`、`7→pqrs`、`9→wxyz`），返回所有可能的字母组合。空输入返回空列表。

### 思路

每层递归处理一个数字，枚举该数字映射的所有字母，选一个后递归到下一层。这棵递归树的深度等于 `digits` 的长度，每层分支数由对应按键决定（`7` 和 `9` 各 4 个字母，其余 3 个）。

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

朴素解与最终做法完全相同——本题的回溯枚举本身就是最优方案，因为必须输出所有组合，总方案数 $4^k$ 无法省略。brute.cpp 与 main.cpp 的区别仅在代码组织形式。

关键实现：`cur` 在递归前 `push_back`，递归后 `pop_back`，保证每个位置的选择、递归、恢复三步对称；`dfs(i)` 表示正在决定第 `i` 位数字对应的字母。

空输入直接返回空列表，不需要进入递归。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(4^k \cdot k)$，其中 $k = \text{len(digits)}$。每个组合需要 $k$ 步构建，总组合数最多 $4^k$（每个数字最多 4 个字母）。
- 空间复杂度：$O(k)$，递归栈深度为 $k$。

### 总结

本题是典型的回溯枚举：递归树的每一层对应一个决策点（选择哪个字母），所有合法路径的终点就是答案。关键是理解 `选择 → 递归 → 撤销` 的三步对称结构。
