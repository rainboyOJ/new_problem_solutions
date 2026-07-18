---
oj: "luogu"
problem_id: "P1085"
title: "[NOIP 2004 普及组] 不高兴的津津"
description: "固定循环 7 天，记录第一个严格超过 8 小时且总课时最大的日期。"
difficulty: "入门"
date: 2026-07-15 18:12
toc: true
tags: ["python", "入门", "模拟", "枚举"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1085
---

[[TOC]]

### 题意

输入 7 天的上课时间。每天有学校上课时间和课外班时间，如果某天总时间超过 8 小时，津津就会不高兴。输出一周里最不高兴的是周几；如果没有任何一天超过 8 小时，输出 `0`。

### 思路

固定只有 7 天，直接逐天检查。用 `max_hours` 记录目前见过的最大总课时，初始为 `8`，因为只有严格大于 8 才算不高兴。

当某一天 `total > max_hours` 时，更新答案为这一天。并列时不更新，这样会自动保留更早的一天。

这题已经有旧 C++ 版本；本篇重点改成 Python 教学。`brute.py` 不适合单独写，因为固定 7 次循环本身就是完整解法。

### Python 知识

- `for day in range(1, 8)` 会依次产生 `1..7`，正好对应周一到周日。
- `school, extra = map(int, input().split())` 一次读入两个整数。
- 把 `max_hours` 初始设为 `8`，可以自然处理“没有不高兴”的情况。
- 并列取更早日期时，只在严格更大 `>` 时更新答案。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：多整数输入和输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：多行输入与单个答案输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：用 `max` 思路维护最优值。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

max + key：

@include-code(./main-pythonic.py, python)

### 复杂度

固定处理 7 天，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

固定天数的比较题，核心是维护“当前最优答案”。并列规则要体现在更新条件里：本题只在严格更不高兴时更新。
