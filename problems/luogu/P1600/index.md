---
oj: "luogu"
problem_id: "P1600"
title: "[NOIP 2016 提高组] 天天爱跑步"
description: "把路径观察条件改写为深度键值，在树形 DFS 中用事件计数统计经过人数。"
difficulty: "提高"
date: 2026-07-17 02:00
toc: true
tags: ["LCA", "树形差分", "事件计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1600
---

[[TOC]]

### 题意

每个玩家沿最短路径跑步，每个节点在指定时刻观察，统计每个观察员能看到的玩家数。

### 思路

路径拆成 `s -> lca` 和 `lca -> t` 两段。第一段满足 `depth[s] = depth[u] + w[u]`；第二段满足 `depth[s]-2*depth[lca] = w[u]-depth[u]`。把两类键作为事件挂到端点，在显式后序 DFS 中用桶计数，进入子树前后的差就是该节点贡献。

### Python 知识

- `defaultdict(list)` 按节点收集稀疏事件，避免创建大量空事件容器。
- `array("i")` 保存祖先、计数和答案；显式栈模拟后序 DFS。
- 事件元组 `(key, delta)` 直接表达加一和减一。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

预处理 `O(n log n)`，路径事件和 DFS 总计 `O((n+m)log n)`。

### 总结

跑步时刻条件本质是深度等式；把等式变成键值后，树形子树计数就能批量完成。
