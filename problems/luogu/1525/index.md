---
oj: "luogu"
problem_id: "P1525"
title: "[NOIP 2010 提高组] 关押罪犯"
description: "按怨气值从大到小加入异组约束，用 2N 并查集找第一条无法避免的冲突边。"
difficulty: "普及+/提高"
date: 2026-06-22 21:34
toc: true
tags: ["并查集", "二分图", "贪心", "排序", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1525
---

[[TOC]]

### 题意

把 `n` 名罪犯分进两座监狱。若有怨气的一对罪犯同狱，就产生对应权值的冲突。求一种分法，使所有同狱冲突的最大权值最小。

### 思路

先把怨气边按权值从大到小处理。对当前边 `(u,v,w)`，希望 `u,v` 进入不同监狱，从而避免权值 `w` 的冲突。

使用 `2n` 个并查集节点表达两个相反阵营：`x` 是人物 `x` 所在侧，`x+n` 是其对立侧。要求 `u,v` 异组时：

- 合并 `u` 与 `v+n`；
- 合并 `u+n` 与 `v`。

处理一条边之前，若 `find(u)==find(v)`，说明此前权值更大的异组约束已经迫使两人同组，当前冲突无法避免。由于边按降序处理，这个 `w` 就是最小可能的最大冲突。

如果所有异组约束都能满足，则没有冲突，输出 `0`。

### Python 知识

- `zip(data[2::3],data[3::3],data[4::3])` 把扁平整数按三元组重组为边。
- `sorted(...,key=lambda edge:-edge[2])` 按第三项权值降序排列。
- Python 整数不会像 C++ `int` 一样溢出，本题权值可以直接比较。
- 循环版并查集和按大小合并兼顾速度与递归安全。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`key` 函数与降序排序。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：整数和递归差异。

### 代码

@include-code(./main.py, python)

### 复杂度

排序需要 $O(m\log m)$，并查集操作为 $O(m\alpha(n))$，总时间复杂度 $O(m\log m)$，空间复杂度 $O(n+m)$。

### 总结

最大值最小化带来“从大到小优先避免”的顺序。2N 并查集负责表达异组约束，第一次矛盾的位置就是答案。
