---
oj: "luogu"
problem_id: "P1904"
title: "天际线"
description: "把建筑左右边界变成扫描事件，用最小堆维护尚未结束的最高建筑并输出高度变化点。"
difficulty: "普及+/提高"
date: 2026-07-16 17:48
toc: true
tags: ["扫描线", "堆", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1904
---

[[TOC]]

### 题意

给出若干建筑 `(left, height, right)`，按横坐标顺序输出城市轮廓每次高度改变的位置和新高度。

### 思路

在每个左端点把 `(-height, right)` 放入堆，并为每个右端点建立事件。扫描到横坐标 `x` 时，先加入同坐标的新建筑，再弹出所有 `right <= x` 的过期建筑。堆顶就是当前位置最高的有效建筑。

只有堆顶高度发生变化时才输出折点。同坐标事件必须整体处理，否则会输出不存在的中间轮廓。

### Python 知识

- `heapq` 只有最小堆，用负高度模拟最大堆。
- `zip(data, data, data)` 可把同一个整数迭代器每三个元素分成一组建筑数据。
- `answer += [x, height]` 直接构造题目要求的一维输出序列。

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度 $O(n\log n)$，空间复杂度 $O(n)$。

### 总结

天际线的关键是“事件排序 + 惰性删除过期建筑 + 只记录最高高度变化”。
