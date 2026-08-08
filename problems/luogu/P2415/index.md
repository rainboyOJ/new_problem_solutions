---
oj: "luogu"
problem_id: "P2415"
title: "集合求和"
description: "每个元素会出现在一半子集中，因此答案是元素总和乘以 2 的 n-1 次方。"
difficulty: "入门"
date: 2026-07-15 21:22
toc: true
tags: ["数学", "集合", "python"]
categories: []
pre: []
common: []
recommend: []
source: https://www.luogu.com.cn/problem/P2415
---

[[TOC]]

### 题意

给定一个集合，求所有子集中所有元素的和。

### 思路

设集合有 `n` 个元素。对任意一个元素来说，其他 `n-1` 个元素都可以选或不选，因此包含它的子集有：

```text
2^(n-1)
```

所以每个元素都会被加 `2^(n-1)` 次，答案就是：

```text
sum(numbers) * 2^(n-1)
```

这题关键是数学计数，不创建 `brute.py`。

### Python 知识

- `/home/rainboy/mycode/hugo-blog/content/program_language/python/input_output_and_strings.md`：输入没有给数量时，可以直接 `input().split()` 读取整行元素。
- `/home/rainboy/mycode/hugo-blog/content/program_language/python/math_tools.md`：Python 整数不会溢出，能直接处理本题答案范围。
- `sum(numbers)` 求列表总和。
- `2 ** k` 表示 $2^k$。

### 代码

@include-code(./main.py, python)

@include-code(./main.cpp, cpp)

### Pythonic 写法

子集和位运算：

@include-code(./main-pythonic.py, python)


### 复杂度

设元素个数为 `n`，时间复杂度是 $O(n)$，空间复杂度是 $O(n)$。

### 总结

不要枚举所有子集。换个角度统计每个元素贡献次数，就能把指数问题变成一次求和。
