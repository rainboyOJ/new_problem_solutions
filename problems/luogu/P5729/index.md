---
oj: "luogu"
problem_id: "P5729"
title: "【深基5.例7】工艺品制作"
description: "用三维布尔列表标记被切掉的小方块，最后统计没有被标记的位置数量。"
difficulty: "入门"
date: 2026-07-15 18:48
toc: true
tags: ["模拟", "列表", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5729
---

[[TOC]]

### 题意

一个 `w * x * h` 的长方体由很多 `1 * 1 * 1` 小方块组成。每次切割给出一个三维闭区间，把区间内所有小方块蒸发掉。问所有切割后还剩多少小方块。

### 思路

数据范围很小：三维尺寸都不超过 `20`。可以直接开三维布尔列表 `removed`，表示每个坐标的小方块是否被切掉。

每次切割给出：

```text
x1 y1 z1 x2 y2 z2
```

就用三重循环枚举这个小长方体内的所有坐标，把它们标成 `True`。

所有切割完成后，再枚举整个长方体，统计仍为 `False` 的小方块数量。

这题是三维数组模拟，正解就是直接标记，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `map(int, input().split())` 读取一行多个整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：三重 `range` 循环可以直接枚举三维坐标。
- 三维列表要用嵌套推导式创建，避免多个层共享同一个子列表。
- 本题坐标从 `1` 开始，所以列表大小开到 `维度 + 1`。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

用 `product` 生成被切坐标集合，体积减去去重后的点数：

@include-code(./main-pythonic.py, python)

### 复杂度

设体积为 `V = w*x*h`。每次切割最多枚举 `V` 个小方块，时间复杂度上界是 $O(qV)$；最后统计是 $O(V)$。空间复杂度是 $O(V)$。

### 总结

当数据规模很小时，直接用三维列表模拟最清楚。重点是坐标范围包含端点，并且不要用错误的列表乘法创建三维数组。
