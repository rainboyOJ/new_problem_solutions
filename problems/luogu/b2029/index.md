---
oj: "luogu"
problem_id: "B2029"
title: "大象喝水"
description: "计算圆柱水桶体积并换算成升，再用向上取整求至少需要多少桶。"
difficulty: "入门"
date: 2026-07-15 23:33
toc: true
tags: ["入门", "数学", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/B2029
---

[[TOC]]

### 题意

水桶是圆柱体，深度为 `h` 厘米，底面半径为 `r` 厘米。大象需要喝 `20` 升水，题目规定 $\pi = 3.14$。求至少需要多少桶水。

### 思路

一个圆柱水桶的体积是：

```text
3.14 * r * r * h 立方厘米
```

因为 `1000` 立方厘米等于 `1` 升，所以一桶水的升数是：

```text
3.14 * r * r * h / 1000
```

需要的桶数是 `20 / 每桶升数` 向上取整。

本题是直接公式计算，不需要暴力程序。

### Python 知识

- `map(int, input().split())` 可以一行读取两个整数。
- `math.ceil(x)` 表示向上取整。
- 本题要使用题面指定的 `3.14`，不要改用 `math.pi`。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

math.ceil：

@include-code(./main-pythonic.py, python)


### 复杂度

时间复杂度是 $O(1)$，空间复杂度是 $O(1)$。

### 总结

单位换算题要先把公式写清楚：立方厘米除以 `1000` 变成升，再对桶数向上取整。
