---
oj: "luogu"
problem_id: "P3038"
title: "[USACO11DEC] Grass Planting G"
description: "重链剖分拆树上路径，Fenwick 差分支持道路覆盖加法和单边查询。"
difficulty: "普及+/提高-"
date: 2026-07-17 02:00
toc: true
tags: ["重链剖分", "树状数组", "树上差分", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3038
---

[[TOC]]

### 题意

给树上路径经过的每条道路加一，查询某条道路被覆盖次数。

### 思路

把每条父子边绑定到较深端点。HLD 将路径拆段；更新时不包含 LCA 对应点，只给子树方向的 DFS 区间加一。Fenwick 维护差分，单点前缀和就是该道路的覆盖次数。

### Python 知识

- `byte` 操作标记直接比较 `b'P'`/`b'Q'`，省去解码。
- `add(right + 1, -value)` 是区间差分的标准端点写法。
- HLD 循环中总是把深链端抬高，代码无需递归。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

每次操作 `O(log^2 n)`，空间 `O(n)`。

### 总结

道路问题先转成“子节点代表父边”，再复用点路径的 HLD 拆分。
