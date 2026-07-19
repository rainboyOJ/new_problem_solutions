---
oj: "luogu"
problem_id: "P2660"
title: "zzc 种田"
description: "欧几里得式铺最大正方形的周长和可化为 4(x+y-gcd(x,y))。"
difficulty: "普及-"
date: 2026-07-16 19:20
toc: true
tags: ["欧几里得算法", "最大公约数", "数学", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2660
---

[[TOC]]

### 题意

用正方形铺满 `x*y` 整数矩形，每块体力等于正方形周长，求最小体力。

### 思路

最优过程与欧几里得算法相同：若 `x>=y`，先铺 `x//y` 个边长 `y` 的最大正方形，剩下 `(x%y)*y` 矩形继续。

每一步体力增加 `4*y*(x//y)`。利用欧几里得过程的恒等式，所有正方形边长之和恰为：

$$x+y-\gcd(x,y)$$

因此答案可直接写成 `4*(x+y-gcd(x,y))`。

### Python 知识

- `math.gcd` 直接计算欧几里得算法最终公因子。
- Python 任意精度整数可安全处理 `10^16` 和周长和。
- 公式化简后代码只有读取与一个表达式，避免重复模拟。
- 元组解包让长宽变量一一对应。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：大整数与溢出差异。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：把欧几里得各步贡献归约成闭式。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

gcd 矩形周长：

@include-code(./main-pythonic.py, python)


### 复杂度

`gcd` 时间复杂度 $O(\log\min(x,y))$，额外空间 $O(1)$。

### 总结

模拟最大正方形铺法会得到欧几里得算法；进一步识别贡献和恒等式，可以把整个循环化成一个公式。
