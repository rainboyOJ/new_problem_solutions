---
oj: "luogu"
problem_id: "P2911"
title: "[USACO08OCT] Bovine Bones G"
description: "三重循环枚举三个骰子的所有点数组合，统计每个和出现次数并取最小众数。"
difficulty: "入门"
date: 2026-07-15 18:54
toc: true
tags: ["枚举", "计数", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2911
---

[[TOC]]

### 题意

有三个骰子，面数分别是 `S1`、`S2`、`S3`。每个骰子点数从 `1` 到自己的面数。问所有投掷组合中，哪个点数和出现次数最多；若有多个，输出最小的那个和。

### 思路

三个骰子的范围都很小，可以直接三重循环枚举所有组合：

```text
a = 1..S1
b = 1..S2
c = 1..S3
```

每次把 `a + b + c` 的出现次数加一。

统计结束后，从小到大扫描所有可能的和，只在 `times > best_count` 时更新答案。因为扫描顺序从小到大，次数相同的时候不更新，就会保留最小的和。

这题是枚举和计数练习，不创建额外 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：用 `s1, s2, s3 = map(int, input().split())` 读取三个整数。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/brute_force_validation.md`：多层 `range` 循环可以直接枚举所有组合。
- `count[sum_value] += 1` 是用列表做频率统计。
- `enumerate(count)` 可以同时获得下标和次数。

### 代码

@include-code(./main.py, python)

### 复杂度

枚举组合数为 `S1*S2*S3`，在本题范围内很小。时间复杂度是 $O(S1S2S3)$，空间复杂度是 $O(S1+S2+S3)$。

### 总结

这题不用推概率公式。把所有组合枚举出来并计数，最后按从小到大的顺序找最大次数即可。
