---
oj: "luogu"
problem_id: "P5742"
title: "【深基7.例11】评等级"
description: "把优秀判断封装成函数，用整数式 academic*7+quality*3 避免浮点误差。"
difficulty: "入门"
date: 2026-07-15 21:15
toc: true
tags: ["模拟", "结构体", "函数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5742
---

[[TOC]]

### 题意

每名学生有学号、学业成绩和素质拓展成绩。优秀条件是：两项成绩总分大于 `140`，并且综合分数不小于 `80`。综合分数按 `70%` 和 `30%` 加权。

### 思路

题面提醒不要直接用浮点比较：

```text
academic * 0.7 + quality * 0.3 >= 80
```

两边同时乘以 10，可以改成整数判断：

```text
academic * 7 + quality * 3 >= 800
```

写一个函数 `is_excellent(academic, quality)`，同时检查总分和综合分即可。

这题是函数封装和条件判断练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：一行三个整数用 `map(int, input().split())`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：能用整数比较时，避免浮点误差。
- 布尔表达式可以直接作为函数返回值。
- 用函数封装判断规则，主循环只负责读入和输出。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

精简写法：

@include-code(./main-pythonic.py, python)

### 复杂度

每名学生只做常数次计算，时间复杂度是 $O(N)$，空间复杂度是 $O(1)$。

### 总结

涉及小数权重判断时，优先把式子转成整数比较。这样既精确，也更符合 OJ 判题习惯。
