---
oj: "luogu"
problem_id: "P1102"
title: "A-B 数对"
description: "用 Counter 统计每个数的出现次数，按 cnt[x]×cnt[x+C] 累加位置数对。"
difficulty: "普及-"
date: 2026-07-16 17:50
toc: true
tags: ["计数", "哈希", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P1102
---

[[TOC]]

### 题意

统计有多少对不同位置上的数满足 $A-B=C$。相同数值出现在不同位置时，要分别计数。

### 思路

把等式改写为 $A=B+C$。若数值 `B` 出现 `cnt[B]` 次，数值 `B+C` 出现 `cnt[B+C]` 次，它们能组成的有序位置数对就是两者乘积。

因此只需统计频率，再对每种 `B` 累加：

$$
\operatorname{cnt}[B]\times\operatorname{cnt}[B+C]
$$

`C` 为正数，所以一对数值只会按较小值 `B` 统计一次。

### Python 知识

- `collections.Counter` 直接把序列变成“数值到出现次数”的映射。
- 访问不存在的键时，`Counter[key]` 返回 `0`，无需单独判断 `B+C` 是否出现。
- `sum(...)` 配合生成器完成乘积聚合，不创建中间列表。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/collections_toolkit.md`：`Counter` 的频率统计模式。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/generator_expression.md`：生成器与 `sum` 的惰性聚合。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

另一种写法：排序后用二分查找统计每个 `B` 对应的 `B+C` 出现次数。

@include-code(./main-bs.cpp, cpp)

### 复杂度

统计和遍历不同数值的期望时间复杂度为 $O(n)$，空间复杂度为 $O(n)$。

### 总结

题目强调“不同位置”，所以不能只判断数值是否存在。频率乘积恰好把两边所有位置组合完整计入答案。
