---
oj: "luogu"
problem_id: "P1469"
title: "找筷子"
description: "利用异或消去所有成对长度，并用分块整数扫描器满足千万数据和低内存限制。"
difficulty: "普及-"
date: 2026-07-16 19:20
toc: true
tags: ["位运算", "异或", "输入优化", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1469
---

[[TOC]]

### 题意

所有筷子长度除一个外都出现偶数次，找出落单长度。`n` 可超过一千万，空间限制很紧。

### 思路

异或满足 `x^x=0`、`x^0=x`，且交换、结合顺序不影响结果。把全部长度异或起来，每对相同长度互相抵消，最终只剩落单值。

不能把所有 token 读成列表。代码每次只读 1 MB 字节块，并在块之间保留尚未结束的整数状态，边解析边异或。

### Python 知识

- `answer ^= value` 是原地异或。
- `iter(lambda: stream.read(size),b"")` 持续分块读取直到 EOF。
- 生成器 `integers()` 每解析出一个数就 `yield`，不会保存全部输入。
- ASCII 数字判断使用 `48<=byte<=57`，避免创建单字符字符串。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：惰性生成数据。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：大输入的分块解析。

### 代码

@include-code(./main.py, python)

### 复杂度

每个输入字节扫描一次，时间复杂度 $O(输入长度)$；除固定读取块外只保存常数状态，额外空间 $O(1)$。

### 总结

异或把“成对消去”降为一个变量；面对千万数据，Python 实现的重点还包括不建立庞大的整数列表。
