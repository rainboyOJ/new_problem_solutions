---
oj: "luogu"
problem_id: "P1089"
title: "[NOIP 2004 提高组] 津津的储蓄计划"
description: "按月份模拟手中现金和存款，失败立即输出负月份，全年成功后结算 20% 利息。"
difficulty: "普及-"
date: 2026-06-18 23:46
toc: true
tags: ["模拟", "思维", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1089
---

[[TOC]]

### 题意

津津每个月月初得到 `300` 元。扣掉本月预算后，如果手里还剩整百的钱，就把整百部分存给妈妈。年末妈妈把存款加上 `20%` 利息还给她。

如果某个月月初拿到钱后仍不够本月预算，输出负的月份编号；否则输出年末总钱数。

### 思路

按月份顺序模拟两个量：

- `hand`：当前手里可用的钱；
- `saved`：已经存给妈妈的本金。

每个月的顺序不能错：

1. 先拿到 `300`；
2. 判断够不够支付预算；
3. 扣掉预算；
4. 把手里整百的钱存起来。

整百部分可以用：

```text
deposit = hand // 100 * 100
```

如果循环中途失败，立刻输出 `-month` 并 `break`。如果 12 个月都没有失败，`for...else` 的 `else` 分支会执行，输出：

```text
hand + saved * 12 // 10
```

旧目录中保留了 C++ 逐百存钱的朴素写法；Python 教学版不新增 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用列表推导式 `[int(input()) for _ in range(12)]` 读取 12 行预算。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：`//` 是整数除法，适合计算整百存款。
- `enumerate(costs, start=1)` 同时得到月份编号和预算。
- `for...else`：当循环没有被 `break` 中断时，才会执行 `else` 分支。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

推导式：

@include-code(./main-pythonic.py, python)

### 复杂度

固定模拟 12 个月，时间复杂度是 $O(1)$，空间复杂度是 $O(1)$。

### 总结

这题的关键是顺序：先领钱，再判断够不够花，扣预算后才存整百。用 `for...else` 可以清楚表达“中途失败”和“全年成功”两种结局。
