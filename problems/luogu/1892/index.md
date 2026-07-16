---
oj: "luogu"
problem_id: "P1892"
title: "[BalticOI 2003] 团伙 (Day 2)"
description: "用 2N 并查集同时维护朋友与对立面，统计真实人物中被迫互为朋友的集合数。"
difficulty: "普及+/提高"
date: 2026-07-16 18:26
toc: true
tags: ["并查集", "种类并查集", "关系传递", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1892
---

[[TOC]]

### 题意

`n` 个人之间有朋友 `F` 或敌人 `E` 关系。朋友的朋友是朋友，敌人的敌人也是朋友。朋友必须在同一团体，求最多能有多少个团体。

### 思路

普通并查集只能表达“相同”，还需要为每个人建立一个“敌对侧”节点：

- `x` 表示人物 `x`；
- `x+n` 表示与 `x` 对立的一侧。

对于朋友关系 `F a b`，合并 `a,b`，同时合并 `a+n,b+n`。

对于敌人关系 `E a b`，合并 `a,b+n`，同时合并 `a+n,b`。

这样两个人若拥有同一个敌人，就会通过对立侧落到同一集合，自动得到“敌人的敌人是朋友”。最后只统计真实人物 `1..n` 的不同代表元。每个代表元是一群被规则强制为朋友的人；让每群单独成团即可取得最大团体数。

### Python 知识

- `range(2*n+1)` 一次建立人物节点和对应的对立节点。
- `{find(person) for person in range(1,n+1)}` 用集合推导式完成“压缩代表元并去重”。
- 关系 token 保留为 `bytes`，直接与 `b"F"` 比较。
- 循环版路径压缩不会受 Python 递归深度影响。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：集合推导式与去重。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：迭代替代深递归。

### 代码

@include-code(./main.py, python)

### 复杂度

每条关系执行常数次并查集操作，时间复杂度 $O((n+m)\alpha(n))$，空间复杂度 $O(n)$。

### 总结

2N 并查集把“相同”和“对立”都变成普通合并操作。关键是对每个真实人物建立一个对应的对立面节点。
