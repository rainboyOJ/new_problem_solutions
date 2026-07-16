---
oj: "luogu"
problem_id: "P7167"
title: "[eJOI 2020] Fountain (Day1)"
description: "单调栈建立水流向的下一只更大圆盘，再对路径容量和做倍增。"
difficulty: "省选/NOI-"
date: 2026-07-16 18:28
toc: true
tags: ["单调栈", "倍增", "前缀和", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P7167
---

[[TOC]]

### 题意

水从指定圆盘开始，装满后流向下方第一个直径更大的圆盘。每次询问互不影响，求给定水量最后停在哪个圆盘；流出喷泉则输出 `0`。

### 思路

每个圆盘的后继是它右侧第一个直径严格更大的圆盘。用单调递减栈线性求出 `next_larger`，并增加编号 `n` 作为流出喷泉的哨兵。

水只会沿这棵“后继森林”向下走。倍增表维护：

- `jump[level][i]`：从 `i` 越过 $2^{level}$ 个圆盘后的位置；
- `total[level][i]`：越过这些圆盘需要装满的总容量。

回答询问时从大层向小层尝试。只有 `total < water` 才会真正溢出这些圆盘；若水量恰好等于容量，水停在最后一个被装满的圆盘，因此不能写成 `<=`。

### Python 知识

- 普通 `list` 很适合实现单调栈，`append/pop` 都是均摊 $O(1)$。
- `array("i")` 和 `array("q")` 分别紧凑保存 32 位下标与 64 位容量和，避免 Python 整数表造成过高内存。
- `n.bit_length()` 直接给出倍增所需层数。
- 多个答案先收集，再用 `"\n".join(answers)` 一次输出。

### 代码

@include-code(./main.py, python)

### 复杂度

单调栈预处理 $O(n)$，倍增预处理 $O(n\log n)$；每次询问 $O(\log n)$。空间 $O(n\log n)$。

### 总结

先用单调栈把几何描述化成唯一后继，再把“沿后继链走多远”交给倍增，是这类题的通用组合。
