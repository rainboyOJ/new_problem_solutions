---
oj: "luogu"
problem_id: "P1553"
title: "数字反转（升级版）"
description: "按整数、小数、分数、百分数四种格式拆分字符串，分别反转数字部分并按规则去掉多余的零。"
difficulty: "普及-"
date: 2026-07-06 20:42
toc: true
tags: ["字符串", "模拟", "分类讨论", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1553
---

[[TOC]]

### 题意

给出一个数字字符串，它可能是整数、小数、分数或百分数。要求把每个数字部分反转，并按题目规则删除多余的 `0`。

### 思路

先按特殊符号判断类型：

| 形式 | 分隔符 | 处理方式 |
| --- | --- | --- |
| 整数 | 无 | 整体反转，再去掉前导零 |
| 小数 | `.` | 整数部分和小数部分分别反转 |
| 分数 | `/` | 分子和分母分别反转，不约分 |
| 百分数 | `%` | 只反转 `%` 前面的数字 |

去零规则要分清方向：

- 整数部分反转后要去掉前导零，例如 `700 -> 7`。
- 小数部分反转后要去掉末尾零，例如 `084 -> 480 -> 48`。
- 如果删除后为空，要保留一个 `0`。

这题是字符串分类讨论，历史目录中保留了 C++ 暴力文件，但本文以 Python 正解为准，不再创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串切片 `s[::-1]` 可以反转字符串。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：单个字符串输入直接用 `input().strip()`。
- `split(".")`、`split("/")` 适合按分隔符拆成两部分。
- `lstrip("0")` 删除左侧零，`rstrip("0")` 删除右侧零。

### 代码

@include-code(./main.py, python)

### 复杂度

设输入长度为 `n`，每次反转和去零都是线性操作，时间复杂度是 $O(n)$，空间复杂度是 $O(n)$。

### 总结

本题最容易错的是去零方向。整数部分去前导零，小数部分去末尾零；分数和百分数仍然只处理各自的数字部分。
