---
oj: "luogu"
problem_id: "P1347"
title: "[ECNA 2001] 排序"
description: "每加入一条大小关系就重跑拓扑排序，用队列分支数判断唯一序列并用处理点数判断矛盾。"
difficulty: "普及/提高-"
date: 2026-07-16 18:42
toc: true
tags: ["拓扑排序", "DAG", "唯一性", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1347
---

[[TOC]]

### 题意

依次给出 `A<B` 形式的关系。求最早在第几条关系后能唯一确定全部顺序，或最早发现矛盾；若所有关系处理完仍不能确定，则输出无法确定。

### 思路

把 `A<B` 建成有向边 `A -> B`。每加入一条新边就对当前图做一次 Kahn 拓扑排序：

- 最终处理点数小于 `n`，说明有环，当前关系产生矛盾；
- 每一步零入度队列都恰好只有一个点，说明每个位置都没有第二种选择，拓扑序唯一；
- 某一步队列有多个点，当前关系还不能唯一确定顺序。

题目要求报告首次确定或首次矛盾，所以每加入一条关系都检查，并在得到结论时立即结束。重复关系不能再次增加入度，代码用邻接矩阵先判重。

### Python 知识

- `bytearray(n)` 作为邻接矩阵的一行，`n<=26` 时紧凑且判重直接。
- `indegree.copy()` 保留原入度，让每次试跑拓扑排序互不影响。
- `enumerate(relations,1)` 同时得到关系和从 `1` 开始的输入序号。
- `"".join(chr(node+65) for node in order)` 把编号转回大写字母序列。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`deque` 拓扑队列。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：生成器拼接答案。

### 代码

@include-code(./main.py, python)

### 复杂度

每条关系后做一次邻接矩阵拓扑排序，时间复杂度 $O(mn^2)$；邻接矩阵空间复杂度 $O(n^2)$。这里 `n<=26`，足够通过。

### 总结

拓扑排序不仅能判断有环，还能判断拓扑序是否唯一：观察每一步是否只有一个零入度选择即可。
