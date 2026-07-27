---
oj: "luogu"
problem_id: "P2789"
title: "直线交点数"
description: "把直线按平行组划分，用集合 DP 枚举新增一组平行线带来的交点数。"
difficulty: "普及/提高-"
date: 2026-07-16 19:20
toc: true
tags: ["动态规划", "集合", "组合计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2789
---

[[TOC]]

### 题意

共有 `n` 条直线，允许平行且无三线共点。求可能出现多少种不同的交点总数。

### 思路

同一平行组内部没有交点，不同平行组的任意两线产生一个交点。令 `possible[t]` 是 `t` 条线能形成的所有交点数。

若最后加入 `parallel` 条互相平行的线，前面已有 `t-parallel` 条，新组和旧线产生 `parallel*(t-parallel)` 个新交点。因此把 `possible[t-parallel]` 中每个值加上这项并放入集合。

小规模状态如下：

| 直线数 `t` | `possible[t]` |
| --- | --- |
| `0` | `{0}` |
| `1` | `{0}` |
| `2` | `{0,1}` |
| `3` | `{0,2,3}` |
| `4` | `{0,3,4,5,6}` |

所以 `n=4` 时有 5 种交点数。

### Python 知识

- 每个 DP 状态直接用 `set` 保存并自动去除重复交点数。
- `set.update(generator)` 把一整批转移结果加入当前状态。
- `[set() for ...]` 保证每个位置拥有独立集合。
- 生成器只逐个产生转移值。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：集合去重和更新。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：转移结果生成器。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

`n<=25`，按实际状态数记为 `S`，时间复杂度 $O(n^2S)$，空间复杂度 $O(nS)$。

### 总结

几何问题可转成平行组大小的整数划分；集合 DP 只关心能否得到某个交点数，天然适合去重。
