---
oj: "usaco"
problem_id: "965"
title: "Livestock Lineup"
description: "按字典序枚举 8 头奶牛的全排列，检查所有相邻限制，第一个合法排列就是答案。"
difficulty: "入门"
date: 2026-07-11 14:45
toc: true
tags: ["枚举", "排列", "模拟"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=965
---

[[TOC]]

### 题意

有 8 头固定名字的奶牛，需要安排一个挤奶顺序。

每条限制形如 `X must be milked beside Y`，表示 `X` 和 `Y` 必须相邻。

要求输出满足所有限制的字典序最小顺序。

### 思路

#### 选择序列暴力

可以把 8 个位置看成一串选择：第 `dep` 个位置选择一头还没用过的奶牛。

@include-code(./brute.cpp, cpp)

这个暴力按字典序递归生成完整排列，在叶子节点统一检查所有相邻限制。

#### 全排列枚举

因为只有 8 头奶牛：

```text
8! = 40320
```

直接枚举全排列即可。

把 8 个名字先按字典序排好，然后使用 `next_permutation` 枚举。每次检查所有限制：

```text
abs(pos[X] - pos[Y]) == 1
```

第一个合法排列就是字典序最小答案。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

最多枚举 `8!` 个排列，每个排列检查最多 7 条限制。由于 8 是常数，时间复杂度可以看作 $O(1)$。

只保存固定数量的名字和限制，空间复杂度为 $O(1)$。

### 总结

这题数据范围非常小，重点不是优化，而是利用字典序枚举。

只要初始名字数组按字典序排列，`next_permutation` 枚举到的第一个合法方案就是题目要求的答案。
