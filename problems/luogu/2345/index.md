---
oj: "luogu"
problem_id: "P2345"
title: "[USACO04OPEN] MooFest G"
description: "按听力递增扫描，用两棵树状数组求当前奶牛到所有已处理坐标的距离和。"
difficulty: "提高+/省选-"
date: 2026-07-16 18:28
toc: true
tags: ["树状数组", "排序", "贡献法", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2345
---

[[TOC]]

### 题意

每对奶牛 $(i,j)$ 贡献 $\max(v_i,v_j)\lvert x_i-x_j\rvert$，求所有无序点对的贡献和。

### 思路

按听力 `v` 从小到大处理。轮到当前奶牛时，所有已处理奶牛的听力都不大于它，因此它与这些奶牛配对时的 `max` 就是当前 `volume`。

只需快速求当前坐标 `x` 到所有旧坐标的距离和。用两棵树状数组分别维护坐标前缀中的数量与坐标和：

```text
左侧距离和 = x * left_count - left_sum
右侧距离和 = right_sum - x * right_count
```

两部分相加后乘当前听力，就是当前奶牛新产生的全部贡献。

### Python 知识

- `sorted((volume, position) for ...)` 默认按元组字典序排序，正好先按听力排序。
- 一个 `prefix(tree, index)` 函数可复用于计数树和坐标和树。
- Python 整数自动扩容，答案超过 64 位边界时也不会溢出。
- 多变量赋值 `seen = position_sum = answer = 0` 适合初始化同类累加器。

### 代码

@include-code(./main.py, python)

### 复杂度

排序 $O(n\log n)$，每头奶牛进行常数次树状数组操作，总时间 $O(n\log n)$；空间 $O(\max x_i)$。

### 总结

先排序固定 `max(v_i,v_j)` 由谁贡献，再用“数量 + 坐标和”拆绝对值，是本题的两个核心步骤。
