---
oj: "luogu"
problem_id: "P1000"
title: "超级玛丽游戏"
description: "用三引号多行字符串保存字符画，并原样输出。"
difficulty: "入门"
date: 2026-07-15 17:50
toc: true
tags: ["python", "入门", "字符串", "输出"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1000
---

[[TOC]]

### 题意

题目没有输入，要求输出一整块固定的超级玛丽字符画。每一行的空格、`#`、`.`、`*`、`-` 都属于答案的一部分。

### 思路

这题不是算法题，核心是学习“按题目格式精确输出”。如果一行一行 `print`，很容易漏掉前导空格；更稳的做法是把整块字符画放进三引号字符串中，再一次性输出。

`brute.py` 不适合这题，因为不存在需要枚举或优化的算法过程。验证重点是最终输出是否和标准输出完全一致。

### Python 知识

- 三引号字符串 `"""..."""` 可以保存多行文本，适合固定字符画。
- 字符串里的前导空格会被保留，所以代码中字符画每行的缩进不能随便调整。
- `sys.stdout.write(scene)` 直接输出字符串，不会额外添加换行；字符串本身最后已经包含换行。

对应的本地 Python 笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字符串切片、输出和常用字符串操作。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：按题面选择输入输出方式。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

精简写法：

@include-code(./main-pythonic.py, python)

### 复杂度

字符画长度是固定的，时间复杂度和空间复杂度都可以看成 $O(1)$。

### 总结

固定输出题训练的是格式意识：不要输出提示语，不要改动题目要求的空格和换行。Python 中三引号字符串很适合保存这种固定的多行答案。
