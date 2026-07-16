---
oj: "luogu"
problem_id: "P2324"
title: "[SCOI2005] 骑士精神"
description: "以错位非空棋子数为估价函数，在深度 15 内做 IDA*。"
difficulty: "提高+/省选-"
date: 2026-07-16 20:10
toc: true
tags: ["IDA*", "启发式搜索", "棋盘", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2324
---

[[TOC]]

### 题意

空位与一个国际象棋骑士步位置交换，求 15 步内到目标棋盘的最少步数。

### 思路

逐步增加深度上限做 IDA*。一次移动只搬动一个非空棋子，所以当前与目标不同的非空棋子数，是到目标至少还需的步数；若它超过剩余深度立即剪枝。

搜索还禁止立刻把空位换回，并记录同一轮中某状态已拥有的最大剩余深度，避免以更差条件重复搜索。

### Python 知识

- 棋盘保存在 `bytearray` 中，递归时交换后再换回，避免大量复制。
- `seen.get(state, -1) >= remaining` 是带搜索资源的状态支配剪枝。
- 目标和输入使用 `bytes`，`*` 的字节值为 42。

### 代码

@include-code(./main.py, python)

### 复杂度

最坏指数级，深度最多 15；空间为当前 DFS 路径和一轮判重表。

### 总结

IDA* 的关键是可证明不高估的下界；错位棋子数简单但已经足够有效。
