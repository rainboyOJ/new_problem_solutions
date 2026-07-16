---
oj: "luogu"
problem_id: "P3916"
title: "图的遍历"
description: "反向建图并按编号从大到小搜索，首次访问时写入该点可达的最大编号。"
difficulty: "普及-"
date: 2026-07-16 18:42
toc: true
tags: ["图论", "反图", "DFS", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3916
---

[[TOC]]

### 题意

对有向图中的每个点 `v`，求从 `v` 出发能够到达的最大编号。

### 思路

从每个点各做一次搜索会达到 $O(n(n+m))$。把问题反过来：原图中 `v` 能到达 `x`，等价于反图中 `x` 能到达 `v`。

按 `n,n-1,...,1` 枚举候选最大编号 `largest`，从它在反图中搜索。凡是首次访问到的点，其答案就是 `largest`：

- 它在原图中可以到达 `largest`；
- 更大的候选已经先处理过却没有访问到它，所以它不可能到达更大编号。

一个点写入答案后不再入栈，因此所有搜索合计只访问每个点、每条反向边常数次。

### Python 知识

- `reverse_graph[v].append(u)` 直接建立反边 `v -> u`。
- `range(n,0,-1)` 表达从大到小的处理顺序。
- `answer[node]==0` 同时表示“尚未访问”，无需单独的 `visited`。
- 显式 `stack` 避免最长链导致递归层数超限。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：显式栈图遍历。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：递归深度注意点。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n+m)$，反图、答案和栈的空间复杂度 $O(n+m)$。

### 总结

“每个起点能到达的最大目标”可以反转成“每个目标能覆盖哪些起点”。再按目标从大到小染色，就能一次确定所有答案。
