---
oj: "luogu"
problem_id: "P1551"
title: "亲戚"
description: "用并查集合并已知亲戚关系，查询两个人的代表元是否相同。"
difficulty: "入门"
date: 2026-07-16 18:26
toc: true
tags: ["并查集", "连通性", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1551
---

[[TOC]]

### 题意

给出 `n` 个人之间的 `m` 条亲戚关系。亲戚关系可以传递，回答 `p` 次询问：两个人是否属于同一个亲戚群体。

### 思路

把每个人看成一个集合。读到关系 `(a,b)` 时合并两人的集合；询问时比较两人的代表元：

- 代表元相同，说明存在一条关系链把两人连在一起，输出 `Yes`；
- 代表元不同，输出 `No`。

代码同时使用路径压缩和按集合大小合并，使并查集操作的均摊代价接近常数。

### Python 知识

- `parent = list(range(n + 1))` 简洁地建立“每个人最初以自己为根”的数组。
- `a, b = find(a), find(b)` 用解包同时取得两个代表元。
- `"Yes" if 条件 else "No"` 适合表达二选一答案，再用列表收集后一次输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：批量读入和字符串输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/cpp_to_python_pitfalls.md`：避免深递归，使用循环版 `find`。

### 代码

@include-code(./main.py, python)

### 复杂度

共有 `m+p` 次并查集操作，时间复杂度为 $O((m+p)\alpha(n))$，空间复杂度为 $O(n)$。

### 总结

“关系可以传递，反复询问是否属于同一组”是并查集的直接使用场景。查询的关键不是保存完整关系链，而是比较最终代表元。
