---
oj: "luogu"
problem_id: "P1363"
title: "幻象迷宫"
description: "在模板范围内搜索，并记录每个模格子第一次对应的绝对坐标；若同一模格子被不同绝对坐标到达，就能无限走远。"
difficulty: "普及+/提高"
date: 2026-06-20 14:41
toc: true
tags: ["BFS", "图论", "网格", "周期", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1363
---

[[TOC]]

### 题意

给一个 `n * m` 的迷宫模板，它会向四周无限平铺。

模板中：

- `.` 是路
- `#` 是墙
- `S` 是起点

每次可以上下左右移动一格，不能走到墙上。

问能否从起点走到距离起点无限远的地方。

### 思路

先看一个小数据暴力：

@include-code(./brute.cpp, cpp)

它把模板向四周复制很多份，在一个足够大的盒子里做 BFS。

这个做法适合帮助理解，也适合对拍，但不能用于正式数据。

本题真正的关键是：

- 迷宫虽然无限大
- 但地形只由 `(x mod n, y mod m)` 决定

也就是说，不同的绝对坐标，可能对应模板中的同一个格子。

于是可以得到一个非常关键的等价条件：

如果同一个模格子，被两个不同的绝对坐标访问到了，那么答案就是 `Yes`。

原因是这两个位置周围环境完全相同，所以从一个走到另一个的路径可以不断平移复制，进而无限走远。

反过来，如果真的能无限走远，由于模板里只有 `n*m` 个模格子，根据抽屉原理，也一定会出现这种情况。

所以做法就变成：

1. 队列里存绝对坐标
2. 访问判重只按模格子判
3. 但每个模格子要记录“第一次到达它时的绝对坐标”
4. 如果后来同一个模格子又被另一个不同绝对坐标访问到，立刻输出 `Yes`

如果整次 BFS 结束都没发生这种情况，输出 `No`。

### Python 知识

- Python 的 `%` 对负数仍返回非负余数，`next_x % n` 可直接映射到模板行。
- `array('i')` 用 4 字节整数保存最多 225 万个坐标，避免两个 Python 整数列表占用过多内存。
- 两个 `array` 加读取指针 `head` 组成紧凑队列，避免为每个格子创建坐标元组。
- 网格行保持为 `bytes`，用 ASCII 码 `35` 判断 `#` 墙。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/bfs_shortest.md`：BFS 队列和访问状态。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：大网格对象内存与递归限制。

### 代码

@include-code(./main.py, python)

### 复杂度

- 时间复杂度：$O(nm)$
- 空间复杂度：$O(nm)$

### 总结

这题最核心的转化是：

- 把“无限迷宫能否走出去”
- 变成“同一个模格子是否会对应多个可达绝对坐标”

一旦抓住这个等价关系，整题就只需要在模板大小范围内搜索。
