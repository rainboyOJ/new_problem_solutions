---
oj: "noi_openjudge"
problem_id: "ch0111-10"
title: "河中跳房子"
description: "二分最短跳跃距离，用贪心扫描统计必须移走的石头数。"
difficulty: "普及+/提高"
date: 2026-07-30 23:01
updated: 2026-10-02 18:55
toc: true
tags: ["二分", "贪心", "python"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common:
  - oj: "usaco"
    problem_id: "1038"
    reason: "同为最大化最小值+贪心扫描判定：跳房子统计需移走的石头数，1038 放置奶牛，判定过程可互相套用。"
  - oj: "luogu"
    problem_id: "P2678"
    reason: "同型题（跳石头）：二分最短跳跃距离+贪心统计最少移走石头数，判定与关键观察完全一致。"
  - oj: "luogu"
    problem_id: "P1824"
    reason: "同为二分最小距离+从左到右贪心扫描判定：P1824 放置奶牛，ch0111-10 统计需移走的石头数，判定同型。"
recommend: []
source: http://noi.openjudge.cn/ch0111/10/
---

[[TOC]]

### 题意

最多移走 $M$ 块中间石头，使从起点到终点的最短一次跳跃距离尽量大。

### 思路

二分候选最短距离 `distance`。从左到右扫描，当前石头与上一个保留位置的距离不足时必须删除一个，贪心地计数即可得到满足该距离至少需要删多少块。若不超过 $M$，该距离可行。

### 代码

## Python代码

@include-code(./main.py, python)

## C++代码

@include-code(./main.cpp, cpp)

### 复杂度

时间复杂度为 $O(n \log L)$，空间复杂度为 $O(n)$。

### 总结

最大化最小跳跃距离是典型的二分答案问题，判定过程由局部贪心完成。
