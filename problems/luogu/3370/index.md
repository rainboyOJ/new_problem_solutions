---
oj: "luogu"
problem_id: "P3370"
title: "【模板】字符串哈希"
description: "利用 Python set 对完整字符串精确去重，集合大小就是不同字符串数量。"
difficulty: "入门"
date: 2025-12-08 17:19
toc: true
tags: ["字符串", "哈希", "集合", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3370
---

[[TOC]]

### 题意

给出 `n` 个大小写敏感的字符串，求不同字符串的个数。

### 思路

虽然题名是字符串哈希模板，但在 Python 中无需手写滚动哈希。把完整字符串放进 `set`，重复字符串只会保留一份，集合长度就是答案。

`set` 内部使用哈希表加速查找，但发生哈希冲突时还会比较对象是否真正相等，所以这里按完整字符串判等，不承担手写单哈希的碰撞风险。

输入的第一个 token 是 `n`，后面的 token 全是字符串，因此核心表达式就是 `len(set(data[1:]))`。

### Python 知识

- `set(iterable)` 从可迭代对象建立集合并自动去重。
- `len(set(...))` 是“只关心不同元素数量”时很常用的 Python 模式。
- `sys.stdin.buffer.read().split()` 返回 `bytes` 列表；字符串只需比较、不需拼接时可以保持字节串。
- Python 集合不保证题目输入顺序；本题只求数量，所以没有影响。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`set` 去重和哈希容器。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：字节输入与字符串处理。

### 代码

@include-code(./main.py, python)

### 复杂度

设所有字符串总长度为 `L`，建立集合的期望时间复杂度 $O(L)$，空间复杂度 $O(L)$。

### 总结

在 Python OJ 中，标准哈希容器通常比手写字符串哈希更短、更可靠。只有题目明确要求子串哈希等能力时，才需要实现滚动哈希。
