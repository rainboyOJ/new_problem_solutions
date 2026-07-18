---
oj: "luogu"
problem_id: "P1423"
title: "小玉在游泳"
description: "用 while 循环累计每一步游过的距离，每次把下一步距离乘以 0.98。"
difficulty: "入门"
date: 2026-07-15 18:35
toc: true
tags: ["模拟", "循环", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1423
---

[[TOC]]

### 题意

小玉第一步游 `2` 米，之后每一步都是上一步距离的 `98%`。给出目标距离 `s`，求累计游到至少 `s` 米需要多少步。

### 思路

维护三个量：

- `distance`：已经游过的总距离；
- `step`：下一步能游多远；
- `answer`：已经游了多少步。

只要 `distance < target`，说明还没到目标，就继续游一步：先把 `step` 加到总距离，再把下一步距离变成 `step * 0.98`，步数加一。

当循环停止时，`distance >= target`，当前步数就是答案。若 `s = 0`，循环一次也不会进入，答案自然是 `0`。

这题是直接循环模拟，`brute.py` 会和正解完全相同，因此不创建额外暴力文件。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：使用 `float(input())` 读取一行实数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：本题有浮点累计，但只比较是否达到一位小数目标，数据范围内直接使用 `float` 足够。
- `while distance < target:` 表达“还没到就继续”的循环条件。
- `step *= 0.98` 是 `step = step * 0.98` 的简写。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

模拟累加：

@include-code(./main-pythonic.py, python)

### 复杂度

设答案为 `k`，循环执行 `k` 次，时间复杂度是 $O(k)$，空间复杂度是 $O(1)$。

### 总结

这题要练习的是把过程变量维护清楚：总距离、下一步距离、步数三者各有职责，循环条件直接对应“是否已经到达目标”。
