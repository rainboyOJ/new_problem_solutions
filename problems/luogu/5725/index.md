---
oj: "luogu"
problem_id: "P5725"
title: "【深基4.习8】求三角形"
description: "按行生成两位宽度的编号字符串，先输出 n 行正方形，再右对齐输出三角形。"
difficulty: "入门"
date: 2026-07-15 18:39
toc: true
tags: ["模拟", "循环", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5725
---

[[TOC]]

### 题意

输入 `n`，先输出一个 `n * n` 的数字正方形，再输出一个右对齐的数字三角形。每个数字都要占两位，不足两位时补前导零。

两个图形之间有一个空行。

### 思路

正方形部分最直接：从 `1` 开始，每行输出 `n` 个数，一共输出 `n` 行。

三角形部分第 `row` 行输出 `row` 个数字，并在前面补空格让它右对齐。因为每个数字占两位，所以少一个数字位置就要补两个空格：

```text
"  " * (n - row)
```

每个数字使用 `f"{value:02d}"` 格式化成两位，例如 `1` 变成 `01`。

这题主要训练循环和格式化输出，`brute.py` 只会重复同样的打印过程，因此不创建额外暴力文件。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：本题用字符串列表收集一行内容，再 `"".join(line)` 输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：单个整数输入使用 `int(input())`。
- `f"{value:02d}"` 表示按整数输出，宽度为 `2`，不足时左侧补 `0`。
- `"  " * k` 可以得到重复 `k` 次的空格块。

### 代码

@include-code(./main.py, python)

### 复杂度

正方形输出 `n^2` 个数，三角形输出约 `n(n+1)/2` 个数，时间复杂度是 $O(n^2)$。除当前行字符串外，额外空间复杂度是 $O(n)$。

### 总结

这题不是算法难题，重点是格式：两位数字、行内不加额外分隔符、三角形按两位宽度右对齐。
