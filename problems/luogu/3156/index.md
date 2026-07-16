---
oj: "luogu"
problem_id: "P3156"
title: "【深基15.例1】询问学号"
description: "保存按入场顺序排列的学号列表，把每个一号起始询问转换成 Python 列表下标。"
difficulty: "入门"
date: 2026-07-16 18:10
toc: true
tags: ["列表", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3156
---

[[TOC]]

### 题意

按进教室顺序给出 `n` 个学号。每次询问第 `i` 个进入的学生学号，逐行输出答案。

### 思路

顺序固定且只查询位置，直接把学号保存到列表。题目编号从 `1` 开始，Python 列表下标从 `0` 开始，因此查询 `position` 的答案是 `student_ids[position-1]`。

### Python 知识

- 列表支持 $O(1)$ 随机下标访问，相当于 C++ `vector`。
- `str(student_ids[position-1]) for position in queries` 用生成器产生多行答案。
- `"\n".join(...)` 比十万次单独 `print` 更适合批量输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：大量整数 token 与多行输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：一次性答案生成器。

### 代码

@include-code(./main.py, python)

### 复杂度

读入为 $O(n+m)$，每个查询 $O(1)$；保存数据和答案需要 $O(n+m)$ 空间。

### 总结

先辨认操作需求：只有按位置查询时，连续列表就是最简单、最高效的数据结构。
