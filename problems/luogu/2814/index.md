---
oj: "luogu"
problem_id: "P2814"
title: "家谱"
description: "用姓名字典记录直接父亲，沿父链查找最早祖先并进行路径压缩。"
difficulty: "普及-"
date: 2026-07-16 18:26
toc: true
tags: ["并查集", "字典", "字符串", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2814
---

[[TOC]]

### 题意

输入按行描述家谱：`#name` 切换当前父亲，随后的 `+child` 表示这个孩子的父亲是当前父亲；`?name` 查询此人的最早祖先，`$` 结束。

### 思路

用字典 `parent[name]` 记录每个人的直接父亲。没有更早祖先的人令 `parent[name]=name`。

查询时沿着父亲指针一直走到 `parent[name]==name`，该名字就是最早祖先。把途中人物都直接指向这个祖先，即路径压缩，后续查询会更快。

处理 `#name` 时只能使用 `setdefault`：一个人可能此前作为 `+child` 已经记录了父亲，后来又成为另一组父子关系的父亲，不能把他错误重置为自己的根。样例中的 `Gareth` 就属于这种情况。

### Python 知识

- Python 字典可以直接用姓名字符串或 `bytes` 作键，不需要先给每个名字编号。
- `setdefault(name,name)` 只在姓名首次出现时初始化，不覆盖已有父子关系。
- `line[:1]` 取操作符，`line[1:].strip()` 取姓名，适合解析这种无空格的命令行。
- 用 `path` 列表记录查询途中的人物，再统一路径压缩，避免递归。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：逐行读取和字符串切片。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：字典映射模式。

### 代码

@include-code(./main.py, python)


### 复杂度

设关系与查询总数为 `q`。路径压缩后总时间接近 $O(q\alpha(q))$，字典和父链占用 $O(q)$ 空间。

### 总结

这题的父子关系天然就是“姓名指向父亲”的映射。`setdefault` 保留旧父亲信息、路径压缩加速重复查询，是 Python 实现中最值得注意的两点。
