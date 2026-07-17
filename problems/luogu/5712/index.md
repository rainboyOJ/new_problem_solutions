---
oj: "luogu"
problem_id: "P5712"
title: "【深基3.例4】Apples"
description: "根据数量是否为 1 选择 apple 或 apples，并用 f-string 拼出完整句子。"
difficulty: "入门"
date: 2026-07-15 18:07
toc: true
tags: ["python", "入门", "字符串", "条件判断"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5712
---

[[TOC]]

### 题意

输入吃掉的苹果数量 `x`。如果 `x == 1`，句子中使用 `apple`；否则使用复数 `apples`。输出完整句子。

### 思路

这题的关键是英文单复数。先根据 `x` 是否等于 `1` 选出单词，再把数字和单词拼进句子。

`brute.py` 不适合这题，因为它是字符串格式和条件表达式练习，没有算法枚举过程。

### Python 知识

- `word = "apple" if x == 1 else "apples"` 是条件表达式，适合二选一。
- f-string 可以把变量直接嵌入字符串：`f"...{x} {word}..."`。
- 注意句末的英文句号也是输出的一部分。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串处理和输入输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：输出一个答案和字符串。

### 代码

@include-code(./main.py, python)

### match-case 写法

按数量是否为 `1` 分支选单词，可用 `case 1` / `case _`：

@include-code(./match_case.py, python)

### 复杂度

只做一次判断和一次输出，时间复杂度 $O(1)$，空间复杂度 $O(1)$。

### 总结

格式题要把标点、空格和单词变化都当成答案的一部分。Python 的条件表达式和 f-string 很适合这种短格式输出。
