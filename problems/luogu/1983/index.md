---
oj: "luogu"
problem_id: "P1983"
title: "[NOIP 2013 普及组] 车站分级"
description: "每趟车建立虚拟节点压缩停靠与不停靠站的大小约束，再做拓扑最长路求最少级别数。"
difficulty: "普及+/提高"
date: 2026-07-16 18:42
toc: true
tags: ["拓扑排序", "DAG", "虚拟节点", "动态规划", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1983
---

[[TOC]]

### 题意

给出若干趟车的停靠站。一趟车始发站到终点站之间，所有不停靠站的级别都必须低于每个停靠站。求满足全部约束时最少需要多少个级别。

### 思路

直接从每个不停靠站向每个停靠站连边，单趟车可能产生 $O(n^2)$ 条边。为每趟车建立一个虚拟节点 `T`：

- 不停靠站 `u -> T`，边权 `0`；
- `T ->` 停靠站 `v`，边权 `1`。

令 `level[x]` 表示满足约束的最低级别。沿边转移：

$$level[v]=\max(level[v],level[u]+weight)$$

权值 `0` 只是把所有不停靠站的最大级别汇总到虚拟节点，权值 `1` 再保证每个停靠站至少高一级。这样单趟车只需线性数量的边。

样例一中关键站点的最低级别可以写成：

| 车站 | 是否受“不停靠 < 停靠”约束 | 最低级别 |
| --- | --- | ---: |
| `2,4` | 区间内不停靠站 | `1` |
| `1,3,5,6` | 停靠站，必须高于 `2,4` | `2` |
| `7,8,9` | 没有更高要求 | `1` |

因此最少需要 `2` 级。对整个压缩 DAG 做拓扑最长路，即可同时满足所有车次约束。

### Python 知识

- 每趟车的 `set(stops)` 支持快速判断区间车站是否停靠。
- 虚拟节点编号为 `n+train`，无需额外对象。
- 为节省大量二元组对象，代码把 `(neighbor,weight)` 编码成整数 `(neighbor<<1)|weight`。
- 解码时 `edge>>1` 取邻点，`edge&1` 取 0/1 权值。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：集合成员判断和 `deque`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：大量元组的对象内存成本。

### 代码

@include-code(./main.py, python)

### 复杂度

设所有车次覆盖区间长度与停靠站数之和为 `E`，有 `E<=O(mn)`。建图和拓扑 DP 时间复杂度 $O(n+m+E)$，空间复杂度 $O(n+m+E)$。

### 总结

虚拟节点把一组到一组的完整约束压成两层边；0/1 权值再准确表达“汇总”和“必须高一级”。
