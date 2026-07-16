---
oj: "luogu"
problem_id: "P5666"
title: "[CSP-S 2019] 树的重心"
description: "换根维护最大相邻组件，并沿最大子树链快速定位每个分割树的重心。"
difficulty: "省选/提高"
date: 2026-07-17 02:00
toc: true
tags: ["重心", "换根", "倍增", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5666
---

[[TOC]]

### 题意

删除原树每条边，分别求两个连通块的重心编号和，最后求总和。

### 思路

一个连通块的重心沿“最大相邻组件”方向向下走，直到下一步子树不足半数。预处理每个节点的最大子树链及其倍增跳表；换根遍历一条边时临时交换两侧的父子关系和子树大小，分别定位两侧重心后恢复现场。

### Python 知识

- `array("i")` 保存多层跳表和子树大小。
- 用显式栈保存待恢复状态，模拟递归换根，避免 30 万深度的 Python 调用栈。
- `rebuild` 只更新发生换根的节点，减少跳表维护开销。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

预处理 `O(n log n)`，每条边定位重心 `O(log n)`，空间 `O(n log n)`。

### 总结

重心判定只看最大组件；把“沿最大组件走”做成倍增，换根就能在线完成。
