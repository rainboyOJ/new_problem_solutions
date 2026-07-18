---
oj: "luogu"
problem_id: "P3853"
title: "[TJOI2007] 路标设置"
description: "二分允许的最大间距，用 (gap-1)//limit 统计每段必须新增的路标数。"
difficulty: "普及/提高-"
date: 2026-07-16 17:49
toc: true
tags: ["二分答案", "贪心", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3853
---

[[TOC]]

### 题意

公路起点、终点和若干位置已有路标。最多新增 `K` 个整数位置路标，求相邻路标最大距离的最小值。

### 思路

假设最大距离不能超过 `limit`。原来长度为 `gap` 的一段至少需要新增：

$$
\left\lfloor\frac{gap-1}{limit}\right\rfloor
$$

个路标。减一是为了处理整除情况：`gap=10, limit=5` 时只需在中间新增一个，而不是两个。

把所有间隔的需求相加，若不超过 `K`，说明 `limit` 可行。限制越大越容易可行，因此二分第一个可行值。

### Python 知识

- `itertools.pairwise(signs)` 直接遍历相邻路标对，比手写下标更贴近“相邻间隔”的含义。
- 列表推导式保存所有间隔，后续二分时可以反复遍历。
- `sum((gap - 1) // maximum_gap for gap in gaps)` 用生成器聚合新增数量。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/itertools_recipes.md`：`pairwise` 的相邻元素模式。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：生成器与 `sum`。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

生成器计数：

@include-code(./main-pythonic.py, python)

### 复杂度

每次判定扫描 $n-1$ 个间隔，时间复杂度为 $O(n\log L)$，保存路标和间隔需要 $O(n)$ 空间。

### 总结

关键不是二分本身，而是推导一个间隔需要的路标数。整除边界用 `(gap-1)//limit` 统一处理。
