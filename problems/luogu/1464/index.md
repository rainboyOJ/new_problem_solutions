---
oj: "luogu"
problem_id: "P1464"
title: "[PacNW 1999] Function"
description: "按题目分支写递归函数，并用 lru_cache 记忆化 1 到 20 范围内的重复状态。"
difficulty: "普及/提高-"
date: 2026-06-21 13:06
toc: true
tags: ["记忆化搜索", "递归", "动态规划", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1464
---

[[TOC]]

### 题意

按题目给出的分支规则定义函数 `w(a,b,c)`。输入多组 `a,b,c`，输出对应函数值，直到 `-1 -1 -1` 结束。

### 思路

直接递归会重复计算大量状态。注意题目给出两个边界：

1. 只要有一个参数 `<= 0`，答案就是 `1`；
2. 只要有一个参数 `> 20`，答案等于 `w(20,20,20)`。

因此真正需要缓存的状态只在 `1..20` 的立方体内，最多 `8000` 个。

按题目顺序写递归分支，再加记忆化即可。

#### 状态示例

| 输入 | 使用规则 | 结果 |
|---|---|---|
| `w(1,1,1)` | 普通分支 | 2 |
| `w(2,2,2)` | 普通分支，会复用小状态 | 4 |
| `w(30,-1,0)` | 先命中 `<=0` | 1 |
| `w(30,30,30)` | 压到 `w(20,20,20)` | 固定缓存值 |

### Python 知识

- `@lru_cache(None)` 是记忆化搜索的标准工具。
- 多组输出先放进 `answers`，最后 `"\n".join(answers)` 一次输出。
- 边界判断顺序必须严格照题目来写。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)


### 复杂度

有效状态最多 $20^3=8000$ 个，每个状态只计算一次。时间复杂度和空间复杂度都是 $O(20^3)$，每个询问之后基本是缓存查询。

### 总结

这题的难点不是递归式，而是避免重复计算，并且严格处理 `<=0` 与 `>20` 的边界顺序。
