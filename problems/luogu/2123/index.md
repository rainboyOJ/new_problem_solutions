---
oj: "luogu"
problem_id: "P2123"
title: "皇后游戏"
description: "把奖金递推看成两机流水作业，使用 Johnson 法则分组排序后线性模拟。"
difficulty: "普及+/提高"
date: 2026-06-22 20:43
toc: true
tags: ["贪心", "排序", "调度"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2123
---

[[TOC]]

### 题意

有 `n` 位大臣，每人有两个数 `a_i,b_i`。排好顺序后：

```text
c_1 = a_1 + b_1
c_2 = max(a_1 + b_1, a_1 + a_2) + b_2 = max(a_1 + b_1 + b_2, a_1 + a_2 + b_2)
c_3 = max(c_2, a_1 + a_2 + a_3) + b_3 = max(a_1 + b_1 + b_2, a_1 + a_2 + b_2, a_1 + a_2 + a_3) + b_3 = max(a_1 + b_1 + b_2 + b_3, a_1 + a_2 + b_2 + b_3, a_1 + a_2 + a_3 + b_3)
c_i = max(c_{i-1}, a_1 + ... + a_i) + b_i
```

要求重新排序，使获得奖金最多的大臣奖金尽量小。

因为 `c_i` 不会下降，最大值就是最后的 `c_n`。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

暴力会枚举所有排列，计算每个排列的 `c_n`，取最小。这个做法只能用于小数据。

观察递推式：

```text
c_i = max(c_{i-1}, prefix_a) + b_i
```

它和两台机器流水作业完全一样：

- 第一阶段耗时是 `a_i`；
- 第二阶段耗时是 `b_i`；
- 第二阶段开始前，必须等当前任务第一阶段完成，也必须等上一个任务第二阶段完成。

所以可以使用 Johnson 法则：

1. 若 `a_i <= b_i`，放在前半段，并按 `a_i` 升序；
2. 若 `a_i > b_i`，放在后半段，并按 `b_i` 降序。

排好后从前到后模拟即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

排序复杂度为：

```text
O(n log n)
```

模拟为 `O(n)`，空间复杂度为 `O(n)`。

### 总结

本题看起来像国王游戏，但排序规则不同。

递推式本质是两机流水作业，直接套 Johnson 法则：前半段按 `a` 升序，后半段按 `b` 降序。排序后线性模拟最后的奖金即可。


## 新的完美解析
