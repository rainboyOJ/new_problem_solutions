---
oj: "usaco"
problem_id: "1182"
title: "Searching for Soulmates"
description: "枚举目标数保留的二进制前缀，贪心压缩起点并统计中间加一和恢复低位的代价。"
difficulty: "普及+/提高"
date: 2026-07-11 19:28
toc: true
tags: ["贪心", "二进制", "数学", "usaco"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=1182
---

[[TOC]]

### 题意

给定若干组 `(a,b)`。只能对 `a` 做这些操作：

- $a = a * 2$
- 如果 `a` 是偶数，$a = a / 2$
- $a = a + 1$

问最少多少次操作能把 `a` 变成 `b`。

### 思路

先看一个小数据暴力。它直接把数字看成状态，用 BFS 枚举三种操作。

@include-code(./brute.cpp, cpp)

满分做法利用一个关键性质：最优方案中，不会出现“先乘 2，后面又除 2”的结构。因为形如：

```text
x -> 2x -> 2x+k -> x+k/2
```

总可以改成更短的：

```text
x -> x+k/2
```

所以操作可以分成三段：

1. 先对 `a` 做若干次“除以 2”相关操作，把它缩小；
2. 中间做若干次 `+1`；
3. 最后做若干次 $*2$ 和少量 `+1`，恢复到 `b`。

关键是枚举第 3 段有多少次 $*2$。设这个次数为 `removed`，那么第 3 段开始前要达到：

```text
prefix = b >> removed
```

也就是 `b` 去掉最后 `removed` 个二进制位后的前缀。

固定 `prefix` 后，把 `a` 缩小到不超过 `prefix` 的过程是贪心确定的：

- 如果当前数是偶数，直接 $/2$；
- 如果当前数是奇数，必须先 `+1`，再 $/2$。

这样每次都会少一位二进制长度，并且不会吃亏。

当 `a` 被压到 $cur <= prefix$ 后，中间需要 `prefix-cur` 次 `+1`。

最后恢复 `b` 的低 `removed` 位：

- 每一位都需要一次 $*2$，所以贡献 `removed`；
- 低位中每个 `1` 还需要一次 `+1`，所以贡献 `popcount(b 的低 removed 位)`。

枚举所有可能的 `removed`，取最小值即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

`removed` 最多枚举到 $b$ 的二进制位数，内部每次也至多除掉 $a$ 的若干位。

单组时间复杂度为 $O(\log^2 \max(a,b))$，空间复杂度为 $O(1)$。

### 总结

本题的关键是从二进制角度看操作。

固定最后的乘二次数后，前面的缩小过程和后面的恢复低位代价都可以直接算出来，于是枚举这个分界点即可。
