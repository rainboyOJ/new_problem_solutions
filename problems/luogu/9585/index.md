---
oj: "luogu"
problem_id: "P9585"
title: "「MXOI Round 2」酒店"
description: "把空房间分配到环上的间隔里，最少相邻住人边数为 max(0, 2n-m)。"
difficulty: "普及-"
date: 2026-06-18 20:59
toc: true
tags: ["数学", "构造"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P9585
---

[[TOC]]

### 题意

在一个有 `m` 个房间的环上安排 `n` 位客人，每个房间最多住 1 人。
每位客人的愤怒值等于左右相邻房间里住人的数量，要求最小化所有客人的总愤怒值。

### 思路

先看一个可以直接验证想法的朴素解：

小数据时可以枚举哪些房间住人，直接统计总愤怒值。

@include-code(./brute.cpp, cpp)

下面是另一种「01 序列」风格的暴力写法。它按房间编号依次决定住人或空着，更适合训练递归枚举思维：

<details>
<summary>另一种暴力写法：01 序列</summary>

@include-code(./brute_01_style.cpp, cpp)

</details>

关键在于把问题看成“空房间分配到环上的间隔里”。

`n` 位客人围成一圈后，中间有 `n` 个间隔。
总共有 `m - n` 个空房间可以放进这些间隔里。
每当某个间隔至少放 1 个空房间，就能切断 1 条相邻住人边。

因此最少的相邻住人边数就是：

```text
max(0, 2n - m)
```

而每条相邻住人边会给答案贡献 2，所以总愤怒值最小为：

```text
2 * max(0, 2n - m)
```

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

主解只做常数次计算，时间复杂度 `O(1)`，空间复杂度 `O(1)`。

### 总结

这题的关键是把环上住人问题转成“间隔里能放多少空房间”的计数。
