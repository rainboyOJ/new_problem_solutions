---
oj: "luogu"
problem_id: "P2404"
title: "自然数的拆分问题"
description: "DFS 枚举非递减加数序列，下一项从上一项开始选择，从源头去除重复拆分。"
difficulty: "普及-"
date: 2026-07-16 18:06
toc: true
tags: ["DFS", "枚举", "整数划分", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2404
---

[[TOC]]

### 题意

把自然数 `n` 拆成至少两个小于 `n` 的自然数之和。每个方案内部非递减，并按字典序输出。

### 思路

`dfs(remaining,minimum)` 表示还需凑出 `remaining`，下一项至少为 `minimum`。

当前值从 `minimum` 递增枚举，选择后把它同时作为下一层的新下界。这样每个方案天然非递减，同一组加数不会以不同顺序重复出现；递增的搜索顺序也自然产生题目要求的字典序。

剩余值为零时得到一个完整方案。根节点直接选择 `n` 会形成单项方案，用 `len(path)>1` 排除即可。

### Python 知识

- `path.append`、递归、`path.pop` 是标准回溯骨架。
- `"+".join(map(str,path))` 把整数路径格式化成加法式。
- 先把每行答案保存为字符串，最后 `print(*answers,sep="\n")` 一次输出。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：DFS 回溯和候选答案生成。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/map_reduce_filter.md`：`map(str,...)` 的一一转换。

### 代码

@include-code(./main.py, python)

### 复杂度

搜索规模与整数 `n` 的拆分数同阶，构造输出还需遍历每个方案的加数；递归深度为 $O(n)$。

### 总结

通过给下一层设置“不得小于上一项”的下界，可以在生成阶段直接保证唯一性，不需要最后再用集合去重或排序。
