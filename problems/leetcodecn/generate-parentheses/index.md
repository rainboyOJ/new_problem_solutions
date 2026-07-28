---
oj: "leetcodecn"
problem_id: "generate-parentheses"
title: "括号生成"
difficulty: "中等"
tags: [回溯, DFS, 字符串, cpp, python]
description: "open < n 放左括号，close < open 放右括号，保证前缀合法。"
---
[[TOC]]
### 题意
生成 n 对括号的所有合法组合。
### 思路
DFS 保证两个条件：已放置左括号不超过 n，右括号不超过左括号。
### 代码
@include-code(./main.cpp, cpp)
@include-code(./main.py, python)
### 复杂度
O(4^n / sqrt(n))。
### 总结
Catalan 数的搜索树剪枝——只保留前缀合法的分支。
