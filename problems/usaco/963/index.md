---
oj: "usaco"
problem_id: "963"
title: "Cow Gymnastics"
description: "枚举有序奶牛对，用每场排名位置判断一头牛是否始终排在另一头前面。"
difficulty: "入门"
date: 2026-07-11 14:34
toc: true
tags: ["枚举", "模拟", "统计"]
categories: []
pre: []
common: []
recommend: []
source: https://usaco.org/index.php?page=viewproblem2&cpid=963
---

[[TOC]]

### 题意

有 `K` 次训练课，每次都会给 `N` 头奶牛排一个名次。

如果奶牛 `a` 在每一次训练课中都排在奶牛 `b` 前面，就称 `(a,b)` 是一对一致关系。

求一致关系的数量。

### 思路

#### 朴素判断

可以枚举两头奶牛 `a`、`b`，然后在每场排名里扫描它们的位置：

@include-code(./brute.cpp, cpp)

这个做法很直观。由于数据范围小，它已经足够快。

#### 位置表

为了让判断更清楚，读入时可以预处理位置表：

```text
pos[s][cow] = cow 在第 s 场训练中的排名位置
```

位置越小，说明排名越靠前。

对于一对有方向的奶牛 `(a,b)`，如果每一场都满足：

```text
pos[s][a] < pos[s][b]
```

那么 `a` 就始终比 `b` 表现好，答案加一。

注意这里要枚举有序对 `(a,b)`，而不是只枚举 `a < b`。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

枚举有序对是 $O(N^2)$，每对检查 `K` 场训练，时间复杂度为 $O(KN^2)$。

使用排名数组和位置数组，空间复杂度为 $O(KN)$。

### 总结

这题本质是在统计稳定的二元先后关系。

先把每场排名转成 `pos` 位置表，再枚举有序对判断“是否每次都靠前”，代码会很直接。
