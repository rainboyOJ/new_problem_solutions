---
oj: "leetcodecn"
problem_id: "word-search"
title: "单词搜索"
description: "DFS 搜索路径，进入格子后标记已访问防止复用，递归后恢复现场，四方向扩展匹配下一个字符。"
difficulty: "普及+/提高"
date: 2026-07-29 11:30
toc: true
tags: ["回溯", "搜索", "DFS", "网格"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://leetcode.cn/problems/word-search/
---

[[TOC]]

### 题意

在 `m x n` 字符网格中判断是否存在一条路径，按相邻（水平/垂直）单元格依次拼出给定单词 `word`。同一个单元格不能重复使用。

### 思路

最直接的思路是从每个格子出发尝试 DFS 匹配单词：

@include-code(./brute.cpp, cpp)

brute.cpp 用独立的 `vis` 数组标记已访问格子，逻辑与 main.cpp 相同（本题 DFS 本身就是最优方案，因为必须逐字符尝试所有路径）。

关键实现要点：

- 进入格子后立即标记（`vis[i][j] = true` 或 `board[i][j] = '#'`），防止路径中重复使用同一格子。
- 递归返回后必须恢复现场（`vis[i][j] = false` 或 `board[i][j] = tmp`），否则后续从其他起点出发的搜索会看到被污染的网格。
- 匹配失败的条件要全部检查：越界、已访问、字符不匹配。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：最坏 $O(m \cdot n \cdot 4^k)$，其中 $k = \text{len(word)}$。每个起点最多 4 方向扩展 $k$ 层。
- 空间复杂度：$O(k)$，递归栈深度为单词长度。

### 总结

网格路径搜索的核心是"标记→递归→恢复"三步必须成对。本题用临时修改网格值或 `vis` 数组来标记访问状态，递归返回时恢复原值，保证后续搜索不受影响。
