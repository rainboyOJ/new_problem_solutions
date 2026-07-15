---
oj: "luogu"
problem_id: "P1046"
title: "[NOIP 2005 普及组] 陶陶摘苹果"
description: "先算踩凳后的可达高度，再用生成器表达式统计不超过该高度的苹果数。"
difficulty: "入门"
date: 2026-07-15 18:17
toc: true
tags: ["python", "入门", "模拟", "枚举"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1046
---

[[TOC]]

### 题意

给出 10 个苹果高度和陶陶伸手可达高度。陶陶有 30 厘米高的板凳，求她能摘到多少个苹果。

### 思路

陶陶最终可达高度是 `taotao + 30`。只要苹果高度 `height <= reach`，就能摘到。

这题已有旧 C++ 版本；本篇改成 Python 教学，重点是列表输入和用 `sum` 统计满足条件的个数。`brute.py` 不单独写，因为逐个统计就是完整解法。

### Python 知识

- `list(map(int, input().split()))` 读取一行整数列表。
- `sum(1 for height in heights if height <= reach)` 会对每个可摘到的苹果贡献 `1`。
- 生成器表达式适合“统计满足条件的数量”这类短逻辑。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：列表输入和输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：生成器表达式与 `sum`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：多行输入格式。

### 代码

@include-code(./main.py, python)

### 复杂度

固定检查 10 个苹果，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

这类题先算阈值，再统计不超过阈值的元素个数。Python 中 `sum(1 for ... if ...)` 很适合表达计数。
