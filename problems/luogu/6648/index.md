---
oj: "luogu"
problem_id: "P6648"
title: "[CCC 2019] Triangle: The Data Structure"
description: "用六个同尺寸正三角形覆盖更大的正三角形，并滚动维护倍增最大值。"
difficulty: "省选/NOI-"
date: 2026-07-16 18:28
toc: true
tags: ["倍增", "ST表", "区间最值", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P6648
---

[[TOC]]

### 题意

给定边长为 `n` 的数字三角形。对每个边长为 `k` 的正子三角形求最大值，再把这些最大值求和。

### 思路

`maximum[i][j]` 表示以第 `i` 行第 `j` 个数为顶点、当前边长为 `size` 的正三角形最大值。

三个角上的小三角形不能盖住中央区域，因此合并时要使用 6 个同尺寸正三角形。把边长 `size` 扩成 `2 * size` 时，它们的顶点相对位置是：

```text
(0, 0)
(size, 0), (size, size)
(half, 0), (half, half), (size, half)
```

其中 `half = size // 2`。六块允许重叠，但会完整覆盖大三角形，所以最大值就是六个状态的最大值。

先倍增到小于 `k` 的最大 2 的幂 `size`。最终查询时令 `offset = k - size`，把上面位置中的 `size` 换成 `offset`、`half` 换成 `offset // 2`，同样用六块覆盖目标三角形。

### Python 知识

- 每一行使用 `array("i")`，比嵌套 Python 整数列表节省大量内存。
- `zip` 把六段等长数组逐项配对，`map(max, ...)` 在内置迭代器中完成六路最大值合并。
- 数组切片清楚表达不同顶点偏移；旧层在新层建好后自动释放，实现滚动数组。
- `sum(sum(map(...)) for i in ...)` 直接累加所有目标三角形答案。

### 代码

@include-code(./main.py, python)

### 复杂度

每个倍增层处理 $O(n^2)$ 个三角形，共 $O(\log k)$ 层，时间 $O(n^2\log k)$；滚动后空间 $O(n^2)$。

### 总结

这里最容易犯的错是只取三个角，从而漏掉中央区域。六块覆盖确定后，Python 的 `zip + map(max, ...)` 既贴近公式，也明显降低逐下标循环的常数。
