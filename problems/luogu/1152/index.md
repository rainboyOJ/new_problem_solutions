---
oj: "luogu"
problem_id: "P1152"
title: "欢乐的跳"
description: "逐个计算相邻差值，用集合判重并检查差值是否落在 1 到 n-1。"
difficulty: "入门"
date: 2026-06-18 23:50
toc: true
tags: ["模拟", "集合", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1152
---

[[TOC]]

### 题意

给定一个长度为 `n` 的整数序列。如果相邻元素差的绝对值恰好包含 `1,2,...,n-1`，就称它为 `Jolly`。

判断输入序列是否满足这个条件。

### 思路

把所有相邻差值看成要收集的数字。

对每一对相邻元素计算：

```text
diff = abs(a[i + 1] - a[i])
```

合法的 `diff` 必须满足两个条件：

1. 在 `1..n-1` 之间；
2. 没有出现过。

如果某个差值越界或重复，就一定不是 `Jolly`。如果所有相邻差值都通过检查，因为一共有 `n-1` 个差值，它们就正好组成 `1..n-1` 的一个排列。

### Python 知识

- `abs(x)` 直接计算绝对值。
- `set()` 用来记录已经出现过的差值，`diff in seen` 是判重。
- `print("Jolly" if ok else "Not jolly")` 是条件表达式，适合二选一输出。
- 本题输入换行位置不重要，可以用 `sys.stdin.buffer.read()` 按 token 读取。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`

### 代码

@include-code(./main.py, python)

### 复杂度

时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

这题的关键不是排序，而是把条件拆成“范围合法”和“没有重复”两个检查。
