---
oj: "luogu"
problem_id: "P3392"
title: "涂条纹"
description: "预处理每行改成 W/B/R 的代价，再枚举白蓝红三段的两个分界位置求最小修改数。"
difficulty: "普及-"
date: 2026-06-19 01:17
toc: true
tags: ["枚举", "前缀和", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3392
---

[[TOC]]

### 题意

把一个 `N x M` 棋盘改成合法条纹旗帜：

- 上方若干行全是 `W`；
- 中间若干行全是 `B`；
- 下方若干行全是 `R`；
- 三种颜色都至少占一行。

每改一个格子代价为 `1`，求最小代价。

### 思路

先把“改格子”压缩成“改一整行”。

对每一行分别计算：

- 改成 `W` 需要改多少格；
- 改成 `B` 需要改多少格；
- 改成 `R` 需要改多少格。

然后枚举两个分界：

```text
[0, white_end)       -> W
[white_end, blue_end)-> B
[blue_end, n)        -> R
```

为了快速求一段行的总代价，对三种颜色分别做前缀和。这样每组分界可以 $O(1)$ 算出总代价。

### Python 知识

- `sum(cell != color for cell in grid[row])` 利用布尔值 `True == 1`，统计一行需要修改的格子数。
- 二维列表 `cost[row][color_index]` 保存每行改成某种颜色的代价。
- 前缀和数组用长度 `n + 1`，这样区间 `[l, r)` 的和就是 `prefix[r] - prefix[l]`。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)

### Pythonic 写法

生成器计数：

@include-code(./main-pythonic.py, python)

### 复杂度

预处理行代价为 $O(NM)$，枚举分界为 $O(N^2)$。总时间复杂度为 $O(NM + N^2)$，空间复杂度为 $O(N)$。

### 总结

先把每行改成某种颜色的代价算出来，问题就从二维棋盘变成了三段行区间的枚举。
