---
oj: "luogu"
problem_id: "P1205"
title: "[USACO1.2] 方块转换 Transformations"
description: "实现矩阵顺时针旋转和水平反射，按题目编号顺序逐一比较目标图案。"
difficulty: "普及-"
date: 2026-07-15 18:58
toc: true
tags: ["模拟", "矩阵", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1205
---

[[TOC]]

### 题意

给出变换前后的 `n * n` 字符方阵，判断它们属于哪一种变换：旋转 `90/180/270` 度、水平反射、反射后再旋转、不变，或无效。若多种都满足，输出编号最小的。

### 思路

把矩阵保存为字符串列表。先写两个函数：

- `rotate(pattern)`：顺时针旋转 `90` 度；
- `reflect(pattern)`：水平反射，也就是每一行反转。

然后按题目编号顺序比较：

1. `rotate(before)`
2. 旋转两次
3. 旋转三次
4. `reflect(before)`
5. 反射后再旋转一次、两次、三次
6. 原图不变
7. 以上都不是

因为按编号顺序判断，第一种匹配就是最小编号答案。

这题是矩阵变换模拟，正解已经枚举所有题面情况，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：字符矩阵可直接保存为字符串列表。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串切片 `row[::-1]` 可以反转一行。
- `rotate` 中用列表推导式生成旋转后的每一行。
- 字符串列表可以直接用 `==` 判断整个矩阵是否相同。

### 代码

@include-code(./main.py, python)

### 复杂度

每次矩阵变换需要 $O(n^2)$，总共常数次变换，时间复杂度是 $O(n^2)$，空间复杂度是 $O(n^2)$。

### 总结

矩阵变换题先把基础操作写成函数，再按题目编号顺序组合比较。这样既不漏情况，也能自然满足“输出最小编号”的要求。
