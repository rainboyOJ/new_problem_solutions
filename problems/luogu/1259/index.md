---
oj: "luogu"
problem_id: "P1259"
title: "黑白棋子的移动"
description: "按样例规律递归把规模 n 的局面缩成 n-1，直到 n=4 后输出固定收尾序列。"
difficulty: "普及-"
date: 2026-07-15 22:15
toc: true
tags: ["递归", "构造", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1259
---

[[TOC]]

### 题意

有 `n` 个白子和 `n` 个黑子，末尾有两个空位。每次移动相邻两个棋子到空位，要求输出从初始状态到黑白相间状态的移动过程。

### 思路

这题不是搜索最短路，而是按固定规律构造输出。

把规模为 `depth` 的局面看成：

```text
oooo...****...-- + 已经整理好的 o*o*...
```

每一层先输出两步，把规模 `depth` 的问题缩成 `depth-1` 的问题：

```text
oooo****--tail
ooo--***o*tail
```

当规模缩到 `4` 时，剩下的收尾过程固定，直接输出 6 行。

### Python 知识

- 字符串可以直接用 `char * count` 重复。
- 把所有状态放入 `states`，最后用 `"\n".join(states)` 一次输出。
- 递归函数只负责追加状态，不需要真的模拟棋子数组。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`

### 代码

@include-code(./main.py, python)

### Pythonic 写法

精简写法：

@include-code(./main-pythonic.py, python)

### 复杂度

输出行数为 $O(n)$，每行长度为 $O(n)$，总输出规模为 $O(n^2)$。额外空间为保存输出状态的 $O(n^2)$。

### 总结

构造输出题要先观察样例规律。这里的核心是每轮把大规模局面缩小一层，最后用固定的 `n=4` 收尾。
