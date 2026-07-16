---
oj: "luogu"
problem_id: "P1032"
title: "[NOIP 2002 提高组] 字串变换（疑似错题）"
description: "把字符串作为 BFS 状态，枚举每条规则的所有出现位置，求十步内到目标串的最少变换数。"
difficulty: "普及+/提高"
date: 2026-07-16 18:01
toc: true
tags: ["BFS", "字符串", "最短路", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1032
---

[[TOC]]

### 题意

给定起始串、目标串和若干替换规则。一次操作可把当前串中某次出现的左串替换为右串，求十步以内的最少操作数，否则输出 `NO ANSWER!`。

### 思路

把每个字符串看成图上的状态，一次合法替换是一条权值为一的边。要求最少变换次数，因此从起始串 BFS。

对每条规则，用 `str.find(old,start)` 循环寻找所有出现位置，包括可能重叠的出现；字符串切片构造替换后的新状态。集合 `visited` 保证同一字符串只入队一次。深度达到十步后不再扩展。

### Python 知识

- 字符串不可变，`current[:pos]+new+current[pos+len(old):]` 会安全生成新状态。
- 字符串本身可哈希，可以直接放进 `set` 判重。
- `sys.stdin.read().splitlines()` 适合读取“首行固定、后续规则直到 EOF”的格式。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：整行字符串与 EOF 输入。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/bfs_shortest.md`：字符串状态图 BFS。

### 代码

@include-code(./main.py, python)

### 复杂度

状态数量最坏呈指数增长；设十步内实际访问 `V` 个字符串，每个状态枚举规则和出现位置的代价为 `T`，总时间为 $O(VT)$，空间为 $O(V)$。

### 总结

字符串变换的关键是把“当前完整字符串”作为状态。BFS 保证第一次到达目标就是最少步数，十步限制控制搜索深度。
