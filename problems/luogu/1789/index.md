---
oj: "luogu"
problem_id: "P1789"
title: "【Mc生存】插火把"
description: "用布尔矩阵标记被照亮的格子，火把按曼哈顿距离不超过 2 标记，萤石标记 5x5 方块。"
difficulty: "入门"
date: 2026-07-15 18:58
toc: true
tags: ["模拟", "矩阵", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1789
---

[[TOC]]

### 题意

在 `n * n` 方阵中放火把和萤石。被光照到的位置不会生成怪物，问最后有多少格没有被照亮。

火把照亮的是以它为中心、曼哈顿距离不超过 `2` 的格子；萤石照亮的是以它为中心的 `5 * 5` 方块。

### 思路

用二维布尔列表 `lit` 记录每个格子是否被照亮。

为了处理边界，写一个小函数 `light_cell(row, col)`：只有坐标在棋盘内时才标记为亮。

火把枚举 `dx, dy` 从 `-2` 到 `2`，只标记满足：

```text
abs(dx) + abs(dy) <= 2
```

的位置。萤石则直接标记整个 `5 * 5` 范围。

最后扫描整个矩阵，统计仍然为 `False` 的格子。

这题是网格模拟，正解就是直接标记，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：二维矩阵用列表推导式创建。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：嵌套 `range` 循环适合枚举二维偏移。
- 坐标输入从 `1` 开始，代码中减一转成 Python 的 `0` 下标。
- `abs(dx) + abs(dy)` 是曼哈顿距离。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

用 `product` 生成偏移，集合并入照亮坐标，答案为 `n*n - len(lit)`：

@include-code(./main-pythonic.py, python)

### 复杂度

每个光源最多标记 `25` 个位置，最后扫描 `n^2` 个格子。时间复杂度是 $O((m+k) \cdot 25 + n^2)$，空间复杂度是 $O(n^2)$。

### 总结

网格模拟题要先统一坐标，再把“照亮一个格子”的边界判断封装好，后面的标记逻辑会更稳定。
