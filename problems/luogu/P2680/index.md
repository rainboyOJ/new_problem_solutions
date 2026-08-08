---
oj: "luogu"
problem_id: "P2680"
title: "[NOIP 2015 提高组] 运输计划"
description: "二分最长运输时间，树上差分检查所有超标路径是否共用一条足够长的边。"
difficulty: "提高"
date: 2026-07-17 02:00
toc: true
tags: ["二分答案", "LCA", "树上差分", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2680
---

[[TOC]]

### 题意

只能把一条边改为耗时 0，求所有运输计划同时完成的最短时间。

### 思路

二分答案 `limit`。对长度超过 `limit` 的路径做边差分，若一条边被所有超标路径共同经过，就可以同时缩短它们；该边权还必须至少覆盖最长缺口。逆序汇总差分即可找到所有公共边。

### Python 知识

- 运输路径先保存端点和长度，`check` 中反复使用同一批数据。
- `array("q")` 保存距离和计划长度，`array("i")` 保存计数。
- 二分模板只保留 `feasible(mid)` 一个判定函数。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

预处理 `O((n+m)log n)`，每次判定 `O((n+m)log n)`，总复杂度 `O((n+m)log n log W)`。

### 总结

“改一条边”意味着所有超标路径必须有公共边，树上差分正好能检测这个交集。
