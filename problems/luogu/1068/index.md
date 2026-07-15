---
oj: "luogu"
problem_id: "P1068"
title: "[NOIP 2009 普及组] 分数线划定"
description: "先按成绩降序、报名号升序排序，取计划人数 150% 处的分数线，再输出所有达线选手。"
difficulty: "入门"
date: 2026-07-15 21:20
toc: true
tags: ["排序", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1068
---

[[TOC]]

### 题意

有 `n` 名选手，每人有报名号和分数。计划录取 `m` 人，面试分数线取排名第 `floor(m * 1.5)` 名选手的分数。

最终所有分数不低于分数线的人都进入面试，并按分数从高到低、报名号从小到大输出。

### 思路

先把选手按题目要求排序：

1. 分数高的在前；
2. 分数相同，报名号小的在前。

排序后，`line_count = m * 3 // 2` 就是题目中的 `floor(m * 150%)`。分数线是排序后第 `line_count` 个人的分数，也就是 Python 下标 `line_count - 1`。

因为可能有并列分数，所以不能只输出前 `line_count` 人，而要输出所有 `score >= line_score` 的选手。

### Python 知识

- `people.sort(key=lambda item: (-item[1], item[0]))` 是多关键字排序：分数用负号实现降序，报名号保持升序。
- `m * 3 // 2` 用整数运算表达 `floor(m * 1.5)`，避免浮点数。
- 列表推导式 `[item for item in people if item[1] >= line_score]` 可以直接筛出达线选手。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`

### 代码

@include-code(./main.py, python)

### 复杂度

排序时间复杂度为 $O(n \log n)$，筛选时间复杂度为 $O(n)$，总时间复杂度为 $O(n \log n)$。空间复杂度为 $O(n)$。

### 总结

分数线由“排序后的某个位置”决定，输出人数由“所有达线者”决定，这两个数量不一定相同。
