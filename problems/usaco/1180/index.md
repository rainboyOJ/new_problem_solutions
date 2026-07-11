---
oj: "usaco"
problem_id: "1180"
title: "Non-Transitive Dice"
description: "枚举第三个骰子的所有 4 个面值，用 16 对面值比较判断是否形成循环胜负。"
difficulty: "入门"
date: 2026-07-11 17:50
toc: true
tags: ["枚举", "模拟", "数学", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1180
---

[[TOC]]

### 题意

给定两个 4 面骰子 `A` 和 `B`。

要求判断是否存在一个 4 面骰子 `C`，使得三个骰子形成非传递关系：每个骰子都能击败另一个骰子，也会输给另一个骰子。

每个骰子的面值都必须在 $1 \dots 10$。

### 思路

先看一个选择序列风格的暴力：

@include-code(./brute.cpp, cpp)

这个暴力把第三个骰子的 4 个面看成 4 层选择，每层枚举 $1 \dots 10$。生成完整的 `C` 后，再检查 `A,B,C` 是否形成循环胜负。

由于 `C` 的可能数量只有：

$$
10^4 = 10000
$$

所以这个枚举规模很小，可以直接作为满分做法。

判断骰子 `X` 是否击败骰子 `Y` 时，枚举所有 16 对面值：

- 若 `X` 的点数更大，`win++`；
- 若 `X` 的点数更小，`lose++`；
- 相等时重掷，不计入胜负。

如果 `win > lose`，则 `X` 击败 `Y`。

对每个候选骰子 `C`，检查两种循环方向：

```text
A beats B, B beats C, C beats A
B beats A, A beats C, C beats B
```

只要有一种成立，就输出 `yes`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每组数据枚举 $10^4$ 个骰子，每次检查是常数规模。

时间复杂度为 $O(10^4)$，空间复杂度为 $O(1)$。

### 总结

本题的关键是看到第三个骰子的搜索空间很小。

直接枚举所有可能骰子，再用 16 对面值比较判断胜负关系，就能稳定解决。
