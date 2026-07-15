---
oj: "luogu"
problem_id: "P5717"
title: "【深基3.习8】三角形分类"
description: "先排序边长，再用平方关系判断角类型，并按顺序追加等腰、等边分类。"
difficulty: "入门"
date: 2026-07-15 18:12
toc: true
tags: ["python", "入门", "条件判断", "排序", "几何"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5717
---

[[TOC]]

### 题意

输入三条线段长度，判断它们能否组成三角形；如果能，还要按顺序输出直角/锐角/钝角、等腰、等边等分类。

### 思路

先把三条边排序成 `a <= b <= c`。这样：

- 只需要检查 `a + b > c` 就能判断是否能组成三角形；
- 只需要比较 `a*a + b*b` 和 `c*c` 就能判断角类型。

如果不能组成三角形，直接输出 `Not triangle`。否则把符合的分类字符串按题目要求的顺序加入 `result` 列表，最后用换行连接输出。

`brute.py` 不适合这题，因为它是规则分类题，排序后按公式判断就是完整解法。

### Python 知识

- `sorted(...)` 返回升序列表，方便统一把最长边放在 `c`。
- `a, b, c = sides` 是序列解包。
- 用列表 `result.append(...)` 收集多行输出，比边判断边 `print` 更容易控制顺序。
- `"\n".join(result)` 把多个答案行连接成最终输出。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：`sorted` 的用法。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：多值输入和多行输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：输出多行答案。

### 代码

@include-code(./main.py, python)

### 复杂度

只排序 3 个数，可以看作时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

几何分类题先把变量顺序整理好。排序后最长边固定为 `c`，三角形判断和角类型判断都会简单很多。
