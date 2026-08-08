---
oj: "luogu"
problem_id: "P5738"
title: "【深基7.例4】歌唱比赛"
description: "每名选手去掉一个最高分和一个最低分后求平均，用 max 维护最高得分。"
difficulty: "入门"
date: 2026-07-15 21:08
toc: true
tags: ["模拟", "数组", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5738
---

[[TOC]]

### 题意

有 `n` 名选手，每人有 `m` 个评委打分。每名选手去掉一个最高分和一个最低分，剩下分数的平均值作为最终得分。求所有选手中的最高得分，保留两位小数。

### 思路

对每名选手的分数 `scores`：

```text
有效总分 = sum(scores) - max(scores) - min(scores)
平均分 = 有效总分 / (m - 2)
```

用变量 `best` 维护目前最高的平均分。

这题是数组聚合函数练习，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：按行读取每名选手的分数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：`sum`、`max`、`min` 是常用聚合函数。
- `best = max(best, average)` 用于维护最大值。
- `f"{best:.2f}"` 输出两位小数。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

生成器求最高均分：

@include-code(./main-pythonic.py, python)


### 复杂度

共有 `n` 名选手，每名选手 `m` 个分数，时间复杂度是 $O(nm)$，空间复杂度是 $O(m)$。

### 总结

去掉最高最低分时，不一定要排序。只需要总和、最大值和最小值，就能算出有效平均分。
