---
oj: "luogu"
problem_id: "P4145"
title: "上帝造题的七分钟 2 / 花神游历各国"
description: "线段树维护区间和与最值，利用平方根快速收敛剪枝区间开方。"
difficulty: "提高"
date: 2026-07-16 23:59
toc: true
tags: ["线段树", "区间开方", "剪枝", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P4145
---

[[TOC]]

### 题意

对区间每个数做一次向下取整平方根，或查询区间和。

### 思路

数值为 1 时再开方不会改变。节点维护区间和、最小值、最大值：若整段 `min == max`，可以直接把整段赋成 `isqrt(value)`；若 `max <= 1`，直接剪枝。否则递归到相交子区间。平方根操作会让大数迅速下降，均摊访问量可控。

### Python 知识

- `math.isqrt` 是整数平方根，避免浮点精度问题。
- 赋值懒标记用 `0` 表示“没有标记”，因为题目中的数始终为正。
- `max <= 1` 的提前 `return` 是这类势能下降操作的关键优化。

### 代码

@include-code(./main.py, python)

原有 C++ 版本仍保留：

@include-code(./main.cpp, cpp)

### 复杂度

建树 `O(n)`；单次操作为线段树访问并带平方根收敛剪枝，空间 `O(n)`。

### 总结

当区间修改会快速降低数值时，维护最值并在“整段相同”时批量处理，通常比强行维护复杂懒标记更简单。
