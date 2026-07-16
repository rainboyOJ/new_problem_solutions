---
oj: "luogu"
problem_id: "P4913"
title: "【深基16.例3】二叉树深度"
description: "用紧凑整数数组保存百万节点左右儿子，再用显式栈遍历并维护节点深度。"
difficulty: "普及-"
date: 2026-07-16 18:17
toc: true
tags: ["二叉树", "DFS", "栈", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4913
---

[[TOC]]

### 题意

给出最多一百万节点二叉树的左右儿子编号，根为 `1`，求最大层数。

### 思路

递归公式是 `depth(node)=1+max(depth(left),depth(right))`，但极端链形树会超过 Python 递归深度。

使用显式栈保存待访问节点和它的层数。每弹出一个节点就更新最大值，并把非空孩子以 `depth+1` 入栈。

### Python 知识

- `array('i')` 以紧凑 C 整数保存百万编号，避免普通 Python 整数列表的较大对象开销。
- 两个 `array` 分别保存节点和深度，最坏链形树也不会递归爆栈。
- `pop/append` 把数组当后进先出栈。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：Python 递归深度限制。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：显式状态遍历。

### 代码

@include-code(./main.py, python)

### 复杂度

每个节点访问一次，时间复杂度 $O(n)$；左右儿子和显式栈空间为 $O(n)$。

### 总结

百万节点时，算法仍是普通 DFS，但 Python 实现必须同时关注递归深度和整数对象内存，`array` 加显式栈更稳。
