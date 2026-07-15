---
oj: "luogu"
problem_id: "P1554"
title: "[USACO06DEC] 梦中的统计 Dream Counting B"
description: "枚举 M 到 N 的每个整数，把数字转成字符串后统计每个数码出现次数。"
difficulty: "入门"
date: 2026-07-15 18:48
toc: true
tags: ["模拟", "字符串", "计数", "python"]
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

对每个整数 `value`，把它转成字符串：

```text
str(value)
```

再枚举其中每个字符，把对应数码的计数加一。

例如 `129` 会依次贡献 `1`、`2`、`9` 三个数码。

这题是直接计数练习，正解就是按定义枚举，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `map(int, input().split())` 读取区间左右端点。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：计数可以用列表或 `Counter`；本题数码固定为 `0..9`，列表更直接。
- `str(value)` 可以把整数拆成可遍历的数字字符。
- `count[int(digit)] += 1` 把字符数码转成下标计数。

### 代码

@include-code(./main.py, python)

### 复杂度

设区间长度为 `L = N-M+1`，每个数字位数最多 `10` 位，时间复杂度可看作 $O(L \log N)$，空间复杂度是 $O(1)$。

### 总结

范围差已经限制在可直接枚举的规模内。用字符串拆位能让计数逻辑非常简单，适合本题的数据范围。
