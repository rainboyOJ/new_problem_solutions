---
oj: "luogu"
problem_id: "P1162"
title: "填涂颜色"
description: "给矩阵补一圈零并从外部 BFS，未被外部搜索到的零就是闭合圈内部。"
difficulty: "普及-"
date: 2026-07-16 18:01
toc: true
tags: ["BFS", "flood fill", "网格", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1162
---

[[TOC]]

### 题意

方阵中的 `1` 形成闭合边界。把无法只经过 `0` 到达矩阵边界的内部零改成 `2`，其余数字不变。

### 思路

直接从每个零判断能否到边界会重复搜索。反过来，从矩阵外部出发，把所有与外界连通的零一次找完；剩下的零恰好被 `1` 包围。

给原矩阵补一圈零后，外界统一成一个起点 `(0,0)`。BFS 把外部零标成 `-1`。输出原区域时：仍为 `0` 的改成 `2`，`-1` 恢复成 `0`，`1` 保持不变。

### 思路二：两次 BFS

标准做法是从外向内一次 BFS 标记外部区域。下面换一种写法：**从每个 `0` 区域判断能不能走出去，能走出的保留，走不出的填涂**。

- **第一次 BFS**：从当前 `0` 格子出发，用独立的 `vis[][]` 遍历整个连通分量。如果该区域**有格子位于矩阵边界**，说明能走出去（外部区域）；否则说明被 `1` 包围（内部闭合圈）。
- **第二次 BFS**：判定为内部闭合圈后，再做一次 BFS，把整个区域的 `0` 改为 `2`。

这样"正难则反"的思路被拆成正向判断 + 条件执行，逻辑上更直观。

@include-code(./main2.cpp, cpp)

### Python 知识

- `[[0]*(n+2)]` 和列表推导式组合出带边框矩阵；每个输入行用 `[0,*map(...),0]` 解包插入左右边框。
- 补边让四方向搜索无需分别枚举原矩阵四条边。
- 输出生成器 `2 if value==0 else max(value,0)` 同时完成三种值映射。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：安全创建二维列表。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`deque` BFS。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### 复杂度

BFS 与输出各扫描常数次矩阵，时间和空间复杂度均为 $O(n^2)$。

### 总结

“找被包围区域”通常适合正难则反：先从边界找出所有外部区域，未被访问的部分自然就是内部。
