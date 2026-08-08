---
oj: "luogu"
problem_id: "P1438"
title: "无聊的数列"
description: "用两个 Fenwick 树维护等差数列区间加，并在单点查询时恢复当前值。"
difficulty: "普及+/提高"
date: 2026-07-16 23:59
toc: true
tags: ["树状数组", "差分", "等差数列", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1438
---

[[TOC]]

### 题意

给 `[l,r]` 加上首项为 `K`、公差为 `D` 的等差数列，并查询某个位置的值。

### 思路

第 `i` 项增加 `K + (i-l)D = (K-lD) + iD`。因此只要分别维护“常数项系数”和“位置系数”的差分数组即可：在 `[l,r]` 的差分端点加上这两个系数，单点查询时取两个 Fenwick 前缀和。

### Python 知识

- `array("q")` 保存整数差分，避免 Python 对象列表的额外空间。
- `iter(map(int, read().split()))` 让所有整数共享一次解析流程。
- 生成器表达式 `(next(data) for _ in range(4))` 适合读取变长操作。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

每次修改和查询均为 `O(log n)`，空间 `O(n)`。

### 总结

等差数列看似需要修改很多位置，拆成“常数项 + 下标系数”后仍然只是两个差分端点。
