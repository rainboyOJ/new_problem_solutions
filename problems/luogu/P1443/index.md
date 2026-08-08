---
oj: "luogu"
problem_id: "P1443"
title: "马的遍历"
description: "把棋盘看成无权图，从起点做一次 BFS，就能同时求出马到所有格子的最短步数。"
difficulty: "普及-"
date: 2026-06-19 08:03
toc: true
tags: ["bfs", "最短路", "图论", "模板题", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1443
---

[[TOC]]

### 题意

给一个 `n × m` 的棋盘，起点是 `(x, y)`，现在有一匹马放在这个位置上。

要求输出一个表格，表示马从起点到棋盘上每个格子的最少步数。

如果某个格子永远到不了，就输出 `-1`。

样例中的最短步数分布可以写成这样：

|   | 1 | 2 | 3 |
|---|---|---|---|
| 1 | 0 | 3 | 2 |
| 2 | 3 | -1 | 1 |
| 3 | 2 | 1 | 4 |

### 思路

最直接的办法，是把每个格子都当成一个独立终点，然后从起点单独跑一次 BFS 去求它的答案。

这个版本最贴近“逐个询问”的思路：

@include-code(./brute.cpp, cpp)

但这样会重复做很多次搜索。

#### 把棋盘看成无权图

我们把每个格子看成图上的一个点。

如果马能从一个格子一步跳到另一个格子，就在这两个点之间连一条边。由于每次跳跃都只算 `1` 步，所以所有边权都相同。

这样一来，这题就变成了一个标准的：

无权图单源最短路问题。

#### 为什么 BFS 正好合适

在无权图中，BFS 是按层扩展的：

- 先访问距离起点 `0` 步的点；
- 再访问距离起点 `1` 步的点；
- 再访问距离起点 `2` 步的点。

因此某个格子第一次被访问到时，记录的距离就一定是最短步数。

这正好满足题目要求。

#### 正式做法

1. 先把所有格子的答案初始化成 `-1`；
2. 把起点距离设为 `0`，压入队列；
3. 每次取出一个格子，尝试向 8 个马步方向跳；
4. 如果新格子没有访问过，就把它的距离设成当前距离加 `1`，然后入队。

整张图只需要做一次 BFS，就能同时得到所有格子的答案。

### Python 知识

- `deque.popleft()` 是 $O(1)$ 队首弹出，对应 C++ 的 `queue.front()+pop()`。
- `distance = [[-1] * m for _ in range(n)]` 每次创建独立行，避免二维列表浅拷贝。
- 队列元素直接使用 `(x,y)` 元组，不需要定义结构体。
- `"\n".join(" ".join(map(str,row)) ...)` 一次构造多行输出，减少大量 `print` 调用。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/bfs_shortest.md`：隐式图 BFS 与距离记录。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：`deque` 和二维列表初始化。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

- 时间复杂度：$O(nm)$
- 空间复杂度：$O(nm)$

### 总结

这题的关键是识别出“棋盘上每次走一步的最少步数”本质上就是无权图最短路。

一旦转成图模型，单源 BFS 就是最自然、也最标准的做法。

### 一图流解析

这张图把本题的建模、关键转移、实现检查和训练方法压缩到一页，适合读完正文后复盘。

![一图流解析](./one-page-explainer.png)
