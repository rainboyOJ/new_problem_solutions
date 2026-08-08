---
oj: "luogu"
problem_id: "P2895"
title: "[USACO08FEB] Meteor Shower S"
description: "先预处理每个格子的最早摧毁时间，再在“到达时间必须严格早于摧毁时间”的约束下做 BFS。"
difficulty: "普及/提高-"
date: 2026-06-19 08:30
toc: true
tags: ["bfs", "最短路", "图论", "坐标搜索", "思维", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2895
---

[[TOC]]

### 题意

平面第一象限上，Bessie 从 `(0,0)` 出发，每秒可以向上、下、左、右走一格。

有 `M` 颗流星，第 `i` 颗会在时间 `Ti` 砸到 `(Xi, Yi)`，并同时摧毁：

- `(Xi, Yi)` 自己；
- 上下左右四个相邻格子。

如果一个格子会在时间 `t` 被摧毁，那么 Bessie 在时间 `t` 以及更晚都不能站在这个格子上。

要求求出：Bessie 最早什么时候能到达一个永远不会被摧毁的安全点；如果办不到，输出 `-1`。

### 思路

最直接的办法，是把状态写成 `(x,y,t)`，按时间一秒一秒搜索。

这个版本最贴近题意：

@include-code(./brute.cpp, cpp)

但这里其实有一个很重要的单调性：

#### 同一个格子，越早到越好

流星只会让格子越来越危险，不会让它重新变安全。

所以对于同一个格子：

- 如果已经能在时间 `t` 到达，
- 那么以后更晚时间再到达它，不会更优。

这意味着我们完全没必要把“时间”完整展开成三维大状态，只要记录每个格子的最早到达时间即可。

#### 先预处理最早摧毁时间

设 `danger_time[x][y]` 表示格子 `(x,y)` 最早什么时候会被流星摧毁。

每颗流星会影响 5 个格子，所以读入时直接更新这 5 个位置的最小摧毁时间。

如果某格子从来不会被摧毁，就把它记成无穷大。

#### 在时间约束下做 BFS

从 `(0,0)` 出发做普通 BFS。

当前在 `(x,y)`，时间是 `t`，若要走到相邻格子 `(nx,ny)`，到达时间就是 `t+1`。

只有在下面这个条件成立时，才能进入它：

`t + 1 < danger_time[nx][ny]`

这里必须是严格小于，因为题目明确说：在一个格子被摧毁的那个时刻以及之后，都不能站在上面。

#### 什么时候可以结束

如果 BFS 到达了某个 `danger_time` 为无穷大的格子，说明这个格子永远安全。

而 BFS 又保证是按时间从小到大扩展的，所以这一定是最早到达安全点的时间，可以立刻输出答案。

### Python 知识

- `danger` 字典只保存会被摧毁的坐标；不在字典中的点天然表示永久安全，不必开固定大小网格。
- `danger.get(point, inf)` 对从未受影响的坐标返回无穷大。
- 坐标使用元组，可直接作为 `dict` 和 `set` 的键；队列状态用 `(*point,time)` 解包构造。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：字典、集合与 `deque` 的选择。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/bfs_shortest.md`：隐式状态图最短路。

### 代码 python

@include-code(./main.py, python)

### 代码 c++ 

@include-code(./main.cpp, cpp)


### 复杂度

- 时间复杂度：$O(M+V)$，其中 `V` 是 BFS 实际访问的坐标数
- 空间复杂度：$O(M+V)$

### 总结

这题的核心不是普通 BFS 本身，而是先抽象出“每个格子的最早死亡时间”。

一旦有了这个时间上限，剩下的就是一个带可进入条件的最短路搜索：  
第一次到达某格子的时间最优，而第一次到达任意永远安全格子的时间就是答案。

### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
