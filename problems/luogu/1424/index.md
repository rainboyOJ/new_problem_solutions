---
oj: "luogu"
problem_id: "P1424"
title: "小鱼的航程（改进版）"
description: "整周贡献 5 个工作日，剩余天数用取模判断是否为周一到周五。"
difficulty: "入门"
date: 2026-07-15 18:12
toc: true
tags: ["python", "入门", "模拟", "取模"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1424
---

[[TOC]]

### 题意

从星期 `x` 开始经过 `n` 天。小鱼周一到周五每天游 `250` 公里，周末休息。求总共游了多少公里。

### 思路

一整周有 7 天，其中 5 天游泳。先把 `n` 拆成完整周和剩余天数：

```python
full_weeks, rest_days = divmod(n, 7)
```

完整周贡献 `full_weeks * 5` 个游泳日。剩余不足一周的几天再逐天判断星期编号是否在 `1..5`。

`brute.py` 不适合这题；直接模拟最多 7 天的剩余部分已经是清晰的完整做法。

### Python 知识

- `divmod(n, 7)` 同时得到完整周数和剩余天数。
- `(x + i - 1) % 7 + 1` 可以把星期编号保持在 `1..7`。
- `weekday <= 5` 表示周一到周五。
- 先处理完整周，再处理余数，可以避免循环 `10^6` 次。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：`divmod` 和取模。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：整数输入输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：单个答案输出。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

生成器按周几计数：

@include-code(./main-pythonic.py, python)

### 复杂度

只循环剩余天数，最多 6 次，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

周期问题先拆完整周期，再处理剩余部分。星期编号这种循环变量，用取模可以自然绕回 `1..7`。
