---
oj: "luogu"
problem_id: "P1044"
title: "[NOIP 2003 普及组] 栈"
description: "把操作过程抽象成还未入栈数量和当前栈大小，用记忆化搜索统计合法 push/pop 序列。"
difficulty: "普及+/提高"
date: 2026-06-20 08:48
toc: true
tags: ["动态规划", "记忆化搜索", "栈", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1044
---

[[TOC]]

### 题意

给定固定入栈顺序 `1..n`，每次可以把下一个数入栈，也可以把栈顶元素弹出到输出序列。问可能得到多少种不同输出序列。

### 思路

具体栈里有哪些数并不重要。因为入栈顺序固定，后续可操作数量只由两个状态决定：

- `waiting`：还有多少个数没有入栈；
- `stack_size`：当前栈里有多少个数。

定义 `count_outputs(waiting, stack_size)` 表示从这个状态出发的方案数。

转移：

- 如果 `waiting > 0`，可以入栈：`(waiting-1, stack_size+1)`；
- 如果 `stack_size > 0`，可以出栈：`(waiting, stack_size-1)`。

当 `waiting == 0` 时，剩下只能一直出栈，方案数为 `1`。

#### 小 DP 表

以 `n=3` 为例，答案为 `f(3,0)`：

| 状态 | 方案数含义 |
|---|---|
| `f(0, k)` | 没有数可入栈，只能全部弹出，值为 `1` |
| `f(1, 0)` | 只能先入栈，再弹出，值为 `1` |
| `f(2, 0)` | 对应 `n=2` 的输出方案，值为 `2` |
| `f(3, 0)` | 对应样例 `n=3`，值为 `5` |

### Python 知识

- `@lru_cache(None)` 可以给递归函数自动加记忆化缓存。
- 递归函数的参数必须能哈希，整数参数天然适合做缓存键。
- Python 大整数可以直接保存 Catalan 数结果。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`

### 代码

@include-code(./main.py, python)

### Pythonic 写法

精简写法：

@include-code(./main-pythonic.py, python)

### 复杂度

状态数量为 $O(n^2)$，每个状态计算一次，时间复杂度 $O(n^2)$，空间复杂度 $O(n^2)$。

### 总结

栈内具体元素可以被“当前栈大小”代替，这是本题从搜索变成 DP 的关键。

### 一图流解析

保留旧图作为复盘材料。

![一图流解析](./one-page-explainer.png)
