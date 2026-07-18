---
oj: "luogu"
problem_id: "P1918"
title: "保龄球"
description: "用字典把互不相同的瓶子数映射到原位置，使每次询问直接查表。"
difficulty: "入门"
date: 2026-06-18 19:27
toc: true
tags: ["哈希", "字典", "查询", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1918
---

[[TOC]]

### 题意

第 `i` 个位置有 `a[i]` 个瓶子，所有 `a[i]` 互不相同。每次询问一个瓶子数，输出对应位置，不存在则输出 `0`。

### 思路

瓶子数互不相同，所以一个瓶子数最多对应一个位置。预处理映射：

```text
瓶子数 -> 位置
```

之后每次询问直接查字典；`position.get(count,0)` 在键不存在时返回题目要求的 `0`。

也可以排序后二分，但 Python 字典更贴合“由唯一值查原位置”的模型，预处理和询问的期望复杂度都更低，代码也更短。

### Python 知识

- `{count: i for i,count in enumerate(values,1)}` 用字典推导式建立反向索引。
- `enumerate(sequence,1)` 让位置直接从题目的 `1` 开始。
- `dict.get(key,default)` 适合“查询不到时输出固定默认值”。
- 生成器表达式逐个生成答案字符串，再交给 `join` 连接，不额外建立答案整数列表。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：字典反向索引与 `get`。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：生成器配合 `join`。

### 代码

@include-code(./main.py, python)

### Pythonic 写法

sys.stdin 快读：

@include-code(./main-pythonic.py, python)

### 复杂度

预处理 `n` 个位置需要期望 $O(n)$ 时间，每次询问期望 $O(1)$；总时间复杂度为期望 $O(n+Q)$，空间复杂度 $O(n)$。

### 总结

当题目保证值唯一，并反复要求“由值找位置”时，建立值到位置的反向字典是最直接的 Python 写法。
