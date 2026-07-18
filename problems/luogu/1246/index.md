---
oj: "luogu"
problem_id: "P1246"
title: "[ECNA 1995] 编码"
description: "先累计所有更短递增单词，再逐位用组合数统计当前字母之前的合法后缀数量。"
difficulty: "普及+/提高"
date: 2026-07-16 19:20
toc: true
tags: ["组合数学", "字典序", "组合数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1246
---

[[TOC]]

### 题意

合法单词长度不超过 6，字母严格递增。所有合法单词按长度优先、同长度字典序排列，求给定单词排名；非法输出 `0`。

### 思路

长度为 `l` 的递增单词等价于从 26 个字母中选 `l` 个，共 `C(26,l)` 个。先累计所有更短长度。

对当前位，枚举比给定字母小且大于前一字母的候选。若当前位置选 `candidate`，剩余 `r` 位必须从它后面的 `25-candidate` 个字母中选择，贡献 `C(25-candidate,r)`。逐位累计，最后加一得到当前单词本身。

输入先检查长度和相邻字母严格递增，否则排名为零。

### Python 知识

- `zip(letters,letters[1:])` 枚举所有相邻字母对。
- `any(left>=right for ...)` 简洁判断非法顺序。
- `math.comb` 精确计算组合数。
- 多个 `sum(generator)` 直接表达“累计更短长度”和“累计更小前缀”。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：条件检查和组合计数生成器。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符编号转换。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

生成器计数：

@include-code(./main-pythonic.py, python)

### 复杂度

单词最长 6，最多枚举 26 个候选，可视为 $O(1)$ 时间和空间。

### 总结

字典序排名的通用方法是：先数更短对象，再逐位数“当前位置更小”的合法补全数量。
