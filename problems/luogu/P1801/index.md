---
oj: "luogu"
problem_id: "P1801"
title: "黑匣子"
description: "两个堆维护已输出排名左侧与右侧元素，使每次 GET 的目标值位于右堆顶。"
difficulty: "普及+/提高"
date: 2026-07-16 21:00
toc: true
tags: ["双堆", "第k小", "heapq", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1801
---

[[TOC]]

### 题意

元素按顺序加入；第 `i` 次 GET 输出当前集合第 `i` 小值。

### 思路

`lower` 用负数最大堆保存已经越过的 `i-1` 个最小元素，`upper` 保存其余元素，小根堆顶就是下一答案。新值按分界线进入对应堆；每次输出 `upper[0]` 后，把它移入 `lower`，为下一排名作准备。

### Python 知识

- 负数把 `heapq` 变成最大堆。
- `heappushpop` 一次完成插入和弹出，比两个独立操作更直接。
- `values[inserted:amount]` 对应两次 GET 间新增的连续输入段。

### 代码

@include-code(./main.py, python)

### 复杂度

每个元素移动常数次，总时间 $O((m+n)\log m)$，空间 $O(m)$。

### 总结

目标排名每次只增加 1，双堆分界也只需向右移动一个元素。
