---
oj: "luogu"
problem_id: "P1149"
title: "[NOIP 2008 提高组] 火柴棒等式"
description: "预处理数字的火柴消耗，枚举 A 和 B，检查 A+B 的总火柴数是否恰好等于 n。"
difficulty: "普及-"
date: 2026-07-15 21:40
toc: true
tags: ["枚举", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1149
---

[[TOC]]

### 题意

给定 `n` 根火柴，要求拼出形如：

```text
A + B = C
```

的等式。加号和等号一共固定消耗 `4` 根火柴，数字 `0..9` 的消耗已知。要求所有火柴恰好用完，统计不同等式数量。

### 思路

先扣掉加号和等号的 `4` 根火柴，剩下的火柴全部用于 `A`、`B`、`C` 三个数。

由于 `n <= 24`，数字部分最多只剩 `20` 根火柴，合法数字不会很大。枚举：

```text
0 <= A < 1000
0 <= B < 1000
C = A + B
```

然后检查：

```text
cost(A) + cost(B) + cost(C) == n - 4
```

为了让 Python 跑得更稳，先预处理 `0..1999` 每个数的火柴消耗。

### Python 知识

- `str(number)` 可以把整数转成十进制字符串，再逐位统计。
- 列表 `MATCH_COUNT[digit]` 保存每个数字需要的火柴数。
- 预处理 `costs = [...]` 可以避免双重循环里反复计算字符串。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`

### 代码

@include-code(./main.py, python)

### Pythonic 写法

生成器计数：

@include-code(./main-pythonic.py, python)

### 复杂度

枚举 `A,B` 共 $1000^2$ 组，预处理是常数规模。时间复杂度为 $O(10^6)$，空间复杂度为 $O(1)$。

### 总结

这题的关键是把符号消耗先扣掉，再把等式变成双重枚举 `A,B` 和一次代价检查。
