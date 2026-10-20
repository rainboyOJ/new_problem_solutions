---
oj: "luogu"
problem_id: "P5960"
title: "【模板】差分约束"
description: "把 x_c-x_c'<=y 转成 c' 到 c 的边，所有点距离取 0 跑 SPFA；无负环即有可行解。"
difficulty: "普及+/提高-"
date: 2026-07-17 03:00
updated: 2026-10-20 09:20
toc: true
tags: ["差分约束", "SPFA", "负环", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5960
---

[[TOC]]

### 题意

为一组 `x_c - x_c' <= y` 不等式求任意可行解，或判断无解。约束只比较两个变量的差，所以对一组解整体加减同一个常数仍然合法，答案不唯一。

### 思路

不等式等价于 `x_c <= x_c' + y`，建边 `c' -> c` 权 `y`。跑完最短路后每条边都满足 `dis[c] <= dis[c'] + y`，即 `dis` 天然是一组可行解。

这里不需要额外的超级源点：把所有点的距离都初始化为 `0` 并全部入队，效果等同于加一个到每个点都是 `0` 权边的源点，且起点距离为 `0` 时不会引入正环问题。

若某个点的最短路径边数达到 `n`，说明路径上必然绕出了一个边权和为负的环。负环意味着约束自相矛盾，输出 `NO`；否则 `dis[1..n]` 就是答案。

### 建边方向

| 题面写法 | 归一为 `<=` | 建边 |
| --- | --- | --- |
| `x_c - x_c' <= y` | 不变 | `c' -> c` 权 `y` |
| `x_c - x_c' >= y` | `x_c' - x_c <= -y` | `c -> c'` 权 `-y` |
| `x_c = x_c'` | 两个方向各一条 `0` 权边 | `c -> c'` 与 `c' -> c` 权 `0` |

本题只有第一种，直接调用 `add_leq(c', c, y)` 即可。

### 代码

C++ 版基于 rbook 代码模板 `diff-constraints`（见文章[差分约束：把不等式组变成最短路](https://rbook2.roj.ac.cn/graph/diff-constraints/index.html)）：`add_leq` 统一不等式方向，`feasible()` 做全局可行性检查并留下可行解。

@include-code(./main.cpp, cpp)

Python 版基于配套模板 `diff-constraints-py`，接口一一对应，只是 `feasible()` 用了局部 `in_queue`：

@include-code(./main.py, python)

### 复杂度

`feasible()` 只跑一次 SPFA，最坏 `O(nm)`，空间 `O(n+m)`。本题 `n,m <= 5e3`，足够。

### Python 知识

- `type WeightedAdj = list[list[tuple[int, int]]]` 给邻接表起别名，读的时候不用反复展开嵌套泛型。
- `deque(range(1, n+1))` 一次把所有点按编号入队，正好是"超级源连 0 权边"的初始状态。
- `sys.stdin.buffer.read().split()` 批量读入再按 `3*i` 偏移切分，避免逐行 `input()` 的开销。
- `dis` 会被重新赋值而不是原地清空，所以 `feasible()` 结束后直接读 `self.dis[1:]` 就是解。

### 对拍

`gen.py` 一半生成随机边（容易造出负环），一半先取一组真解再反推边权（保证有解）；`brute.cpp` 直接枚举 `x_i` 取值并检查约束，用来自动核对 `main.cpp` 与 `main.py` 的输出是否满足全部不等式。

### 总结

差分约束的建边方向来自把不等式写成一次松弛公式：`x_v <= x_u + w` 对应 `u -> v` 权 `w`。跑最短路得到的是所有差值上界里最紧的那一组，它同时是解；负环则是"上界可以无限收缩"的表现，即无解。
