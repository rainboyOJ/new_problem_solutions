---
oj: "luogu"
problem_id: "P5707"
title: "【深基2.例12】上学迟到"
description: "把时间统一成分钟，向上取整步行时间后用取模处理跨天。"
difficulty: "入门"
date: 2026-07-15 17:56
toc: true
tags: ["python", "入门", "模拟", "数学"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5707
---

[[TOC]]

### 题意

从家到学校距离为 $s$ 米，速度为 $v$ 米每分钟。路上还要花 $10$ 分钟垃圾分类。必须在 `08:00` 到达，求最晚出门时间，格式为 `HH:MM`。

### 思路

先算出总共需要提前多少分钟：

- 步行时间是 $\lceil s/v\rceil$，因为只能整分钟出发；
- 再加上垃圾分类的 $10$ 分钟。

把 `08:00` 转成第 `480` 分钟，减去所需时间。如果结果为负，说明要前一天出发，用对一天总分钟数 `24 * 60` 取模即可。

`brute.py` 不适合这题，因为直接时间换算已经是完整解法；暴力枚举出门时间反而会掩盖统一成分钟的核心技巧。

### Python 知识

- `ceil(s / v)` 向上取整，表示走完这段路至少需要多少整分钟。
- `% (24 * 60)` 可以把负分钟数绕回前一天的时间。
- `divmod(latest, 60)` 同时得到小时和分钟，相当于 `(latest // 60, latest % 60)`。
- `f"{hour:02d}:{minute:02d}"` 会把小时和分钟补成两位，例如 `7` 变成 `07`。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：`divmod` 和常用数学工具。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：输出格式控制。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入和格式化输出。

### 代码

@include-code(./main.py, python)

### 复杂度

只做常数次运算，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

时间题的核心技巧是统一单位。全部换成“从当天零点开始的分钟数”后，跨天用取模处理，最后再拆回小时和分钟。
