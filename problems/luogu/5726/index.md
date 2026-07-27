---
oj: "luogu"
problem_id: "P5726"
title: "【深基4.习9】打分"
description: "从总分中减去一个最高分和一个最低分，再除以剩余评委人数并保留两位小数。"
difficulty: "入门"
date: 2026-07-15 18:39
toc: true
tags: ["模拟", "列表", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5726
---

[[TOC]]

### 题意

有 `n` 位评委打分。去掉一个最高分和一个最低分后，输出剩余分数的平均值，保留两位小数。

如果最高分或最低分出现多次，也只去掉其中一个。

### 思路

读入所有分数后，直接计算：

```text
(sum(scores) - max(scores) - min(scores)) / (n - 2)
```

因为只去掉一个最高分和一个最低分，所以只减一次 `max(scores)` 和一次 `min(scores)`。

最后用 `f"{answer:.2f}"` 保留两位小数。

这题是列表统计入门题，Python 正解已经直接对应题意，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：使用 `list(map(int, input().split()))` 读取一行评分。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：这是“第一行 `n`，第二行数组”的标准格式。
- `sum(scores)` 求总分，`max(scores)` 求最高分，`min(scores)` 求最低分。
- `f"{answer:.2f}"` 保留两位小数输出。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

去极值平均：

@include-code(./main-pythonic.py, python)


### 复杂度

`sum`、`max`、`min` 都会扫描列表，时间复杂度是 $O(n)$；存储评分列表需要 $O(n)$ 空间。

### 总结

这题的关键是“只去掉一个最高分和一个最低分”。直接用列表内置统计函数，能让代码和题意保持一致。
