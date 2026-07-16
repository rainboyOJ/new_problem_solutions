---
oj: "luogu"
problem_id: "P1955"
title: "[NOI2015] 程序自动分析"
description: "先用字典并查集合并所有相等约束，再检查每条不等约束的两端是否落在同一集合。"
difficulty: "普及+/提高"
date: 2026-07-16 17:48
toc: true
tags: ["并查集", "离散化", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1955
---

[[TOC]]

### 题意

判断若干形如 $x_i=x_j$、$x_i\ne x_j$ 的约束能否同时成立。

### 思路

相等关系具有传递性，先把所有相等约束放进并查集。随后逐条检查不等约束：若两端已经属于同一集合，就产生矛盾。

变量编号可达 $10^9$，但实际只出现 $O(n)$ 个。Python 可以直接用 `dict` 以原编号为键，相当于把离散化和并查集存储合在一起。

### Python 知识

- 字典推导式从约束中收集实际出现的变量，参见 `/home/rainboy/mycode/hugo-blog/content/program_language/python/dict_usage.md`。
- `all(...)` 会在第一个矛盾处短路，不会继续做无用检查。
- `dict.fromkeys(parent, 1)` 为所有根初始化集合大小。

### 代码

@include-code(./main.py, python)

### 复杂度

设约束数为 $n$，时间复杂度 $O(n\alpha(n))$，空间复杂度 $O(n)$。

### 总结

先处理“必须相等”，再验证“必须不等”，即可把约束满足转成并查集判冲突。
