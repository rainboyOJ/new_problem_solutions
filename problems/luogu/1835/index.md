---
oj: "luogu"
problem_id: "P1835"
title: "素数密度"
description: "先筛出不超过 sqrt(R) 的素数，再在长度不超过一百万的区间内做分段筛。"
difficulty: "普及+/提高"
date: 2026-07-16 19:20
toc: true
tags: ["数论", "分段筛", "素数", "bytearray", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1835
---

[[TOC]]

### 题意

统计 `[L,R]` 中素数个数。`R` 接近 `2^31`，但区间长度不超过 `10^6`。

### 思路

不能筛到 `R`。任何区间合数都至少有一个不超过 `sqrt(R)` 的质因子：

1. 普通埃氏筛得到 `2..sqrt(R)` 的素数；
2. 建立长度 `R-L+1` 的区间标记；
3. 对每个基础素数 `p`，从 `max(p*p,ceil(L/p)*p)` 开始标记倍数；
4. 若 `L=1`，单独把 1 标为非素数。

从 `p*p` 开始可避免把区间中的质数 `p` 自己误删。

### Python 知识

- `bytearray` 适合百万长度 0/1 标记。
- 扩展切片赋值一次标记同一质数的全部倍数。
- `(left+p-1)//p*p` 是不小于 `left` 的第一个 `p` 倍数。
- `sum(segment)` 直接统计仍为 1 的位置。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：紧凑标记和切片性能。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：区间按需处理思路。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

生成器计数：

@include-code(./main-pythonic.py, python)

### 复杂度

基础筛和区间标记约 $O(\sqrt R\log\log R+(R-L+1)\log\log R)$，空间 $O(\sqrt R+R-L+1)$。

### 总结

数值上界大但查询区间短，是分段筛的典型信号：只为当前区间分配标记。
