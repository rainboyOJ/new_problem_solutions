---
oj: "luogu"
problem_id: "P5732"
title: "【深基5.习7】杨辉三角"
description: "逐行构造杨辉三角，边界为 1，中间元素等于上一行相邻两个数之和。"
difficulty: "入门"
date: 2026-07-15 18:58
toc: true
tags: ["模拟", "矩阵", "递推", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5732
---

[[TOC]]

### 题意

输入 `n`，输出杨辉三角前 `n` 行。

### 思路

杨辉三角每一行两端都是 `1`。中间位置由上一行相邻两个数相加得到：

```text
current[col] = previous[col - 1] + previous[col]
```

因此可以从第 `0` 行开始逐行构造。每次先创建长度为 `row + 1`、全是 `1` 的列表，再填中间位置。

这题是二维列表和递推入门，正解已经直接对应定义，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：使用 `int(input())` 读取单个整数，使用 `print(*row)` 输出一行数字。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：多行输出可以逐行 `print`。
- `current = [1] * (row + 1)` 创建当前行。
- `range(1, row)` 只枚举当前行的中间位置。

### 代码

@include-code(./main.py, python)

### 复杂度

一共输出约 `n^2/2` 个数字，时间复杂度是 $O(n^2)$，保存三角形需要 $O(n^2)$ 空间。

### 总结

杨辉三角的关键是“边界为 1，中间来自上一行”。逐行构造最适合入门学习。
