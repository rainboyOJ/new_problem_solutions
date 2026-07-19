---
oj: "luogu"
problem_id: "P3799"
title: "小 Y 拼木棒"
description: "统计每种长度数量，预处理两根短棒能拼出的长度，再为两条单棒边选择两根等长木棒。"
difficulty: "普及-"
date: 2026-07-15 21:50
toc: true
tags: ["组合计数", "枚举", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P3799
---

[[TOC]]

### 题意

从 `n` 根木棒中选 `4` 根，拼成一个正三角形。问有多少种选法，答案对 $10^9+7$ 取模。

### 思路

4 根木棒拼成 3 条相等的边，必然有一条边由两根木棒拼成，另外两条边各用一根木棒。

设正三角形边长为 `side`：

- 需要选两根长度为 `side` 的木棒，作为两条单独的边；
- 再选两根长度之和为 `side` 的木棒，拼成第三条边。

先统计每个长度出现次数 `count[length]`。

再预处理：

```text
pair_sum[s] = 有多少种选两根木棒，使长度和为 s
```

最后枚举 `side`：

```text
C(count[side], 2) * pair_sum[side]
```

累加即可。

### Python 知识

- 用列表 `count = [0] * 5001` 做频率表，比字典更适合长度上限明确的题。
- `x * (x - 1) // 2` 是组合数 `C(x, 2)`。
- Python 整数不会溢出，但答案仍要按题目要求取模。

参考笔记：

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`

### 代码

@include-code(./main.py, python)


### 复杂度

木棒长度最大为 `5000`。预处理两根木棒长度和为 $O(V^2)$，其中 `V=5000`，统计答案为 $O(V)$。空间复杂度为 $O(V)$。

### 总结

关键是看出 4 根木棒拼正三角形时，结构只能是“两根整边 + 两根拼成一边”。
