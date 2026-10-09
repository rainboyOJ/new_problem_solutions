---
oj: "luogu"
problem_id: "P3916"
title: "图的遍历"
description: "反向建图并按编号从大到小搜索，首次访问时写入该点可达的最大编号。"
difficulty: "普及-"
date: 2026-07-16 18:42
updated: 2026-10-09 20:01
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

@include-code(./main.cpp, cpp)


### STL 写法

上面的 `main.cpp` 用链式前向星（`head` / `to` / `nxt` 三个数组）手工存图。C++ 里还有更省事的做法：`vector<vector<int>>` 邻接表，一句 `rg[v].push_back(u)` 就是给点 `v` 挂上一条反向边，不用自己管下标和指针，代价只是多一层 vector 的间接访问。

染色过程本来写成递归最直观，但 $n$ 可以到 $10^5$，图退化成一条长链时递归层数太深会爆栈，所以这里用 `stack<int>` 显式模拟：弹出点 `u`，没被染过就写上当前的 `marker`，再把没染色的邻居压栈。外层依旧按编号从大到小枚举，每个点只会被染色一次，复杂度不变。

对应的 cppbook 章节：[vector：能改变长度的数组](https://cppbook.roj.ac.cn/stl/sequence-containers/vector/)、[stack：最后放入，最先取出](https://cppbook.roj.ac.cn/stl/container-adapters/stack/)

@include-code(./main-stl.cpp, cpp)


### 复杂度

时间复杂度 $O(n+m)$，反图、答案和栈的空间复杂度 $O(n+m)$。

### 总结

“每个起点能到达的最大目标”可以反转成“每个目标能覆盖哪些起点”。再按目标从大到小染色，就能一次确定所有答案。
