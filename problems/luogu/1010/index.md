---
oj: "luogu"
problem_id: "P1010"
title: "[NOIP 1998 普及组] 幂次方"
description: "按二进制位从高到低拆分整数，对大于 1 的指数递归生成 0,2 表示。"
difficulty: "普及-"
date: 2026-07-07 14:55
toc: true
tags: ["递归", "二进制", "模拟", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1010
---

[[TOC]]

### 题意

把正整数写成若干个 `2` 的幂之和，并按题目规定输出：

- `2^0` 写成 `2(0)`；
- `2^1` 写成 `2`；
- `2^k (k > 1)` 写成 `2(k 的同类表示)`。

### 思路

任意正整数都可以按二进制拆成若干个 `2^exponent`。

从高位到低位扫描每个为 `1` 的二进制位：

- 指数为 `0`：输出 `2(0)`；
- 指数为 `1`：输出 `2`；
- 指数大于 `1`：输出 `2(express(exponent))`。

所有片段用 `+` 连接。

### Python 知识

- `1 << power` 表示 `2^power`。
- `number >> exponent & 1` 判断某个二进制位是否为 `1`。
- 递归函数 `express(number)` 返回字符串，外层只负责 `print`。
- 先把片段放进 `parts`，最后 `"+".join(parts)`，避免处理最后一个加号。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)

### 复杂度

`n <= 20000`，二进制位数很小。时间复杂度约为 $O(\log n \log\log n)$，空间复杂度为递归深度 $O(\log n)$。

### 总结

这题的核心是把数字的二进制分解和题目的递归输出规则对齐。用列表收集片段可以让输出格式更稳。
