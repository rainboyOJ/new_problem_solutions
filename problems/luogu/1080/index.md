---
oj: "luogu"
problem_id: "P1080"
title: "[NOIP 2012 提高组] 国王游戏"
description: "用相邻交换证明按 a*b 升序排列大臣，Python 大整数直接维护前缀左手乘积。"
difficulty: "普及+/提高"
date: 2026-06-22 20:40
toc: true
tags: ["贪心", "排序", "高精度", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1080
---

[[TOC]]

### 题意

国王固定在队首，后面有 `n` 位大臣。每个人有左手数 `a` 和右手数 `b`。某位大臣获得的金币数是他前面所有人的左手数乘积除以自己的右手数，向下取整。要求重新排列大臣，使获得金币最多的大臣的金币数尽量小。

### 思路

先看一个小数据暴力：

@include-code(./brute.cpp, cpp)

暴力枚举所有排列，只能验证小数据。

正解用相邻交换。考虑相邻两个大臣 `x=(a_x,b_x)`、`y=(a_y,b_y)`，设他们前面左手乘积为 `P`。

若顺序是 `x,y`，这两人的金币上界来自：

```text
P / b_x
P * a_x / b_y
```

若顺序是 `y,x`，对应为：

```text
P / b_y
P * a_y / b_x
```

整理可以得到：当 `a_x * b_x <= a_y * b_y` 时，把 `x` 放在 `y` 前面不会更差。因此按 `a*b` 升序排序。

排序后从前到后模拟即可。Python 的整数是任意精度，不需要手写高精度乘除。

### Python 知识

- `ministers.sort(key=lambda item: item[0] * item[1])` 按 `a*b` 排序。
- Python `int` 自动支持大整数，本题可以直接维护 `prefix *= left`。
- `prefix // right` 是整数除法，对应题目中的向下取整。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

排序复杂度是 $O(n \log n)$。若把大整数位数记作 `D`，模拟乘除约为 $O(nD)$。

空间复杂度是 $O(n + D)$。

### 总结

排序依据不是单独的左手数或右手数，而是相邻交换推出的 `a*b`。Python 版本最大的优势是可以直接使用大整数。
