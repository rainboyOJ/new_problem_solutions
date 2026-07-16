---
oj: "luogu"
problem_id: "P1120"
title: "[CERC 1995] 小木棍"
description: "枚举总长度的因数作为原木长度，用降序拼组 DFS 与失败剪枝判断可行性。"
difficulty: "提高+/省选-"
date: 2026-07-16 20:10
toc: true
tags: ["DFS", "剪枝", "回溯", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1120
---

[[TOC]]

### 题意

若干短木段来自若干根等长原木，求原木最小可能长度。

### 思路

候选长度至少是最长木段，并且必须整除总长度，按从小到大枚举。对固定目标，用 DFS 依次拼满每根原木。

木段降序能更早产生冲突。搜索中跳过同层相同长度；若一根新原木的第一段失败，或某段恰好补满后仍失败，换同层其他段也不可能挽救，立即回退。

### Python 知识

- `sorted(generator, reverse=True)` 直接生成降序木段。
- `used = [False] * n` 配合闭包回溯，无需复制整个状态。
- `previous` 跳过同层重复值，是处理重复元素组合搜索的常用写法。

### 代码

@include-code(./main.py, python)

### 复杂度

最坏仍为指数级，但因数筛选、降序和三类剪枝使题目数据可通过；空间 $O(n)$。

### 总结

组合搜索的速度往往取决于失败是否足够早：先放大段、去重、识别等价失败分支缺一不可。
