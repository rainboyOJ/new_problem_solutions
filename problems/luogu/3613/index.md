---
oj: "luogu"
problem_id: "P3613"
title: "【深基15.例2】寄包柜"
description: "为每个寄包柜维护一个稀疏字典，只保存实际写入过的格子编号和物品。"
difficulty: "普及-"
date: 2026-07-16 18:10
toc: true
tags: ["字典", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3613
---

[[TOC]]

### 题意

有很多寄包柜，每个柜子的格子上界未知。支持给 `(柜子,格子)` 写入物品编号，以及查询该位置的物品。

### 思路

格子编号可能很大，但操作总数只有 `10^5`，没有必要为每个柜子开到最大编号。

建立 `lockers[i]` 字典，只记录第 `i` 个柜子实际写入过的 `cell -> item`。写入和查询都直接使用两次下标，期望 $O(1)$ 完成。

### Python 知识

- `[dict() for _ in range(n+1)]` 为每个柜子创建独立字典；不能写 `[{}]*(n+1)`，否则所有柜子会共享同一个字典。
- `lockers[locker][cell]=item` 直接表达二维稀疏映射。
- 操作行长度不同，按行读取后解包比整份 token 更直观。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`dict` 键值映射。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：可变容器不能用乘法复制。

### 代码

@include-code(./main.py, python)


### 复杂度

每次操作期望 $O(1)$，总空间与不同的实际写入格子数成正比，最坏 $O(q)$。

### 总结

面对巨大但稀疏的二维编号空间，字典只存出现过的位置，通常比按最大下标开二维数组更自然。
