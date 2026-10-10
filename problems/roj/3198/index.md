---
oj: "roj"
problem_id: "3198"
title: "「PKU ACM Team's Excursion」 北大ACM队的远足"
description: "DAG 上求 S→T 的必经边：拓扑 DP 统计每点路径条数（mod 1e9+7），边为必经边当且仅当 入段路径数×出段路径数=总路径数，配合最短路树输出方案。"
difficulty: "省选/NOI-"
date: 2026-10-02 01:40
updated: 2026-10-10 13:30
toc: true
tags:
  - "图论"
  - "DAG"
  - "拓扑排序"
  - "必经边"
  - "路径计数"
favorite: false
favorite_reason: ""
categories:
  - "图论"
showAtRbook: []
pre: []
common: []
recommend: []
source: https://roj.ac.cn/problem/3198
---

[[TOC]]

## 形式化题目

$N$ 点 $M$ 边带权有向无环图，起点 $S$、终点 $T$。若 $S\to T$ 的每条路径都经过边 $e$，称 $e$ 为**必经边**。求所有必经边（按题面约定输出）。

## 正解

### 思路

#### 1. 路径计数判定必经边

设 $cnt[v]$ 为 $S\to v$ 的路径条数（$S\to T$ 的路径视为若干条）。边 $e=(u,v)$ 是必经边当且仅当

$$cnt_S(u)\cdot cnt_T(v) = cnt_S(T)$$

（所有 $S\to T$ 路径恰好都从 $u$ 进 $v$ 出）。DAG 上 $cnt_S$ 正向拓扑 DP、$cnt_T$ 反向拓扑 DP，各 $O(N+M)$。

模意义下注意：取 $10^9+7$ 时，「乘积相等」在模意义下成立即可（数据保证无冲突，按题面 std 语义复刻）。

#### 2. 输出方案

按题面还需求一条具体路径/最短路信息：用最短路树记录每个点的入边，从 $T$ 回溯即可还原路径（拓扑 DP 时顺带维护 `dist` 与 `pre`）。

拓扑序里入度非 0 但无法到达 $S$ 的环/游离点路径数保持 0，自然被排除。

### 代码

@include-code(./main.cpp, cpp)

@include-code(./main.py, python)

### 复杂度

- **时间复杂度**：$O(N+M)$（拓扑 DP）。
- **空间复杂度**：$O(N+M)$。

## 总结

- 「必经点/必经边」的标准判定：**路径计数**分解，前段 × 后段 = 总数即必经。
- DAG 上路径计数用拓扑 DP，模大质数避免溢出。
- 最短路树 + 回溯是输出具体方案的通用手法。
