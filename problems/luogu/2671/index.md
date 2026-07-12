---
oj: "luogu"
problem_id: "P2671"
title: "[NOIP 2015 普及组] 求和"
description: "把三元组化成同颜色同奇偶的端点对，再按颜色和奇偶分组维护四个历史统计量线性求和。"
difficulty: "普及/提高-"
date: 2026-06-20 13:15
toc: true
tags: ["数学", "计数", "推导", "模拟", "noip"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2671
---

[[TOC]]

### 题意

纸带上有 `n` 个位置，每个位置有一个数字 `number_i` 和一种颜色 `color_i`。

三元组 `(x,y,z)` 合法，当且仅当：

- `x < y < z`
- `y - x = z - y`
- `color_x = color_z`

合法三元组的得分是：

- `(x + z) * (number_x + number_z)`

要求所有合法三元组得分总和，对 `10007` 取模。

### 思路

先看一个可以直接验证想法的朴素解：

@include-code(./brute.cpp, cpp)

关键观察是：题目里的中点 `y` 其实不是重点，真正决定合法性的只有两端点 `x,z`。

因为：

- `y - x = z - y`

等价于：

- `y = (x + z) / 2`

所以只要 `x < z` 且 `x + z` 为偶数，就存在唯一的整数中点 `y`。
也就是说，合法三元组等价于：

1. `x < z`
2. `x,z` 同奇偶
3. `color_x = color_z`

于是我们只需要统计“同颜色、同奇偶”的端点对贡献。

固定当前位置 `i` 作为右端点 `z`，
它能配对的左端点，全部来自同一个 `(颜色, 奇偶)` 分组。

设这些历史左端点的总贡献为：

- `sum (x + i) * (number_x + number_i)`

展开后得到四项：

- `sum(x * number_x)`
- `i * sum(number_x)`
- `number_i * sum(x)`
- `cnt * i * number_i`

所以对每个 `(颜色, 奇偶)` 分组，只要维护：

1. 个数 `cnt`
2. 位置和 `sum_pos`
3. 数值和 `sum_num`
4. `位置 * 数值` 的和 `sum_pos_num`

就能在 $O(1)$ 时间算出当前位置作为右端点时的全部贡献。

从左到右扫一遍，先算贡献，再把当前点加入统计即可。

### 代码

@include-code(./main.cpp, cpp)

### 复杂度

每个位置只处理一次，时间复杂度 $O(n)$；
按颜色和奇偶维护统计量，空间复杂度 $O(m)$。

### 总结

这题最关键的是先把三元组条件化简成端点对条件：

- 同颜色
- 同奇偶

一旦去掉了中点 `y` 这个表面信息，后面就是一个很自然的分组统计题。
