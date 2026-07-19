---
oj: "luogu"
problem_id: "P1554"
title: "[USACO06DEC] 梦中的统计 Dream Counting B"
description: "枚举 M 到 N 的每个整数，用取模拆位统计 0..9 出现次数，避免 str 带来的常数开销。"
difficulty: "入门"
date: 2026-07-15 18:48
toc: true
tags: ["模拟", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1554
---

[[TOC]]

### 题意

给出整数区间 `[M, N]`，统计从 `M` 数到 `N` 的过程中，数字 `0..9` 各出现了多少次。

### 思路

题目保证 `N - M <= 5 * 10^5`，可以直接枚举区间中的每个整数。

对每个整数 `value`，反复：

- `count[value % 10] += 1` 统计最低位；
- `value //= 10` 去掉最低位；

直到变成 `0`。

例如 `129` 会依次贡献 `9`、`2`、`1` 三个数码。

注意：不要用 `str(value)` 拆位。区间最长约 `5 * 10^5`，每个数最多 10 位，总操作约 `5 * 10^6`。算法量级足够，但 Python 里反复创建字符串的常数偏大，最坏点可能 TLE。取模拆位更稳。

这题是直接计数练习，正解就是按定义枚举，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `map(int, input().split())` 读取区间左右端点。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：计数可以用列表或 `Counter`；本题数码固定为 `0..9`，列表更直接。
- `x % 10` / `x //= 10` 是整数拆位的常用写法，比 `str` 更省常数。
- `while True` 再在末尾 `if x == 0: break`，保证至少统计一位（本题 `M >= 1`）。

### 代码

@include-code(./main.py, python)



### 复杂度

设区间长度为 `L = N-M+1`，每个数字位数最多 `10` 位，时间复杂度可看作 $O(L \log N)$，空间复杂度是 $O(1)$。

### 总结

范围差已经限制在可直接枚举的规模内。拆位时优先用取模，而不是字符串，才能在 Python 下稳定通过最坏数据。
