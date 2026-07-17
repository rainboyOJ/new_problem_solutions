---
oj: "luogu"
problem_id: "P5728"
title: "【深基5.例5】旗鼓相当的对手"
description: "枚举所有学生对，检查三科分差都不超过 5 且总分差不超过 10。"
difficulty: "入门"
date: 2026-07-15 18:44
toc: true
tags: ["枚举", "模拟", "列表", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5728
---

[[TOC]]

### 题意

给出 `N` 名同学的语文、数学、英语成绩。若一对同学满足：

- 每一科成绩差都不超过 `5`；
- 总分差不超过 `10`；

则这对同学是“旗鼓相当的对手”。求这样的学生对数量。

### 思路

`N <= 1000`，枚举所有无序学生对 `i < j` 即可。

为了检查总分差，读入每个学生时顺手计算总分，并把四个数存成：

```text
(语文, 数学, 英语, 总分)
```

枚举一对学生时，先检查三科分差。如果有一科超过 `5`，这一对不合法。三科都满足后，再检查总分差是否不超过 `10`。

这题的正解就是按定义枚举所有学生对，不创建额外 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：多行三整数输入使用 `map(int, input().split())`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：`for i in range(n)` 与 `for j in range(i + 1, n)` 枚举无序点对。
- 元组 `(chinese, math, english, total)` 可以把一个学生的信息打包保存。
- `abs(a - b)` 计算分差的绝对值。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

用 `combinations` 枚举学生对，`all` + `zip` 检查三科分差：

@include-code(./main-pythonic.py, python)

### 复杂度

共有 $O(n^2)$ 对学生，每对检查常数个成绩，时间复杂度是 $O(n^2)$；存储学生信息需要 $O(n)$ 空间。

### 总结

这题的关键是枚举“不重复的一对学生”，也就是只枚举 `i < j`。每对学生按题面条件逐项检查即可。
