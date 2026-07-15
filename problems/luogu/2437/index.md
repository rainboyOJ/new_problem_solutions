---
oj: "luogu"
problem_id: "P2437"
title: "蜜蜂路线"
description: "路线数满足斐波那契递推，距离为 d 时答案为第 d+1 项。"
difficulty: "入门"
date: 2026-07-15 22:00
toc: true
tags: ["动态规划", "递推", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2437
---

[[TOC]]

### 题意

蜜蜂只能从编号小的蜂房走到编号大的相邻蜂房。给定 `m < n`，求从 `m` 到 `n` 的路线数。

### 思路

这个蜂房路线模型的递推与斐波那契数相同。

设距离 `d = n - m`。从起点到终点的路线数满足：

```text
ways[0] = 1
ways[1] = 1
ways[d] = ways[d-1] + ways[d-2]
```

因此答案是斐波那契式递推的第 `d` 项。

#### 小 DP 表

| d | 0 | 1 | 2 | 3 | 4 | 5 |
|---|---|---|---|---|---|---|
| ways[d] | 1 | 1 | 2 | 3 | 5 | 8 |

样例 `1 -> 14`，距离为 `13`，答案为 `377`。

### Python 知识

- Python 大整数可以直接处理路线数。
- `previous, current = current, previous + current` 是滚动递推常用写法。
- `map(int, input().split())` 读取一行两个整数。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度为 $O(n-m)$，空间复杂度为 $O(1)$。

### 总结

本题和数楼梯一样，是斐波那契递推模型；区别只是把“台阶距离”换成了“蜂房编号差”。
