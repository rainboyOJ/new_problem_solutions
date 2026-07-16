---
oj: "luogu"
problem_id: "P1536"
title: "村村通"
description: "并查集合并已有道路并实时维护连通块数，最少新道路数就是连通块数减一。"
difficulty: "入门"
date: 2026-06-20 00:23
toc: true
tags: ["并查集", "图论", "连通块", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1536
---

[[TOC]]

### 题意

多组数据中给出 `n` 个城镇和已有道路，求最少再建多少条道路，才能让任意两个城镇互相到达。输入以单独的 `0` 结束。

### 思路

已有道路把城镇分成若干连通块。若有 `k` 个连通块，每建一条连接不同块的道路最多使块数减少一，因此至少需要 `k-1` 条；把各块依次连接起来也恰好只需 `k-1` 条。

用并查集维护已有道路：

1. 初始每个城镇单独成块，`blocks=n`；
2. 一条道路连接两个不同代表元时合并，并令 `blocks-=1`；
3. 重边或块内道路不会改变块数；
4. 输出 `blocks-1`。

### Python 知识

- 用一个下标 `pos` 顺序消费批量读取的整数，便于处理组数未知、以 `0` 结束的输入。
- 在 `union` 成功时直接减少 `blocks`，省去最后再次扫描所有节点。
- `answer` 收集每组结果，最后 `"\n".join(answer)` 一次输出。
- 循环版 `find` 配合路径减半 `parent[x]=parent[parent[x]]`，短且不依赖递归深度。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：多组和终止标记输入。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：递归深度与批量输出。

### 代码

@include-code(./main.py, python)

### 复杂度

一组数据有 `n` 个点、`m` 条路，时间复杂度 $O((n+m)\alpha(n))$，空间复杂度 $O(n)$。

### 总结

答案只取决于已有图的连通块数。并查集合并成功时实时计数，是比“最后逐点数根”更直接的写法。
