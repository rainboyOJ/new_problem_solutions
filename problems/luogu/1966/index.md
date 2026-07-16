---
oj: "luogu"
problem_id: "P1966"
title: "[NOIP 2013 提高组] 火柴排队"
description: "按高度排名建立两列位置的对应排列，再把最少相邻交换次数转成逆序对。"
difficulty: "提高+/省选-"
date: 2026-07-16 18:28
toc: true
tags: ["排序", "树状数组", "逆序对", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1966
---

[[TOC]]

### 题意

两列火柴内部都可以交换相邻元素。先让两列对应位置的高度平方差之和最小，再求达到该最小值所需的最少交换次数。

### 思路

根据排序不等式，最小距离一定来自“第 $r$ 小和第 $r$ 小配对”。因此先分别得到两列下标按高度递增的顺序，再用 `zip` 把相同排名的两根火柴配对。

令 `target[i]` 表示第一列位置 `i` 最终应对应第二列的哪个位置。现在问题变成：通过相邻交换把一个排列调整到 `target` 的顺序。一个相邻交换恰好改变一个逆序对，所以最少交换次数就是 `target` 的逆序对数。

最后用树状数组从左到右统计逆序对，并按题意取模。

### Python 知识

- `sorted(range(n), key=first.__getitem__)` 排序的是下标，而不是复制 `(值, 下标)` 元组。
- `list.__getitem__` 可以直接充当 `key`，比只做下标访问的 `lambda` 更简洁。
- `zip(order_a, order_b)` 能自然表达“把相同排名配成一对”。
- Python 整数不会溢出，可以最后统一 `% MOD`。

### 代码

@include-code(./main.py, python)

### 复杂度

两次排序与树状数组统计都是 $O(n\log n)$，空间 $O(n)$。

### 总结

本题有两次转化：最小平方差决定“相同排名配对”，最少相邻交换又等于目标排列的逆序对数。
