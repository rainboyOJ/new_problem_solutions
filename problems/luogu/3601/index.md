---
oj: "luogu"
problem_id: "P3601"
title: "签到题"
description: "利用 qiandao(x)=x-phi(x)，在短区间内分段分解质因数并计算每个数的欧拉函数。"
difficulty: "提高+/省选-"
date: 2026-07-16 19:20
toc: true
tags: ["欧拉函数", "分段筛", "数论", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3601
---

[[TOC]]

### 题意

定义 `qiandao(x)` 为 `1..x` 中与 `x` 不互质的数的个数。求区间 `[l,r]` 的函数和模 `666623333`，其中 `r` 可达 `10^12`，区间长度不超过 `10^6`。

### 思路

`1..x` 中与 `x` 互质的数有 `phi(x)` 个，所以：

$$qiandao(x)=x-\varphi(x)$$

需要在短区间内批量求欧拉函数。为每个区间数保存 `remaining` 和初始 `phi=value`。枚举不超过 `sqrt(r)` 的质数 `p`，处理区间中所有 `p` 的倍数：

- 首次发现因子 `p` 时更新 `phi=phi/p*(p-1)`；
- 从 `remaining` 中除尽 `p`；
- 所有小质数处理后，若剩余因子大于 1，再做一次同样更新。

最后累加 `value-phi`。

### Python 知识

- `array('Q')` 用 8 字节无符号整数保存百万个不超过 `10^12` 的值。
- `array('Q',remaining)` 高效复制初始欧拉函数数组。
- `enumerate(remaining)` 同时取得区间下标和剩余质因子。
- 埃氏筛仍用 `bytearray` 切片批量标记。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：大整数数组的紧凑存储。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：区间答案生成与求和。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

生成器计数：

@include-code(./main-pythonic.py, python)

### 复杂度

设区间长度为 `D`，筛质数和分段处理约 $O(\sqrt r\log\log r+D\log\log r)$，空间复杂度 $O(\sqrt r+D)$。

### 总结

先把“不互质计数”转成欧拉函数，再利用区间很短的条件做分段质因数分解，是解决大端点区间数论的核心。
