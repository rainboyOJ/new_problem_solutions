---
oj: "luogu"
problem_id: "P5076"
title: "【深基16.例7】普通二叉树（简化版）"
description: "用有序列表配合 bisect 查询排名、前驱和后继，并用 insort 插入新值。"
difficulty: "普及-"
date: 2026-07-16 18:17
toc: true
tags: ["二分", "有序集合", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P5076
---

[[TOC]]

### 题意

维护一个无重复整数集合，支持排名、第 k 小、前驱、后继和插入，共不超过 `10^4` 次操作。

### 思路

始终保持列表升序：

- `bisect_left(x)+1` 是 `x` 的排名；
- 第 `k` 小直接访问 `numbers[k-1]`；
- `bisect_left(x)-1` 是前驱位置；
- `bisect_right(x)` 是后继位置；
- `insort` 在正确位置插入。

查询都是 $O(\log q)$，列表中间插入需要移动后缀，是 $O(q)$。本题只有 `10^4` 次操作，标准库写法足够简洁可靠；更大范围才需要平衡树。

### Python 知识

- `bisect_left/right` 分别定位左、右插入边界。
- `insort` 等价于先二分位置再 `list.insert`。
- 边界不存在时按题目输出固定哨兵值。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/sorting_and_ordering.md`：维护和使用有序序列。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/oj_input_output_cheatsheet.md`：多行操作与批量输出。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)


### 复杂度

查询 $O(\log q)$，插入最坏 $O(q)$，总时间最坏 $O(q^2)$，空间 $O(q)$。

### 总结

题目规模决定实现：`bisect` 负责边界语义，列表负责第 k 小；在一万次操作下可用更短的标准库方案。
