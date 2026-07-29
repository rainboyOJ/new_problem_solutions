---
oj: "leetcodecn"
problem_id: "generate-parentheses"
title: "括号生成"
description: "回溯生成括号组合，open < n 放左括号，close < open 放右括号，保证前缀合法。"
difficulty: "普及+/提高"
date: 2026-07-29 11:25
toc: true
tags: ["回溯", "枚举", "递归", "字符串"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/generate-parentheses/
---

[[TOC]]

### 题意

给定整数 $n$，生成所有由 $n$ 对括号组成的合法括号组合。

合法括号组合要求：任意前缀中左括号数量 $\geqslant$ 右括号数量，且最终两者相等。

### 思路

最直接的思路是枚举所有长度为 $2n$ 的括号序列，逐一检查合法性：

@include-code(./brute.cpp, cpp)

这个暴力先生成完整序列再到叶子节点检查合法性。它在小数据上可靠，但分支数为 $2^{2n}$，对 $n \geqslant 8$ 就会超时。

优化的关键是剪枝：不等到序列完成后再检查，而是在每一步就保证前缀合法。

- `open < n` 时可以放左括号——左括号总数不能超过 $n$。
- `close < open` 时可以放右括号——任意前缀中右括号不能多于左括号。

这两个条件保证每一步之后前缀仍然合法，因此最终到达叶子时一定是一个合法组合，且所有合法组合都会被访问到。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(C_n)$，其中 $C_n = \frac{1}{n+1}\binom{2n}{n}$ 是 Catalan 数，即合法组合的数量。每个组合需要 $2n$ 步构建。
- 空间复杂度：$O(n)$，递归栈深度为 $2n$。

### 总结

括号生成是 Catalan 数的经典应用。关键剪枝条件 `close < open` 保证任意前缀中右括号不超过左括号，等价于只保留搜索树中合法的分支。这与"从左到右扫描括号序列"的合法性判定完全一致。
