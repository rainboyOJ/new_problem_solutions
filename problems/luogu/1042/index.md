---
oj: "luogu"
problem_id: "P1042"
title: "[NOIP 2003 普及组] 乒乓球"
description: "先读到 E 前的所有 W/L 记录，再分别按 11 分制和 21 分制模拟分局。"
difficulty: "普及-"
date: 2026-07-15 21:22
toc: true
tags: ["模拟", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1042
---

[[TOC]]

### 题意

输入一串 `W/L` 比赛记录，以 `E` 结束。分别按 11 分制和 21 分制输出每局比分。某局至少达到目标分，且双方分差至少为 2 时结束。

### 思路

先读取所有输入字符，遇到 `E` 就停止，只保留 `W` 和 `L`。

然后写一个函数：

```python
build_scores(records, target)
```

它按照给定目标分制模拟比赛：

1. 当前局 `W` 分和 `L` 分从 0 开始；
2. 扫描每个球的胜负，给对应一方加分；
3. 如果 `max(win, lose) >= target` 且 `abs(win-lose) >= 2`，当前局结束并清零；
4. 所有记录扫完后，还要输出正在进行的最后一局。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：不确定行数时，可以用 `sys.stdin.read()` 读取全部输入。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：f-string 适合格式化 `win:lose`。
- `break` 可以在遇到 `E` 时停止解析。
- 把分制作为函数参数，避免给 11 分制和 21 分制写两份代码。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

设有效记录长度为 `n`，分别模拟两种分制，时间复杂度是 $O(n)$，空间复杂度是 $O(n)$。

### 总结

模拟题先把输入清洗成统一的事件序列，再写一个可复用的模拟函数。不同规则只作为参数传入。
