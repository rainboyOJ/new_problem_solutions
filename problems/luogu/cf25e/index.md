---
oj: "luogu"
problem_id: "CF25E"
title: "Test"
description: "Luogu 无法提交 Codeforces 原题，解析已迁移至 codeforces/25E，本页仅保留入口。"
difficulty: "普及+/提高"
date: 2026-07-16 19:57
toc: true
tags: ["KMP", "最短公共超串", "全排列"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/CF25E
---

[[TOC]]

### 题意

本题是 Codeforces 原题，Luogu 侧无法提交 CF 题目，完整解析（题意、思路、代码）已迁移至：

- [[problem: codeforces,25E]] · [CF25E Test 题解](https://codeforces.com/problemset/problem/25/E)

### 思路

枚举 $3!$ 种拼接顺序，每次把新串尽量重叠地接到当前串后面；重叠长度用 KMP 前缀函数求出（对 `right + '#' + left` 求 pi，最后一位即重叠长度）。完整教学解析见 codeforces 页。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

排列数为常数，每次合并线性，总时间 $O(|s_1|+|s_2|+|s_3|)$，辅助空间同阶。

### 总结

完整解析（含 Python 版本与思考过程）已迁移至 [[problem: codeforces,25E]]。
