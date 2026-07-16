---
oj: "luogu"
problem_id: "P4092"
title: "[HEOI2016/TJOI2016] 树"
description: "HLD 后在线段树维护已标记 DFS 序最大值，逐链向上找到最近祖先。"
difficulty: "提高"
date: 2026-07-17 02:00
toc: true
tags: ["重链剖分", "线段树", "祖先查询", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4092
---

[[TOC]]

### 题意

标记节点，查询某节点到根路径上最近的已标记祖先。

### 思路

在 DFS 序位置保存“已标记则为 dfn，否则 0”。查询从节点所在链向上，线段树求 `[top[x], x]` 的最大 dfn；当前链找到即为最近祖先，否则跳到父链。根初始标记。

### Python 知识

- 点标记是幂等的，叶子直接写入 dfn 后向上更新最大值。
- 迭代线段树区间最大值避免频繁递归。
- `inverse[dfn]` 把线段树位置恢复为节点编号。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

每次查询 `O(log^2 n)`，每次标记 `O(log n)`，空间 `O(n)`。

### 总结

“最近祖先”在同一重链上就是 DFS 序最大的已标记位置。
