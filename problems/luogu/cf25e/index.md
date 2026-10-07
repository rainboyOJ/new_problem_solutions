---
oj: "luogu"
problem_id: "CF25E"
title: "Test"
description: "Luogu 无法提交 Codeforces 原题，解析已迁移至 codeforces/25E，本页仅保留入口。"
difficulty: "普及+/提高"
date: 2026-07-16 19:57
updated: 2026-10-07 12:15
toc: true
tags: ["KMP", "最短公共超串", "全排列"]
categories: []
pre:
  - oj: "roj"
    problem_id: "1458"
    reason: "B 的双串重叠步直接复用 A 教的「前后缀相等即 border、pi 给出最长 border」这一判定：用分隔符把 A 的后缀与 B 的前缀关系压成单串，再取 pi 末位即最大重叠；A 特有的 pi 链枚举全部 border 未被使用，故只算模板级复用，B 另叠加 3! 全排列与贪心合并。"
  - oj: "roj"
    problem_id: "1467"
    reason: "B 的双串重叠计算正是复用 A 教的「border 即前后缀相等长度」这一判定，靠分隔符把两串前后缀关系压成单串 border 后仍用同一 pi 求法，只是再叠加全排列枚举拼接顺序"
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
