---
oj: "luogu"
problem_id: "P2638"
title: "安全系统"
description: "把未使用信号视为额外盒子，用隔板法分别计算 0 和 1 的分配方案再相乘。"
difficulty: "普及/提高-"
date: 2026-07-16 19:20
toc: true
tags: ["组合数学", "隔板法", "math.comb", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2638
---

[[TOC]]

### 题意

有 `a` 个相同的 0 信号和 `b` 个相同的 1 信号，可分到 `n` 个有编号存储区，也可以不全部使用。求方案数。

### 思路

先只看 0。增加一个“未使用区”，把全部 `a` 个 0 分给 `n+1` 个盒子，隔板法方案数为：

$$\binom{a+n}{a}$$

这与枚举实际使用 `0..a` 个信号等价。1 信号同理有 $\binom{b+n}{b}$ 种。两类信号分配互不影响，根据乘法原理相乘。

### Python 知识

- `math.comb(total,chosen)` 精确计算任意精度组合数。
- Python 大整数能直接输出本题组合数，不需要高精度库。
- 元组解包读取 `n,zeros,ones`，变量名直接表达含义。
- 两个独立方案数直接相乘对应乘法原理。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：任意精度整数优势。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：独立选择的乘法归约。

### 代码
@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

调用两次组合数计算；在本题 `n+a,n+b<=50` 下可视为常数时间和空间。

### 总结

“可以不用完”常可转成额外的未使用盒子，从而直接套用隔板法。
