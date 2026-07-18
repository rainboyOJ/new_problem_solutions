---
oj: "luogu"
problem_id: "P3741"
title: "小果的键盘"
description: "枚举不修改或修改每一个位置，统计每种结果中的 VK 数量并取最大值。"
difficulty: "入门"
date: 2026-07-15 20:35
toc: true
tags: ["字符串", "枚举", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3741
---

[[TOC]]

### 题意

给定一个只含 `V` 和 `K` 的字符串。最多修改一个字符，问修改后字符串中最多有多少个相邻子串 `VK`。

### 思路

因为 `n <= 100`，可以直接枚举所有可能：

1. 先统计原字符串里的 `VK` 数量。
2. 对每个位置，尝试把 `V` 改成 `K`，或把 `K` 改成 `V`。
3. 统计修改后字符串里的 `VK` 数量，更新最大值。

这个枚举本身就是足够快、足够清楚的正解，不单独创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串切片 `text[i:i+2]` 适合检查相邻两个字符。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：小范围枚举每个候选修改位置，是常见验证和解题方式。
- 字符串不可原地修改，所以先转成 `list(s)`，改完后 `"".join(...)` 转回字符串。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

`itertools.pairwise` 统计相邻 `VK`：

@include-code(./main-pythonic.py, python)

### 复杂度

枚举 `n` 个修改位置，每次统计需要 $O(n)$，总时间复杂度是 $O(n^2)$。`n <= 100`，可以轻松通过。空间复杂度是 $O(n)$。

### 总结

遇到“最多改一个位置”且数据很小的字符串题，直接枚举每个修改位置通常最稳。
