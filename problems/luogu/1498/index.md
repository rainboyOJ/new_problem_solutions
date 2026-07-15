---
oj: "luogu"
problem_id: "P1498"
title: "南蛮图腾"
description: "从最小三角形开始，每次把旧图放在上方居中和下方左右两份，迭代生成分形图案。"
difficulty: "入门"
date: 2026-07-15 22:30
toc: true
tags: ["递归", "分形", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1498
---

[[TOC]]

### 题意

给定 `n`，输出对应大小的三角分形图腾。

### 思路

从 `n=1` 的基础图形开始：

```text
 /\
/__\
```

每放大一层：

- 上半部分：旧图整体居中；
- 下半部分：左右各放一份旧图。

这样迭代到第 `n` 层即可。

### Python 知识

- 字符串可以用 `line + line` 拼接成左右两份。
- `" " * height` 用来补居中空格。
- 输出时 `rstrip()` 去掉右侧多余空格，但保留左侧缩进。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)

### 复杂度

最终图形高度为 $2^n$，宽度为 $2^{n+1}$，时间和空间复杂度都与输出规模同阶。

### 总结

字符画题最重要的是先找到“上一层如何拼成下一层”。这里就是上方居中、下方复制两份。
