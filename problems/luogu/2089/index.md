---
oj: "luogu"
problem_id: "P2089"
title: "烤鸡"
description: "用 itertools.product 枚举 10 种配料各取 1 到 3 的所有状态，筛出总和等于 n 的方案。"
difficulty: "入门"
date: 2026-07-15 21:30
toc: true
tags: ["枚举", "DFS", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2089
---

[[TOC]]

### 题意

有 `10` 种配料，每种配料可以放 `1,2,3` 克。给定总美味程度 `n`，输出所有总和等于 `n` 的方案，按字典序排列。

### 思路

每个位置都有 `1,2,3` 三种选择，一共是：

```text
3^10 = 59049
```

种方案，可以直接枚举。

Python 的 `itertools.product(range(1, 4), repeat=10)` 正好表示“10 个位置，每个位置从 1 到 3 中选一个”。`product` 产生的顺序就是字典序，因此筛选后直接输出即可。

### Python 知识

- `product(range(1, 4), repeat=10)` 可以代替 10 层循环。
- `sum(plan)` 直接计算一个方案的总质量。
- `print(*plan)` 把元组拆开，用空格分隔输出。
- 这里需要先保存全部合法方案，因为第一行要输出方案总数。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/itertools_recipes.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`

### 代码

@include-code(./main.py, python)


### 复杂度

总共枚举 $3^{10}$ 个方案。每个方案求和需要 $O(10)$，所以时间复杂度为 $O(10 \cdot 3^{10})$。空间复杂度为合法方案数量。

### 总结

当每个位置都有固定候选值时，`product` 是非常适合 Python 初学者模仿的枚举工具。
