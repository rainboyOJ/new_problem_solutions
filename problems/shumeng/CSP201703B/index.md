---
oj: "shumeng"
problem_id: "CSP201703B"
title: "学生排队"
description: "找到指定学号在当前队列的位置，移出后在原位置加移动距离处插回。"
difficulty: "入门"
date: 2026-07-31 16:21
toc: true
tags: ["模拟", "数组"]
favorite: false
favorite_reason: ""
categories: []
pre: []
common: []
recommend: []
source: https://oj.shumeng.tech/p/CSP201703B
---

[[TOC]]

### 题意

学生最初按学号 `1..n` 排队。每次操作给出一名学生的学号和有符号移动距离：正数向后、负数向前，输出全部操作后的队列。

### 思路

最直观的做法是把目标学生与相邻学生逐次交换，交换次数就是移动距离的绝对值。

@include-code(./brute.cpp, cpp)

正式实现直接维护当前队列。先线性查找学号为 `p` 的位置 `position`，把它删除，再插回 `position+q`。这里的下标在删除前保存：向后移动 `q` 后，在删去该学生的队列中正好应插到这个位置；向前移动时同一公式也成立。

题目保证移动合法，`n,m<=1000`，因此每次在线性数组上操作已经足够。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每次查找、删除和插入均为 $O(n)$，总时间复杂度为 $O(nm)$，空间复杂度为 $O(n)$。

### 总结

题目给的是学号而不是当前位置，所以每次操作前必须在当前队列重新寻找该学生。删除后按 `原下标 + 移动距离` 插回，可以统一处理前移和后移。
