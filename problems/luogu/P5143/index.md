---
oj: "luogu"
problem_id: "P5143"
title: "攀爬者"
description: "按高度 z 从低到高排序所有点，再累加相邻点之间的三维欧几里得距离。"
difficulty: "入门"
date: 2026-07-15 21:20
toc: true
tags: ["排序", "数学", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5143
---

[[TOC]]

### 题意

给出 `n` 个三维点，每个点的高度 `z` 互不相同。攀爬路线必须从低到高经过所有点，求相邻经过点之间的三维欧几里得距离之和。

### 思路

因为每一步都必须到一个更高的点，并且要经过所有点，所以路线没有选择余地：把所有点按 `z` 从小到大排序，就是唯一的经过顺序。

然后枚举排序后相邻的两点，累加：

$$
\sqrt{(x_1-x_2)^2+(y_1-y_2)^2+(z_1-z_2)^2}
$$

最后保留三位小数输出。

### Python 知识

- 把点存成 `(z, x, y)`，直接 `points.sort()` 就会按高度 `z` 升序排列。
- `math.sqrt(value)` 计算平方根。
- `f"{distance:.3f}"` 按三位小数格式化浮点数。
- `n` 最大到 `50000`，使用 `sys.stdin.buffer.read()` 读入更稳妥。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

排序时间复杂度为 $O(n \log n)$，累加距离为 $O(n)$，总时间复杂度为 $O(n \log n)$。空间复杂度为 $O(n)$。

### 总结

题目看起来像路径问题，但高度严格递增并且必须经过所有点，直接把路线固定成按 `z` 排序。
