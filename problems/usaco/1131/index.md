---
oj: "usaco"
problem_id: "1131"
title: "Acowdemia I"
description: "先排序求当前 h-index，再利用每篇论文最多加一引用的限制，只判断 h+1 是否可达。"
difficulty: "普及-"
date: 2026-07-11 13:24
toc: true
tags: ["排序", "贪心", "枚举"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1131
---

[[TOC]]

### 题意

Bessie 有 `N` 篇论文，第 `i` 篇论文当前有 `c_i` 次引用。

她最多可以在综述中引用 `L` 篇自己的论文，每篇论文最多被引用一次，也就是最多给这些论文各加 1 次引用。

求修改后能达到的最大 h-index。

### 思路

#### 暴力想法

最直接的想法是枚举每篇论文是否被综述引用：

@include-code(./brute.cpp, cpp)

这个暴力把问题看成一串 01 选择：`choose_paper[i] = 0/1` 表示第 `i` 篇论文不引用或引用。递归生成完整选择后，检查引用数量是否不超过 `L`，再计算当前 h-index。

这种写法适合小数据，但满数据下有 $2^N$ 种选择，无法通过。

#### 只判断 `h+1`

官方解析的关键结论是：最终 h-index 最多只会比当前 h-index 多 1。

原因是每篇论文最多只能增加 1 次引用。若当前 h-index 是 `h`，那么第 `h+1` 高引用的论文原本最多只有 `h` 次引用，综述后最多也只能到 `h+1`。

所以答案只可能是：

```text
h 或 h+1
```

先把引用次数从大到小排序，求出当前 h-index。然后设 $target = h + 1$。

为了达到 `target`，需要至少 `target` 篇论文引用次数不少于 `target`：

- 已经不少于 `target` 的论文，记为 `already_ok`；
- 还差 1 次，也就是引用次数为 `target - 1` 的论文，记为 `can_add`；
- 还缺的达标论文数是 $need = target - already_ok$。

如果 $need <= L$ 且 $need <= can_add$，就能把这些差 1 次的论文各引用一次，答案变成 `target`。否则答案仍是 `h`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

排序复杂度为 $O(N \log N)$，之后线性扫描，整体时间复杂度为 $O(N \log N)$。

空间复杂度为 $O(N)$。

### 总结

这题的核心不是枚举引用方案，而是先看清每篇论文最多只会增加 1 次引用。

这个限制让 h-index 最多提升 1，于是问题从“选择哪些论文”变成了“判断 `h+1` 是否可达”。
